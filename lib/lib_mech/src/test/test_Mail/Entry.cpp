#include <Windows.h>
#include <stdio.h>
#include <conio.h>

#include "SMTPClient.h"

void main()
{
	SMTPClient		smtp;
	BOOL			ret;

	ret = smtp.Connect( "extremendl.net" );
	ret = smtp.MailFrom( "Sender@extremendl.net" );
	ret = smtp.MailTo( "Receiver@extremendl.net" );
	ret = smtp.MailContents( "Nickname", "reinlainer@extremendl.net", "Subject", "Body" );
	ret = smtp.MailAttachFile( "TestFile.dat" );
	ret = smtp.MailSubmit();

	smtp.Disconnect();
}