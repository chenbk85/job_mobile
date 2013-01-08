using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using ProtoBuf;
//using Google.ProtocolBuffers;


namespace nPROTO
{

    [ProtoContract]
    public class Version {

        // 메이저 버전 : 1
        [ProtoMember(1, IsRequired = false)]
        public int major { get;  set; }

        // 프로토콜 버전 2012/04/01 #0
        [ProtoMember(2, IsRequired = false)]
        public int protocol { get; set; }

        [ProtoMember(3, IsRequired = true)]
        public int framework { get; set; }

        [ProtoMember(4, IsRequired = true)]
        public int service { get; set; }

        public Version()
        {
            major = 1;
            protocol = 1204010;
        }
    }

    [ProtoContract]
    public class Error {

        [ProtoMember(1, IsRequired = true)]
        public int errorCode { get; set; }

        [ProtoMember(2, IsRequired = true)]
        public string errorInfo { get; set; }

        [ProtoMember(3, IsRequired = true)]
        public int reqMode { get; set; }

        public void CopyFrom(ref Error error)
        {
            errorCode = error.errorCode;
            errorInfo = error.errorInfo;
            reqMode = error.reqMode;
        }
    }

    [ProtoContract]
    public class Desc {

        [ProtoMember(1, IsRequired = true)]
	    public int id { get; set; }

        [ProtoMember(2, IsRequired = true)]
	    public string desc { get; set; }

        public void CopyFrom(ref Desc _desc)
        {
            id = _desc.id;
            desc = _desc.desc;
        }
    }

    [ProtoContract]
    public class Notice {

        [ProtoMember(1, IsRequired = true)]
	    public bool popup { get; set; }

        [ProtoMember(2, IsRequired = true)]
	    public int srl { get; set; }

        [ProtoMember(3, IsRequired = true)]
	    public string notice { get; set; }

        public void CopyFrom(ref Notice _notice)
        {
            popup = _notice.popup;
            srl = _notice.srl;
            notice = _notice.notice;
        }
    }


    [ProtoContract]
    public class UError {
	    public enum EErrorType {
		    EET_VERSION_INCORRECT = 1,
		    EET_DATABASE = 2,		// Database 에러
            EET_INTERNAL = 3,		// 내부 서버 문제
		    EET_ALREADY_LOGGED = 4,	// 다른 접속이 존재
		    EET_NOT_LOGGED = 5,		// 로그인이 되어 있지 않음
		    EET_ALREADY_PLAYING = 6,// 이미 게임중임
		    EET_NOT_PLAYING = 7,	// 게임중이 아님
		    EET_CANT_PLUG_GS = 8,	// 게임서버가 플러그를 거부함

            // 요청 인자가 잘못 들어올 경우 : 현재 plug때 game_id가 상이할때
		    EET_INVALID_VALUE = 9, 
           
		    EET_TIME_OUT = 10,      // unused
		    EET_UNDEFINE = 11,      // unused
		    EET_MAX_REFILL = 12,	//리필 제한
		    EET_OVER_USER = 13,		//유저가 넘친다

            EET_PLUG = 14,          // 플러그가 안됨

            EET_BUSY = 15          // 현재는 이 패킷은 처리 못함 다시 시도할것
	    }

        [ProtoMember(1, IsRequired = true)]
	    public Error error { get; set; }

        [ProtoMember(2, IsRequired = false)] 
        public bool over { get; set; }

        public UError()
        {
            error = new Error();
        }

        public void CopyFrom(ref UError uerror)
        {
            //error.CopyFrom(ref uerror.error);
            //over = uerror.over;
        }
    }

    // Packet type specification
    [ProtoContract]
    public class UReqConnect {

        [ProtoMember(1, IsRequired = true)]
	    public int svcID { get; set; }

        [ProtoMember(2, IsRequired = true)]
	    public int gameID { get; set; }

        [ProtoMember(3, IsRequired = true)]
	    public int lastCloseTime { get; set; }

        [ProtoMember(4, IsRequired = true)]
	    public Version version { get; set; }

        [ProtoMember(5, IsRequired = true)]
	    public MemberInfo memberInfo { get; set; }

        public UReqConnect()
        {
            version = new Version();
            memberInfo = new MemberInfo();
        }

        public void CopyFrom(ref UReqConnect _reqconnect)
        {
            //svcID = _reqconnect.svcID;
            //gameID = _reqconnect.gameID;
            //lastCloseTime = _reqconnect.lastCloseTime;
            //version.CopyFrom(ref _reqconnect.version);
            //memberInfo.CopyFrom( ref _reqconnect.memberInfo );
        }
    }


    [ProtoContract]
    public class UAnsConnect {

        [ProtoMember(1, IsRequired = true)]
        public int svcID { get; set; }

        [ProtoMember(2, IsRequired = true)]
	    public int gameID { get; set; }

        [ProtoMember(3, IsRequired = true)]
	    public int status { get; set; }

        [ProtoMember(4, IsRequired = true)]
	    public string ip { get; set; }

        [ProtoMember(5, IsRequired = true)]
	    public int port { get; set; }

        [ProtoMember(6, IsRequired = true)]
	    public string passwd { get; set; }
    }


    [ProtoContract]
    public class UReqNotice {
    }

    [ProtoContract]
    public class UAnsNotice {

        [ProtoMember(1, IsRequired = false)] 
	    public List<Notice> notices { get; set; }

        public UAnsNotice()
        {
            notices = new List<Notice>();
        }

        public void CopyFrom(ref UAnsNotice ansnotice)
        {
            notices = ansnotice.notices;
        }
    }

    [ProtoContract]
    public class UReqChannel {
    }
    [ProtoContract]
    public class UAnsChannel {

        [ProtoMember(1, IsRequired = false)] 
        public List<Desc> channelInfo { get; set; }

        public UAnsChannel()
        {
            channelInfo = new List<Desc>();
        }

        public void CopyFrom(ref UAnsChannel anschannel)
        {
            channelInfo = anschannel.channelInfo;
        }
    }
    [ProtoContract]
    public class UErrChannel {
        [ProtoMember(1, IsRequired = true)]
        public Error error { get; set; }

        public UErrChannel()
        {
            error = new Error();
        }

        public void CopyFrom(ref UErrChannel errchannel)
        {
            //error.CopyFrom(errchannel.error);
        }
    }

    [ProtoContract]
    public class UReqStore {
    }
    [ProtoContract]
    public class UAnsStore {
        [ProtoMember(1, IsRequired = false)] 
	    public List<Desc> itemInfo { get; set; }

        public UAnsStore()
        {
            itemInfo = new List<Desc>();
        }

        public void CopyFrom(ref UAnsStore store)
        {
            itemInfo = store.itemInfo;
        }
    }

    [ProtoContract]
    public class UReqInfo {
    }
    [ProtoContract]
    public class UAnsInfo {

        [ProtoMember(1, IsRequired = true)]
        public byte[] gameInfo { get; set; }

        public void CopyFrom(ref UAnsInfo info)
        {
            gameInfo = info.gameInfo;
        }
    }

    [ProtoContract]
    public class UReqAutoJoin {

        [ProtoMember(1, IsRequired = true)]
	    public int categoryID { get; set; }

        [ProtoMember(2, IsRequired = true)]
	    public int channelID { get; set; }
    }
    [ProtoContract]
    public class UAnsAutoJoin {

        [ProtoMember(1, IsRequired = true)]
        public byte[] gameRoomInfo { get; set; }

        public void CopyFrom(ref UAnsAutoJoin join)
        {
            gameRoomInfo = join.gameRoomInfo;
        }

    }

    [ProtoContract]
    public class UReqLeaveGame {

        [ProtoMember(1, IsRequired = true)]
	    public int gameID { get; set; }

        [ProtoMember(2, IsRequired = true)]
	    public bool kick { get; set; }

    }
    [ProtoContract]
    public class UAnsLeaveGame {
        public enum KICK_TYPE{
          EXIT_RESERVATION=1,
          LIMITMONEY=2,
          ALLIN=3,
          SYSTEM_ERROR = 4,
          KICK_ZERO = 5,
          PURGE = 6, // 강퇴처리
          KILL = 7 // 게이트웨이 종료
        }

        [ProtoMember(1, IsRequired = true)]
        public int gameID { get; set; }

        [ProtoMember(2, IsRequired = true)]
        public KICK_TYPE nType { get; set; }
    }


    [ProtoContract]
    public class UReqClose {
    }
    [ProtoContract]
    public class UAnsClose {
    }

    [ProtoContract]
    public class UReqPong {

        [ProtoMember(1, IsRequired = true)]
	    public int seq { get; set; }
    }

    [ProtoContract]
    public class UAnsPing {

        [ProtoMember(1, IsRequired = true)]
	    public int seq { get; set; }
    }


    [ProtoContract]
    public class UReqPlug {

        [ProtoMember(1, IsRequired = true)]
	    public int gameID { get; set; }

        [ProtoMember(2, IsRequired = true)]
	    public string passwd { get; set; }

    }

    [ProtoContract]
    public class UAnsPlug {

        [ProtoMember(1, IsRequired = true)]
	    public int gameID { get; set; }
    }


    [ProtoContract]
    public class UReqProtocol {
        public enum Type {
	        NONE = 1,
	        UREQCONNECT = 2,
	        UREQCHANNEL = 3,
	        UREQSTORE = 4,
	        UREQINFO = 5,
	        UREQAUTOJOIN = 6,
	        UREQLEAVEGAME = 7,
	        UREQCLOSE = 8,
	        UREQPONG = 9,
	        UREQPLUG = 10,
	        GLREQGAMEPROTOCOL = 11,
	        UREQDB = 12,
	        UREQNOTICE = 13
        }

        [ProtoMember(1, IsRequired = true)]
	    public Type type { get; set; }

	    [ProtoMember( 2, IsRequired = false)]
        public UReqConnect reqConnect { get; set; }

	    [ProtoMember( 3, IsRequired = false)]
        public UReqChannel reqChannel { get; set; }

	    [ProtoMember( 4, IsRequired = false)]
        public UReqStore reqStore { get; set; }

	    [ProtoMember( 5, IsRequired = false)]
        public UReqInfo reqInfo { get; set; }

	    [ProtoMember( 6, IsRequired = false)]
        public UReqAutoJoin reqAutoJoin { get; set; }

	    [ProtoMember( 7, IsRequired = false)]
        public UReqLeaveGame reqLeaveGame { get; set; }

	    [ProtoMember( 8, IsRequired = false)]
        public UReqClose reqClose { get; set; }

	    [ProtoMember( 9, IsRequired = false)]
        public UReqPong reqPong { get; set; }

	    [ProtoMember( 10, IsRequired = false)]
        public UReqPlug reqPlug { get; set; }
    	
	    [ProtoMember( 11, IsRequired = false)]
        public byte[] reqGameProtocol { get; set; }

	    [ProtoMember( 12, IsRequired = false)]
        public ReqDB reqDB { get; set; }

	    [ProtoMember( 13, IsRequired = false)]
        public UReqNotice reqNotice { get; set; }

        public UReqProtocol()
        {
            reqConnect = new UReqConnect();
            reqChannel = new UReqChannel();
            reqStore = new UReqStore();
            reqInfo = new UReqInfo();
            reqAutoJoin = new UReqAutoJoin();
            reqLeaveGame = new UReqLeaveGame();
            reqClose = new UReqClose();
            reqPong = new UReqPong();
            reqPlug = new UReqPlug();
            reqDB = new ReqDB();
            reqNotice = new UReqNotice();
        }

        public void CopyFrom(ref UReqProtocol ureq)
        {
            //reqConnect.CopyFrom(ureq.reqConnect);

            //reqChannel = (ureq.reqChannel);
            //reqStore = (ureq.reqStore);
            //reqInfo = (ureq.reqInfo);
            //reqAutoJoin = (ureq.reqAutoJoin);
            //reqLeaveGame = (ureq.reqLeaveGame);
            //reqClose = (ureq.reqClose);
            //reqPong = (ureq.reqPong);
            //reqPlug = (ureq.reqPlug);
            //reqDB.CopyFrom(ureq.reqDB);
            //reqNotice = (ureq.reqNotice);
        }
    };

    [ProtoContract]
    public class UAnsProtocol {
        public enum Type {
	        NONE = 1,

	        UANSCONNECT = 2,
	        UANSCHANNEL = 3,
	        UANSSTORE = 4,
	        UANSINFO = 5,
	        UANSAUTOJOIN = 6,
	        UANSLEAVEGAME = 7,
	        UANSCLOSE = 8,
	        UANSPING = 9,
	        UANSPLUG = 10,
	        GLANSGAMEPROTOCOL = 11,
	        UANSDB = 12,
	        UANSNOTICE = 13,

	        UERROR = 14
        }

        [ProtoMember(1, IsRequired = true)]
	    public Type type { get; set; }

	    [ProtoMember( 2, IsRequired = false)]
        public UAnsConnect ansConnect { get; set; }

	    [ProtoMember( 3, IsRequired = false)]
        public UAnsChannel ansChannel { get; set; }

	    [ProtoMember( 4, IsRequired = false)]
        public UAnsStore ansStore { get; set; }

	    [ProtoMember( 5, IsRequired = false)] 
        public UAnsInfo ansInfo { get; set; }

	    [ProtoMember( 6, IsRequired = false)]
        public UAnsAutoJoin ansAutoJoin { get; set; }

	    [ProtoMember( 7, IsRequired = false)]
        public UAnsLeaveGame ansLeaveGame { get; set; }

	    [ProtoMember( 8, IsRequired = false)]
        public UAnsClose ansClose { get; set; }

	    [ProtoMember( 9, IsRequired = false)]
        public UAnsPing ansPing { get; set; }

	    [ProtoMember( 10, IsRequired = false)] 
        public UAnsPlug ansPlug { get; set; }


	    [ProtoMember( 11, IsRequired = false)]
        public byte[] ansGameProtocol { get; set; }

	    [ProtoMember( 12, IsRequired = false)]
        public AnsDB ansDB { get; set; }

	    [ProtoMember( 13, IsRequired = false)]
        public UAnsNotice ansNotice { get; set; }


	    [ProtoMember( 14, IsRequired = false)] 
        public UError ansError { get; set; }

        public UAnsProtocol()
        {
            
            ansConnect = new UAnsConnect();
            ansChannel = new UAnsChannel();
            ansStore = new UAnsStore();
            ansInfo = new UAnsInfo();
            ansAutoJoin = new UAnsAutoJoin();
            ansLeaveGame = new UAnsLeaveGame();
            ansClose = new UAnsClose();
            ansPing = new UAnsPing();
            ansPlug = new UAnsPlug();
            ansDB = new AnsDB();
            ansNotice = new UAnsNotice();
            ansNotice = new UAnsNotice();
            ansError = new UError();
            
        }
    }


    /* -------------------------------------------------------------------------- */

    [ProtoContract]
    public class MemberInfo
    {
        // 피망플러스 사용자 아이디
        [ProtoMember(1, IsRequired = true)]
        public int game_id { get; set; }

        // 아바타 이미지 URL
        [ProtoMember(2, IsRequired = true)]
        public string avatar_url { get; set; }

        // 닉네임 정보관리는 PP에서만 하고 게임서버에서는 통보만 받는다.
        // 이름의 길이등은 알 필요 없다.
        [ProtoMember(3, IsRequired = true)]
        public string nick_name { get; set; }

        [ProtoMember(4, IsRequired = true)]
        public bool gender_option { get; set; }
    }

    /* -------------------------------------------------------------------------- */



}
