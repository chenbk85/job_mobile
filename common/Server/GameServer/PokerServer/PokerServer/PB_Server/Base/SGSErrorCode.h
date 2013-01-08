#ifndef _SGSERRORCODE_H_
#define _SGSERRORCODE_H_

///////////////////////////////////////////////////////////////////////////////
// ErrorCode
//		0xABCD EFGH
//		  A				- OK / Error
//		   B			- Error Location
//		    CD			- Reserved (not using)
//			   EFGH		- Error Code
///////////////////////////////////////////////////////////////////////////////

#define SGS_S_OK					0x00000000
#define SGS_E_FAIL					0x80000000

// Error Location
#define SGS_E_CHANNEL				0x01000000
#define SGS_E_ROOM					0x02000000

// Channel Error
#define SGS_E_CHANNEL_ERROR			(0x00000001 | SGS_E_FAIL | SGS_E_CHANNEL)
#define SGS_E_CHANNEL_NOTFOUND		(0x00000002 | SGS_E_FAIL | SGS_E_CHANNEL)
#define SGS_E_CHANNEL_DBERROR		(0x00000003 | SGS_E_FAIL | SGS_E_CHANNEL)
#define SGS_E_CHANNEL_INVALID_MSG	(0x00000004 | SGS_E_FAIL | SGS_E_CHANNEL)
#define SGS_E_CHANNEL_AUTH_FAIL		(0x00000005 | SGS_E_FAIL | SGS_E_CHANNEL)
#define SGS_E_CHANNEL_NOT_QUALIFIED	(0x00000006 | SGS_E_FAIL | SGS_E_CHANNEL)
#define SGS_E_CHANNEL_DUPLICATED	(0x00000007 | SGS_E_FAIL | SGS_E_CHANNEL)

// Room Error
#define SGS_E_ROOM_ERROR			(0x00000001 | SGS_E_FAIL | SGS_E_ROOM)
#define SGS_E_ROOM_NOTFOUND			(0x00000002 | SGS_E_FAIL | SGS_E_ROOM)
#define SGS_E_ROOM_DBERROR			(0x00000003 | SGS_E_FAIL | SGS_E_ROOM)
#define SGS_E_ROOM_INVALID_MSG		(0x00000004 | SGS_E_FAIL | SGS_E_ROOM)
#define SGS_E_ROOM_DUPLICATED		(0x00000005 | SGS_E_FAIL | SGS_E_ROOM)
#define SGS_E_ROOM_FULL				(0x00000006 | SGS_E_FAIL | SGS_E_ROOM)
#define SGS_E_ROOM_BLACKLIST		(0x00000007 | SGS_E_FAIL | SGS_E_ROOM)

// Util
#define SGS_IS_ERROR(code)			(0x80000000 == (0x80000000 & code))
#define SGS_GET_ERROR_LOC(code)		(0x0F000000 & code)

// 신고관련 Error
enum ERROR_ACCUSE
{
	ERR_ACCUSE_SUCCESS			= 0,
	ERR_ACCUSE_DUPLICATE		= 1, 
	ERR_ACCUSE_NOCHATDATA, 
	ERR_ACCUSE_NOTEXISTROOM,
	ERR_ACCUSE_SYSTEM			= 9,
};

// SGRC Error
#define SGRC_S_OK					0
#define SGRC_E_ROOM_FULL			-1
#define SGRC_E_BLACKLIST			-2
#define SGRC_E_DUPLICATED			-3

#endif // _SGSERRORCODE_H_
