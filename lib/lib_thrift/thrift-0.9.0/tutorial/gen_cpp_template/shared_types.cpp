/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "shared_types.h"

#include <algorithm>

namespace shared {

const char* SharedStruct::ascii_fingerprint = "3F5FC93B338687BC7235B1AB103F47B3";
const uint8_t SharedStruct::binary_fingerprint[16] = {0x3F,0x5F,0xC9,0x3B,0x33,0x86,0x87,0xBC,0x72,0x35,0xB1,0xAB,0x10,0x3F,0x47,0xB3};

void swap(SharedStruct &a, SharedStruct &b) {
  using ::std::swap;
  swap(a.key, b.key);
  swap(a.value, b.value);
  swap(a.__isset, b.__isset);
}

} // namespace