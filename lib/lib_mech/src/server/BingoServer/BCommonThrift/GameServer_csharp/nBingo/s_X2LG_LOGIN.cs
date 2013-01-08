/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.IO;
using Thrift;
using Thrift.Collections;
using System.Runtime.Serialization;
using Thrift.Protocol;
using Thrift.Transport;

namespace nBingo
{

  /// <summary>
  /// const i32 INT32CONSTANT = 9853
  /// const map<string,string> MAPCONSTANT = {'hello':'world', 'goodnight':'moon'}
  /// enum Operation {
  ///   ADD = 1,
  ///   SUBTRACT = 2,
  ///   MULTIPLY = 3,
  ///   DIVIDE = 4
  /// }
  /// </summary>
  #if !SILVERLIGHT
  [Serializable]
  #endif
  public partial class s_X2LG_LOGIN : TBase
  {
    private string _id;
    private byte[] _passwd;
    private string _info;

    public string Id
    {
      get
      {
        return _id;
      }
      set
      {
        __isset.id = true;
        this._id = value;
      }
    }

    public byte[] Passwd
    {
      get
      {
        return _passwd;
      }
      set
      {
        __isset.passwd = true;
        this._passwd = value;
      }
    }

    public string Info
    {
      get
      {
        return _info;
      }
      set
      {
        __isset.info = true;
        this._info = value;
      }
    }


    public Isset __isset;
    #if !SILVERLIGHT
    [Serializable]
    #endif
    public struct Isset {
      public bool id;
      public bool passwd;
      public bool info;
    }

    public s_X2LG_LOGIN() {
    }

    public void Read (TProtocol iprot)
    {
      TField field;
      iprot.ReadStructBegin();
      while (true)
      {
        field = iprot.ReadFieldBegin();
        if (field.Type == TType.Stop) { 
          break;
        }
        switch (field.ID)
        {
          case 1:
            if (field.Type == TType.String) {
              Id = iprot.ReadString();
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          case 2:
            if (field.Type == TType.String) {
              Passwd = iprot.ReadBinary();
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          case 3:
            if (field.Type == TType.String) {
              Info = iprot.ReadString();
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          default: 
            TProtocolUtil.Skip(iprot, field.Type);
            break;
        }
        iprot.ReadFieldEnd();
      }
      iprot.ReadStructEnd();
    }

    public void Write(TProtocol oprot) {
      TStruct struc = new TStruct("s_X2LG_LOGIN");
      oprot.WriteStructBegin(struc);
      TField field = new TField();
      if (Id != null && __isset.id) {
        field.Name = "id";
        field.Type = TType.String;
        field.ID = 1;
        oprot.WriteFieldBegin(field);
        oprot.WriteString(Id);
        oprot.WriteFieldEnd();
      }
      if (Passwd != null && __isset.passwd) {
        field.Name = "passwd";
        field.Type = TType.String;
        field.ID = 2;
        oprot.WriteFieldBegin(field);
        oprot.WriteBinary(Passwd);
        oprot.WriteFieldEnd();
      }
      if (Info != null && __isset.info) {
        field.Name = "info";
        field.Type = TType.String;
        field.ID = 3;
        oprot.WriteFieldBegin(field);
        oprot.WriteString(Info);
        oprot.WriteFieldEnd();
      }
      oprot.WriteFieldStop();
      oprot.WriteStructEnd();
    }

    public override string ToString() {
      StringBuilder sb = new StringBuilder("s_X2LG_LOGIN(");
      sb.Append("Id: ");
      sb.Append(Id);
      sb.Append(",Passwd: ");
      sb.Append(Passwd);
      sb.Append(",Info: ");
      sb.Append(Info);
      sb.Append(")");
      return sb.ToString();
    }

  }

}
