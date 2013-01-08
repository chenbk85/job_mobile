// squirrelWrapper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>
#include <stdio.h>
#include <squirrel.h>
#include <stdarg.h>
#include "Squirrelator.h"
//#include "testy.h"
/////////////////////////////////////////////////////////////////////
//TEST CLASS
class Testy 
{
public:
	DECLARE_SCRIPTABLE(Testy);
	Testy(){number = 0; }
	virtual ~Testy(){}
private:	
	int setnumber(HSQUIRRELVM v);
	int getnumber(HSQUIRRELVM v);
	int number;
};

int Testy::setnumber(HSQUIRRELVM v)
{
	//the param index is 2 because the index 1 is the 'this'
	sq_getinteger(v,2,&number);
	return 0;
}

int Testy::getnumber(HSQUIRRELVM v)
{
	sq_pushinteger(v,number);
	return 1;
}

BEGIN_FUNCTIONS_MAP(Testy)
	FUNCTION_ENTRY(Testy,getnumber)
	FUNCTION_ENTRY(Testy,setnumber)
END_FUNCTIONS_MAP()



/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

SQInteger file_lexfeedASCII(SQUserPointer file)
{
	int ret;
	char c;
	if( ( ret=fread(&c,sizeof(c),1,(FILE *)file )>0) )
		return c;
	return 0;
}

void PrintCallStack(HSQUIRRELVM v)
{
	SQStackInfos si;
	SQInteger i;
	SQFloat f;
	const SQChar *s;
	int level=1; //1 is to skip this function that is level 0
	const SQChar *name=NULL; 
	int seq=0;
	fprintf(stderr,"\nCALLSTACK\n");
	while(sq_stackinfos(v,level,&si))
	{
		const SQChar *fn="unknown";
		const SQChar *src="unknown";
		if(si.funcname)fn=si.funcname;
		if(si.source)src=si.source;
		fprintf(stderr,"*FUNCTION [%s] %s line [%d]\n",fn,src,si.line);
		level++;
	}
	level=0;
	fprintf(stderr,"\nLOCALS\n");
	
	for(level=0;level<10;level++){
		seq=0;
		while(name=sq_getlocal(v,level,seq))
		{
			seq++;
			switch(sq_gettype(v,-1))
			{
			case OT_NULL:
				fprintf(stderr,"[%s] NULL\n",name);
				break;
			case OT_INTEGER:
				sq_getinteger(v,-1,&i);
				fprintf(stderr,"[%s] %d\n",name,i);
				break;
			case OT_FLOAT:
				sq_getfloat(v,-1,&f);
				fprintf(stderr,"[%s] %.14g\n",name,f);
				break;
			case OT_USERPOINTER:
				fprintf(stderr,"[%s] USERPOINTER\n",name);
				break;
			case OT_STRING:
				sq_getstring(v,-1,&s);
				fprintf(stderr,"[%s] \"%s\"\n",name,s);
				break;
			case OT_TABLE:
				fprintf(stderr,"[%s] TABLE\n",name);
				break;
			case OT_ARRAY:
				fprintf(stderr,"[%s] ARRAY\n",name);
				break;
			case OT_CLOSURE:
				fprintf(stderr,"[%s] CLOSURE\n",name);
				break;
			case OT_NATIVECLOSURE:
				fprintf(stderr,"[%s] NATIVECLOSURE\n",name);
				break;
			case OT_USERDATA:
				fprintf(stderr,"[%s] USERDATA\n",name);
				break;
			}
			sq_pop(v,1);
		}
	}
}


int CompileScript(HSQUIRRELVM v,SQLEXREADFUNC read,SQUserPointer p,const SQChar *sourcename,int bprinterror)
{
	int ret=-1;
	if(SQ_SUCCEEDED(sq_compile(v,read,p,sourcename,bprinterror))){
		ret=1;
	}
	return ret;
}

int CompileScriptFromFile(HSQUIRRELVM v,const char *filename,int bprinterror)
{
	FILE *file=fopen(filename,"rb");
	if(file){
		if(CompileScript(v,file_lexfeedASCII,file,filename,bprinterror)>0){
			fclose(file);
			return 1;
		}
		fclose(file);
		return 0;
	}
	return sq_throwerror(v,"(dofile)cannot open the file");
}

int printerror(HSQUIRRELVM v)
{
	const char *sErr=NULL;
	if(sq_gettop(v)>=1){
		if(SQ_SUCCEEDED(sq_getstring(v,2,&sErr)))	{
			fprintf(stderr,"\nAN ERROR HAS OCCURED [%s]\n",sErr);
		}
		else{
			fprintf(stderr,"\nAN ERROR HAS OCCURED [unknown]\n");
		}
		PrintCallStack(v);
	}
	return 0;
}

void printfunc(HSQUIRRELVM v,const SQChar *s,...)
{
	va_list vl;
	va_start(vl, s);
	vprintf( s, vl);
	va_end(vl);
}


int main(int argc, char* argv[])
{
	const SQChar *filename=NULL;
	HSQUIRRELVM v=sq_open(1024);

	sq_setprintfunc(v,printfunc);
	sq_pushroottable(v);
	//register the class
	Squirrelator<Testy>::Register(v,"Testy");

	if(argc>1)
		filename=argv[1];
	//
	sq_newclosure(v,printerror,0);
	sq_seterrorhandler(v);
	if(filename && CompileScriptFromFile(v,filename,1)>0){
		sq_pushroottable(v);
		sq_call(v,1,1,SQTrue);
	}

	sq_close(v);
	
	return 0;
}

