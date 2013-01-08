#if UNITY_3_0 || UNITY_3_0_0 || UNITY_3_1 || UNITY_3_2 || UNITY_3_3 || UNITY_3_4 || UNITY_3_5 || UNITY_4_0 || UNITY_4_1 || UNITY_4_2
using UnityEngine;
using System.Collections;
using System.IO;
namespace MSG
{	
	public class UnityConsoleLogger : Logger
	{
        public override void HandleLog(string log)
        {
            Debug.Log(log);
        }
	}
}
#endif