using System;
using System.Collections.Generic;
using System.Text;
using ProtoBuf;

namespace nPROTO
{
     
    [ProtoContract]
    public class DBIn {
	        public enum Type {
		        INT = 1,
		        INT64 = 2,
		        STR = 3
	        }

        [ProtoMember(1,IsRequired = true)]
	    public Type type { get; set; }

        [ProtoMember(2,IsRequired = true)]
	    public string val { get; set; }

        public DBIn()
        {
            val = "";
        }
    }

    [ProtoContract]
    public class ReqDB {

        [ProtoMember(1,IsRequired = true)]
	    public Int32 seq { get; set; }

        [ProtoMember(2,IsRequired = true)]
	    public string query { get; set; }

        [ProtoMember(3,IsRequired = true)]
	    public List<DBIn> _params { get; set; }

        [ProtoMember(4, IsRequired = false)] 
        public byte[] options { get; set; }

        public ReqDB()
        {
            query = "";
            _params = new List<DBIn>();
        }
    }

    [ProtoContract]
    public class AnsDB {

        [ProtoMember(1,IsRequired = true)]
	    public Int32 seq { get; set; }

        [ProtoMember(2,IsRequired = true)]
	    public string query { get; set; }

        [ProtoMember(3,IsRequired = true)]
	    public Int32 retCode { get; set; }

        [ProtoMember(4,IsRequired = true)]
	    public byte[] result { get; set; }

        public AnsDB()
        {
            query = "";
        }
    }

       

}
