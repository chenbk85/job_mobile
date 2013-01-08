
//////////////////////////////////////////////////////////////////////
//
//	jGame Source code (c) jGame 2001-2004
// 
//	File: Validator.h	
// 
//	History:
//	-Feb 09,2004:Created 
//
//////////////////////////////////////////////////////////////////////

#ifndef VALIDATOR_H
#define VALIDATOR_H

#if _MSC_VER > 1000
# pragma once
#endif
//////////////////////////////////////////////////////////////////////////
// Default validator implementation.
//////////////////////////////////////////////////////////////////////////
namespace nMech
{
	namespace nLOG
	{

		struct SDefaultValidator : public IValidator
		{
			jIVar *m_pv_sys_warnings;

			SDefaultValidator( jID* ) 
			{
				m_pv_sys_warnings  = jCV(SYS,sys_warnings,false,0,"Toggles printing system warnings");
			};
			virtual void Report( SValidatorRecord &record )
			{
				if (record.text)
				{
					if (record.severity == VALIDATOR_ERROR)
					{
						jERROR(_T(" %s"),record.text );
					}
					else if (record.severity == VALIDATOR_WARNING)
					{
						jWARN(_T("%s"),record.text );
					}
					else
					{
						jLOG( _T("%s"),record.text );
					}

					if ( (record.text[0] == '!')  || m_pv_sys_warnings->Get_bool())
					{
#ifdef WIN32
						tstring strMessage = record.text;
						strMessage += _T("\n---------------------------------------------\n\
Abort - terminate application\n\
Retry - continue running the application\n\
Ignore - don't show this message box any more");

						switch (::MessageBox( NULL, strMessage.c_str(), _T("jGame Warning")
							, MB_ABORTRETRYIGNORE|MB_DEFBUTTON2|MB_ICONWARNING|MB_SYSTEMMODAL ))
						{
						case IDABORT:
							GetjILog()->Error(GetCurrentThreadId(),_T("User abort requested during showing the warning box with the following message: %s")
								, record.text );
							break;
						case IDRETRY:
							break;
						case IDIGNORE:
							if(m_pv_sys_warnings)
								m_pv_sys_warnings->Set_bool(false);
							break;
						}
#endif
					}
				}
			}
		};

	}
}

#endif