using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using ProtoBuf;
//using Google.ProtocolBuffers;

namespace nPROTOCOL
{
    //--------------------------------------------------------------------------
    // 여기에 서버간( ug서버) 공용 구조체 선언
    //--------------------------------------------------------------------------
    [ProtoContract]
	public class GameUserInfo { // game.proto에서 사용.
        [ProtoMember(1, IsRequired = true)]
		public GameInfo gameInfo {get;set;} // UG가 전달해줌. 게임내의 유저 정보.
        [ProtoMember(2, IsRequired = true)]
        public byte[] memberInfo { get; set; }

        public GameUserInfo()
        {
            gameInfo = new GameInfo();
        }
        
    }

    [ProtoContract]
	public class GameRoomInfo {//game.proto에서 사용.
        [ProtoMember(1, IsRequired = true)]
		public int roomID {get;set;}
        [ProtoMember(2, IsRequired = true)]
		public int pointMoney {get;set;} // 맞고의 경우 룸의 정보에 "점당머니정보" 하나만 있으면 된다.
	    [ProtoMember(3, IsRequired=false)]
        public List<GameUserInfo> gameUserInfo {get;set;}

        public GameRoomInfo()
        {
            gameUserInfo = new List<GameUserInfo>();
        }
    }

    [ProtoContract]
	public class GameInfo {//game.proto에서 사용. // DB에 저장된 유저게임정보.
        [ProtoMember(1, IsRequired = true)]
		public int gameID {get;set;} // pp에서 알려준 유저 id number ( USN)
        [ProtoMember(2, IsRequired = true)]
		public int gameIndex {get;set;}// 고스톱의 경우는 0 또는 1, 포커는 0~4
        [ProtoMember(3, IsRequired = true)]
		public string level {get;set;} // 입문/초보/제왕 ,,,, 또는 레벨1 레벨2,,,
        [ProtoMember(4, IsRequired = true)]
		public string money {get;set;} // 단위에 독립적으로 하기 위해.
        [ProtoMember(5, IsRequired = true)]
		public int winCnt {get;set;} // 전적.
        [ProtoMember(6, IsRequired = true)]
		public int loseCnt {get;set;}
        [ProtoMember(7, IsRequired = true)]
		public int allInCnt {get;set;}
    }


    //--------------------------------------------------------------------------
    // 여기에 PokerServer용 공용 구조체 선언.
    //--------------------------------------------------------------------------


    [ProtoContract]
	public class AnsJoinUser {
        [ProtoMember(1, IsRequired = true)]
		public int game_id {get;set;}
        [ProtoMember(2, IsRequired = true)]
		public string name {get;set;}
    }

    [ProtoContract]
	public class AnsLeaveUser {
        [ProtoMember(1, IsRequired = true)]
		public int game_id {get;set;}

    }

    [ProtoContract]
	public class ReqPurgeUser {
        [ProtoMember(1, IsRequired = true)]
		public int game_id {get;set;}
    }

    //--------------------------------------------------------------------------
    [ProtoContract]
	public class GLReqGameProtocol { 
	    public enum Type {
		    NONE =1,
            PURGE_USER =2,
            ROOM_TIMER_TEST =3,
            USER_TIMER_TEST =4
	    }

        [ProtoMember(1, IsRequired = true)]
		public Type type {get;set;}
        [ProtoMember(2, IsRequired=false)]
	    public ReqPurgeUser purge_user {get;set;}

        public GLReqGameProtocol()
        {
            purge_user = new ReqPurgeUser();
        }
    }

    //--------------------------------------------------------------------------
    [ProtoContract]
	public class GLAnsGameProtocol { 
	    public enum Type {
		    NONE =1,
		    JOIN_USER =2,
            LEAVE_USER =3
	    }

        [ProtoMember(1, IsRequired = true)]
		public Type type {get;set;}
        [ProtoMember(2,IsRequired=false)]
	    public AnsJoinUser join_user {get;set;} 
        [ProtoMember(3,IsRequired=false)]
        public AnsLeaveUser leave_user {get;set;}

        public GLAnsGameProtocol()
        {
            join_user = new AnsJoinUser();
            leave_user = new AnsLeaveUser();
        }
    }
}