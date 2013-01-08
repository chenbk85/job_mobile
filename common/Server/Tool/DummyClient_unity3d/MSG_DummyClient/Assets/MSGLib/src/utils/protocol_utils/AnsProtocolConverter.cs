using System;
using System.Collections.Generic;
using MSG.Protocol;
namespace MSG
{
	public class AnsProtocolConverter
	{
		private static Dictionary<UAnsProtocol.Type, AnswerMessage.AnsType> typeTable = 
			new Dictionary<UAnsProtocol.Type, AnswerMessage.AnsType>
		{
			{ UAnsProtocol.Type.NONE, AnswerMessage.AnsType.None },
			{ UAnsProtocol.Type.UANSCONNECT, AnswerMessage.AnsType.Connect },
			{ UAnsProtocol.Type.UANSCHANNEL, AnswerMessage.AnsType.Channel },
			{ UAnsProtocol.Type.UANSINFO, AnswerMessage.AnsType.Info },
			{ UAnsProtocol.Type.UANSAUTOJOIN, AnswerMessage.AnsType.AutoJoin },
			{ UAnsProtocol.Type.UANSLEAVEGAME, AnswerMessage.AnsType.LeaveGame },
			{ UAnsProtocol.Type.UANSCLOSE, AnswerMessage.AnsType.Close },
			{ UAnsProtocol.Type.UANSPLUG, AnswerMessage.AnsType.Plug },
			{ UAnsProtocol.Type.GLANSGAMEPROTOCOL, AnswerMessage.AnsType.GameProtocol },
			{ UAnsProtocol.Type.UANSNOTICE, AnswerMessage.AnsType.Notice },
			{ UAnsProtocol.Type.UERROR, AnswerMessage.AnsType.Error },
			{ UAnsProtocol.Type.UANSGATEWAYPROTOCOL, AnswerMessage.AnsType.GatewayProtocol },
			{ UAnsProtocol.Type.UANSDB, AnswerMessage.AnsType.DB },
		};
		private static Dictionary<UAnsProtocol.Type, Func<UAnsProtocol, AnswerMessage>> convertFucTable = 
			new Dictionary<UAnsProtocol.Type, Func<UAnsProtocol, AnswerMessage>>
		{
			{ UAnsProtocol.Type.NONE, ConvertNoneMsg },
			{ UAnsProtocol.Type.UANSCONNECT, ConvertConnectMsg },
			{ UAnsProtocol.Type.UANSCHANNEL, ConvertChannelMsg },
			{ UAnsProtocol.Type.UANSINFO, ConvertInfoMsg },
			{ UAnsProtocol.Type.UANSAUTOJOIN, ConvertAutoJoinMsg },
			{ UAnsProtocol.Type.UANSLEAVEGAME, ConvertLeaveGameMsg },
			{ UAnsProtocol.Type.UANSCLOSE, ConvertCloseMsg },
			{ UAnsProtocol.Type.UANSPLUG, ConvertPlugMsg },
			{ UAnsProtocol.Type.GLANSGAMEPROTOCOL, ConvertGameProtocolMsg },
			{ UAnsProtocol.Type.UANSNOTICE, ConvertNoticeMsg },
			{ UAnsProtocol.Type.UERROR, ConvertErrorMsg },
			{ UAnsProtocol.Type.UANSGATEWAYPROTOCOL, ConvertGatewayProtocolMsg },
			{ UAnsProtocol.Type.UANSDB, ConvertDBMsg }
		};
			
		
		/**  if need cache, write t */
		public static AnswerMessage Convert(UAnsProtocol ug)
		{
			if(!convertFucTable.ContainsKey(ug.type))
				return null;
			Func<UAnsProtocol, AnswerMessage> func = convertFucTable[ug.type];
			return func(ug);
		}
		
		
		private static AnswerMessage ConvertNoneMsg(UAnsProtocol ug)
		{
			return new AnswerMessage
			{
				Type = ConvertType(ug.type)
			};
		}
		
		private static AnswerMessage ConvertConnectMsg(UAnsProtocol ug)
		{
			UAnsConnect connect = ug.ansConnect;
			
			return new AnswerMessage
			{
				Type = ConvertType(ug.type),
				Connect = new AnsConnect
				{
					SvcID = connect.svcID,
					GameID = connect.gameID
				}
								
			};
		}
		
		private static AnswerMessage ConvertChannelMsg(UAnsProtocol ug)
		{
			UAnsChannel channel = ug.ansChannel;
			List<Desc> infos = channel.channelInfo;
			List<ChannelInfo> channelInfos = new List<ChannelInfo>(infos.Count);
			foreach( Desc info in infos )
			{
				ChannelInfo channelInfo = new ChannelInfo
				{
					ID = info.id,
					Description = info.desc
				};
				channelInfos.Add(channelInfo);
				
			}

			return new AnswerMessage
			{
				Type = ConvertType(ug.type),
				Channel = new AnsChannel
				{
					ChannelInfo = channelInfos
				}
								
			};
		}

		private static AnswerMessage ConvertInfoMsg(UAnsProtocol ug)
		{
			var ans = ug.ansInfo;
			
			return new AnswerMessage
			{
				Type = ConvertType(ug.type),
				Info = new AnsInfo
				{
					GameInfo = ans.gameInfo
				}
								
			};
		}

		private static AnswerMessage ConvertAutoJoinMsg(UAnsProtocol ug)
		{
			var ans = ug.ansAutoJoin;
			
			return new AnswerMessage
			{
				Type = ConvertType(ug.type),
				AutoJoin = new AnsAutoJoin
				{
					GameRoomInfo = ans.gameRoomInfo
				}
								
			};
		}

		private static AnswerMessage ConvertLeaveGameMsg(UAnsProtocol ug)
		{
			var ans = ug.ansLeaveGame;
			
			AnsLeaveGame.KickTypeEnum kickType = AnsLeaveGame.KickTypeEnum.Allin;
			switch(ans.nType)
			{
				case UAnsLeaveGame.KICK_TYPE.EXIT_RESERVATION:
					kickType = AnsLeaveGame.KickTypeEnum.ExitReservation;
					break;
				case UAnsLeaveGame.KICK_TYPE.LIMITMONEY:
					kickType = AnsLeaveGame.KickTypeEnum.LimitMoney;
					break;
				case UAnsLeaveGame.KICK_TYPE.ALLIN:
					kickType = AnsLeaveGame.KickTypeEnum.Allin;
					break;
				case UAnsLeaveGame.KICK_TYPE.SYSTEM_ERROR:
					kickType = AnsLeaveGame.KickTypeEnum.SystemError;
					break;
				case UAnsLeaveGame.KICK_TYPE.KICK_ZERO:
					kickType = AnsLeaveGame.KickTypeEnum.KickZero;
					break;
				case UAnsLeaveGame.KICK_TYPE.PURGE:
					kickType = AnsLeaveGame.KickTypeEnum.Purge;
					break;
				case UAnsLeaveGame.KICK_TYPE.KILL:
					kickType = AnsLeaveGame.KickTypeEnum.Kill;
					break;
			}
			
			return new AnswerMessage
			{
				Type = ConvertType(ug.type),
				LeaveGame = new AnsLeaveGame
				{
					GameID = ans.gameID,
					KickType = kickType,
					LeaveInfo = ans.leave_info
				}
								
			};
		}

		private static AnswerMessage ConvertCloseMsg(UAnsProtocol ug)
		{
			return new AnswerMessage
			{
				Type = ConvertType(ug.type),
				Close = new AnsClose{}
								
			};
		}

		private static AnswerMessage ConvertPlugMsg(UAnsProtocol ug)
		{
			var ans = ug.ansPlug;
			
			return new AnswerMessage
			{
				Type = ConvertType(ug.type),
				Plug = new AnsPlug
				{
					GameID = ans.gameID
				}
			};
		}

		private static AnswerMessage ConvertGameProtocolMsg(UAnsProtocol ug)
		{
			return new AnswerMessage
			{
				Type = ConvertType(ug.type),
				GameProtocol = new AnsGameProtocol
				{
					Buffer = ug.ansGameProtocol
				}
			};
		}

		private static AnswerMessage ConvertNoticeMsg(UAnsProtocol ug)
		{
			var ans = ug.ansNotice;
			List<Protocol.Notice> datas = ans.notices;
			List<MSG.Notice> notices = new List<MSG.Notice>(datas.Count);
			
			foreach( var data in datas )
			{
				var notice = new MSG.Notice
				{
					Popup = data.popup,
					Srl = data.srl,
					NoticeContent = data.notice
				};
				notices.Add(notice);				
			}

			return new AnswerMessage
			{
				Type = ConvertType(ug.type),
				Notice = new AnsNotice
				{
					Notices = notices					
				}
			};
		}
		
		private static AnswerMessage ConvertDBMsg(UAnsProtocol ug)
		{
			var ans = ug.ansDB;
			
			return new AnswerMessage
			{
				Type = ConvertType(ug.type),
				DB = new MSG.AnsDB
				{
					Seq = ans.seq,
					ReturnCode = ans.retCode,
					Query = ans.query,
					Result = ans.result
				}
			};
				
		}
		
		private static AnswerMessage ConvertErrorMsg(UAnsProtocol ug)
		{
			var ans = ug.ansError;
			var error = (UError.EErrorType)ans.error.errorCode;
			AnsError.ErrorCodeEnum errorCode = AnsError.ErrorCodeEnum.Undefine;
			
			switch(error)
			{				
				case UError.EErrorType.EET_VERSION_INCORRECT:
					errorCode = AnsError.ErrorCodeEnum.VersionIncorrect;
					break;
				case UError.EErrorType.EET_DATABASE:
					errorCode = AnsError.ErrorCodeEnum.Database;
					break;
				case UError.EErrorType.EET_INTERNAL:
					errorCode = AnsError.ErrorCodeEnum.Internal;
					break;
				case UError.EErrorType.EET_ALREADY_LOGGED:
					errorCode = AnsError.ErrorCodeEnum.AlreadyLogged;
					break;
				case UError.EErrorType.EET_NOT_LOGGED:
					errorCode = AnsError.ErrorCodeEnum.NotLogged;
					break;
				case UError.EErrorType.EET_ALREADY_PLAYING:
					errorCode = AnsError.ErrorCodeEnum.AlreadyPlaying;
					break;
				case UError.EErrorType.EET_NOT_PLAYING:
					errorCode = AnsError.ErrorCodeEnum.NotPlaying;
					break;
				case UError.EErrorType.EET_CANT_PLUG_GS:
					errorCode = AnsError.ErrorCodeEnum.CantPlugGS;
					break;
				case UError.EErrorType.EET_INVALID_VALUE:
					errorCode = AnsError.ErrorCodeEnum.InvalidValue;
					break;
				case UError.EErrorType.EET_TIME_OUT:
					errorCode = AnsError.ErrorCodeEnum.TimeOut;
					break;
				case UError.EErrorType.EET_UNDEFINE:
					errorCode = AnsError.ErrorCodeEnum.Undefine;
					break;
				case UError.EErrorType.EET_MAX_REFILL:
					errorCode = AnsError.ErrorCodeEnum.MaxRefill;
					break;
				case UError.EErrorType.EET_OVER_USER:
					errorCode = AnsError.ErrorCodeEnum.OverUser;
					break;
				case UError.EErrorType.EET_PLUG:
					errorCode = AnsError.ErrorCodeEnum.Plug;
					break;
				case UError.EErrorType.EET_BUSY:
					errorCode = AnsError.ErrorCodeEnum.Busy;
					break;
			}
			
			return new AnswerMessage
			{
				Type = ConvertType(ug.type),
				Error = new AnsError
				{
					ErrorCode = errorCode,
					ErrorInfo = ans.error.errorInfo
				}
			};
		}
		private static AnswerMessage ConvertGatewayProtocolMsg(UAnsProtocol ug)
		{
			return new AnswerMessage
			{
				Type = ConvertType(ug.type),
				GatewayProtocol = new AnsGatewayProtocol
				{
					Buffer = ug.ansGatewayProtocol					
				}
			};
		}

		private static AnswerMessage.AnsType ConvertType(UAnsProtocol.Type type)
		{
			return typeTable[type];
		}
		
	}
	
}