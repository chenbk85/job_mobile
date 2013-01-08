using UnityEngine;
using System.Collections;
using nNWM;

public class rps_recv_UserGateServer_Client : MonoBehaviour
{
	//#--------------------------------------------------------------------------
	// Util function 
	//#--------------------------------------------------------------------------
	nProtoUGrps.UserGateServer_Client ToRecvData(nNWM.nDummy.NetEventArg arg) 
	{ 
		return (nProtoUGrps.UserGateServer_Client)arg.recvData; 
	}
	nNWM.nRPS.NetEventPlugin_rps ToPlugin(nNWM.nDummy.NetEventArg arg) 
	{ 
		return (nNWM.nRPS.NetEventPlugin_rps)arg.plugin; 
	}
	//#--------------------------------------------------------------------------
	// UserGate Server -> Client Net Receiver.
	//#--------------------------------------------------------------------------
	public void ug2x_echo(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_ug2x_echo;
		var plugin = ToPlugin(arg);
		//User_rps user = plugin.m_User;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}


	/*
	 * 아래 탬플릿 코드를 복사하여 사용. rps를 원하는 프로토콜이름으로 바꾸시오.
	 
	public void rps(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_rps;
		var plugin = ToPlugin(arg);
		//User_rps user = plugin.m_User;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}
	  
	 *
	 * */
}
