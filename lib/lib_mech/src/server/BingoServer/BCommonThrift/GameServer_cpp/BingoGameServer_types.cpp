/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "BingoGameServer_types.h"

#include <algorithm>

namespace nBingo {

const char* s_X2LG_LOGIN::ascii_fingerprint = "AB879940BD15B6B25691265F7384B271";
const uint8_t s_X2LG_LOGIN::binary_fingerprint[16] = {0xAB,0x87,0x99,0x40,0xBD,0x15,0xB6,0xB2,0x56,0x91,0x26,0x5F,0x73,0x84,0xB2,0x71};

uint32_t s_X2LG_LOGIN::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->id);
          this->__isset.id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->passwd);
          this->__isset.passwd = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->info);
          this->__isset.info = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t s_X2LG_LOGIN::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("s_X2LG_LOGIN");

  xfer += oprot->writeFieldBegin("id", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->id);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("passwd", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeBinary(this->passwd);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("info", ::apache::thrift::protocol::T_STRING, 3);
  xfer += oprot->writeString(this->info);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(s_X2LG_LOGIN &a, s_X2LG_LOGIN &b) {
  using ::std::swap;
  swap(a.id, b.id);
  swap(a.passwd, b.passwd);
  swap(a.info, b.info);
  swap(a.__isset, b.__isset);
}

const char* s_LG2X_LOGIN::ascii_fingerprint = "AFAFBCDB9822F9D1AA4E44188E720B47";
const uint8_t s_LG2X_LOGIN::binary_fingerprint[16] = {0xAF,0xAF,0xBC,0xDB,0x98,0x22,0xF9,0xD1,0xAA,0x4E,0x44,0x18,0x8E,0x72,0x0B,0x47};

uint32_t s_LG2X_LOGIN::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->uid);
          this->__isset.uid = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->result);
          this->__isset.result = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t s_LG2X_LOGIN::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("s_LG2X_LOGIN");

  xfer += oprot->writeFieldBegin("uid", ::apache::thrift::protocol::T_I64, 1);
  xfer += oprot->writeI64(this->uid);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("result", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->result);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(s_LG2X_LOGIN &a, s_LG2X_LOGIN &b) {
  using ::std::swap;
  swap(a.uid, b.uid);
  swap(a.result, b.result);
  swap(a.__isset, b.__isset);
}

const char* ServerExeption::ascii_fingerprint = "3F5FC93B338687BC7235B1AB103F47B3";
const uint8_t ServerExeption::binary_fingerprint[16] = {0x3F,0x5F,0xC9,0x3B,0x33,0x86,0x87,0xBC,0x72,0x35,0xB1,0xAB,0x10,0x3F,0x47,0xB3};

uint32_t ServerExeption::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->what);
          this->__isset.what = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->why);
          this->__isset.why = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t ServerExeption::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("ServerExeption");

  xfer += oprot->writeFieldBegin("what", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->what);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("why", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->why);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(ServerExeption &a, ServerExeption &b) {
  using ::std::swap;
  swap(a.what, b.what);
  swap(a.why, b.why);
  swap(a.__isset, b.__isset);
}

} // namespace