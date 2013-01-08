/* file : protoHelper.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-03 12:06:31
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __protoHelper_header__
#define __protoHelper_header__
#pragma once


#define jMAKE_PROTO_SEND_BUFFER(iSize,buf,aos,msg)\
	char buf[MAX_BODY_LENGTH];\
	int iSize = (int)msg.ByteSize();\
	google::protobuf::io::ArrayOutputStream aos(buf, msg.ByteSize());\
	sendMsgU.SerializeToZeroCopyStream(&aos);\

#endif // __protoHelper_header__
