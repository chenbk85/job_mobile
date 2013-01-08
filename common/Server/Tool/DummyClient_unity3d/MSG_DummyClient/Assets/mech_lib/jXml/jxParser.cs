
/* -------------------------------------------------------------------

 Author:
	 Cameron T. Owen
 * modify 
 *  whdnrfo@gmail.com
  
 Contact:
		cameron.t.owen at gmail dot com

 Copyright (c) 2011,	Wayward Logic, www.waywardlogic.com
												Cameron T. Owen

 All rights reserved.

 Redistribution and use in source and binary forms, with or without 
 modification, are permitted provided that the following conditions 
 are met:

		* Redistributions of source code must retain the above 
			copyright notice, this list of conditions and the 
			following disclaimer.
		* Redistributions in binary form must reproduce the above 
			copyright notice, this list of conditions and the following
			disclaimer in the documentation and/or other materials 
			provided with the distribution.
		* Neither the name of Wayward Logic nor the names of its
			contributors may be used to endorse or promote products 
			derived from this software without specific prior written 
			permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
*/

using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

using nSD = System.Diagnostics;

namespace nNWM
{

	namespace nXML
	{

		using jxAttribute = jxVar;
		using jxAttributeList = System.Collections.Generic.Dictionary<string, jxVar>;
		using jxElementList = System.Collections.Generic.List<jxElement>;

		/// XMLParser is a static class used to parse XML formmated strings into a hierarchy of jXmlElement objects.
		class jxParser
		{
			jxElement m_Root;
			jxElement m_currentElement;
			bool m_isRootFlag;
			string m_sXmlDocString;

			/// Gets the last XML string that was parsed by the parser or sets a new one for future parse calls.
			public string XmlDocString
			{
				get
				{
					return m_sXmlDocString;
				}
				set
				{
					m_sXmlDocString = value;
					m_isRootFlag = false;
				}
			}

			private bool _SkipComment(ref char c,ref int i)
			{
				c = m_sXmlDocString[i];
				char next1 = m_sXmlDocString[i + 1];
				if (next1 != '!') return false;

				char next2 = m_sXmlDocString[i + 2];
				char next3 = m_sXmlDocString[i + 3];
				if (!(next2 == '-' && next3 == '-')) return false;

				i += 3;
				for (; ; ++i)
				{
					if (m_sXmlDocString.Length < (i + 3))
					{
						throw new System.Exception("xml error");
					}

					if (m_sXmlDocString[i + 0] == '-' && m_sXmlDocString[i + 1] == '-' && m_sXmlDocString[i + 2] == '>')
					{
						i += 3;
						c = m_sXmlDocString[i];
						return true;
					}
				}
				//return false;
			}

			/// Initializes a new instance of the <see cref="XMLParser"/> class.
			/// XML formatted string to parse.
			public jxParser(string _xmlString)
			{
				this.m_sXmlDocString = _xmlString;
			}

			/// Handles XML decleration. Base implimentation does nothing.
			protected virtual void Callback_DeclarationHandler(string content)
			{
				// does nothing
			}

			/// Handles entitys like comments. Base implimentation does nothing.
			protected virtual void Callback_EntityHandler(string content)
			{
				// does nothing
			}

			/// Handles opening tags.
			protected virtual void Callback_StartElementHandler(string tagName, ref jxAttributeList attrList)
			{

				// placeholder for new element.
				jxElement newElement; // no assignment is bad form but necessary

				if (!m_isRootFlag)
				{ // need to setup root element...
					newElement = new jxElement(tagName.Trim(), null);
					m_Root = newElement;
					m_isRootFlag = true;
				}
				else
				{ // standard new element creations...
					newElement = new jxElement(tagName.Trim(), m_currentElement);
				}
				//newElement.DebugPrint();

				// Add attributes we've encounted thus far
				if (attrList.Count != 0)
				{
					newElement.m_AttrList = attrList;
				}

				// clear saved attribute list
				attrList = new jxAttributeList();

				// advance current element
				m_currentElement = newElement;

			}

			/// Handles end tags.
			protected virtual void Callback_EndElementHandler(string tagName)
			{
				if (!m_isRootFlag) return;
				if (m_Root == m_currentElement) return;
				m_currentElement = (jxElement)m_currentElement.GetParent();
			}

			/// Handles attribute name = value pairs.
			protected virtual void Callback_AttributeHandler(string name, string val, ref jxAttributeList attrList)
			{
				name.Trim();
				jxAttribute attr = new jxAttribute(EDataType.e_string);
				attr.SetDataByEDataType(name, val);
				attrList.Add(attr.GetTagName(), attr);
			}

			/// Handles text content inetween tags. Combines neighbouring text nodes where possible.
			protected virtual void Callback_TextHandler(string text)
			{
				// only if usable text and root flag set
				if (!m_isRootFlag || text.Trim().Length == 0) return;
				if (m_currentElement.IsEType(EDataType.e_string))
				{
					m_currentElement.Set_string(m_currentElement.Get_string() + text);
					return;
				}

				m_currentElement.ConvertFromString(text);
			}


			public static char ParseEntityReference(string entity)
			{

				switch (entity)
				{
					case "lt": return '<';
					case "gt": return '>';
					case "quot": return '"';
					case "apos": return '\'';
					case "amp": return '&';
				}

				return '\0'; // return unicode 0 for unknown entities

			}

			public static string GetEntityReference(char c)
			{
				switch (c)
				{
					case '<': return "&lt;";
					case '>': return "&gt;";
					case '"': return "&quot;";
					case '\'': return "&apos;";
					case '&': return "&amp;";
				}
				return c.ToString();

			}

			enum EXmlParserAttrbuteMode
			{
				eName,
				eAssignment,
				eValue
			}
			public enum EXMLTokenType
			{
				eNONE,
				eDeclaration,
				eEntityElement,
				eStartElement,
				eEndElement,
				eAttribute,
				eText,
				eEntity
			}


			// return :  
			//      string.Length==0 SUCCESS. 
			//      string.Length!=0 THEN string is error_code
			public jxElement Parse()
			{
				m_isRootFlag = false;

				string contentString = "";
				string elementName = "";
				string attributeName = "";
				string sEentitySuspendedContent = "";

				EXMLTokenType eCurr_EXMLTokenType = EXMLTokenType.eNONE;
				EXMLTokenType ePrev_EXMLTokenType = EXMLTokenType.eNONE;

				EXmlParserAttrbuteMode eEXmlParserAttrbuteMode = EXmlParserAttrbuteMode.eName;

				jxAttributeList attrList = new jxAttributeList();

				int i = 0;
				int xmlStringLength = m_sXmlDocString.Length;

				// TOKENIZE XML FORMATTED STRING
				while (i < xmlStringLength)
				{

					char c = m_sXmlDocString[i];

					switch (c)
					{

						// TAG TOKEN START
						case '<':

							if (_SkipComment(ref c,ref i))
								break;


							ePrev_EXMLTokenType = eCurr_EXMLTokenType;
							// switching token types...
							// deal with passive token handlers on active token start
							switch (ePrev_EXMLTokenType)
							{
								case EXMLTokenType.eEntity:
									Callback_EntityHandler(contentString);
									break;
								case EXMLTokenType.eText:
									Callback_TextHandler(contentString);
									break;
							}


							// What kind of tag start?
							char cnext = m_sXmlDocString[i + 1];
							switch (cnext)
							{
								case '?':
									eCurr_EXMLTokenType = EXMLTokenType.eDeclaration;
									i++;
									break;
								case '!':
									eCurr_EXMLTokenType = EXMLTokenType.eEntityElement;
									break;
								case '/':
									eCurr_EXMLTokenType = EXMLTokenType.eEndElement;
									i++;
									break;
								default: // Non specific token start, decide type based on previous token
									switch (ePrev_EXMLTokenType)
									{
										case EXMLTokenType.eDeclaration:
											eCurr_EXMLTokenType = EXMLTokenType.eDeclaration;
											break;
										case EXMLTokenType.eEntityElement:
											eCurr_EXMLTokenType = EXMLTokenType.eEntityElement;
											break;
										default:
											eCurr_EXMLTokenType = EXMLTokenType.eStartElement;
											break;
									}
									break;

							}

							// reset content string for new token
							contentString = "";

							break;

						// TAG TOKEN END
						case '>':

							// switching token types...
							ePrev_EXMLTokenType = eCurr_EXMLTokenType;

							switch (eCurr_EXMLTokenType)
							{

								case EXMLTokenType.eDeclaration:
									Callback_DeclarationHandler(contentString);
									break;
								case EXMLTokenType.eEntityElement:
									Callback_EntityHandler(contentString);
									break;
								case EXMLTokenType.eStartElement:
									Callback_StartElementHandler(contentString, ref attrList);
									// handle special case for solo tags
									char prev_char = m_sXmlDocString[i - 1];

									if (prev_char == '/')
									{
										Callback_EndElementHandler(contentString);
									}
									break;
								case EXMLTokenType.eEndElement:
									Callback_EndElementHandler(contentString);
									break;
								case EXMLTokenType.eAttribute:
									char next_char = m_sXmlDocString[i + 1];
									if (next_char != '>')
										Callback_StartElementHandler(elementName, ref attrList);

									ePrev_EXMLTokenType = EXMLTokenType.eStartElement;
									break;
							}

							// Default to text token untill we find something different...
							contentString = "";
							eCurr_EXMLTokenType = EXMLTokenType.eText;

							break;

						// WHITESPACE & ATTRIBUTE START
						case ' ':

							// This ought to remove needless whitespace but it mucks up
							// entity parsing, not sure why :( - probably don't need
							// to agressively stip whitsepace for game use though.
							/*
							int contentStringLength = contentString.Length;
							if (contentStringLength > 1) {
									if (contentString[contentStringLength - 2] == ' ')
											break; // break and ignore extra whitespace
					
							}
							*/

							switch (eCurr_EXMLTokenType)
							{
								case EXMLTokenType.eStartElement:
									ePrev_EXMLTokenType = eCurr_EXMLTokenType;
									eCurr_EXMLTokenType = EXMLTokenType.eAttribute;
									elementName = contentString;
									contentString = "";
									eEXmlParserAttrbuteMode = EXmlParserAttrbuteMode.eName;
									break;
								case EXMLTokenType.eText:
									contentString += c;
									break;
								case EXMLTokenType.eAttribute:
									if (eEXmlParserAttrbuteMode == EXmlParserAttrbuteMode.eValue)
									{
										contentString += c;
									}
									break;
							}

							break;

						// ATTRIBUTE ASSIGNMENT
						case '=':
							switch (eCurr_EXMLTokenType)
							{
								case EXMLTokenType.eAttribute:
									switch (eEXmlParserAttrbuteMode)
									{
										case EXmlParserAttrbuteMode.eName:
											attributeName = contentString.Trim();
											contentString = "";
											eEXmlParserAttrbuteMode = EXmlParserAttrbuteMode.eAssignment;
											break;
										case EXmlParserAttrbuteMode.eValue:
											contentString += c;
											break;
									}

									break;
								default:
									contentString += c;
									break;
							}

							break;

						// ATTRIBUTE VALUE
						case '"':
							switch (eCurr_EXMLTokenType)
							{
								case EXMLTokenType.eAttribute:
									switch (eEXmlParserAttrbuteMode)
									{
										// Start Value
										case EXmlParserAttrbuteMode.eAssignment:
											eEXmlParserAttrbuteMode = EXmlParserAttrbuteMode.eValue;
											break;
										// End Value
										case EXmlParserAttrbuteMode.eValue:
											Callback_AttributeHandler(attributeName, contentString, ref attrList);
											contentString = "";
											eEXmlParserAttrbuteMode = EXmlParserAttrbuteMode.eName;
											break;
									}

									break;
							}

							break;

						// ENTITY REFERENCE START
						case '&':
							ePrev_EXMLTokenType = eCurr_EXMLTokenType; // siwtch to entity mode
							eCurr_EXMLTokenType = EXMLTokenType.eEntity;
							sEentitySuspendedContent = contentString; // save current content while in entity mode
							contentString = "";  // clear content for recording entity
							break;

						// ENTITY REFERENCE END
						case ';':
							if (eCurr_EXMLTokenType == EXMLTokenType.eEntity)
							{
								eCurr_EXMLTokenType = ePrev_EXMLTokenType; // swicth back to last token mode.
								contentString = sEentitySuspendedContent + ParseEntityReference(contentString); // restore content string with parsed entity
							}
							else
							{
								contentString += c;
							}
							break;

						case '/':
							{
								// handle special case for solo tags
								char next_char = m_sXmlDocString[i + 1];
								if (next_char == '>')
								{
									Callback_StartElementHandler(elementName, ref attrList);
									Callback_EndElementHandler(elementName);
									eCurr_EXMLTokenType = EXMLTokenType.eNONE;
									i++;
								}
								break;
							}
						// DEFAULT CONTENT
						default:
							contentString += c; // jsut add it to the content string...
							break;

					}

					i++;
				}

				return m_Root;

			}

		}


	}//namespace nXML


}//namespace nNWM
