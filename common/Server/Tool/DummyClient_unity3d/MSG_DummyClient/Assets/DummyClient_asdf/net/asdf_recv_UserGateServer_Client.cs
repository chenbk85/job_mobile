using UnityEngine;
using System.Collections;
using nNWM;

public class asdf_recv_UserGateServer_Client : MonoBehaviour
{
	//#--------------------------------------------------------------------------
	// Util function 
	//#--------------------------------------------------------------------------
	nProtoUGasdf.UserGateServer_Client ToRecvData(nNWM.nDummy.NetEventArg arg) 
	{ 
		return (nProtoUGasdf.UserGateServer_Client)arg.recvData; 
	}
	nNWM.nASDF.NetEventPlugin_asdf ToPlugin(nNWM.nDummy.NetEventArg arg) 
	{ 
		return (nNWM.nASDF.NetEventPlugin_asdf)arg.plugin; 
	}
	//#--------------------------------------------------------------------------
	// UserGate Server -> Client Net Receiver.
	//#--------------------------------------------------------------------------
	public void ug2x_echo(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_ug2x_echo;
		var plugin = ToPlugin(arg);
		//User_asdf user = plugin.m_User;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}


	/*
	 * �Ʒ� ���ø� �ڵ带 �����Ͽ� ���. asdf�� ���ϴ� ���������̸����� �ٲٽÿ�.
	 
	public void asdf(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_asdf;
		var plugin = ToPlugin(arg);
		//User_asdf user = plugin.m_User;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}
	  
	 *
	 * */
}
