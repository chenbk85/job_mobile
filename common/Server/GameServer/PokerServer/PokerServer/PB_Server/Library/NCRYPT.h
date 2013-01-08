#ifndef __NCRYPT_H__
#define __NCRYPT_H__

#ifdef __cplusplus
	extern "C" {
#endif


#ifndef _NCRYPT_LIB_BUILD_
	#ifdef _DEBUG
		#pragma comment(lib,"NCryptD.lib")	
	#else
		#pragma comment(lib,"NCrypt.lib")		
	#endif
#endif 

///////// CRYPT 라이브러리 공통 ///////////////
typedef 	unsigned	int		U32;
typedef 	  signed	int		S32;
typedef		unsigned	short	U16;
typedef		  signed	short	S16;
typedef		unsigned	char	 U8;
typedef		  signed	char	 S8;


// 바이너리 데이터
typedef struct BData_st{
	U32   len;
	U8  *data;
} BData;

// 에러코드	    
#define NC_ERR_INVALID_PARAM_NULL			0x80000001
#define NC_ERR_INVALID_PARAM_INVALIDLEN		0x80000002
#define NC_ERR_DIFF_ENDECRYPT_ALGORITHM		0x80000003
#define NC_ERR_DIFF_ENDECRYPT_KEY			0x80000004
#define NC_ERR_ENCRYPTED_MESSAGE_EDCFAIL	0x80000005
#define NC_SUCCESS							0x00000000


char*	NC_CRYPT_err_message(int errcode);


///////// RC4의 변형된 형태인 NRC4(Neowiz RC4)  //////////////////

// NC_NRC4_KEY
// 암/복호화에 사용될 스케쥴링된 키
// 암호모듈 내부적으로 사용하는 데이터이므로 
// Application에서는 이 구조체의 멤버를 직접 조작하지 않는다.
typedef struct rc4_key_struct
{
	U32 hint;
	U32 data[256];
} NC_NRC4_KEY;


//  키 스케쥴링.(키 형태 변환)
//  패러미터 :	key		[in]  - 사용자 입력 키를 저장하고 있는 버퍼 
//				keylen  [in]  - key 버퍼의 바이트 길이. 현재 키 길이는 16byte로 고정해서 사용함
//				rc4key  [out] - 암/복호화에 사용될 스케쥴링된 키
//	리턴값	 :	성공인 경우  0(NC_SUCCESS), 에러인 경우 0 아닌 에러코드
//  특이사항 :  키 스케쥴링은 한 번만 수행하도록 한다.
int NC_NRC4_set_key		(const U8 *key, U32 keylen, NC_NRC4_KEY *rc4key);


//  NRC4 암호화. 
//  패러미터 :	key		[in]	 - 스케쥴링 된 키. 내부에서 copy된 데이터를 사용하므로 포인터가 아닌 구조체 자체를 넘김
//				in		[in]	 - 평문 데이터를 담고 있는 바이너리 버퍼
//				inlen	[in]	 - in 버퍼의 바이트 길이
//				out		[out]	 - 암호문 데이터를 담을 바이너리 버퍼. caller에서 메모리 할당/해제
//				outlen	[in/out] - [in]  caller에서 할당한 out 버퍼의 바이트 길이. outlen 은 inlen+10 이상이어야 함.
//								 - [out] 암호화된 데이터의 바이트 크기. callee에서 설정해 줌.
//	리턴값	 :	성공인 경우  0(NC_SUCCESS), 에러인 경우 0 아닌 에러코드
//  특이사항 :	out==NULL 인 경우 암호화 수행 없이 caller에서 할당해야할 out 버퍼 크기만 outlen 에 설정하여 리턴
//				[in, in+inlen), [out, out+outlen) 구간이 오버레핑 되는 경우는 허용되지 않으나,
//				효율을 위해 in==out 인 경우는 예외적으로 허용.
int		NC_NRC4_encrypt	(NC_NRC4_KEY  key, const U8 *in, U32 inlen, U8* out, U32 *outlen);


//  NRC4 복호화.
//  패러미터 :	key		[in]	 - 스케쥴링 된 키. 내부에서 copy된 데이터를 사용하므로 포인터가 아닌 구조체 자체를 넘김
//				in		[in]	 - 암호문 데이터를 담고 있는 바이너리 버퍼
//				inlen	[in]	 - in 버퍼의 바이트 길이
//				out		[out]	 - 평문 데이터를 담을 바이너리 버퍼. caller에서 메모리 할당/해제
//				outlen	[in/out] - [in]  caller에서 할당한 out 버퍼의 바이트 길이. outlen 은 inlen-10 이상이어야 함.
//								 - [out] 복호화된 데이터의 바이트 크기. callee에서 설정해 줌.
//	리턴값	 :	성공인 경우  0(NC_SUCCESS), 실패인 경우 0 아닌 에러코드
//  특이사항 :	out==NULL 인 경우 복호화 수행 없이 caller에서 할당해야할 out 버퍼 크기만 outlen 에 설정하여 리턴
//				[in, in+inlen), [out, out+outlen) 구간이 오버레핑 되는 경우는 허용되지 않으나,
//				효율을 위해 in==out 인 경우는 예외적으로 허용한다.
int		NC_NRC4_decrypt	(NC_NRC4_KEY  key, const U8 *in, U32 inlen, U8 *out, U32 *outlen);

#ifdef __cplusplus
	}
#endif

#endif __NCRYPT_TYPE_H__