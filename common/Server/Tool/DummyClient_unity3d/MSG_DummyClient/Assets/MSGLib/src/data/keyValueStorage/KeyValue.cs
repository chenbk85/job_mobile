/** ------------------------------------------------------------------------------ */
/**  <auto-generated> */
/**      This code was generated by a tool. */
/**  */
/**      Changes to this file may cause incorrect behavior and will be lost if */
/**      the code is regenerated. */
/**  </auto-generated> */
/** ------------------------------------------------------------------------------ */

/**  Option: light framework (CF/Silverlight) enabled */
    
/**  Generated from: keyValue.proto */
namespace MSG
{
  [global::ProtoBuf.ProtoContract(Name=@"KeyValue")]
  public partial class KeyValue : global::ProtoBuf.IExtensible
  {
    public KeyValue() {}
    
    private string _key;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"key", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string key
    {
      get { return _key; }
      set { _key = value; }
    }
    private string _value;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"value", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string value
    {
      get { return _value; }
      set { _value = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::ProtoBuf.ProtoContract(Name=@"KeyValueList")]
  public partial class KeyValueList : global::ProtoBuf.IExtensible
  {
    public KeyValueList() {}
    
    private readonly global::System.Collections.Generic.List<KeyValue> _list = new global::System.Collections.Generic.List<KeyValue>();
    [global::ProtoBuf.ProtoMember(1, Name=@"list", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<KeyValue> list
    {
      get { return _list; }
    }
  
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
}