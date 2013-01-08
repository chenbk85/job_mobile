using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using ProtoBuf;
//using Google.ProtocolBuffers;

namespace nPROTO
{

    public enum PresenceCommand {
	    NONE = 0,
	    LOGIN = 1,
	    LOGOUT = 2,
	    GAMEENTER = 3,
	    GAMELEAVE = 4,
	    DETACH = 5,
	    PLUG = 6,
	    CATEGORY = 7,
	    ROOMLIST = 8
    }

    [ProtoContract]
	public class PReqProtocol
    {
        [ProtoMember(1, IsRequired = true)]
		public PresenceCommand command {get;set;}
        [ProtoMember(2, IsRequired = true)]
		public int seqID {get;set;}
        [ProtoMember(3, IsRequired = true)]
		public int gameID {get;set;}
        [ProtoMember(4, IsRequired = true)]
		public int svcID {get;set;}
        [ProtoMember(5, IsRequired = true)]
		public int category {get;set;}

	    [ProtoMember(6, IsRequired = false)]
	    public int arg1 {get;set;}
	    [ProtoMember(7, IsRequired = false)]
	    public int arg2 {get;set;}
    }

    [ProtoContract]
	public class PAnsProtocol
    {
        [ProtoMember(1, IsRequired = true)]
		public PresenceCommand command{get;set;}
        [ProtoMember(2, IsRequired = true)]
		public int seqID {get;set;}
        [ProtoMember(3, IsRequired = true)]
		public int gameID {get;set;}
        [ProtoMember(4, IsRequired = true)]
		public int svcID {get;set;}

        [ProtoMember(5, IsRequired = true)]
		public int category {get;set;}

	    // true - success/false - fail
        [ProtoMember(6, IsRequired = true)]
		public bool result {get;set;}

        [ProtoMember(7, IsRequired = true)]
		public string status {get;set;}
        [ProtoMember(8, IsRequired = true)]
		public bool detached {get;set;}

	    [ProtoMember(9, IsRequired = false)]
    	public string ip {get;set;}
	    [ProtoMember(10, IsRequired = false)]
	    public int port {get;set;}
	    [ProtoMember(11, IsRequired = false)]
	    public int roomID {get;set;}
	    [ProtoMember(12, IsRequired = false)]
	    public int arg1 {get;set;}
	    [ProtoMember(13, IsRequired = false)]
	    public int arg2 {get;set;}
	    [ProtoMember(14, IsRequired = false)]
	    public string info {get;set;}
    }



}
