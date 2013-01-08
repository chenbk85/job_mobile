#include "stdafx.h"
#include "Crypt.h"

namespace nMech
{
	namespace nNET
	{
		namespace nUTIL
		{

			const int		C1				= 52845;
			const int		C2				= 22719;
			const int		KEY				= 72957;

			bool CCrypt::Encrypt(CCrypt::uint8_t *source, CCrypt::uint8_t *destination, CCrypt::uint32_t length)
			{
				if( !pv_UseEncryt->Get_bool() ) return true;

				uint32_t	i;
				int		Key = KEY;

				if (!source || !destination || length <= 0)
					return FALSE;

				for (i=0;i<length;i++)
				{
					destination[i] = source[i]^Key >> 8;
					Key = (destination[i] + Key) * C1 + C2;
				}

				return TRUE;
			}

			bool CCrypt::Decrypt(CCrypt::uint8_t *source, CCrypt::uint8_t *destination, CCrypt::uint32_t length)
			{
				if( !pv_UseEncryt->Get_bool() ) return true;

				uint32_t	i;
				uint8_t	PreviousBlock;
				int		Key	= KEY;

				if (!source || !destination || length <= 0)
					return FALSE;

				for (i=0;i<length;i++)
				{
					PreviousBlock = source[i];
					destination[i] = source[i]^Key >> 8;
					Key = (PreviousBlock + Key) * C1 + C2;
				}

				return TRUE;
			}

		}// nNet::nUTIL

	} //nNET
}//nMech


