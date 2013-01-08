/* file : ReadMe.txt
Coder : by icandoit ( mech12@nate.com)
Date : 2007-08-23 13:41:57
comp.: jgame.co.kr
title : 
desc : 

*/

*.usd파일에서 내부 문서 이름이 Skip으로 시작하면 해당 usd파일은 파싱하지않음.


//--------------------------------------------------------------------------
usd파일에서 enum형 정의 문법
//--------------------------------------------------------------------------

	<enum 프로토콜도메인명::enum형대표이름>
	enum변수[=상수값] , 설명

	예제)

		<enum GMServer::EAddAccount>
		AA_SUCCESS=0,성공 
		AA_AccountDuple,계정중복
		AA_Auth, 권한없음
		AA_Unkown,알수없는실패




#define jNOT_USE_DebugPrint_[Server명] 
	디버깅 출력용 define문


PT_[콘솔"Server_TAG"]_LIB_API 
	DLL 임포트 익스포트 define명




packetgenerator.exe net 해더파일.xml 생성Tag [TEXTEDITOR]


		<PT_REG_USER>			=---------------------- 프로토콜 정의
			<USER_ID TYPE="int32" /> ---------------  자료 정의
			<USER_NAME TYPE="CHAR" i_Length="32" />
			<AGE TYPE="DWORD" />
			<SEX TYPE="BYTE" />
			<ADDRESS TYPE="CHAR" i_Length="32" />
		</PT_REG_USER>



//--------------------------------------------------------------------------
프로토콜문서 속성 ( 프로토콜 xml문서에서)
			b_jxDEFINE 이 있고 값이 0이면 jxDEFINE문을 출력안함.
			
			i_DebugPrint속성이 있으면 그 값이 각 프로토콜의 i_DebugPrint 디펄트값이됨

				i_DebugPrint= 0이면 DebugPrint문을 출력안하는것이 디펄트.
				i_DebugPrint =1이면 프로토콜이름만 출력하는것이 디펄트.
				i_DebugPrint =2이거나 b_DebugPrint속성이 없으면 전체 출력이 디펄트.
				i_DebugPrint =3이면 패킷 read할때 무조건 출력
			

//--------------------------------------------------------------------------
프로토콜의 속성	:  USD파일에서  프로토콜정의할때 {OPTION} 다음에 위치
//--------------------------------------------------------------------------
			b_jxDEFINE 이 있고 값이 0이면 jxDEFINE문을 출력안함.
			단 프로토콜 네임스페이스에 대한 jxDEFINE출력은 DOC ROOT에 정의하면 된다.
			
			i_DebugPrint= 0이면 DebugPrint문을 출력안함.
			i_DebugPrint =1이면 프로토콜이름만 출력.
			i_DebugPrint =2이거나 b_DebugPrint속성이 없으면 전체 출력
			
				예)

				[TA_SET_TEST_ENV]

				테스트 환경세팅

				{PARAM}

				i_DummySessionCount-int16-더미클라이언트의 세션갯수
				sLoginIP-net_string32
				iLoginPort-uint32

				{OPTION}
				i_DebugPrint=2
			
			
			u_CustomNumber=1234 가 정의 되어 있으면 프로토콜번호를 1234로 강제 세팅한다.
			
			thread_name = 작업스레드명 
				해당 프로토콜은 "작업스레드명"의 스레드에서 따로 처리된다.

			
			
자료의 속성
			
			i_Length를 사용하면 배열을 의미한다.
//--------------------------------------------------------------------------



//--------------------------------------------------------------------------
TYPE에 올수 있는 자료형
//--------------------------------------------------------------------------


			bool 

			CHAR : tstring일경우 사용 
			WCHAR : wstring일 경우 사용
			tstring
			wstring
			astring

			int8 : 
			uint8 : 

			int16 : 
			uint16 :

			int32 : 
			uint32 :
			
			float


//--------------------------------------------------------------------------
// ProtocalPrototype.xml가 항상 타겟 Seucence파일 폴더 안에 있어야 한다.
// 기본 내용은 다음과 같다.
//--------------------------------------------------------------------------
<?xml version='1.0' encoding='euc-kr'?>
<PROTOCAL HEADER='NULL' VERSION='1' i_DebugPrint='2' b_jxDEFINE='1' >
	<!-- CODE에서 개행문자 지원안됨. anpersent # x 0 A ; 를 사용할것-->
	<CODE TYPE='ENUM_FILE'></CODE>
	<STRUCT_LIST>
	</STRUCT_LIST>
	<PROTOCAL_LIST>
	</PROTOCAL_LIST>
	<CODE TYPE='ENUM_FILE'>
	</CODE>
</PROTOCAL>
