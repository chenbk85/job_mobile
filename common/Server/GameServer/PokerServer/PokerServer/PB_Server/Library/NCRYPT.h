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

///////// CRYPT ���̺귯�� ���� ///////////////
typedef 	unsigned	int		U32;
typedef 	  signed	int		S32;
typedef		unsigned	short	U16;
typedef		  signed	short	S16;
typedef		unsigned	char	 U8;
typedef		  signed	char	 S8;


// ���̳ʸ� ������
typedef struct BData_st{
	U32   len;
	U8  *data;
} BData;

// �����ڵ�	    
#define NC_ERR_INVALID_PARAM_NULL			0x80000001
#define NC_ERR_INVALID_PARAM_INVALIDLEN		0x80000002
#define NC_ERR_DIFF_ENDECRYPT_ALGORITHM		0x80000003
#define NC_ERR_DIFF_ENDECRYPT_KEY			0x80000004
#define NC_ERR_ENCRYPTED_MESSAGE_EDCFAIL	0x80000005
#define NC_SUCCESS							0x00000000


char*	NC_CRYPT_err_message(int errcode);


///////// RC4�� ������ ������ NRC4(Neowiz RC4)  //////////////////

// NC_NRC4_KEY
// ��/��ȣȭ�� ���� �����층�� Ű
// ��ȣ��� ���������� ����ϴ� �������̹Ƿ� 
// Application������ �� ����ü�� ����� ���� �������� �ʴ´�.
typedef struct rc4_key_struct
{
	U32 hint;
	U32 data[256];
} NC_NRC4_KEY;


//  Ű �����층.(Ű ���� ��ȯ)
//  �з����� :	key		[in]  - ����� �Է� Ű�� �����ϰ� �ִ� ���� 
//				keylen  [in]  - key ������ ����Ʈ ����. ���� Ű ���̴� 16byte�� �����ؼ� �����
//				rc4key  [out] - ��/��ȣȭ�� ���� �����층�� Ű
//	���ϰ�	 :	������ ���  0(NC_SUCCESS), ������ ��� 0 �ƴ� �����ڵ�
//  Ư�̻��� :  Ű �����층�� �� ���� �����ϵ��� �Ѵ�.
int NC_NRC4_set_key		(const U8 *key, U32 keylen, NC_NRC4_KEY *rc4key);


//  NRC4 ��ȣȭ. 
//  �з����� :	key		[in]	 - �����층 �� Ű. ���ο��� copy�� �����͸� ����ϹǷ� �����Ͱ� �ƴ� ����ü ��ü�� �ѱ�
//				in		[in]	 - �� �����͸� ��� �ִ� ���̳ʸ� ����
//				inlen	[in]	 - in ������ ����Ʈ ����
//				out		[out]	 - ��ȣ�� �����͸� ���� ���̳ʸ� ����. caller���� �޸� �Ҵ�/����
//				outlen	[in/out] - [in]  caller���� �Ҵ��� out ������ ����Ʈ ����. outlen �� inlen+10 �̻��̾�� ��.
//								 - [out] ��ȣȭ�� �������� ����Ʈ ũ��. callee���� ������ ��.
//	���ϰ�	 :	������ ���  0(NC_SUCCESS), ������ ��� 0 �ƴ� �����ڵ�
//  Ư�̻��� :	out==NULL �� ��� ��ȣȭ ���� ���� caller���� �Ҵ��ؾ��� out ���� ũ�⸸ outlen �� �����Ͽ� ����
//				[in, in+inlen), [out, out+outlen) ������ �������� �Ǵ� ���� ������ ������,
//				ȿ���� ���� in==out �� ���� ���������� ���.
int		NC_NRC4_encrypt	(NC_NRC4_KEY  key, const U8 *in, U32 inlen, U8* out, U32 *outlen);


//  NRC4 ��ȣȭ.
//  �з����� :	key		[in]	 - �����층 �� Ű. ���ο��� copy�� �����͸� ����ϹǷ� �����Ͱ� �ƴ� ����ü ��ü�� �ѱ�
//				in		[in]	 - ��ȣ�� �����͸� ��� �ִ� ���̳ʸ� ����
//				inlen	[in]	 - in ������ ����Ʈ ����
//				out		[out]	 - �� �����͸� ���� ���̳ʸ� ����. caller���� �޸� �Ҵ�/����
//				outlen	[in/out] - [in]  caller���� �Ҵ��� out ������ ����Ʈ ����. outlen �� inlen-10 �̻��̾�� ��.
//								 - [out] ��ȣȭ�� �������� ����Ʈ ũ��. callee���� ������ ��.
//	���ϰ�	 :	������ ���  0(NC_SUCCESS), ������ ��� 0 �ƴ� �����ڵ�
//  Ư�̻��� :	out==NULL �� ��� ��ȣȭ ���� ���� caller���� �Ҵ��ؾ��� out ���� ũ�⸸ outlen �� �����Ͽ� ����
//				[in, in+inlen), [out, out+outlen) ������ �������� �Ǵ� ���� ������ ������,
//				ȿ���� ���� in==out �� ���� ���������� ����Ѵ�.
int		NC_NRC4_decrypt	(NC_NRC4_KEY  key, const U8 *in, U32 inlen, U8 *out, U32 *outlen);

#ifdef __cplusplus
	}
#endif

#endif __NCRYPT_TYPE_H__