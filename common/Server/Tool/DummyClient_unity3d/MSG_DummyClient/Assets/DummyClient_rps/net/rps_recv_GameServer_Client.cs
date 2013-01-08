using UnityEngine;
using System.Collections;
using nNWM;

public class rps_recv_GameServer_Client : MonoBehaviour 
{
	//#--------------------------------------------------------------------------
	// Util function 
	//#--------------------------------------------------------------------------
	nProtoGSrps.GameServer_Client ToRecvData(nNWM.nDummy.NetEventArg arg)
	{
		return (nProtoGSrps.GameServer_Client)arg.recvData;
	}
	nNWM.nRPS.NetEventPlugin_rps ToPlugin(nNWM.nDummy.NetEventArg arg)
	{
		return (nNWM.nRPS.NetEventPlugin_rps)arg.plugin;
	}
	
	//#--------------------------------------------------------------------------
	// Game Server -> Client Net Receiver.
	//#--------------------------------------------------------------------------
	public void gs2x_echo(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_gs2x_echo;
		var plugin = ToPlugin(arg);
		//nNWM.nRPS.jUser user = plugin.m_User;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}
		
	/*
	 * �Ʒ� ���ø� �ڵ带 �����Ͽ� ���. rps�� ���ϴ� ���������̸����� �ٲٽÿ�.
	 
	public void rps(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_rps;
		var plugin = ToPlugin(arg);
		//nNWM.nRPS.jUser user = plugin.m_User;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}
	  
	 *
	 * */
}
