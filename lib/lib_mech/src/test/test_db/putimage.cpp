/* file : putimage.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-08-24 01:34:51
comp.: t3.co.kr
title : 
desc : 

http://msdn.microsoft.com/en-us/library/ms811006.aspx


CREATE TABLE emp2 (name CHAR(30), age FLOAT, 
birthday DATETIME, BigBin IMAGE)



SELECT name, age, birthday, BinLen = datalength(BigBin)
FROM emp2


*/

#include "stdafx.h"
// Sample application to write SQL_LONGVARBINARY data using SQLPutData.
// Assumes DSN has table:
//  CREATE TABLE EMP2 (NAME CHAR(30), AGE FLOAT, 
//           BigBin IMAGE)
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#define MAXDSN      25
#define MAXUID      25
#define MAXAUTHSTR   25
#define MAXBUFLEN    255
#define SIZEOFTEXT   300000
HENV   henv = SQL_NULL_HENV;
HDBC   hdbc1 = SQL_NULL_HDBC;
HSTMT   hstmt1 = SQL_NULL_HSTMT;
char   logstring[MAXBUFLEN] = "";
void   ProcessLogMessages(HENV plm_henv, HDBC plm_hdbc,
						  HSTMT plm_hstmt, char *logstring);
int main_putimage()
{
	RETCODE retcode;
	UCHAR   szDSN[MAXDSN+1] = "test_db",
		szUID[MAXUID+1] = "sa",
		szAuthStr[MAXAUTHSTR+1] = "qwer";      
	// SQLBindParameter variables.
	SQLLEN cbTextSize, lbytes;
	//SQLParamData variable.
	PTR   pParmID;
	//SQLPutData variables.
	UCHAR   Data[] = 
		"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyz";
	SDWORD   cbBatch = (SDWORD)sizeof(Data)-1;
	// Allocate the ODBC environment and save handle.
	retcode = SQLAllocEnv (&henv);
	// Allocate ODBC connection and connect.
	retcode = SQLAllocConnect(henv, &hdbc1);
	retcode = SQLConnectA(hdbc1, szDSN, (SWORD)strlen((acstr)szDSN),
		szUID, (SWORD)strlen((acstr)szUID),szAuthStr,
		(SWORD)strlen((acstr)szAuthStr));
	// Print info messages returned.
	if ( (retcode != SQL_SUCCESS) &&
		(retcode != SQL_SUCCESS_WITH_INFO) ) {
			ProcessLogMessages(henv,
				hdbc1,
				hstmt1,
				"SQLConnect() Failed\n\n");
			return(9);
	}
	else {
		ProcessLogMessages(henv,
			hdbc1,
			hstmt1,
			"\nConnect Successful\n\n");
	}   
	// Allocate a statement handle.
	retcode = SQLAllocStmt(hdbc1,&hstmt1);
	// Let ODBC know total length of data to send.
	lbytes = (SDWORD)SIZEOFTEXT;
	cbTextSize = SQL_LEN_DATA_AT_EXEC(lbytes);

	// Bind the parameter.
	retcode = SQLBindParameter(hstmt1,   // hstmt
		1,         // ipar
		SQL_PARAM_INPUT,   // fParamType
		SQL_C_BINARY,      // fCType
		SQL_LONGVARBINARY,   // FSqlType
		lbytes,         // cbColDef
		0,         // ibScale
		(VOID *)1,      // rgbValue
		0,         // cbValueMax
		&cbTextSize);      // pcbValue
	if ( (retcode != SQL_SUCCESS) &&
		(retcode != SQL_SUCCESS_WITH_INFO) ) {
			ProcessLogMessages(henv, hdbc1, hstmt1,
				"SQLBindParam hstmt1 Failed\n\n");
			return(9);
	}
	retcode = SQLExecDirectA(hstmt1,
		(SQLCHAR*)"INSERT INTO EMP2 VALUES('JOHN SMITH', 27.3, ?)",
		SQL_NTS);
	if ( (retcode != SQL_SUCCESS) &&
		(retcode != SQL_SUCCESS_WITH_INFO) &&
		(retcode != SQL_NEED_DATA) ) {
			ProcessLogMessages(henv, hdbc1, hstmt1,
				"SQLExecute Failed\n\n");
			return(9);
	}
	// Get ID of parameter that needs data.
	retcode = SQLParamData(hstmt1, &pParmID);
	// If data is needed for the Data-At-Execution parameter:
	if (retcode == SQL_NEED_DATA) {
		// Send all but the final batch.
		while (lbytes > cbBatch) {
			SQLPutData(hstmt1, Data, cbBatch);
			lbytes -= cbBatch;
		}  // End while.
		// Put final batch.
		SQLPutData(hstmt1, Data, lbytes); 
	}
	else { // If not SQL_NEED_DATA, is some error.
		ProcessLogMessages(henv, hdbc1, hstmt1,
			"SQLPutData Failed\n\n");
		return(9);
	}  // end if
	// Make final SQLParamData call to signal end of data.
	retcode = SQLParamData(hstmt1, &pParmID);
	if ( (retcode != SQL_SUCCESS) &&
		(retcode != SQL_SUCCESS_WITH_INFO) &&
		(retcode != SQL_NEED_DATA) ) {
			ProcessLogMessages(henv, hdbc1, hstmt1,
				"SQLParamData Failed\n\n");
			return(9);
	}
	/* Clean up. */
	SQLFreeStmt(hstmt1, SQL_DROP);
	SQLDisconnect(hdbc1);
	SQLFreeConnect(hdbc1);
	SQLFreeEnv(henv);
	return(0);
}
void ProcessLogMessages(HENV plm_henv, HDBC plm_hdbc,
						HSTMT plm_hstmt, char *logstring)
{
	RETCODE   plm_retcode = SQL_SUCCESS;
	UCHAR   plm_szSqlState[MAXBUFLEN] = "",
		plm_szErrorMsg[MAXBUFLEN] = "";
	SDWORD   plm_pfNativeError = 0L;
	SWORD   plm_pcbErrorMsg = 0;

	printf(logstring);
	while (plm_retcode != SQL_NO_DATA_FOUND) {
		plm_retcode = SQLErrorA(plm_henv, plm_hdbc,
			plm_hstmt, plm_szSqlState,
			&plm_pfNativeError,
			plm_szErrorMsg, MAXBUFLEN - 1,
			&plm_pcbErrorMsg);
		if (plm_retcode != SQL_NO_DATA_FOUND){
			printf("szSqlState = %s\n", plm_szSqlState);
			printf("pfNativeError = %d\n",
				plm_pfNativeError);
			printf("szErrorMsg = %s\n", plm_szErrorMsg);
			printf("pcbErrorMsg = %d\n\n",
				plm_pcbErrorMsg);
		} //end if
	} // end while
}





// Sample reading SQL_LONGVARBINARY using SQLGetData.
// Tested with SQL Server 6.5 and 2.65 drivers.
// Assumes DSN has table:
//  CREATE TABLE EMP2 (NAME CHAR(30), AGE FLOAT, 
//           BigBin IMAGE)
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#define MAXDSN      25
#define MAXUID      25
#define MAXAUTHSTR   25
#define MAXBUFLEN   255
#define BUFFERSIZE   450

namespace nTEST_ODBC
{
#if 0

HENV   henv = SQL_NULL_HENV;
HDBC   hdbc1 = SQL_NULL_HDBC;
HSTMT   hstmt1 = SQL_NULL_HSTMT;
char   logstring[MAXBUFLEN] = "";
void   ProcessLogMessages(HENV plm_henv, HDBC plm_hdbc,
						  HSTMT plm_hstmt, char *logstring);
int main_putimage()
{
	RETCODE retcode;
	// Authorization strings.
	UCHAR   szDSN[MAXDSN+1] = "ab65def",
		szUID[MAXUID+1] = "sa",
		szAuthStr[MAXAUTHSTR+1] = "password";
	SWORD   cntr;
	//SQLGetData variables.
	UCHAR   Data[BUFFERSIZE];
	SDWORD   cbBatch = (SDWORD)sizeof(Data)-1;
	SDWORD   cbBinSize;
	// Clear data array.
	for(cntr = 0; cntr < BUFFERSIZE; cntr++)
		Data[cntr] = 0x00;
	// Allocate the ODBC environment and save handle.
	retcode = SQLAllocEnv (&henv);

	// Allocate ODBC connection and connect.
	retcode = SQLAllocConnect(henv, &hdbc1);
	// Make the connection, then print the information messages.
	retcode = SQLConnect(hdbc1, szDSN, (SWORD)strlen(szDSN),
		szUID, (SWORD)strlen(szUID),
		szAuthStr,
		(SWORD)strlen(szAuthStr));
	if ( (retcode != SQL_SUCCESS) &&
		(retcode != SQL_SUCCESS_WITH_INFO) ) {
			ProcessLogMessages(henv, hdbc1, hstmt1,
				"SQLConnect() Failed\n\n");
			return(9);
	}
	else {
		ProcessLogMessages(henv, hdbc1, hstmt1,
			"\nConnect Successful\n\n");
	}
	// Allocate the statement handle.
	retcode = SQLAllocStmt(hdbc1,&hstmt1);
	// Execute the SELECT statement.
	retcode = SQLExecDirect(hstmt1,
		"SELECT BigBin FROM emp2", SQL_NTS);
	if ( (retcode != SQL_SUCCESS) &&
		(retcode != SQL_SUCCESS_WITH_INFO) ) {
			ProcessLogMessages(henv, hdbc1, hstmt1,
				"SQLExecDirect hstmt1 Failed\n\n");
			return(9);
	}
	// Get first row.
	retcode = SQLFetch(hstmt1);
	if ( (retcode != SQL_SUCCESS) &&
		(retcode != SQL_SUCCESS_WITH_INFO) ) {
			ProcessLogMessages(henv, hdbc1, hstmt1,
				"SQLFetch hstmt1 Failed\n\n");
			return(9);
	}
	// Get the SQL_LONG column. CbBatch has size of data chunk
	// the buffer can handle. Call SQLGetData until
	// SQL_NO_DATA_FOUND.  cbBinSize on each call has the
	// amount of data left to transfer.
	cntr = 1;
	do {
		retcode = SQLGetData(hstmt1,   // hstmt
			1,         // ipar
			SQL_C_BINARY,      // fCType
			Data,         // rgbValue
			cbBatch,      // cbValueMax
			&cbBinSize);      // pcbValue
		printf("GetData iteration %d, pcbValue = %d\n",
			cntr++, cbBinSize);
		if ( (retcode != SQL_SUCCESS) &&
			(retcode != SQL_SUCCESS_WITH_INFO) &&
			retcode != SQL_NO_DATA_FOUND ){
				ProcessLogMessages(henv, hdbc1, hstmt1,
					"SQLGetData hstmt1 Failed\n\n");
				return(9);
		}
	} while (retcode != SQL_NO_DATA_FOUND);
	/* Clean up. */
	SQLFreeStmt(hstmt1, SQL_DROP);
	SQLDisconnect(hdbc1);
	SQLFreeConnect (hdbc1);
	SQLFreeEnv(henv);
	return(0);
}
#endif

}