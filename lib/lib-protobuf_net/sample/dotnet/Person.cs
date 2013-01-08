
    // Generated from 
    namespace tutorial
    {
      
    [System.Serializable, ProtoBuf.ProtoContract(Name=@"Person")]
    
    public partial class Person : ProtoBuf.IExtensible
    
    {
      public Person() {}
      
      
    private string _name;

    [ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"name", DataFormat = ProtoBuf.DataFormat.Default)]
    
    public string name
    {
      get { return _name; }
      set { _name = value; }
    }
    
    private int _id;

    [ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"id", DataFormat = ProtoBuf.DataFormat.TwosComplement)]
    
    public int id
    {
      get { return _id; }
      set { _id = value; }
    }
    
    private string _email = "";

    [ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"email", DataFormat = ProtoBuf.DataFormat.Default)]
    [System.ComponentModel.DefaultValue("")]
    
    public string email
    {
      get { return _email; }
      set { _email = value; }
    }
    
    private readonly System.Collections.Generic.List<tutorial.Person.PhoneNumber> _phone = new System.Collections.Generic.List<tutorial.Person.PhoneNumber>();

    [ProtoBuf.ProtoMember(4, Name=@"phone", DataFormat = ProtoBuf.DataFormat.Default)]
    
    public System.Collections.Generic.List<tutorial.Person.PhoneNumber> phone
    {
      get { return _phone; }
      
    }
  
    [System.Serializable, ProtoBuf.ProtoContract(Name=@"PhoneNumber")]
    
    public partial class PhoneNumber : ProtoBuf.IExtensible
    
    {
      public PhoneNumber() {}
      
      
    private string _number;

    [ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"number", DataFormat = ProtoBuf.DataFormat.Default)]
    
    public string number
    {
      get { return _number; }
      set { _number = value; }
    }
    
    private tutorial.Person.PhoneType _type = tutorial.Person.PhoneType.HOME;

    [ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"type", DataFormat = ProtoBuf.DataFormat.TwosComplement)]
    [System.ComponentModel.DefaultValue(tutorial.Person.PhoneType.HOME)]
    
    public tutorial.Person.PhoneType type
    {
      get { return _type; }
      set { _type = value; }
    }
    
      private ProtoBuf.IExtension extensionObject;
      ProtoBuf.IExtension ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
        { return ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
    }
  
    public enum PhoneType
    {
      MOBILE = 0,
    HOME = 1,
    WORK = 2
    }
  
      private ProtoBuf.IExtension extensionObject;
      ProtoBuf.IExtension ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
        { return ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
    }
  
    }
  