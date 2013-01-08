using UnityEngine;
using System.Collections.Generic;
using System;
using System.IO;
using MSG;
using rps;


public class TestScene : MonoBehaviour 
{
	enum Status
	{
		Init,					
		Connected,
		Login,
		InRoom,
		InGame,
	}

	public string urlOrIp;
	public int port;
	
	private const int GAME_ID = 9999;

	private delegate void MenuFuc(string menuName);
	
	
	private Rect LOG_AREA_FRAME = new Rect(150, 30, 300, 250);
	private Rect GAME_AREA_FRAME = new Rect(150, 300, 300, 600);
	private Rect DEFAULT_BUTTON_FRAME = new Rect(30,30,100,40);
	
	private float BUTTON_INTERVAL = 45;
	
		
	private MSGClient client;
	private Status status = Status.Init;
	
	private string log = "";
	private string gameMessage = "";
	
	private int round = 0;
	
	private Dictionary<string, MenuFuc> funcDic;
	private Dictionary<Status,List<string>> menuByStatus = new Dictionary<Status, List<string>>
	{
		{ Status.Init, new List<string>
			{
				"Connect",
				"PlugConnect",
				"Close",
				"Close-graceful"
			}
		},
		{ Status.Connected, new List<string>
			{
				"Login",
				"Plug",
				"Notice",
				"Close",
				"Close-graceful"
			}
		},
		{ Status.Login, new List<string>
			{
				"GameInfo",
				"Channel",
				"AutoJoin",
				"PoliteClose",
				"Notice",
				"ReqDB",
				"Close",
				"Close-graceful"
			}
		},
		{ Status.InRoom, new List<string>
			{
				"GameInfo",
				"Channel",
				"StartGame",
				"Leave",
				"Notice",
				"ReqDB",
				"Close",
				"Close-graceful"
			}
		},
		{ Status.InGame, new List<string>
			{
				"Rock",
				"Scissors",
				"Paper"
			}
		}
	};
	
	/**  Use this for initialization */
	void Start () 
	{
		client = new MSGClient("Test");
		client.LogLevel = LogLevel.Debug;
		funcDic = new Dictionary<string, MenuFuc>
		{
			{ "Connect", 		this.Connect},
			{ "PlugConnect", 	this.PlugConnect},
			{ "Plug", 			this.Plug},
			{ "Close", 			this.Close},
			{ "Close-graceful", this.CloseGraceful},
			{ "Login", 			this.Login},
			{ "GameInfo", 		this.GameInfo},
			{ "Channel", 		this.Channel},
			{ "AutoJoin", 		this.AutoJoin},
			{ "Leave", 			this.Leave},
			{ "PoliteClose", 	this.PoliteClose},
			{ "Notice", 		this.Notice},
			{ "ReqDB",			this.ReqDB},
			{ "StartGame",		this.StartGame},
			{ "Rock",			this.RequestToss},
			{ "Scissors",		this.RequestToss},
			{ "Paper",			this.RequestToss},
		};

	}
	
	/**  Update is called once per frame */
	void Update () 
	{
		MSGEvent e;
		while( client != null && client.PopEvent(out e) )
		{
			var dt = System.DateTime.Now;
			Debug.Log(dt.ToLongTimeString() + " => " +"EventType: " + e.EventType.ToString());
			
			switch(e.EventType)
			{
			case MSGEventType.Connected:
				status = Status.Connected;
				Log (ObjectDumper.Dump(e));
				break;
			case MSGEventType.Disconnected:
				status = Status.Init;
				Log (ObjectDumper.Dump(e));
				break;
			case MSGEventType.RecvMessage:
				ProcessEvent(e);
				break;
			default:
				Log (ObjectDumper.Dump(e));
				break;
			}
			client.InsertEventToRecyclingPool(e);
		}
	
	}
	
	void OnGUI()
	{
		Rect rect = new Rect(DEFAULT_BUTTON_FRAME);
		List<string> menus = AvailableBehaviours();
		
		foreach(string menu in menus)
		{
			if(GUI.Button(rect,menu))
			{
				ClearLog();				
				funcDic[menu](menu);
			}
			rect.y += BUTTON_INTERVAL;
		}
		
		GUI.TextArea(LOG_AREA_FRAME, log);
		GUI.TextArea(GAME_AREA_FRAME, gameMessage);
		
	}
	private void ProcessEvent(MSGEvent e)
	{
		AnswerMessage ans = e.RecvMessage;
		
		switch(ans.Type)
		{
		case AnswerMessage.AnsType.Connect:
			status = Status.Login;
			Log("Login Succeed");
			Log("Connect ans =>" + ObjectDumper.Dump(ans.Connect));
			break;
		case AnswerMessage.AnsType.Info:
			Log ("Game Info Received");
			Log ("Info => " + BitConverter.ToString(ans.Info.GameInfo));
			break;
		case AnswerMessage.AnsType.Channel:
			Log ("Channel Info Received");
			Log ("Channel Info => \n" + ObjectDumper.Dump(ans.Channel.ChannelInfo));
			break;
		case AnswerMessage.AnsType.AutoJoin:
			status = Status.InRoom;
			Log ("Auto Join Ans");
			Log ("Ans => " + BitConverter.ToString(ans.AutoJoin.GameRoomInfo));
			ProcessAutoJoin(ans.AutoJoin.GameRoomInfo);
			break;
		case AnswerMessage.AnsType.LeaveGame:
			status = Status.Login;
			Log ("Leave Game");
			Log ("Ans => " + ObjectDumper.Dump(ans.LeaveGame));
			break;
		case AnswerMessage.AnsType.Close:
			Log("Ans Close");
			break;
		case AnswerMessage.AnsType.Notice:
			Log ("Notice Received");
			Log ("Notices =>" + ObjectDumper.Dump(ans.Notice.Notices));
			break;
		case AnswerMessage.AnsType.DB:
			Log ("Ans DB Received");
			Log ("Ans DB =>" + ObjectDumper.Dump(ans.DB));
			break;
		case AnswerMessage.AnsType.GameProtocol:
			status = Status.InGame;
			Log ("Game Message");
			Log ("Message => " + BitConverter.ToString(ans.GameProtocol.Buffer));
			ProcessGameProtocol( ans.GameProtocol.Buffer );
			
			break;
		case AnswerMessage.AnsType.Error:
			Log("Error");
			Log ("Error Msg =>" + ObjectDumper.Dump(ans.Error));
			break;
		
		default:
			Log("Ans =>" + ObjectDumper.Dump(ans));
			break;
		}
	}

	private void ClearLog()
	{
		log = "";
	}
	private void Log(string text)
	{
		log += text + "\n";
	}

	private void ClearMessage()
	{
		gameMessage = "";
	}
	
	private void Message(string text)
	{
		gameMessage += text + "\n";
	}
	
	private List<string> AvailableBehaviours()
	{
		return menuByStatus[status];
	}
	
	private void Connect(string menuName)
	{
		client.Connect(urlOrIp, port);
	}
	private void PlugConnect(string menuName)
	{
		client.PlugConnect();
	}
	private void Close(string menuName)
	{
		client.Close(false);
		ClearMessage();
	}
	private void CloseGraceful(string menuName)
	{
		client.Close(true);
	}
	private void Login(string menuName)
	{
		var connect = new ReqConnect
		{
			SvcID = 100,
			GameID = 56,
			Version = 270,
			MemberInfo = new MemberInfo
			{
				GameID = GAME_ID,
				AvatarUrl = "test",
				NickName = "test",
				GenderOption = true,
			}
		};
		
		client.Send(connect);
		Log ("Sending connect req => " + ObjectDumper.Dump(connect));
	}
	private void Plug(string menuName)
	{
		var plug = new ReqPlug
		{
			GameID = GAME_ID
		};
		client.Send(plug);
		Log ("Sending plug req => " + ObjectDumper.Dump(plug));
	}
	private void GameInfo(string menuName)
	{
		var gameInfo = new ReqInfo{};
		
		client.Send(gameInfo);
		Log ("Sending info req => " +ObjectDumper.Dump(gameInfo));
		
	}
	
	private void Channel(string menuName)
	{
		var channel = new ReqChannel{};
		client.Send (channel);
		Log ("Sending channel req => " +ObjectDumper.Dump(channel));
	}
	private void AutoJoin(string menuName)
	{
		var autoJoin = new ReqAutoJoin
		{
			CategoryID = 1,
			ChannelID = 1
		};
		client.Send (autoJoin);
		Log ("Sending auto join req => " +ObjectDumper.Dump(autoJoin));
	}
	
	private void StartGame(string menuName)
	{
		ClearMessage();
		rps.ReqGameProtocol request 	= new rps.ReqGameProtocol
		{
			type = rps.ReqGameProtocol.Type.REQ_START_GAME,
			req_start_game = new rps.ReqStartGame
			{
				option =  new rps.GameOption{ round_num = rps.GameOption.RoundNum.THREE }
			}
		};
		
		SendGameProtocol(request);		
	}
	
	private void RequestToss(string menuName)
	{
		rps.ReqGameProtocol request = new rps.ReqGameProtocol()
		{
			type = rps.ReqGameProtocol.Type.REQ_TOSS,
			req_toss = new rps.ReqToss()
			{
				round = this.round,
				rps_type = ConvertFromMenuToRPSType(menuName)
			}
			
		};
		SendGameProtocol(request);
	}
	
	private void Leave(string menuName)
	{
		var leaveGame = new ReqLeaveGame
		{
			GameID = GAME_ID,
			LeaveInfo = new byte[1]
		};
		client.Send(leaveGame);
		Log ("Leave =>" + ObjectDumper.Dump(leaveGame));
	}
	
	private void PoliteClose(string menuName)
	{
		var close = new ReqClose{};
		client.Send(close);
		Log ("Close =>" + ObjectDumper.Dump(close));
	}
	
	private void Notice(string menuName)
	{
		var notice = new ReqNotice{};
		client.Send (notice);
		Log ("Req Notice");
	}
	
	private void ReqDB(string menuName)
	{
		var db = new ReqDB
		{
			Seq = 201,
			Query = "201",
		};
		db.Params.Add(new DBIn
		{
			Type = DBIn.TypeEnum.Int,
			Value = GAME_ID.ToString()
		});
		client.Send (db);
		Log ("Req DB" + ObjectDumper.Dump(db));
	}
	private void ProcessGameProtocol(byte[] buffer)
	{			
		MemoryStream ansStream = new MemoryStream(buffer, 0, buffer.Length);
		var answer = ProtoBuf.Serializer.Deserialize<rps.AnsGameProtocol>(ansStream);
		if(answer == null)
		{
			Log ("Serialize fail");	
			return;
		}
		else
		{
			switch(answer.type)
			{
			case rps.AnsGameProtocol.Type.ANS_START_GAME:
				Message("=========================");
				Message("Game Start");
				Message("\tResult : " + ((0 == answer.ans_start_game.error_code)?"Success" : "Fail"));
				Message("\tGame Rounds : " + answer.ans_start_game.option.round_num);
				if(answer.ans_start_game.error_code == rps.AnsStartGame.ErrorCode.FAIL)
				{
					Leave ("");	
				}
				break;
			case rps.AnsGameProtocol.Type.ANS_START_ROUND:
				Message("=========================");
				Message("Round Start");
				Message("\tRound : " + answer.ans_start_round.round);
				Message("\tTimeout : " +answer.ans_start_round.timeout);
				Message("\tSelect your move in " + answer.ans_start_round.timeout + "seconds");
				this.round = answer.ans_start_round.round;
				break;
			case rps.AnsGameProtocol.Type.ANS_END_ROUND:
				Message("=========================");
				Message("Round End");
				Message("\tResult : " + answer.ans_end_round.result);
				Message("\tYou : " + answer.ans_end_round.your_rps_type);
				Message("\tEnemy : " + answer.ans_end_round.other_rps_type);
				break;
			case rps.AnsGameProtocol.Type.ANS_END_GAME:
				Message("=========================");
				Message ("Game End");
				Message ("\tWins : " + answer.ans_end_game.win_count);
				Message ("\tLoses: " + answer.ans_end_game.lose_count);
				Message ("\tDraws: " + answer.ans_end_game.draw_count);
				Leave ("");
				break;
			case rps.AnsGameProtocol.Type.ANS_SYNC_GAME_STATE:
				break;
			default:
				break;
			}
		}

	}
	private void ProcessAutoJoin(byte[] roomInfo)
	{
		MemoryStream memStream = new MemoryStream(roomInfo, 0 , roomInfo.Length);
		var room_info = ProtoBuf.Serializer.Deserialize<rps.RoomInfo>(memStream);
		
		Message("Room Info : ");
		Message("\tRoom Number : " + room_info.room_id);
		Message("\tUsers : ");
		foreach (var game_id in room_info.game_ids)
		{
			if(game_id == -2)
				Message("\t\t player : AI");
			else
				Message("\t\t player : " + game_id);
		}
	}
	private rps.RPS_Type ConvertFromMenuToRPSType(string menuName)
	{
		switch(menuName)
		{
			case "Rock":
				return rps.RPS_Type.RPS_ROCK;
			case "Scissors":
				return rps.RPS_Type.RPS_SCISSORS;
			case "Paper":
				return rps.RPS_Type.RPS_PAPER;
			default:
				return rps.RPS_Type.RPS_NONE;
		}
	}
	private void SendGameProtocol(rps.ReqGameProtocol gameProtocol)
	{
		MemoryStream memStream = new MemoryStream();
		ProtoBuf.Serializer.Serialize<rps.ReqGameProtocol>(memStream, gameProtocol);
		MSG.ReqGameProtocol req_game_protocol = new MSG.ReqGameProtocol(memStream.ToArray());
		client.Send(req_game_protocol);
	}
}
