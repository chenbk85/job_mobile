using System;
using System.Collections;
using System.Reflection;
using System.Text;

namespace nNWM
{
	namespace nUtil
	{
		public class jDumper
		{
			public enum EDumpType
			{
				eNOT,// 덤프하지 않음.
				eONLY_NAME, //객체이름만 출력.
				eLEVEL1, //객체의 한단계 맴버들에 대해서만 출력.
				eALL, // 객체의 모든 하위 객체 맴버들에대해서도 출력.
			}

			private int _level;
			private readonly int _indentSize;
			private readonly StringBuilder _stringBuilder;

			public static System.Collections.Generic.Dictionary<string,EDumpType> m_LogPolicy = new System.Collections.Generic.Dictionary<string,EDumpType>();

			private jDumper(int indentSize)
			{
				_indentSize = indentSize;
				_stringBuilder = new StringBuilder();
			}

			public static string NamedDump(object obj, EDumpType eType=EDumpType.eONLY_NAME)
			{
				EDumpType eCurrentType;
				string sType = obj.GetType().ToString() ;
				if( m_LogPolicy.TryGetValue(sType, out eCurrentType) ==false)
				{
					m_LogPolicy.Add(sType, eType);
					eCurrentType = eType;
				}

				switch(eCurrentType)
				{
					case EDumpType.eNOT:
						return null;
					case EDumpType.eONLY_NAME:
						return obj.ToString();
					case EDumpType.eLEVEL1:
						return Dump(obj, 1);
					case EDumpType.eALL:
						return Dump(obj, 2);
				}
				return null;
			}


			public static string Dump(object element, int indentSize)
			{
				var instance = new jDumper(indentSize);
				return instance.DumpElement(element);
			}

			private string DumpElement(object element)
			{
				if (element == null || element is ValueType || element is string)
				{
					Write(FormatValue(element));
				}
				else
				{
					var objectType = element.GetType();
					if (!typeof(IEnumerable).IsAssignableFrom(objectType))
					{
						Write("{{{0}}}", objectType.FullName);
						_level++;
					}

					var enumerableElement = element as IEnumerable;
					if (enumerableElement != null)
					{
						foreach (object item in enumerableElement)
						{
							if (item is IEnumerable && !(item is string))
							{
								_level++;
								DumpElement(item);
								_level--;
							}
							else
							{
								DumpElement(item);
							}
						}
					}
					else
					{
						MemberInfo[] members = element.GetType().GetMembers(BindingFlags.Public | BindingFlags.Instance);
						foreach (var memberInfo in members)
						{
							var fieldInfo = memberInfo as FieldInfo;
							var propertyInfo = memberInfo as PropertyInfo;

							if (fieldInfo == null && propertyInfo == null)
								continue;

							var type = fieldInfo != null ? fieldInfo.FieldType : propertyInfo.PropertyType;
							object value = fieldInfo != null
																 ? fieldInfo.GetValue(element)
																 : propertyInfo.GetValue(element, null);

							if (type.IsValueType || type == typeof(string))
							{
								Write("{0}: {1}", memberInfo.Name, FormatValue(value));
							}
							else
							{
								Write("{0}: {1}", memberInfo.Name, typeof(IEnumerable).IsAssignableFrom(type) ? "..." : "{ }");
								_level++;
								DumpElement(value);
								_level--;
							}
						}
					}

					if (!typeof(IEnumerable).IsAssignableFrom(objectType))
					{
						_level--;
					}
				}

				return _stringBuilder.ToString();
			}

			private void Write(string value, params object[] args)
			{
				var space = new string(' ', _level * _indentSize);

				if (args != null)
					value = string.Format(value, args);

				//_stringBuilder.AppendLine(space + value);
				_stringBuilder.Append(space + value + ",");
			}

			private string FormatValue(object o)
			{
				if (o == null)
					return ("null");

				if (o is DateTime)
					return (((DateTime)o).ToShortDateString());

				if (o is string)
					return string.Format("\"{0}\"", o);

				if (o is ValueType)
					return (o.ToString());

				if (o is IEnumerable)
					return ("...");

				return ("{ }");
			}
		}
	}//namespace nUtil

}//namespace nNWM
