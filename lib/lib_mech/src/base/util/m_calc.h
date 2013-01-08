/* 
	filename:	m_calc.h
	coder	:	Cho Wook Rea (mech12@dreamwiz.com)(icq:74456993) 
	comp.	:	EmailPet 
	compiler:	vc++ 6.0
	date	:	2001-10-08오후 7:13:18
	title	:	

		Calculator program - 9 May 1985
		Please send corrections or remarks to:
			Bob Brodt
			34 Mehrhof Rd.
			Little Ferry, NJ 07643
			(201)-641-9582

		This is a simple integer arithmetic calculator program. It uses infix
		notation, i.e. 1+2*3 as opposed to "reverse polish" notation: 1 2 3 * +.

		CONSTANTS:
			Numbers may be input as in C using 0x notation for hex, and a
			leading zero for octal, everything else is assumed to be decimal.
		VARIABLES:
			Also available are 26 registers referenced by a single letter
			(a-z or A-Z, case is ignored).
		OPERATORS:
			The following operators are supported (from highest precedence to
			lowest):

			( )		associativity
			~		one's complement
			* / %		mutliply, divide and modulo
			+ -		unary and binary add & subtract
			<< >>		shift left and right
			&		bitwise AND
			^		bitwise exclusive OR
			|		bitwise inclusive OR
			=		assignment
			,		comma - seperates function arguments

			All operators associate from left to right with the exception of
			the assignment (=) operator.
		FUNCTIONS:
			The calculator also has built-in function capabilties which may be
			enhanced later:
			base n  - set the output conversion base to n (n = 8, 10 or 16)
		ADDITIONAL FEATURES:
			help - displays a help screen containing the above information.
			? - displays all of the variables and their current values.


#include "calc.h"


UINT CalcProbability(int nRoom)
{
	TCHAR	line[1024];
	TCHAR*	szExp;
	CString	strExp;
	UINT	Ret = 0;

	uCalculator calc("10 + (x * 2)");

	CString strUsers;
	calc.Replace("x" , 24);
	calc.skipWhiteSpace();
	calc.calc( szExp );
	return calc.GetValue(); // 계산 결과.
}


#include "calc.h"

void main(int argc , TCHAR** argv)
{

	uCalculator cal("x + 2*yy + x *2 + 1");
	cal.Replace("x" , 2);
	cal.Replace("yy" , 3);

	int ret = cal.calc();
}

*/

#ifndef __m_calc_h__
#define __m_calc_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000

/*
 * Tokens
 */
#define T_EOL		TEXT(';')
#define T_CONST		TEXT('C')
#define T_SYMBOL	TEXT('S')
#define T_LPAR		TEXT('(')
#define T_RPAR		TEXT(')')
#define T_COMMA		TEXT(',')
#define T_ASSIGN	TEXT('=')
#define T_POINT		TEXT('$')
#define T_MUL		TEXT('*')
#define T_DIV		TEXT('/')
#define T_MOD		TEXT('%')
#define T_ADD		TEXT('+')
#define T_SUB		TEXT('-')
#define T_NEG		TEXT('_')
#define T_NOT		TEXT('~')
#define T_SHL		TEXT('L')
#define T_SHR		TEXT('R')
#define T_AND		TEXT('&')
#define T_XOR		TEXT('^')
#define T_IOR		TEXT('|')
#define T_FUNC		TEXT('F')

namespace nMech
{
	using namespace std;
	namespace nUtil
	{

		const int iSTAKSZ = 128;
		const int iMAXLEVEL =32;

		extern TCHAR *g_OPcode;
		//----------------------------------------------------------------
		class JUTIL_API  uCalculator
			//----------------------------------------------------------------
		{

			//----------------------------------------------------------------
		private:
			//----------------------------------------------------------------
			typedef int (uCalculator::*uCalculator_func_t)();
			static uCalculator_func_t mf_Functab[2];
			// * Built-in Functions and jump table
			//----------------------------------------------------------------
			int uCalculator::evaluate();
			int push( int val )
			{
				if ( m_nValsp >= iSTAKSZ )
				{
					//err( "stack overflow" );
				}
				return m_nValstk[ m_nValsp++ ] = val;
			}

			//----------------------------------------------------------------
			int pop()
			{
				if ( --m_nValsp < 0 )
					m_nValsp = 0;
				return m_nValstk[ m_nValsp ];
			}

			//----------------------------------------------------------------
			//                   EXPRESSION PARSER                        *
			//----------------------------------------------------------------
			void expression()
			{
				/*
				* Parse an expression. Expressions have the following syntax:
				*    <expression> := <primary> <operator> <primary>
				* so the first thing to look for is a primary.
				*/
				int lvalue;

				if ( !(lvalue = primary()) )
				{
					//		err( "bad expression" );
				}
				else if ( m_chEol )
				{
					if ( lvalue < 0 )
						generate( T_POINT, 0 );
				}
				else
				{
					op_prim( 0, lvalue );
				}
			}

			/* precedence of current <operator> */
			/* type of current <primary>: -1 => lvalue */
			/*                             0 => no <primary> (error) */
			/*                             1 => rvalue */
			int op_prim( int precedence, int lvalue );

			int uCalculator::primary();

			int binop( TCHAR op )
			{
				/*
				* Determine if "op" is a binary operator and return its
				* precedence level if so. If not, return 0.
				*/
				switch ( op )
				{
				case T_COMMA:
					return 1;
				case T_ASSIGN:
					return 2;
				case T_IOR:
					return 3;
				case T_XOR:
					return 4;
				case T_AND:
					return 5;
				case T_SHL:
				case T_SHR:
					return 6;
				case T_ADD:
				case T_SUB:
					return 7;
				case T_MUL:
				case T_DIV:
				case T_MOD:
					return 8;
				case T_NOT:
					return 9;
				}
				return 0;
			}

			//----------------------------------------------------------------
			void generate( TCHAR tkn, int val )
			{
				// * Push the given token and value onto the Operator/Operand stack.
				if ( m_iOpSp < iSTAKSZ )
				{
					m_Opstk[ m_iOpSp ].o_token = tkn;
					m_Opstk[ m_iOpSp ].o_value = val;
					++m_iOpSp;
				}
				else
				{
					//		err( "expression too complex" );
				}
			}

			// *                     LEXICAL ANALYZER                       *
			TCHAR uCalculator::getoken();

			int uCalculator::isBinOp( TCHAR **cpp );

			// *                   BUILT-IN FUNCTIONS                       *
			int f_sum()
			{
				/*
				* usage: sum( a, b )
				*    Sum all the numbers between a and b
				*/
				int i, a, b;

				b = pop();
				a = pop();
				for ( i=a+1; i<=b; ++i )
					a += i;

				return push( a );
			}

			int f_base()
			{
				/*
				* usage: base( n )
				*    Set output number base
				*/
				switch ( pop() )
				{
				case 8:
					m_szOfmt = TEXT("0%o");
					break;
				case 16:
					m_szOfmt = TEXT("0x%x");
					break;
				case 10:
				default:
					m_szOfmt = TEXT("%d");
					break;
				}

				return 0;
			}


			// *                       MISCELLANEOUS                        *
			int isHexDigit( TCHAR c )	{		return	isInString( c, TEXT("0123456789abcdefABCDEF") );	}
			int isOctDigit( TCHAR c )	{		return isInString( c, TEXT("01234567") );	}
			bool isInString( TCHAR c, TCHAR *s )
			{
				while ( *s ) 
					if ( c == *s++ )
						return true;

				return false;
			}

			//----------------------------------------------------------------
			int isfunc( TCHAR **cpp )
			{
				// * Check if *cpp is the name of a built-function, return the
				// * function jump table index+1 if so and bump *cpp to next
				// * character. Return 0 if not a function.
				TCHAR *cp, *bp, buf[ 80 ];
				int funcno;

				// * copy the name from input line buffer to a local buffer so
				// * we can use it to make a proper comparison to function names.
				// *
				for ( cp=*cpp, bp=buf; isalpha( *cp ); )
					*bp++ = *cp++;

				*bp = 0;

				// * compare it to all of the function names we know about.
				if ( _tcscmp( buf, TEXT("sum") ) == 0 )
					funcno = 1;
				else if ( _tcscmp( buf, TEXT("base") ) == 0 )
					funcno = 2;
				else			// * not a built-in function
					funcno = 0;

				if ( funcno )
					*cpp = cp;

				return funcno;
			} // int isfunc( TCHAR **cpp )

			//----------------------------------------------------------------
			TCHAR* skipWhiteSpace( TCHAR *cp )
			{
				while ( *cp==TEXT(' ') || *cp==TEXT('\t') )	++cp;
				return cp;
			} //TCHAR* skipWhiteSpace( TCHAR *cp )

			//----------------------------------------------------------------
		public:
			//----------------------------------------------------------------
			struct 
			{// Operator/Operand stack, base ptr and top of stack ptr
				TCHAR	o_token;
				int		o_value;
			} m_Opstk[ iSTAKSZ ];

			int m_iOpBase, m_iOpSp;
			fname_t m_szExp;// 수식.

			typedef jvector<tstring>::iterator iterator;
#pragma warning(disable : 4251)
			jvector<tstring> m_aExp;
#pragma warning(default : 4251)

			// * Symbol Table
			int m_iaSymbols[ 26 ];

			//  Miscellaneous
			TCHAR	m_chLevel;	// * current recursion level in calc() 
			TCHAR	m_chToken;	// * current input token 
			TCHAR	m_chEol;	// * set when end of line encountered 
			int		m_nValue;	// * and its value 
			TCHAR*	m_szLineptr;	// * points to next character in input line 
			TCHAR*	m_szOfmt;	// * current output format (set by "base" command) 
			int		m_nError;	// * set if parsing error occurred 

			// * m_nValue (working) stack, base ptr and top of stack ptr
			int		m_nValstk[ iSTAKSZ ];
			int		m_nValbase, m_nValsp;

			//----------------------------------------------------------------
		public:
			//----------------------------------------------------------------
			uCalculator()
			{
				Init();
			}
			//----------------------------------------------------------------
			uCalculator(cstr sz)
			{
				Init();
				Set(sz);
			}

			void Init()
			{
				memset(this , 0, sizeof(*this) );
				push( 10 );
				f_base();
			}
			void Set(cstr sz)	
			{ 		
				jt_strcpy_s(m_szExp , sz);	
				nString::jSplit(sz , g_OPcode , m_aExp);
			}


			//----------------------------------------------------------------
			// *                 EXPRESSION EVALUATOR                       *
			int calc();
			void Replace(cstr sz , int val)
			{
				m_szExp;
				TCHAR buf[1024];
				fname_t szVal ;
				jt_sprintf_s(szVal , TEXT("%d"), val);
				int sLen  = (int)_tcslen(sz);
				int dLen	= (int)_tcslen(szVal);
				TCHAR* s = m_szExp;
				TCHAR* sp = jt_strstr( m_szExp , sz);
				TCHAR* dp= buf;

				while(sp)
				{
					int i = sp - s;
					jt_strncpy( dp, s , i);
					dp[i]=0;
					s=sp+sLen;
					dp+=i;
					jt_strcpy( dp, szVal );
					dp+=dLen;
					sp = jt_strstr(s , sz);
				}
				if(*s)
				{
					jt_strcpy(dp ,s);
				}
				jt_strcpy_s(m_szExp , buf);
			}

		};//struct uCalculator

	}
}

#endif //__m_calc_h__
