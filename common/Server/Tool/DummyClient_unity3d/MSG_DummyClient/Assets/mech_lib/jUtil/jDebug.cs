using UnityEngine;
using System.Collections;

using nSD = System.Diagnostics;

namespace nNWM
{
    public class jDebug
    {
        private static string jFUNC(int iSkipFuncLevel = 1)
        {
            nSD.StackTrace st = new nSD.StackTrace();
            nSD.StackFrame sf = st.GetFrame(iSkipFuncLevel);
            nSD.StackFrame sf_prev = st.GetFrame(iSkipFuncLevel+1);
            string prev_func = "";
            if(sf_prev!=null)
            {
                prev_func = sf_prev.GetMethod().ToString();
            }
            
            return prev_func + ">" + sf.GetMethod().ToString() +":" + sf.GetFileName() + ":"+ sf.GetFileLineNumber();
        }

        public static void jERROR(string msg, int iSkipFuncLevel=1)
        {
            Debug.LogError("<" + jFUNC(++iSkipFuncLevel) + ">" + msg);
        }
        public static void jWARN(string msg, int iSkipFuncLevel=1)
        {
            Debug.LogWarning("<" + jFUNC(++iSkipFuncLevel) + ">" + msg);
        }
        public static void jLOG(string msg, int iSkipFuncLevel=1)
        {
            iSkipFuncLevel +=1;
            Debug.Log(msg);
        }

        public static void jTHROW(bool isValid , string msg="" ,int iSkipFuncLevel =1 )
        {
            if(isValid) return;
            jWARN("jTHROW : " + msg,++iSkipFuncLevel);
            throw new System.Exception("jTHROW : " + msg);
        }

        public static void jCHECK(bool isValid , string msg="",int iSkipFuncLevel =1 )
        {
            if(isValid) return;
            jWARN("jCHECK : " + msg,++iSkipFuncLevel);
        }
        
        public static void jASSERT(bool isValid , string msg="",int iSkipFuncLevel =1 )
        {
            if(isValid) return;
            jERROR("jASSERT : " + msg,++iSkipFuncLevel);
            throw new System.Exception("jASSERT : " + msg);
        }
    }

}//namespace nNWM
