using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using ProtoBuf;

namespace ProtoTest
{
    // Simple model classes, with some inheritence and generics thrown in.
    [ProtoContract]
    public class MyModel
    {
        [ProtoMember(1, IsRequired = false)]
        public int int1 { get; set; }
        [ProtoMember(2)]
        public TestEnum enum1 { get; set; }

        [ProtoMember(3)]
        public List<int> intList { get; set; }
        [ProtoMember(4)]
        public List<float> floatList { get; set; }
        [ProtoMember(5)]
        public List<string> stringList { get; set; }

//         [ProtoMember(6)]
//         public List<AnotherClass> anotherClassList { get; set; }

        [ProtoMember(6)]
        //[global::System.ComponentModel.DefaultValue(1234)]
        public int int2 { get; set; }

    }

    [ProtoContract, ProtoInclude(10, typeof(DerivedClass))]
    public class AnotherClass
    {
        [ProtoMember(1)]
        public string string1 { get; set; }
    }


    [ProtoContract]
    public class DerivedClass : AnotherClass
    {
        [ProtoMember(1)]
        public float float1
        {
            get;
            set;
        }
    }

    public enum TestEnum
    {
        run,
        walk,
        skip
    }

    public class Regist_MyModel
    {
        public static ArrayList GetTypes()
        {
            ArrayList list = new ArrayList();
            list.Add(typeof(AnotherClass));
            list.Add(typeof(TestEnum));
            list.Add(typeof(MyModel));
            return list;
        }

    }

}


namespace db
{
    [global::System.Serializable, global::ProtoBuf.ProtoContract(Name = @"DBIn")]
    public partial class DBIn 
    {
        public DBIn() { }

        private DBIn.Type _type;
        [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name = @"type", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
        public DBIn.Type type
        {
            get { return _type; }
            set { _type = value; }
        }
        private string _val;
        [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name = @"val", DataFormat = global::ProtoBuf.DataFormat.Default)]
        public string val
        {
            get { return _val; }
            set { _val = value; }
        }
        [global::ProtoBuf.ProtoContract(Name = @"Type")]
        public enum Type
        {

            [global::ProtoBuf.ProtoEnum(Name = @"INT", Value = 1)]
            INT = 1,

            [global::ProtoBuf.ProtoEnum(Name = @"INT64", Value = 2)]
            INT64 = 2,

            [global::ProtoBuf.ProtoEnum(Name = @"STR", Value = 3)]
            STR = 3
        }

    }

    [global::System.Serializable, global::ProtoBuf.ProtoContract(Name = @"ReqDB")]
    public partial class ReqDB 
    {
        public ReqDB() { }

        private int _seq;
        [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name = @"seq", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
        public int seq
        {
            get { return _seq; }
            set { _seq = value; }
        }
        private string _query;
        [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name = @"query", DataFormat = global::ProtoBuf.DataFormat.Default)]
        public string query
        {
            get { return _query; }
            set { _query = value; }
        }
        private readonly global::System.Collections.Generic.List<DBIn> _params = new global::System.Collections.Generic.List<DBIn>();
        [global::ProtoBuf.ProtoMember(3, Name = @"params", DataFormat = global::ProtoBuf.DataFormat.Default)]
        public global::System.Collections.Generic.List<DBIn> @params
        {
            get { return _params; }
        }


        private byte[] _options = null;
        [global::ProtoBuf.ProtoMember(4, IsRequired = false, Name = @"options", DataFormat = global::ProtoBuf.DataFormat.Default)]
        [global::System.ComponentModel.DefaultValue(null)]
        public byte[] options
        {
            get { return _options; }
            set { _options = value; }
        }
    }

    [global::System.Serializable, global::ProtoBuf.ProtoContract(Name = @"AnsDB")]
    public partial class AnsDB 
    {
        public AnsDB() { }

        private int _seq;
        [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name = @"seq", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
        public int seq
        {
            get { return _seq; }
            set { _seq = value; }
        }
        private string _query;
        [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name = @"query", DataFormat = global::ProtoBuf.DataFormat.Default)]
        public string query
        {
            get { return _query; }
            set { _query = value; }
        }
        private int _retCode;
        [global::ProtoBuf.ProtoMember(3, IsRequired = true, Name = @"retCode", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
        public int retCode
        {
            get { return _retCode; }
            set { _retCode = value; }
        }
        private byte[] _result;
        [global::ProtoBuf.ProtoMember(4, IsRequired = true, Name = @"result", DataFormat = global::ProtoBuf.DataFormat.Default)]
        public byte[] result
        {
            get { return _result; }
            set { _result = value; }
        }

    }

}