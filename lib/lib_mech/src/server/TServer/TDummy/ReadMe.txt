/* file : ReadMe.txt
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-08 01:14:15
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "ReadMe.h"

<새로운 서버를 추가하는 방법>

: MsgServer서버는 프로토타입 서버로서 새로운 기능의 서버를 추가할때 복사하여 사용하기위한 용도이다.
	
	0. TDummy폴더를 복사하여 원하는 이름으로 변경.
	
	1. 파일명중에서 Msg를 원하는 이름으로 바꾼다.
	
	2. 파일내용중 Msg로 시작하는 글자를 원하는 이름으로 바꿈.
	
	3. stdafx.h 에서 각종 문자들을 바꿔줌 ( NIC NAME TAG)
	
	4. Z:\job_taebak\src\server\TServer\doc\sequece\TServer\ProtocalDefine.xml 에서 
		<TDummyServer>를 복사하여 원하는서버이름으로 추가.
		
		이때 종속관계확인필요.

	5. Z:\job_taebak\src\server\TServer\doc\sequece\TServer\C_01_03_MsgServer.usd를 복사하여
		원하는 서버명으로 변경 ( 내용중에서 NIC TAG도 같이 변경)

	6. Z:\job_taebak\bin\client\xml\net\TServer_NetConfig.xml를 열어서 
		<TDummyServer>관련 항목을 복사하여 원하는 서버이름으로 추가.
		
	7. z:\job_taebak\src\server\TServer\TCommonServer\TCommonServer.h에서 
	
		#define PT_MsgServer_LIB_API T_SERVER_LIB_API
		#define jxDECL_MsgServer jxDECL_NET
		#define jxDEFINE_MsgServer jxDEFINE_NET
		
		를 복사하여 변경.
		
	8. TCommonServer.vcproj에 다음 파일들을 추가.
		: 패킷생성기를 실행후 z:\job_taebak\src\server\TServer\TCommonClient\protocal폴더
		PT_Msg.xml
		PT_MsgServer_Enum.cpp
		PT_MsgServer_Enum.h
