using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using ProtoBuf;
//using Google.ProtocolBuffers;

namespace nPROTO
{

    //#--------------------------------------------------------------------------
    [ProtoContract]
	public class GReqGameEnter 
    //#--------------------------------------------------------------------------
    {
	    // category > channel > room
	    // 현제 게임서버가 몇번 카테고리의 몇번 채널인지는 UG에서 판단하여 알려줌)
	    // 채널별로 게임서버를 뛰울려고 계획중인걸로 알고 있음.
        [ProtoMember(1, IsRequired = true)]
		public int gameID {get; set;}
        [ProtoMember(2, IsRequired = true)]
		public int categoryID {get; set;}
        [ProtoMember(3, IsRequired = true)]
		public int channelID {get; set;}
        [ProtoMember(4, IsRequired = true)]
		public int roomID {get; set;}
        [ProtoMember(5, IsRequired = true)]
        public byte[] gameUserInfo { get; set; }
    }

    //#--------------------------------------------------------------------------
    [ProtoContract]
	public class GAnsGameEnter 
    //#--------------------------------------------------------------------------
    {
        [ProtoMember(1, IsRequired = true)]
        public byte[] gameRoomInfo { get; set; }
    }

    //#--------------------------------------------------------------------------
    [ProtoContract]
	public class GReqGameLeave 
    //#--------------------------------------------------------------------------
    {
        [ProtoMember(1, IsRequired = true)]
		public int gameID {get; set;}
        [ProtoMember(2, IsRequired = true)]
		public bool kick {get; set;} //차후 확정성을 위해 추가해놓은것.
    }

    //#--------------------------------------------------------------------------
    [ProtoContract]
	public class GAnsGameLeave 
    //#--------------------------------------------------------------------------
    {
      public enum KICK_TYPE{
        EXIT_RESERVATION=1, //정상적으로 나감.
        LIMITMONEY=2, // 돈 한도가 모지라서 내보냄.
        ALLIN=3, // 돈이 다 털려서 내보냄.
        SYSTEM_ERROR=4, //DB 업데이트 실패.
        KICK_ZERO=5,
        PURGE = 6,      // 강퇴
        KILL = 7      // 나가면서 게이트웨이 강제로 종료
      }

      [ProtoMember(1, IsRequired = true)]
		public int gameID {get; set;}
      [ProtoMember(2, IsRequired = true)]
		public KICK_TYPE nType {get; set;} // enum KICK_TYPE 참조할것.
    }

    //#--------------------------------------------------------------------------
    [ProtoContract]
	public class GReqDetach 
    //#--------------------------------------------------------------------------
    { 
	    //게임나가기에서 UG가 클라접속이 너무오래지속된체 반응이 없으면 접속을 끊는상황.
	    //GAnsGameLeave에 대한 처리를 해주면 된다.
        [ProtoMember(1, IsRequired = true)]
		public int gameID {get; set;}	
    }
    //#--------------------------------------------------------------------------
    [ProtoContract]
	public class GAnsDetach {
    //#--------------------------------------------------------------------------
        [ProtoMember(1, IsRequired = true)]
		public int gameID {get; set;}
    }

    //#--------------------------------------------------------------------------
    [ProtoContract]
	public class GReqPlug  // 게임중 비정상 종료후 재접속하여 게임중 난입하는 상태. 이어치기(맞고,포커)
    //#--------------------------------------------------------------------------
    {
        [ProtoMember(1, IsRequired = true)]
		public int gameID {get; set;}
    }

    //#--------------------------------------------------------------------------
    [ProtoContract]
	public class GAnsPlug 
    //#--------------------------------------------------------------------------
    {
        [ProtoMember(1, IsRequired = true)]
		public int gameID {get; set;}
    }

    [ProtoContract]
	public class GError {
        [ProtoMember(1, IsRequired = true)]
		public int errorCode {get; set;}
        [ProtoMember(2, IsRequired = true)]
		public string errorInfo {get; set;}
    }

    [ProtoContract]
	public class GErrPlug {
        [ProtoMember(1, IsRequired = true)]
		public GError error {get; set;} //
    }

    [ProtoContract]
	public class GAnsUserUpdate {
        [ProtoMember(1, IsRequired = true)]
		public int type {get; set;}
        [ProtoMember(2, IsRequired = true)]
        public byte[] updateInfo { get; set; }
    }

    [ProtoContract]
	public class GAnsStatus
    {
    }

    [ProtoContract]
	public class GReqStatus
    {
        public enum Status 
        {
            NORMAL = 1,
            DETACHED = 2
        }
        [ProtoMember(1)]
		public Status status {get; set;}
    }

    [ProtoContract]
	public class GReqProtocol {
    public enum Type {
	    NONE = 1,
	    GREQGAMEENTER = 2,
	    GREQGAMELEAVE = 3,
	    GREQDETACH = 4,
	    GREQPLUG = 5,
	    GLREQGAMEPROTOCOL = 6,
	    GDBANS = 7,
        GREQSTATUS = 8
    }
    [ProtoMember(1, IsRequired = true)]
		public Type type {get; set;}
	    [ProtoMember(2, IsRequired = false)]
	    public GReqGameEnter reqGameEnter {get; set;}
	    [ProtoMember(3, IsRequired = false)]
	    public GReqGameLeave reqGameLeave {get; set;}
	    [ProtoMember(4, IsRequired = false)]
	    public GReqDetach reqDetach {get; set;}
	    [ProtoMember(5, IsRequired = false)]
		public GReqPlug reqPlug {get; set;}
	    [ProtoMember(6, IsRequired = false)]
        public byte[] reqGameProtocol { get; set; }
	    [ProtoMember(7, IsRequired = false)]
		public AnsDB ansDB {get; set;}
        [ProtoMember(8, IsRequired = false)]
        public GReqStatus reqStatus { get; set; }

        public GReqProtocol()
        {
            reqGameEnter = new GReqGameEnter();
            reqGameLeave = new GReqGameLeave();
            reqDetach = new GReqDetach();
            reqPlug = new GReqPlug();
            ansDB = new AnsDB();
            reqStatus = new GReqStatus();
        
        }
    }

    [ProtoContract]
	public class GAnsProtocol {
    public enum Type {
	    NONE = 1,
	    GANSGAMEENTER = 2,
	    GANSGAMELEAVE = 3,
	    GANSDETACH = 4,
	    GANSPLUG = 5,
	    GERRPLUG = 6,
	    GLANSGAMEPROTOCOL = 7,
	    GDBREQ = 8,
        GANSUSERUPDATE = 9,
        GANSSTATUS = 10
    }
    [ProtoMember(1, IsRequired = true)]
		public Type type {get; set;}
	    [ProtoMember(2, IsRequired = false)]
		public GAnsGameEnter ansGameEnter {get; set;}
	    [ProtoMember(3, IsRequired = false)]
		public GAnsGameLeave ansGameLeave {get; set;}
	    [ProtoMember(4, IsRequired = false)]
		public GAnsDetach ansDetach {get; set;}
	    [ProtoMember(5, IsRequired = false)]
		public GAnsPlug ansPlug {get; set;}
	    [ProtoMember(6, IsRequired = false)]
		public GErrPlug ansErr {get; set;}
	    [ProtoMember(7, IsRequired = false)]
        public byte[] ansGameProtocol { get; set; }
	    [ProtoMember(8, IsRequired = false)]
		public ReqDB reqDB {get; set;}
        [ProtoMember(9, IsRequired = false)]
		public GAnsUserUpdate ansUpdate {get; set;}
        [ProtoMember(10, IsRequired = false)]
		public GAnsStatus ansStatus {get; set;}

        public GAnsProtocol()
        {
            ansGameEnter = new GAnsGameEnter();
            ansGameLeave = new GAnsGameLeave();
            ansDetach = new GAnsDetach();
            ansPlug = new GAnsPlug();
            ansErr = new GErrPlug();
            reqDB = new ReqDB();
            ansUpdate = new GAnsUserUpdate(); 
            ansStatus = new GAnsStatus();
        }
    }
}

