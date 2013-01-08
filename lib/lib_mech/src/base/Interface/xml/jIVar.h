/* 
filename:	jIVar.h
coder	:	Cho Hyun Min (icandoit@wemade.com) 
comp.	:	-we_jGame_made-
compiler:	vc++ 6.0
date	:	2005-02-16 오후 2:42:30
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
		// array type 관련.
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
	_N_(EDargb) /* D3DCOLOR용 , <argb_name>255;255;255;255<argb_name> Get_ARGB() , Get_R() ,G , B , A() */\
	_N_(EDrgb ) /* RGB 용 , <rgb_name>255;255;255<rgb_name>  Get_RGB() , Get_R() , Get_G() , Get_B() */\
	_N_(EDStringID) /* <x_name>skdfks<x_name>			Get_cstr(); Set_cstr("dddd") */\
	_N_(EDataType_SIMPLE_INT_END )\
	_N_(EDcstr  )/* stl tstring   */\
	/* m_Data에는 EDataType형의 자료가 저장됨.   */\
	/* <name>skdfks<name>			Get_cstr(); Set_cstr("dddd") */\
	\
	_N_(EDataType_SIMPLE_END)\
	_N_(EDataType_ARRAY_BEGIN)\
	_N_(EDataType_INT_ARRAY_BEGIN )\
	_N_(EDint2 ) /* <i2_name>23;23<i2_name>		GetInt(0) , GetInt(1) , int* pI = GetInt() */\
	_N_(EDint3 ) /* <i3_name>23;23;23<i3_name> GetInt(0) , GetInt(1) , GetInt(2) ,int* pI = GetInt() */\
	_N_(EDint4)/* <i4_name>23;23;3;23<i4_name> EDargb와 유사하지만 접근 함수가 다름. */\
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
	_N_(ETelement)   /* m_aObj에는 ETelement , ETcontents , ETcomment등의 자료가 올수 있다. */\
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
			virtual cstr ToString(fname_t buf)const ##X /* 해당 자료형을 스트링으로 변환후 buf에 값저장.*/\
			\
			/* 해당 buf의 내용을 내부자료형에 맞게 변환.*/\
			/* pV->GetType() == jIVar::EDint3일때 pV->FromString("32;32;32");*/\
			virtual void FromString(cstr buf)##X \
			virtual bool IsContents(cstr sz) const##X \
			virtual void Set_cstr(cstr sz)##X \
			virtual cstr Get_cstr() const ##X \
			virtual int IsIntValue() const ##X				/* IsIntArray()이거나 EDint형이면 해당 type리턴*/\
			virtual int IsArrayValue() const ##X 			/* Array value이면 해당 type을 아니면 0을 리턴.*/\
			virtual bool IsNotArrayValue() const ##X	/* IsIntSizeValue() 이거나 EDcstr형이면 true리턴*/\
			virtual bool IsIntSizeValue() const ##X		/* sizeof(int)인 값이면 true 이다.  int , uint , float , StringID 등등*/\
			virtual int IsFloatArray() const ##X			/* float [] 자료.*/\
			virtual int IsIntArray() const ##X				/* int []자료*/\
			virtual bool IsStringValue()const ##X			/* string, xmlstring ,element형이면 참 리턴*/\
			\
			virtual bool IsType(EElementType eType) ##X\
			virtual EElementType GetType()const ##X \
			virtual void SetType(EElementType eT)##X		/* 해당 자료형을 변환후 자신을 반환*/\
			virtual bool IsNULL() const ##X							/* EDcstr에 대해 값이 비었으면 true*/\
			virtual bool IsOuterMemorySource() const ##X /* 내부저장소가 외부 변수의 주소를 참조하면 true*/\
			virtual void ChangeMemorySource(void*)##X		/* 내부저장소를 해당 변수의 주소(void*)로 세팅.*/\
			\
			virtual void DebugPrint(bool isInsert_CR)const ##X /* 내용 출력. 해당 jIVar에 자료형까지 포함하여 내용 복사.*/\
			virtual void CopyTo(jIVar* pvDest)const ##X		/* 자료형관계없이 무조건복사.*/\
			virtual bool IsEqual(jIVar* pV) const##X			/* pV와 동일한 데이타인지. bool , int , uint , StringID일때는 형이 달라도 비교*/\
			virtual bool IsLessThen(jIVar* pV) const##X  /* pV보다 작은지 비교 < 연산  bool , int , uint , StringID일때는 형이 달라도 비교*/\
			\
			virtual void Lerp(jIVar* pV1 , jIVar* pV2, float fLerpRatio)##X \
			\
			virtual cstr GetTypeString() const ##X /* EElementType에 대한 타입 스트링을 넘겨줌 */\
			\
			/* EDataType_ARRAY_BEGIN와 EDataType_ARRAY_END사이에 속한 타입에 대해 자료형의 array사이즈를 넘겨줌*/\
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
			virtual POINT* GetPOINT()##X  /* EDint2자료형에 대해 POINT형을 넘겨줌*/\
			virtual RECT* GetRECT()##X  /* EDint4에 대해 RECT*를 넘겨줌.*/\
			virtual RECT GetRect()const ##X  /*EDint4에 대해 RECT복사본을 리턴*/\
			\
			/* EDataType_INT_ARRAY_BEGIN의 자료형에 대해 array 주소 넘겨줌.*/\
			virtual float& GetFloat(int i)##X \
			virtual int& GetInt(int i)##X \
			virtual int *GetIntP()##X \
			virtual float *GetFloatP()##X \
			\
			/* 해당 jIVar객체에 대해 user data를 세팅할수 있는지 여부.*/\
			virtual bool IsUserDataOK() const ##X \
			\
			/* user data 주소값을 세팅*/\
			virtual void SetUserData(void* pV)##X \
			virtual void* GetUserData()	const ##X \
			\
			/* 사용예 .	pV->InitValue("23;23" , jIVar::EDint2 );*/\
			/*						pV->InitValue("asdf", jIVar::EDcstr);*/\
			virtual jIVar* 	InitValue(cstr sData , EElementType type)##X \
			virtual	void _Resize_string(size_t i) ##X \

			jINTERFACE_ABSTRACT(jIVar);
			virtual ~jIVar(){}


	}; // struct jIVar
	typedef jIVar* jIVarP;


	namespace nXML
	{
		// 속성이름이 "___"로 시작하면 파일에 저장을 안함.
		class jxAttribute;
		//---------------------------------------------------------------
		struct jIAttribute
			//----------------------------------------------------------------
		{
		public:
			virtual ~jIAttribute(){}

			// 다음 속성 리턴.
			virtual jIAttribute* GetRight()=0;

			// 앞 속성 리턴.
			virtual jIAttribute* GetLeft()=0;

			virtual nXML::jxAttribute* Base() =0;

			// 속성의 jIVar객체 리턴.
			virtual jIVar* GetVar()=0;
			virtual StringID GetTagID()=0;
			virtual cstr	GetTagName()=0;
			virtual bool IsName(cstr sz)=0;
			// 메모리 핸들 리턴. jIXml::FindElementByHandle()에서 사용.
			virtual uint GetHandle()=0;

			virtual void Create()=0;
			virtual void Destroy()=0;

			virtual void ChangeTagName(cstr sz)=0;
		};

		struct jIAttributeList
		{
			virtual ~jIAttributeList(){}
			struct iterator // 반복자
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
