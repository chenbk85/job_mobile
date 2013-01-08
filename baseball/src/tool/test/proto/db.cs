using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using ProtoBuf;
//using Google.ProtocolBuffers;

namespace nPROTO
{
     
    [ProtoContract]
    public class DBIn {
	        public enum Type {
		        INT = 1,
		        INT64 = 2,
		        STR = 3
	        }

        [ProtoMember(1, IsRequired = true)]
	    public Type type { get; set; }

        [ProtoMember(2, IsRequired = true)]
	    public string val { get; set; }

        
        public void CopyFrom( ref DBIn dbin )
        {
            type = dbin.type;
            val = dbin.val;
        }
    }

    [ProtoContract]
    public class ReqDB {

        [ProtoMember(1, IsRequired = true)]
	    public int seq { get; set; }

        [ProtoMember(2, IsRequired = true)]
	    public string query { get; set; }

        [ProtoMember(3, IsRequired = true)]
	    public List<DBIn> _params { get; set; }

        [ProtoMember(4, IsRequired = false)] 
        public byte[] options { get; set; }

        public void CopyFrom( ref ReqDB req_db )
        {
            seq = req_db.seq;
            query = req_db.query;
            _params = req_db._params;
            req_db.options.CopyTo(options, 0);
        }

    }

    [ProtoContract]
    public class AnsDB {

        [ProtoMember(1, IsRequired = true)]
	    public int seq { get; set; }

        [ProtoMember(2, IsRequired = true)]
	    public string query { get; set; }

        [ProtoMember(3, IsRequired = true)]
	    public int retCode { get; set; }

        [ProtoMember(4, IsRequired = true)]
        public byte[] result { get; set; }

        public void CopyFrom( ref AnsDB db )
        {
            //seq = db.seq;
            //query = db.query;
            //retCode = db.retCode;
            //db.result.CopyTo(result, 0);

            //read_binary. this
            
        }
    }

       

}
