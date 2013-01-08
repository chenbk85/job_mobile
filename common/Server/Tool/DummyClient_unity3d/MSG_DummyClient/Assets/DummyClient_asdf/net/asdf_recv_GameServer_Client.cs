using UnityEngine;
using System.Collections;
using nNWM;

public class asdf_recv_GameServer_Client : MonoBehaviour 
{
	//#--------------------------------------------------------------------------
	// Util function 
	//#--------------------------------------------------------------------------
	nProtoGSasdf.GameServer_Client ToRecvData(nNWM.nDummy.NetEventArg arg)
	{
		return (nProtoGSasdf.GameServer_Client)arg.recvData;
	}
	nNWM.nASDF.NetEventPlugin_asdf ToPlugin(nNWM.nDummy.NetEventArg arg)
	{
		return (nNWM.nASDF.NetEventPlugin_asdf)arg.plugin;
	}
	
	//#--------------------------------------------------------------------------
	// Game Server -> Client Net Receiver.
	//#--------------------------------------------------------------------------
	public void gs2x_echo(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_gs2x_echo;
		var plugin = ToPlugin(arg);
		//nNWM.nASDF.jUser user = plugin.m_User;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}
		
	/*
	 * �Ʒ� ���ø� �ڵ带 �����Ͽ� ���. asdf�� ���ϴ� ���������̸����� �ٲٽÿ�.
	 
	public void asdf(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_asdf;
		var plugin = ToPlugin(arg);
		//nNWM.nASDF.jUser user = plugin.m_User;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}
	  
	 *
	 * */
}
