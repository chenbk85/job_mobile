/* file : jDefine_flag.h
Coder : by icandoit ( mech12@nate.com)
Date : 2011-07-25 14:16:26
comp.: neobian.co.kr
title : 
desc : 

*/

#ifndef __jDefine_flag_header__
#define __jDefine_flag_header__
#pragma once



#define jBIT_0		0x00000001
#define jBIT_1		0x00000002
#define jBIT_2		0x00000004
#define jBIT_3		0x00000008
#define jBIT_4		0x00000010
#define jBIT_5		0x00000020
#define jBIT_6		0x00000040
#define jBIT_7		0x00000080
#define jBIT_8		0x00000100
#define jBIT_9		0x00000200
#define jBIT_10		0x00000400
#define jBIT_11		0x00000800
#define jBIT_12		0x00001000
#define jBIT_13		0x00002000
#define jBIT_14		0x00004000
#define jBIT_15		0x00008000
#define jBIT_16		0x00010000
#define jBIT_17		0x00020000
#define jBIT_18		0x00040000
#define jBIT_19		0x00080000
#define jBIT_20		0x00100000
#define jBIT_21		0x00200000
#define jBIT_22		0x00400000
#define jBIT_23		0x00800000
#define jBIT_24		0x01000000
#define jBIT_25		0x02000000
#define jBIT_26		0x04000000
#define jBIT_27		0x08000000
#define jBIT_28		0x10000000
#define jBIT_29		0x20000000
#define jBIT_30		0x40000000
#define jBIT_31		0x80000000


#define MASK_OFF			0x00000000
#define MASK_ON				0xffffffff



#define jSET_FLAG(var , bit)\
	bool GetFlag##var(){ return m_iFlag &bit; }\
	void SetFlag##var(bool is){ if(is) m_iFlag |=bit; 	else		m_iFlag &=~(bit); }

#define jFLAG_ENUM(enum_bit)\
	bool GetFlag_##enum_bit() const { return m_iFlag &enum_bit; }\
	void SetFlag_##enum_bit(bool is){ if(is) m_iFlag |=enum_bit; 	else		m_iFlag &=~(enum_bit); }


#define jFLAG_ENUM_VAL(val, enum_bit)\
	bool GetFlag_##enum_bit() const { return val &enum_bit; }\
	void SetFlag_##enum_bit(bool is){ if(is) val |=enum_bit; 	else		val &=~(enum_bit); }

namespace nMech
{
	inline int jGETFLAG(int var, int bit) { return (var & bit);}
	inline void jSETFLAG(int& var, int bit, bool is) {	if(is) var|=bit;	else var &=~bit;}

	//--------------------------------------------------------------------------
	class jFlagHelper
		//--------------------------------------------------------------------------
	{
		/*
		int m_iFlag = 0;
		bool myOldValue=jGETFLAG(m_iFlag,jBIT_12);
		bool myNewValue = true;
		jFlagHelper  flagTinyXml(m_iFlag, jBIT_12, myNewValue);
		jEQUAL(flagTinyXml.Get() , myNewValue);
		flagTinyXml.Set(false);
		jEQUAL(flagTinyXml.Get() , false);
		flagTinyXml.Reset();
		jEQUAL(flagTinyXml.Get() , myOldValue);
		*/
	private:
		int &m_iFlag;
		int m_iBit;
		bool m_bNewVal;
		bool m_bOldVal;
	public:
#pragma warning(disable : 4800)
		jFlagHelper(int& flag, int bit, bool bNewVal)	:m_iFlag(flag),m_iBit(bit), m_bNewVal(bNewVal)	
		{	
			m_bOldVal = (bool)jGETFLAG(flag, bit);
			Set();
		}
		bool Get(){ return (bool)jGETFLAG(m_iFlag,m_iBit);}
#pragma warning(default : 4800)

		~jFlagHelper(){ Reset();}
		void Set(bool is)	{		jSETFLAG(m_iFlag, m_iBit, is);}
		void Set()	{		jSETFLAG(m_iFlag, m_iBit, m_bNewVal);}
		void Reset() { jSETFLAG(m_iFlag, m_iBit, m_bOldVal);}
	};

	template<typename T>	struct jChangeHelper
	{
		T& m_TargetVar;
		T m_savedValue;
		jChangeHelper(T &oldValue,T newValue): m_TargetVar(oldValue),m_savedValue(oldValue){ m_TargetVar = newValue;}
		~jChangeHelper(){ m_TargetVar= m_savedValue; }
	};

}


#define jSET_GET(type, var) type m_##var;type Get_##var(){return m_##var;};void Set_##var(type val){m_##var=val;}


// use -> jSET_FLAG(MouseOver, jBIT_0);


#endif // __jDefine_flag_header__
