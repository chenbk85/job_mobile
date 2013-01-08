/* file : Crypt.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-08 15:53:07
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __Crypt_header__
#define __Crypt_header__
#pragma once

namespace nMech
{
	namespace nNET
	{
		namespace nUTIL
		{
			class CCrypt
			{
			public:
				typedef unsigned char uint8_t;
				typedef unsigned int uint32_t;
				static bool Encrypt(uint8_t *source, uint8_t *destination, uint32_t length);
				static bool Decrypt(uint8_t *source, uint8_t *destination, uint32_t length);
			};

		}// nNet::nUTIL

	} //nNET
}//nMech



#endif // __Crypt_header__
