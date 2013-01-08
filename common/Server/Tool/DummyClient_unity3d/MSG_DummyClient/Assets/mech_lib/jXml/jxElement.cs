using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

using jxD = nNWM.nXML.jxDocument; // xml doc;
using jxE = nNWM.nXML.jxElement; // xml element
using jxA = nNWM.nXML.jxVar; // element attribute
using jxV = nNWM.nXML.jxVar; // attribute or element data
using string_id_t = System.Int32;



namespace nNWM
{
	namespace nXML
	{
	using jxAttribute = jxVar;
	using jxAttributeList = System.Collections.Generic.Dictionary<string, jxVar>;
	using NamedUserData_t = System.Collections.Generic.Dictionary<string, Object>;

	public delegate void for_each_jxE (jxE e);
	public delegate bool find_if_jxE (jxE e);
	public delegate void for_each_jxA (jxA e);
	public delegate bool find_if_jxA (jxA e);

	//[System.Serializable]
	public class jxElement : jxVar
	{
		//#--------------------------------------------------------------------------
		// private member.
		//#--------------------------------------------------------------------------
		private int m_iOrder;
		private int m_iChildCount;
		private jxElement m_Parent;
		private jxElement m_Prev;// big brother
		private jxElement m_Next;// under brother
		private jxElement m_Child;

		//#--------------------------------------------------------------------------
		// public member.
		//#--------------------------------------------------------------------------
		public jxAttributeList m_AttrList;

		NamedUserData_t m_NamedUserData;
		public Object m_UserData;


		//#--------------------------------------------------------------------------
		// private member function.
		//#--------------------------------------------------------------------------
		private void reorderChild()
		{
				int iCount=0;
				for(jxE e = m_Child ; e!=null ; e = e.m_Next)
				{
						e.m_iOrder=iCount++;
				}
				jDebug.jCHECK(iCount==m_iChildCount);
				m_iChildCount = iCount;
		}

		//#--------------------------------------------------------------------------
		// public member function.
		//#--------------------------------------------------------------------------
		public void SetUserData(string name , Object o)
		{
			if(m_NamedUserData==null)
				m_NamedUserData= new NamedUserData_t();

			m_NamedUserData[name] = o;
		}
		public Object GetUserData(string name)
		{
			if(m_NamedUserData.ContainsKey(name)==false) 
				return null;
			return m_NamedUserData[name];
		}

		public string_id_t GetTagID() { return base.m_string_id;}
		public jxE GetParent(){ return m_Parent;}
		public jxE GetPrev(){ return m_Prev;}
		public jxE GetNext(){ return m_Next;}
		public jxE GetChild(){ return m_Child;}
		public int GetOrder(){ return m_iOrder;}

		public jxE begin(){ return GetChild();}
		public int size(){ return m_iChildCount;}
		//~jxElement() { clear(); }
		private void clear()
		{
			if(IsEType(EDataType.e_null))
			{
				bool isOk = m_Parent==null && m_Prev==null && m_Next==null && m_Child==null && m_iChildCount==0 && m_AttrList==null;
				if(!isOk)
				{
					throw new System.Exception("ERROR : m_Parent==null && m_Prev==null && m_Next==null && m_Child==null && m_iChildCount==0 && m_AttrList==null");
				}
				return;
			}
			m_iOrder=-1;
			m_iChildCount=0;
			m_Parent=null;
			jxE ePrev = m_Prev;
			if(m_Prev!=null)
			{
				m_Prev.m_Next = m_Next;
				m_Prev =null;
			}

			if(m_Next!=null)
			{
				m_Next.m_Prev= ePrev;
				m_Next=null;
			}
			for( jxE e = m_Child ; e !=null ; e = m_Child.m_Next)
			{
				e = null;
			}
			m_AttrList = null;
			m_NamedUserData =null;
			m_UserData =null;
		}


		public jxE Find(string name, int iDepth=-1){return Find(jIndexString.GetIndex(name),iDepth);}
		public string Attr(string_id_t id){ return Attr(jIndexString.GetString(id) );}
		public jxVar AttrVar(string_id_t id){ return AttrVar(jIndexString.GetString(id) );}


		// iDepth=-1이면 모든 자식에 대해 검색.
		public jxE Find(string_id_t id , int iDepth = -1)
		{
			if(iDepth==0) return null;
			if(id==0) return null;
			for(jxE e = m_Child ; e!=null ; e = e.m_Next )
			{
					if(e.GetIndex() != id) continue;
					return e;
			}

			--iDepth;
			if(iDepth==0) return null;

			for(jxE e = m_Child ; e!=null ; e = e.m_Next )
			{
					jxE eFind = e.Find(id, iDepth);
					if(eFind==null ) continue;
					return eFind;
			}

			return null;
		}

		public string Attr(string name)
		{
				jxVar v = AttrVar(name);
				if(v==null) return null;
				jDebug.jASSERT(v.GetEType()==EDataType.e_string);
				return m_AttrList[name].Get_string();
		}
		public jxVar AttrVar(string name)
		{
				if (m_AttrList==null || ! m_AttrList.ContainsKey(name) ) 
						return null;

				return m_AttrList[name];
		}

		public jxElement (string name, jxElement parent) : base(EDataType.e_unkown)
		{
			SetTagName(name);
			m_iOrder=0;
			m_Parent = parent;
			if (parent != null) 
			{
				parent.InsertChild(this);
			}
		}

		public jxE GetChild(int iOrder) // -1이면 맨마지막 , 0이면 첫번째
		{
			int i=0;
			jxE prev= null;
			for(jxE e = m_Child ; e!=null ; e = e.m_Next, ++i)
			{
				prev =e;
				if(i==iOrder)
				{
						return e;
				}
			}
			return prev;
		}


		//depth==-1이면 모든 자식들에 대해. 1이면바로밑자식에 대해서만 수행.
		public void for_each(for_each_jxE func, int depth=-1)  
		{ 
			if(depth==0) return;

			jxE e;
			for(e = m_Child ; e!=null ; e = e.m_Next)
			{
			func(e);
			}

			if(depth-1==0) return;

			for(e = m_Child ; e!=null ; e = e.m_Next)
			{
				e.for_each(func,depth-1);
			}
		}

		//depth==-1이면 모든 자식들에 대해. 1이면바로밑자식에 대해서만 수행.
		public jxE  find_if(find_if_jxE func,int depth=-1)    
		{ 
			if(depth==0) return null;

			jxE e ;
			for(e = m_Child ; e!=null ; e = e.m_Next)
				if(func(e)==true) 
						return e; 

			if(depth-1==0) return null;

			for(e = m_Child ; e!=null ; e = e.m_Next)
			{
				jxE eFind = e.find_if(func,depth-1);
				if(eFind!=null) return eFind;
			}
			return null;
		}

		public void for_each(for_each_jxA func)  { foreach(var a in m_AttrList) func(a.Value);}
		public jxA  find_if(find_if_jxA func)    
		{ 
		foreach(var a in m_AttrList) 
		{
				if(func(a.Value)==true) 
						return a.Value; 
		}
		return null;
		}

		public void InsertChild(jxE eInsert, int iOrder=-1)// -1이면 맨마지막에 추가, 0이면 첫번째노드 다음에 추가.
		{
			eInsert.m_Parent = this;

			jxE eInsertNextPos = GetChild(iOrder);
			if(eInsertNextPos==null)
			{
					m_Child = eInsert;
					eInsert.m_Prev = eInsert.m_Next = null;
					eInsert.m_iOrder = 0;
					m_iChildCount=1;
			}
			else
			{
					++m_iChildCount;

					eInsert.m_Prev = eInsertNextPos;
					eInsert.m_Next = eInsertNextPos.m_Next;

					if(eInsertNextPos.m_Next!=null)
					{
							eInsertNextPos.m_Next.m_Prev = eInsert;
					}
					eInsertNextPos.m_Next = eInsert;

			}

			reorderChild();
		}

		public void ToDebugString2()
		{
			string s=GetTagName();
			s+=" : p=" ;
			s+= (m_Parent==null ? "NULL" : m_Parent.GetTagName());
			s+= " : L=";
			s+= (m_Prev==null ? "NULL" : m_Prev.GetTagName());
			s+= " : R=";
			s+= (m_Next==null ? "NULL" : m_Next.GetTagName());
			s+= " : C=";
			s+= (m_Child==null ? "NULL" : m_Child.GetTagName());
			jDebug.jLOG( s );

		}


		// rebuilds xml string in output, ugly little method but it works
		public void WriteToString(ref string output)
		{
			output="";
			writeToString(ref output , 0);
		}
		private void writeToString(ref string output, int tab_depth)
		{
			// tab strings for nicer formatting...
			int i = 0;
			string sTab_space = "";
			while (i < tab_depth)
			{
					sTab_space += "\t";
					i++;
			}
			bool isElement = this.GetEType() == EDataType.e_element;
			jDebug.jASSERT(GetEType() <= EDataType.e_element);
			
			// add opening tag to output
			output += sTab_space;
			output += "<" + this.GetTagNameFull();
			// add attributes to opening tag
			if(m_AttrList != null)
			{
				foreach (var a in m_AttrList)
				{
					output += (" " + a.Value.GetTagNameFull() + "=\"" + a.Value.ConvertToString() + "\" ");
					i++;
				}
			}
			//output += ("{{ " + GetTagName() + "= " + this.GetEType().ToString() + "}}");

			if(size()==0)
			{
				// if textnode add content to output return early...
				if (isElement)
				{
					output += "/>\n";
					return;
				}
				else
				{
					output += ">";
					output += Base().ConvertToString();
				}
			}
			else
			{
				jDebug.jASSERT(IsEType(EDataType.e_element));
				output += ">";
				output += ("\n");
				// recurse through all child elements
				for(jxE e = m_Child ; e!=null ; e = e.m_Next )
				{
					e.writeToString(ref output, tab_depth + 1);
				}
			}
			// close opening tag

			if (isElement)
			{
				output+= sTab_space;
			}
			output += "</" + GetTagNameFull() + ">\n";
		}

		public IEnumerator GetEnumerator()
		{
				for(jxE e = m_Child ; e!=null ; e = e.m_Next)
				{
					yield return e;
				}
		}

		public jxE FindFromParent(string name)
		{
			for(jxE e = m_Parent ; e!=null ; e = e.m_Parent)
			{
				if(e.IsTagName(name))
				{
					return e;
				}
			}
			return null;
		}

		public jxE FindByAttr(string attribute_name, string value, out jxA a )
		{
			a= AttrVar(attribute_name) ;
			if(a!=null)
			{
				if(value==null) return this;

				if( a.IsEType(EDataType.e_string) )
				{
					if( a.Get_string()== value)
					{
						return this;
					}
				}
			}
			for(jxE e = m_Child ; e!=null ; e = e.m_Next)
			{
				jxE eFind = e.FindByAttr(attribute_name,value ,out a);
				if(eFind!=null)
					return eFind;
			}
			return null;
		}

		public jxE MakeClone()
		{
		  string outString = "";
      this.WriteToString(ref outString);
			jxParser p = new jxParser(outString);
			jxE e = p.Parse();
// 			string outString1 = "";
// 			e.WriteToString(ref outString1);
			return e;
		}

		public jxE this[int i]
		{
			get
			{
				if(i < 0 || i >= size() )
				{
					return null;
				}
				return GetChild(i);
			}
		}

		public void DebugPrint()
		{
			string outString = "";
			this.WriteToString(ref outString);
			jDebug.jLOG(outString);
		}


	}//public class jxElement

	}//namespace nXML

}//namespace nNWM
