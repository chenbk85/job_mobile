/* 
filename:	jIVar.h
coder	:	Cho Hyun Min (icandoit@wemade.com) 
comp.	:	-we_jGame_made-
compiler:	vc++ 6.0
date	:	2005-02-16 ���� 2:42:30
title	:	
*/


#ifndef __jIVar_h__
#define __jIVar_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000


namespace nMech
{
	namespace nLOG{struct jILog;}
#pragma warning(disable : 4251)
#ifndef _WINDOWS_
	typedef struct tagRECT
	{
		LONG left;
		LONG top;
		LONG right;
		LONG bottom;
	} 	RECT;
#endif
	namespace nUtil
	{
		struct jMemoryChunk;
	}
	class jxVar;

	//****************************************************************
	struct jIVar
		//****************************************************************
	{
	public:
		//---------------------------------------------------------------
		// array type ����.
		//----------------------------------------------------------------

#define _for_each_data_type_jvar(_N_)\
	_N_(b_,EDbool)\
	_N_(i8_,EDint8)\
	_N_(i16_,EDint16)\
	_N_(u8_,EDuint8)\
	_N_(u16_,EDuint16)\
	_N_(i_,EDint)\
	_N_(h_,EDhex)\
	_N_(u_,EDuint)\
	_N_(f_,EDfloat)\
	_N_(x_,EDStringID)\
	_N_(i2_,EDint2)\
	_N_(i3_,EDint3)\
	_N_(i4_,EDint4)\
	_N_(rgb_,EDrgb)\
	_N_(argb_,EDargb)\
	_N_(f2_,EDvector2)\
	_N_(f3_,EDvector3)\
	_N_(f4_,EDvector4)\
	_N_(m33_,EDmatrix33)\
	_N_(m44_,EDmatrix44)


#define _for_each_ENUM_type_jvar(_N_)\
	_N_(EDataType_SIMPLE_BEGIN )\
	_N_(EDataType_SIMPLE_INT_BEGIN)\
	_N_(EDbool )  /* <b_ELEMENT>0<b_ELEMENT>  intValue()*/\
	_N_(EDint8)\
	_N_(EDint16)\
	_N_(EDuint8)\
	_N_(EDuint16)\
	_N_(EDint )/* <i_ELEMENT>23<i_ELEMENT>		intValue() */\
	_N_(EDuint )/* <u_NAME>234<U_NAME>		 uintValue() */\
	_N_(EDhex ) /* <h_NAME>0x2f32<h_NAME>		intValue() */\
	_N_(EDfloat )/* <f_name>32.32<f_name>		floatValue() */\
	_N_(EDargb) /* D3DCOLOR�� , <argb_name>255;255;255;255<argb_name> Get_ARGB() , Get_R() ,G , B , A() */\
	_N_(EDrgb ) /* RGB �� , <rgb_name>255;255;255<rgb_name>  Get_RGB() , Get_R() , Get_G() , Get_B() */\
	_N_(EDStringID) /* <x_name>skdfks<x_name>			Get_cstr(); Set_cstr("dddd") */\
	_N_(EDataType_SIMPLE_INT_END )\
	_N_(EDcstr  )/* stl tstring   */\
	/* m_Data���� EDataType���� �ڷᰡ �����.   */\
	/* <name>skdfks<name>			Get_cstr(); Set_cstr("dddd") */\
	\
	_N_(EDataType_SIMPLE_END)\
	_N_(EDataType_ARRAY_BEGIN)\
	_N_(EDataType_INT_ARRAY_BEGIN )\
	_N_(EDint2 ) /* <i2_name>23;23<i2_name>		GetInt(0) , GetInt(1) , int* pI = GetInt() */\
	_N_(EDint3 ) /* <i3_name>23;23;23<i3_name> GetInt(0) , GetInt(1) , GetInt(2) ,int* pI = GetInt() */\
	_N_(EDint4)/* <i4_name>23;23;3;23<i4_name> EDargb�� ���������� ���� �Լ��� �ٸ�. */\
	/* GetInt(0) , GetInt(1) , GetInt(2) , GetInt(3) ,int* pI = GetInt() */\
	_N_(EDataType_INT_ARRAY_END)\
	\
	_N_(EDataType_FLOAT_ARRAY_BEGIN)\
	_N_(EDvector2  ) /* float v[2]		, <v2_name>23.2; 32.5<v2_name>  GetFloat(0) , GetFloat(1) , float* pF = GetFloat() */\
	_N_(EDvector3 ) /*  float v[3] , D3DVECTOR , <v3_name>32.5;1.0;0.5<v3_name> , GetFloat(0) , GetFloat(1) , float* pF = GetFloat() */\
	_N_(EDvector4 ) /* float v[4] ,<v4_name>23;23;23;3<v4_name> */\
	_N_(EDmatrix44 ) /* float v[4*4]		, <m44_name>1;1;1;1;2;2;2;2;3;3;3;3;4;4;4;4<m44_name> ,	GetFloat(idx) */\
	_N_(EDmatrix33 ) /* float v[3*3] ,		<m33_name>2;3;23;23;23;23;23;23;3<m33_name>	,	GetFloat(idx) */\
	_N_(EDataType_FLOAT_ARRAY_END)\
	_N_(EDataType_ARRAY_END )\
	\
	_N_(EDataType_MAX)\
	_N_(ETelement)   /* m_aObj���� ETelement , ETcontents , ETcomment���� �ڷᰡ �ü� �ִ�. */\
	_N_(EElementType_MAX)

#define _for_each_simple_type_jvar(_N_) 	_N_(bool) 	_N_(int) 	_N_(float) 	_N_(uint) 	_N_(StringID) 
#define _for_each_setter_type_jvar(_N_)  _for_each_simple_type_jvar(_N_) _N_(cstr) 

#undef __JVAR_ENUM
#define __JVAR_ENUM(x)  x,
		enum EElementType
		{
			_for_each_ENUM_type_jvar(__JVAR_ENUM)
#undef __JVAR_ENUM
		};
		virtual void clear()=0;

#define JVAR_DATA_INTERFACE(X) 	virtual X Get_##X()const =0;	virtual void Set_##X(X)=0;	virtual X& X##Value()=0;
		_for_each_simple_type_jvar(JVAR_DATA_INTERFACE);
#undef  JVAR_DATA_INTERFACE


#define _InitValue_interface_j(X)		virtual jIVar* 	InitValue(X)=0;
		_for_each_setter_type_jvar(_InitValue_interface_j)
#undef _InitValue_interface_j

#define jINTERFACE_jIVar(X)\
			virtual jxVar* Base() ##X \
			virtual char& Get_c8User() ##X \
			virtual uchar& Get_i16User() ##X \
			\
			virtual cstr ToString(fname_t buf)const ##X /* �ش� �ڷ����� ��Ʈ������ ��ȯ�� buf�� ������.*/\
			\
			/* �ش� buf�� ������ �����ڷ����� �°� ��ȯ.*/\
			/* pV->GetType() == jIVar::EDint3�϶� pV->FromString("32;32;32");*/\
			virtual void FromString(cstr buf)##X \
			virtual bool IsContents(cstr sz) const##X \
			virtual void Set_cstr(cstr sz)##X \
			virtual cstr Get_cstr() const ##X \
			virtual int IsIntValue() const ##X				/* IsIntArray()�̰ų� EDint���̸� �ش� type����*/\
			virtual int IsArrayValue() const ##X 			/* Array value�̸� �ش� type�� �ƴϸ� 0�� ����.*/\
			virtual bool IsNotArrayValue() const ##X	/* IsIntSizeValue() �̰ų� EDcstr���̸� true����*/\
			virtual bool IsIntSizeValue() const ##X		/* sizeof(int)�� ���̸� true �̴�.  int , uint , float , StringID ���*/\
			virtual int IsFloatArray() const ##X			/* float [] �ڷ�.*/\
			virtual int IsIntArray() const ##X				/* int []�ڷ�*/\
			virtual bool IsStringValue()const ##X			/* string, xmlstring ,element���̸� �� ����*/\
			\
			virtual bool IsType(EElementType eType) ##X\
			virtual EElementType GetType()const ##X \
			virtual void SetType(EElementType eT)##X		/* �ش� �ڷ����� ��ȯ�� �ڽ��� ��ȯ*/\
			virtual bool IsNULL() const ##X							/* EDcstr�� ���� ���� ������� true*/\
			virtual bool IsOuterMemorySource() const ##X /* ��������Ұ� �ܺ� ������ �ּҸ� �����ϸ� true*/\
			virtual void ChangeMemorySource(void*)##X		/* ��������Ҹ� �ش� ������ �ּ�(void*)�� ����.*/\
			\
			virtual void DebugPrint(bool isInsert_CR)const ##X /* ���� ���. �ش� jIVar�� �ڷ������� �����Ͽ� ���� ����.*/\
			virtual void CopyTo(jIVar* pvDest)const ##X		/* �ڷ���������� �����Ǻ���.*/\
			virtual bool IsEqual(jIVar* pV) const##X			/* pV�� ������ ����Ÿ����. bool , int , uint , StringID�϶��� ���� �޶� ��*/\
			virtual bool IsLessThen(jIVar* pV) const##X  /* pV���� ������ �� < ����  bool , int , uint , StringID�϶��� ���� �޶� ��*/\
			\
			virtual void Lerp(jIVar* pV1 , jIVar* pV2, float fLerpRatio)##X \
			\
			virtual cstr GetTypeString() const ##X /* EElementType�� ���� Ÿ�� ��Ʈ���� �Ѱ��� */\
			\
			/* EDataType_ARRAY_BEGIN�� EDataType_ARRAY_END���̿� ���� Ÿ�Կ� ���� �ڷ����� array����� �Ѱ���*/\
			/* EDint4 -> assert( 4 == GetArraySize );*/\
			virtual int GetArraySize() const ##X \
			/*#define GetAValue(rgb)      ((BYTE)((rgb)>>24))*/\
			virtual uchar Get_A() const ##X \
			virtual uchar Get_R()const ##X \
			virtual uchar Get_G()const ##X \
			virtual uchar Get_B()const ##X \
			virtual uint	Get_ARGB()const ##X \
			virtual uint	Get_RGB()const ##X \
			\
			virtual POINT* GetPOINT()##X  /* EDint2�ڷ����� ���� POINT���� �Ѱ���*/\
			virtual RECT* GetRECT()##X  /* EDint4�� ���� RECT*�� �Ѱ���.*/\
			virtual RECT GetRect()const ##X  /*EDint4�� ���� RECT���纻�� ����*/\
			\
			/* EDataType_INT_ARRAY_BEGIN�� �ڷ����� ���� array �ּ� �Ѱ���.*/\
			virtual float& GetFloat(int i)##X \
			virtual int& GetInt(int i)##X \
			virtual int *GetIntP()##X \
			virtual float *GetFloatP()##X \
			\
			/* �ش� jIVar��ü�� ���� user data�� �����Ҽ� �ִ��� ����.*/\
			virtual bool IsUserDataOK() const ##X \
			\
			/* user data �ּҰ��� ����*/\
			virtual void SetUserData(void* pV)##X \
			virtual void* GetUserData()	const ##X \
			\
			/* ��뿹 .	pV->InitValue("23;23" , jIVar::EDint2 );*/\
			/*						pV->InitValue("asdf", jIVar::EDcstr);*/\
			virtual jIVar* 	InitValue(cstr sData , EElementType type)##X \
			virtual	void _Resize_string(size_t i) ##X \

			jINTERFACE_ABSTRACT(jIVar);
			virtual ~jIVar(){}


	}; // struct jIVar
	typedef jIVar* jIVarP;


	namespace nXML
	{
		// �Ӽ��̸��� "___"�� �����ϸ� ���Ͽ� ������ ����.
		class jxAttribute;
		//---------------------------------------------------------------
		struct jIAttribute
			//----------------------------------------------------------------
		{
		public:
			virtual ~jIAttribute(){}

			// ���� �Ӽ� ����.
			virtual jIAttribute* GetRight()=0;

			// �� �Ӽ� ����.
			virtual jIAttribute* GetLeft()=0;

			virtual nXML::jxAttribute* Base() =0;

			// �Ӽ��� jIVar��ü ����.
			virtual jIVar* GetVar()=0;
			virtual StringID GetTagID()=0;
			virtual cstr	GetTagName()=0;
			virtual bool IsName(cstr sz)=0;
			// �޸� �ڵ� ����. jIXml::FindElementByHandle()���� ���.
			virtual uint GetHandle()=0;

			virtual void Create()=0;
			virtual void Destroy()=0;

			virtual void ChangeTagName(cstr sz)=0;
		};

		struct jIAttributeList
		{
			virtual ~jIAttributeList(){}
			struct iterator // �ݺ���
			{
				jIA* _Ptr;

				iterator() {}
				iterator(jIA* _pL):_Ptr(_pL) {}

				iterator&	operator = (jIA* _pL)	{ _Ptr=_pL; return *this; }
				iterator&	operator ++()	{ _Ptr=_Ptr->GetRight();return *this; 		}
				iterator&	operator --()	{ _Ptr=_Ptr->GetLeft(); return *this; }
				iterator	operator ++(int)		
				{ 
					iterator it = *this; 
					_Ptr=_Ptr->GetRight(); 
					return it; 
				}
				iterator	operator --(int)		{ iterator it = *this; _Ptr=_Ptr->GetLeft(); return it; }
				jIA*		operator ->() const		{ return _Ptr; } // ok!
				bool		operator ! ()			{ return !_Ptr; }
				bool		operator !=(iterator it){ return (_Ptr!=it._Ptr); }
				bool		operator ==(iterator it){ return (_Ptr==it._Ptr); }
				bool		operator ==(jIA* it){ return (_Ptr==it); }
				bool		operator >=(iterator it){ return (_Ptr>=it._Ptr); }
				bool		operator <=(iterator it){ return (_Ptr<=it._Ptr); }
				operator jIA*(){ return _Ptr;		}
			};
			virtual iterator begin()=0;
			virtual iterator end()=0;
			virtual int size()=0;
			virtual void DebugPrint(bool isInsert_CR)=0;
		};
		typedef jIAttributeList jIAL;
	}


}


#define jIVar_Elment(TYPE, VAL, DEFAULT, pE) TYPE VAL=DEFAULT;jIE* _pv_##VAL = pE->Find(jS(VAL));if(_pv_##VAL)VAL=_pv_##VAL->GetVar()-> Get_##TYPE();
#define jIVar_Attribute(TYPE, VAL, DEFAULT, pE) TYPE VAL=DEFAULT;jIVar* _pv_##VAL = pE->GetAttrVar(jS(VAL));if(_pv_##VAL)VAL=_pv_##VAL-> Get_##TYPE();

#endif //__jIVar_h__
