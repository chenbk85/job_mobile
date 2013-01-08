using System;
using System.Collections.Generic;
////using System.Linq;
using System.Text;
using System.IO;

namespace nEXCEL
{


    using Sys_T_Test_id_t = System.Int16;

    using int8 = Char;
    using uint16 = UInt16;
    using uint32 = UInt32;
    using uint64 = UInt64;

    using int32 = Int32;
    using int16 = Int16;
    using int64 = Int64;

    public struct DATETIME
    {
        public int test;
        public override string ToString()
        {
            return "test";
        }

    }
    namespace nUtil
    {
        public class jString_DATETIME
        {
            public static void Parse(string sDebug, string sVal, ref DATETIME o)
            {
                o.test = 1;
            }
        }
    }

    public class jItemObj1
    {
        public string s2;
        public string s;
        public int i;
        public float f;
        public List<int> aa;

        public override string ToString()
        {
            string output = s2 + ":" + s + ":" + i.ToString() +"";
            return output;
        }
    }
    namespace nUtil
    {
        class jString_jItemObj1
        {
            public static void Parse(string sDebug, string sVal, ref jItemObj1 o)
            {
                o = new jItemObj1();
                string[] token = sVal.Split(';');

                o.s2 = token[0];
                o.i = Int32.Parse(token[1]);
                o.f = float.Parse(token[2]);
            }
        }
    }


    namespace nUtil
    {

        class jCSV
        {
            public static void not_thing(object o) { }
            public static void jCHECK_null(Object o, string error1,string error2)
            {
                if (o != null) return;
                Console.WriteLine("jCHECK_null : {0} - {1}", error1, error2);
            }

            public delegate void PostParseFunc(PostParseData ppd);
            /*
            public struct PostParseData
            {
                public PostParseFunc func;
                public string sVal;
                public Object o;
                public string sDebug;
            }
            public static List<PostParseData> m_PostParseList = new List<PostParseData>{};
            public static void PostParse()
            {
                foreach (PostParseData ppd in m_PostParseList)
                {
                    Object o = ppd.o;
                    ppd.func(ppd);
                }
            }
             * */
            public struct PostParseData
            {
                public PostParseFunc func;
                public string[] token;
                public int idx;
                public Object o;
                public string sDebug;
            }
            public static Dictionary<Object, PostParseData> m_PostParseList = new Dictionary<Object, PostParseData> { };

            public static void PostParse()
            {
                foreach (KeyValuePair<Object,PostParseData> ppd in m_PostParseList)
                {
                    ppd.Value.func(ppd.Value);
                }
            }

        }
        //public static void FromString<T>(string sVal, ref T eVal) { eVal = (T)Enum.Parse(typeof(T), sVal ); }

        class jString_bool
        {
            public static void Parse(string sDebug, string sVal, ref bool v) 
            {
                if (sVal == "1") 
                    v = true;
                else if (sVal == "0") 
                    v = false;
                else
                    v = bool.Parse(sVal); 
            }
            public static void Parse(string sDebug, string sVal, ref List<bool> v) 
            {
                if (v.Count != 0) return;
                foreach (string s in sVal.Split(';')) { if (s.Length != 0) v.Add(bool.Parse(s)); } 
            }
            public static string ToString(List<bool> v) { string output = ""; foreach (bool i in v) { output += (i.ToString() + ";"); } return output; }
        }

        
        class jString_Int64
        {
            public static void Parse(string sDebug, string sVal, ref Int64 v) { v = Int64.Parse(sVal); }
            public static void Parse(string sDebug, string sVal, ref List<Int64> v) 
            {
                if (v.Count != 0) return;
                foreach (string s in sVal.Split(';')) { if (s.Length != 0) v.Add(Int64.Parse(s)); } 
            }
            public static string ToString(List<Int64> v) { string output = ""; foreach (Int64 i in v) { output += (i.ToString() + ";"); } return output; }
        }
        class jString_Int32
        {
            public static void Parse(string sDebug,string sVal, ref Int32 v) { v = Int32.Parse(sVal); }
            public static void Parse(string sDebug,string sVal, ref List<Int32> v) 
            {
                if (v.Count!= 0) return;
                foreach (string s in sVal.Split(';')) { if (s.Length != 0) v.Add(Int32.Parse(s)); }
            }
            public static string ToString(List<Int32> v) { string output = ""; foreach (Int32 i in v) { output += (i.ToString() + ";"); }  return output; }
        }
        class jString_Int16
        {
            public static void Parse(string sDebug,string sVal, ref Int16 v) { v = Int16.Parse(sVal); }
            public static void Parse(string sDebug,string sVal, ref List<Int16> v) 
            {
                if (v.Count!= 0)return; 
                foreach (string s in sVal.Split(';')) { if(s.Length!=0) v.Add(Int16.Parse(s)); } 
            }
            public static string ToString(List<Int16> v) { string output = ""; foreach (Int16 i in v) { output += (i.ToString() + ";"); }  return output; }
        }
        class jString_byte
        {
            public static void Parse(string sDebug,string sVal, ref byte v) { v = byte.Parse(sVal); }
            public static void Parse(string sDebug,string sVal, ref List<byte> v) 
            {
                if (v.Count!= 0) return; 
                foreach (string s in sVal.Split(';')) { if(s.Length!=0) v.Add(byte.Parse(s)); } 
            }
            public static string ToString(List<byte> v) { string output = ""; foreach (byte i in v) { output += (i.ToString() + ";"); }  return output; }
        }
        class jString_UInt64
        {
            public static void Parse(string sDebug,string sVal, ref UInt64 v) { v = UInt64.Parse(sVal); }
            public static void Parse(string sDebug,string sVal, ref List<UInt64> v) 
            {
                if (v.Count!= 0)return; 
                foreach (string s in sVal.Split(';')) { if(s.Length!=0) v.Add(UInt64.Parse(s)); } 
            }
            public static string ToString(List<Int64> v) { string output = ""; foreach (Int64 i in v) { output += (i.ToString() + ";"); }  return output; }
        }
        class jString_UInt32
        {
            public static void Parse(string sDebug,string sVal, ref UInt32 v) { v = UInt32.Parse(sVal); }
            public static void Parse(string sDebug,string sVal, ref List<UInt32> v) 
            {
                if (v.Count!= 0)return;
                foreach (string s in sVal.Split(';')) { if(s.Length!=0) v.Add(UInt32.Parse(s)); }
            }
            public static string ToString(List<UInt32> v) { string output = ""; foreach (UInt32 i in v) { output += (i.ToString() + ";"); }  return output; }
        }
        class jString_UInt16
        {
            public static void Parse(string sDebug,string sVal, ref UInt16 v) { v = UInt16.Parse(sVal); }
            public static void Parse(string sDebug,string sVal, ref List<UInt16> v) 
            {
                if (v.Count!= 0)return;
                foreach (string s in sVal.Split(';')) { if(s.Length!=0) v.Add(UInt16.Parse(s)); } 
            }
            public static string ToString(List<Int64> v) { string output = ""; foreach (Int64 i in v) { output += (i.ToString() + ";"); }  return output; }
        }
        class jString_Char
        {
            public static void Parse(string sDebug,string sVal, ref char v) { v = char.Parse(sVal); }
            public static void Parse(string sDebug,string sVal, ref List<char> v) 
            {
                if (v.Count!= 0)return;
                foreach (string s in sVal.Split(';')) { if(s.Length!=0) v.Add(char.Parse(s)); } 
            }
            public static string ToString(List<char> v) { string output = ""; foreach (char i in v) { output += (i.ToString() + ";"); }  return output; }
        }
        class jString_string
        {
            public static void Parse(string sDebug,string sVal, ref String v) { v = sVal; }
            public static void Parse(string sDebug,string sVal, ref List<string> v) 
            {
                if (v.Count!= 0)return;
                foreach (string s in sVal.Split(';')) { if(s.Length!=0) v.Add(s); } }
            public static string ToString(List<string> v) { string output = ""; foreach (string i in v) { output += (i + ";"); }  return output; }
        }
        class jString_float
        {
            public static void Parse(string sDebug,string sVal, ref float v) { v = float.Parse(sVal); }
            public static void Parse(string sDebug,string sVal, ref List<float> v) 
            {
                if (v.Count!= 0)return;
                foreach (string s in sVal.Split(';')) { if(s.Length!=0) v.Add(float.Parse(s)); } 
            }
            public static string ToString(List<float> v) { string output = ""; foreach (float i in v) { output += (i.ToString() + ";"); }  return output; }
        }

    }//namespace nUtil

}//namespace nEXCEL
