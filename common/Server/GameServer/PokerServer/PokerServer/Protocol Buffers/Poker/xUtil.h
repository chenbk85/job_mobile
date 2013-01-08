/*
 *  xUtil.h
 *  iNetwork
 *
 *  Created by Kevin Ahn on 7/26/10.
 *  Copyright 2010 neowiz games. All rights reserved.
 *
 */
#ifndef XUTIL_H
#define XUTIL_H
#pragma once

#include <vector>
#include <string>
#include <string.h>
using namespace std;

template<class T>
bool LLoad(T& obj, string& sBuf)
{
	unsigned long dwOrgLen=static_cast<unsigned long>(sBuf.length());
	unsigned long dwLen=0;
	if(dwOrgLen<sizeof(unsigned long)){
		return false;
	}
	dwLen=*(unsigned long*)(sBuf.data());
	if(sBuf.length()<dwLen){
		return false;
	}
	sBuf=sBuf.substr(sizeof(unsigned long));
	if(!adl::BLoad(obj, sBuf)){
		return false;
	}
	if((sBuf.length()+dwLen)!=dwOrgLen){
		return false;
	}	
	return true;
}
template<class T>
bool LStore(string& sBuf, const T& obj)
{
	unsigned long dwPrevLen=static_cast<unsigned long>(sBuf.length());
	int nLen=0;
	if(!adl::BStore(sBuf, nLen)) return false;
	if(!adl::BStore(sBuf, obj)) return false;
	unsigned long dwNewLen=static_cast<unsigned long>(sBuf.length()) - dwPrevLen;
	memcpy((char*)(sBuf.data() + dwPrevLen), &dwNewLen, sizeof(int));

	return true;
}
/*
void unpack(const char* text, const char separator, vector<string>& words)
{
	int nLen=static_cast<int>(strlen(text));
	char* szBuf=new char[ nLen ];
	int i=0;
	int j=0;
	for(i=0, j=0; i<nLen ; i++){
		if (text[i]=='\\'){
			szBuf[j++]=text[++i];     
		}
		else if (text[i]==separator){
			szBuf[j]=0x00;
			words.push_back(szBuf);
			j=0;
		}
		else{
			szBuf[j++]=text[i];
		}
	}
	szBuf[j]=0;
	if (strlen(szBuf) >= 0){
		words.push_back(szBuf);
	}
	delete [] szBuf;
}


void pack( vector<string>& words, const char separator, string& sOutput )
{
	unsigned int nBufferSize=0;
	unsigned int nSeparatorSize=sizeof(separator);
	typename std::vector<std::string>::const_iterator it;
	for( it=words.begin(); it!=words.end(); ++it ){
		// Increase buffer size for each single word.
		nBufferSize+=static_cast<unsigned int>( (*it).length() );
		// Increase buffer size for separator
		nBufferSize+=nSeparatorSize;
	}
	// Decrease buffer size because it doesn't need to add last separator
	nBufferSize-=nSeparatorSize;
	// Increase buffer size for string terminate character.(\0)
	nBufferSize++;
	char* text=new char[ nBufferSize ];
	memset( text, 0, nBufferSize );
	for ( it=words.begin(); it!=words.end(); ++it ){
		memcpy( text , (*it).c_str(), (*it).length() ); text+=(*it).length();
		memcpy( text, &separator, nSeparatorSize );		text+=nSeparatorSize;
	}

	text-=nBufferSize;
	// Overwrite last separator with string end character.
	text[ nBufferSize - 1 ]=0x00;

	sOutput=string(text);

	delete [] text;
}
/**/
#endif
