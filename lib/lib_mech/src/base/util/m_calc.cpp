/* 
	filename:	m_calc.cpp
	coder	:	Cho Wook Rea (mech12@dreamwiz.com)(icq:74456993) 
	comp.	:	EmailPet 
	compiler:	vc++ 6.0
	date	:	2001-10-09¿ÀÈÄ 2:46:47
	title	:	
*/
#include "stdafx.h"
#include "m_calc.h"


namespace nMech
{
	namespace nUtil
	{

		uCalculator::uCalculator_func_t uCalculator::mf_Functab[2] = {&uCalculator::f_sum , &uCalculator::f_base};
		TCHAR *g_OPcode=TEXT(" \t~!%^&*()-=+|/");


		int uCalculator::calc()
		{	// * Parse and calculate an arithmetic expression pointed to by "line". This routine is fully re-entrant - a feature
			// * that is not currently used, but may come in handy later (for instance if a variable points to a character tstring
			// * that contains an expression to be evaluated).

			fname_t line;
			_tcscpy( line , skipWhiteSpace(m_szExp) );

			TCHAR	*savLineptr;
			int		savValbase, savValsp, savOpbase, savOpsp;

			if ( (++m_chLevel) <= iMAXLEVEL )
			{
				// * Save all global variables that may change if calc() is called recursively.
				savLineptr	= m_szLineptr;
				savValbase	= m_nValbase;
				savValsp	= m_nValsp;
				savOpbase	= m_iOpBase;
				savOpsp		= m_iOpSp;

				// * Set up stack base ptrs and input line ptr
				m_nValbase	= m_nValsp;
				m_iOpBase		= m_iOpSp;
				m_szLineptr = line;

				// Get the first token from input line and parse an expression and then evaluate it.
				m_chEol = 0;

				getoken();
				if ( !m_chEol )
				{
					expression();
					if ( m_nError <= 0 )
						m_nValue = evaluate();
				}

				// * Restore previous values of globals
				m_szLineptr = savLineptr;
				m_nValbase	= savValbase;
				m_nValsp	= savValsp;
				m_iOpBase		= savOpbase;
				m_iOpSp		= savOpsp;
			}
			--m_chLevel;

			return m_nValue;

		} //void calc( TCHAR *line )


		//----------------------------------------------------------------
		int uCalculator::evaluate()
			//----------------------------------------------------------------
		{
			/*
			* Evaluate an expression by popping operators and operands
			* from the Operator/Operand stack and performing each indicated
			* operation. Only the operators starting from current base ptr
			* (m_iOpBase) to top of stack (m_iOpSp) are evaluated, so that evaluate()
			* may be called by any generation of calc().
			*/
			//	int iOpSp, val, *ip;
			int iOpSp, val, ip;
			TCHAR op;

#define TOS (m_nValstk[m_nValsp-1])	// top of stack macro 
			for ( iOpSp=m_iOpBase; iOpSp<m_iOpSp; ++iOpSp )
			{
				op = m_Opstk[ iOpSp ].o_token;

				if ( op == T_CONST )
				{
					push( m_Opstk[ iOpSp ].o_value );
				}
				else if ( op == T_SYMBOL )
				{//* Push the address of a variable

					//push( &m_iaSymbols[ m_Opstk[ iOpSp ].o_value ] );
					push( m_iaSymbols[ m_Opstk[ iOpSp ].o_value ] );
				}
				else if ( op == T_POINT )
				{	// * Get the value of the integer pointed to by the address on top of the stack. This usually follows
					// * a T_SYMBOL when the symbol is not being used as an "lvalue".
					ip = pop();
					//push( *ip );
					push( ip );
				}
				else if ( op == T_ASSIGN )
				{
					// * Assignment operator: The item on top of stack isthe "rvalue", second on stack is the "lvalue"
					// * (an address where to store the "rvalue"). The	"rvalue" gets pushed back on top of the stack.
					val = pop();
					ip = pop();
					//push( *ip = val );
					push( ip = val );
				}
				else if ( op == T_ADD )
				{
					val = pop();
					TOS += val;
				}
				else if ( op == T_SUB )
				{
					val = pop();
					TOS -= val;
				}
				else if ( op == T_NOT )
					TOS = ~TOS;
				else if ( op == T_NEG )
					TOS = -TOS;
				else if ( op == T_MUL )
				{
					val = pop();
					TOS *= val;
				}
				else if ( op == T_DIV )
				{
					val = pop();
					TOS /= val;
				}
				else if ( op == T_MOD )
				{
					val = pop();
					TOS %= val;
				}
				else if ( op == T_SHL )
				{
					val = pop();
					TOS <<= val;
				}
				else if ( op == T_SHR )
				{
					val = pop();
					TOS >>= val;
				}
				else if ( op == T_AND )
				{
					val = pop();
					TOS &= val;
				}
				else if ( op == T_XOR )
				{
					val = pop();
					TOS ^= val;
				}
				else if ( op == T_IOR )
				{
					val = pop();
					TOS |= val;
				}
				else if ( op == T_COMMA )
					;
				else if ( op == T_FUNC )
					//push( (*mf_Functab[ m_Opstk[ iOpSp ].o_value ])() );
					//(((BaseT*)this)->*(fn))(it);
					push( (((uCalculator*)this)->*(mf_Functab[ m_Opstk[ iOpSp ].o_value ]))() );

				else
				{
					//"bad operator in stack: 0x%x (%c)", op, op );
				}
			} // for ( iOpSp=m_iOpBase; iOpSp<m_iOpSp; ++iOpSp )
			return m_nValstk[ m_nValbase ];
		}

		//----------------------------------------------------------------
		int uCalculator::op_prim( int precedence, int lvalue )
			//----------------------------------------------------------------
		{
			/*
			* Parse the <operator> <primary> part of an expression.
			* "precedence" is the PREVIOUS <operator>'s precedence level
			* (0=low, +n=high).
			*/
			TCHAR	tkn;
			int		pr, lv;

			while ( !m_chEol )
			{
				/*
				* Get the precedence level of current <operator> ("pr").
				* If it is greater than previous operator ("precedence"),
				* get the next <primary> and do another <operator> <primary>
				* NOTE: For left-to-right associativity, the condition
				*     pr > precedence
				* must be true. for right-to-left associativity,
				*     pr >= precedence
				* must be true (assignment operator only).
				*/

				pr = binop( m_chToken );

				if ((pr>precedence && pr>0) ||	(m_chToken==T_ASSIGN && pr>=precedence))
				{
					if ( m_chToken == T_ASSIGN )
					{
						if ( lvalue > 0 )
						{
							//					err( "= needs and lvalue" );
						}
					}
					else if ( lvalue < 0 )
					{
						generate( T_POINT, 0 );
					}

					/*
					* Save the operator token and do a primary.
					*/
					tkn = m_chToken;
					getoken();
					if ( ! (lv = primary()) )
					{
						//				err( "missing an operand" );
					}
					/*
					* Now look at the next operator. If its precedence
					* is greater than this one ("tkn" above), generate
					* code for it BEFORE this one.
					*/
					lvalue = op_prim( pr, lv );

					if ( m_chToken != T_ASSIGN && lvalue < 0 )
					{
						/*
						* Next operator is not the assignment op.
						* and the current <primary> is an lvalue,
						* therefore generate a "load from address
						* on top of stack" instruction.
						*/
						generate( T_POINT, 0 );
						/*
						* This makes it an rvalue now.
						*/
						lvalue = 1;
					}
					else if ( tkn!=T_ASSIGN && m_chToken==T_ASSIGN )
					{
						/*
						* YEECH! this is the only way I know of to
						* detect errors like: a+b=c
						*/
						//				err( "= needs an lvalue" );
					}

					/*
					* Generate the instruction for the current operator.
					*/
					generate( tkn, 0 );
				}
				else
				{
					break;
				}
			}

			return lvalue;
		}

		//----------------------------------------------------------------
		int uCalculator::primary()
			//----------------------------------------------------------------
		{
			/*
			* Parse a primary. Primaries have the following syntax:
			*    <primary> := <constant> |
			*                 '(' <expression> ')' |
			*                 <unary op> <primary> |
			*                 <function> <primary>
			*/
			int rtn;
			int val;

			if ( m_chEol )
				return 0;

			/*
			* Return value:
			*   -1   => the <primary> is an lvalue
			*    0   => not a <primary> (usually end of line or a syntax error)
			*    1   => the <primary> is an rvalue
			*/
			rtn = 1;

			switch ( m_chToken )
			{
			case T_SYMBOL:	/* a symbol */
				rtn = -1;
			case T_CONST:	/* a constant */
				generate( m_chToken, m_nValue );
				getoken();
				break;
			case T_LPAR:	/* a parenthesized expression */
				getoken();
				expression();
				if ( m_chToken != T_RPAR )
				{
					//			err( "missing ')'" );
					rtn = 0;
				}
				else
					getoken();
				break;
			case T_SUB:	/* unary - */
				/*
				* The lexical analyzer is not smart enough to recognize
				* unary operators (+ and -), that's why we have to do
				* it here
				*/
				getoken();
				expression();
				generate( T_NEG, 0 );
				break;
			case T_NOT:	/* unary ~ */
				getoken();
				expression();
				generate( T_NOT, 0 );
				break;
			case T_ADD:	/* unary + */
				getoken();
				expression();
				break;
			case T_FUNC:	/* built-in function */
				val = m_nValue;
				getoken();
				expression();
				generate( T_FUNC, val );
				break;
			default:
				/*
				* Not a primary
				*/
				rtn = 0;
			}
			return rtn;
		}


		//----------------------------------------------------------------
		TCHAR uCalculator::getoken()
			//----------------------------------------------------------------
		{
			/*
			* Lexical Analyzer. Gets next token from the input line
			* pointed to by "m_szLineptr" and advances "m_szLineptr" to next
			* character. If end of input line is encountered, the
			* "m_chEol" flag is set.
			*/
			TCHAR	*cp, buf[ 128 ];

			/*
			* skip white space
			*/
			m_szLineptr = skipWhiteSpace( m_szLineptr );

			if ( ! *m_szLineptr )
			{
				m_chEol		= 1;
				m_chToken	= T_EOL;
			}
			else if ( *m_szLineptr == '0' )
			{
				/*
				* Check if it's a hex or octal constant
				*/
				m_chToken = T_CONST;
				++m_szLineptr;
				if ( toupper( *m_szLineptr ) == 'X' )
				{
					++m_szLineptr;
					for ( cp = buf; isHexDigit( *m_szLineptr ); )
						*cp++ = *m_szLineptr++;
					*cp = 0;
					jt_sscanf( buf, TEXT("%x"), &m_nValue );
				}
				else if ( isdigit( *m_szLineptr ) )
				{
					for ( cp = buf; isOctDigit( *m_szLineptr ); )
						*cp++ = *m_szLineptr++;
					*cp = 0;
					jt_sscanf( buf, TEXT("%o"), &m_nValue );
				}
				else
					m_nValue = 0;
			}
			else if ( isdigit( *m_szLineptr ) )
			{
				/*
				* It's a numeric constant, TEXT("m_nValue") will be its value.
				*/
				m_chToken = T_CONST;
				for ( cp = buf; isdigit( *m_szLineptr ); )
					*cp++ = *m_szLineptr++;
				*cp = 0;
				m_nValue = _tstoi( buf );
			}
			else if ( m_nValue = isfunc( &m_szLineptr ) )
			{
				/*
				* It's a built-in function, "m_nValue" will be the index
				* into the function jump table.
				*/
				m_chToken = T_FUNC;
				--m_nValue;
			}
			else if ( m_chToken = isBinOp( &m_szLineptr ) )
			{
				/*
				* It's a binary operator
				*/
				;
			}
			else if ( isalpha( *m_szLineptr ) )
			{
				m_chToken = T_SYMBOL;
				m_nValue = toupper( *m_szLineptr ) - 'A';
				++m_szLineptr;
			}
			else
			{
				/*
				* Bad character in input line
				*/
				//		err( "bad syntax: %s", Lineptr );
				++m_szLineptr;
			}

			return m_chToken;
		}


		//----------------------------------------------------------------
		int uCalculator::isBinOp( TCHAR **cpp )
		{
			// * Check if *cpp is a binary operator, return its token value and bump *cpp to next character.
			int tkn;
			TCHAR c;

			c = **cpp;
			if ( c == ',' )
				tkn = T_COMMA;
			else if ( c == '=' )
				tkn = T_ASSIGN;
			else if ( c == '<' )
			{
				if ( *(++(*cpp)) == '<' )
					tkn = T_SHL;
			}
			else if ( c == '>' )
			{
				if ( *(++(*cpp)) == '>' )
					tkn = T_SHR;
			}
			else if ( c == '(' )
				tkn = T_LPAR;
			else if ( c == ')' )
				tkn = T_RPAR;
			else if ( c == '*' )
				tkn = T_MUL;
			else if ( c == '/' )
				tkn = T_DIV;
			else if ( c == '%' )
				tkn = T_MOD;
			else if ( c == '+' )
				tkn = T_ADD;
			else if ( c == '-' )
				tkn = T_SUB;
			else if ( c == '^' )
				tkn = T_XOR;
			else if ( c == '&' )
				tkn = T_AND;
			else if ( c == '|' )
				tkn = T_IOR;
			else if ( c == '~' )
				tkn = T_NOT;
			else
				tkn = 0;

			if ( tkn )
				++(*cpp);

			return tkn;
		} // int isBinOp( TCHAR **cpp )

	}
}

