/* file : jODBC_Util.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-10-02 19:14:29
comp.: jgame.co.kr
title : 
desc : 

*/

#ifndef __jODBC_Util_header__
#define __jODBC_Util_header__
#pragma once


#define for_each_SQL_SIMPLE_TYPE(FUNC)\
	\
	FUNC(uint64, SQL_C_UBIGINT,0);\
	FUNC(uint32, SQL_C_ULONG,0);\
	FUNC(uint16, SQL_C_USHORT,0);\
	FUNC(uint8, SQL_C_UTINYINT,0);\
	\
	FUNC(int64, SQL_C_SBIGINT,0);\
	FUNC(int32, SQL_C_SLONG,0);\
	FUNC(int16, SQL_C_SSHORT,0);\
	FUNC(int8, SQL_C_STINYINT,0);\
	\
	FUNC(bool, SQL_C_BIT,0);\
	\
	FUNC(float, SQL_C_DOUBLE,0);\
	FUNC(double, SQL_C_DOUBLE,0);\


#endif // __jODBC_Util_header__
