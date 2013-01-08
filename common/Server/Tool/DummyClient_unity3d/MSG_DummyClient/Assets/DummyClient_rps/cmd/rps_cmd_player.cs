using UnityEngine;
using System.Collections;

namespace nNWM
{
	namespace nRPS
	{
		public class rps_cmd_player : CmdEvent_base
		{
			nNWM.nRPS.NetEventPlugin_rps cmd_NetEventPlugin2(string sUID)
			{
				return (nNWM.nRPS.NetEventPlugin_rps)base.cmd_NetEventPlugin(sUID);
			}

		}

	}//namespace nRPS
}//namespace nNWM
