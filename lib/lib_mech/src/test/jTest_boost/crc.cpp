#include <stdafx.h>
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <boost/crc.hpp>
using namespace std;
 
int main_crc()
{
       const unsigned char data[] = {
               0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39
       };
       const size_t data_len = sizeof(data)/sizeof(data[0]);
 
       // CRC-CCITT
       // | 16bit, 생성 다항식 0x1021, 초기치 0xFFFF
       // | 마지막에XOR하는 비트열 0, 출력/입력 비트 오더 MSB-First
       boost::crc_basic<16> crc1( 0x1021, 0xFFFF, 0, false, false );
       crc1.process_bytes( data, data_len );
 
       if( crc1.checksum() == 0x29B1 )
               cout << "OK" << endl;
 
       // CRC-CCITT 최적화 버젼
       boost::crc_optimal<16, 0x1021, 0xFFFF, 0, false, false> crc2;
       crc2 = for_each( data, data+data_len, crc2 );
 
       if( crc2() == 0x29B1 )
               cout << "OK" << endl;
 
       return 0;
}
