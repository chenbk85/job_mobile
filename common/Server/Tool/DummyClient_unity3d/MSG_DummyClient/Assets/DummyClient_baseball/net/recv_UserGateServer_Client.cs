using UnityEngine;
using System.Collections;
using nNWM;

public class recv_UserGateServer_Client : MonoBehaviour
{
	//#--------------------------------------------------------------------------
	// Util function 
	//#--------------------------------------------------------------------------
	nProtoUG.UserGateServer_Client ToRecvData(nNWM.nDummy.NetEventArg arg) 
	{ 
		return (nProtoUG.UserGateServer_Client)arg.recvData; 
	}
	nNWM.nBaseball.NetEventPlugin_baseball ToPlugin(nNWM.nDummy.NetEventArg arg) 
	{ 
		return (nNWM.nBaseball.NetEventPlugin_baseball)arg.plugin; 
	}

	//#--------------------------------------------------------------------------
	// UserGate Server -> Client Net Receiver.
	//#--------------------------------------------------------------------------
	public void ans_ug_error(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_ans_ug_error;
		var plugin = ToPlugin(arg);

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}

	public void ug2x_client_version(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_ug2x_client_version;
		var plugin = ToPlugin(arg);

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}

	public void ug2x_echo(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_ug2x_echo;
		var plugin = ToPlugin(arg);
		//jUser user = plugin.m_User;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}


	/*
	 * 아래 탬플릿 코드를 복사하여 사용. asdf를 원하는 프로토콜이름으로 바꾸시오.
	 
	public void asdf(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_asdf;
		var plugin = ToPlugin(arg);
		//jUser user = plugin.m_User;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}
	  
	 *
	 * */
}
