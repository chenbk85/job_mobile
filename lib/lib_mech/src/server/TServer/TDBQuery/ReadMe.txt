<GAMEDB_CONNECTION_STRING>
Driver={SQL Server};Address=127.0.0.1,1433\sam_db;Server=;Uid=sa;Pwd=qwer;Trusted_Connection=Yes;Database=tgame_db;Network=dbmssocn
</GAMEDB_CONNECTION_STRING>


Network=
			case protoNamedPipes:_tcscat_s(szDriverString, _T("dbnmpntw"));break;
			case protoWinSock:_tcscat_s(szDriverString, _T("dbmssocn"));break;
			case protoIPX:_tcscat_s(szDriverString, _T("dbmsspxn"));break;
			case protoBanyan:_tcscat_s(szDriverString, _T("dbmsvinn"));break;
			case protoRPC:_tcscat_s(szDriverString, _T("dbmsrpcn"));break;
			default:_tcscat_s(szDriverString, _T("dbmssocn"));break;
