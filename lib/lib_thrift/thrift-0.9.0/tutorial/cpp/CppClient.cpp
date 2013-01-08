/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#include <intrin.h>
#pragma intrinsic(__rdtsc)
#define RDTSC() __rdtsc();


#include <stdio.h>
#include <conio.h>
//#include <unistd.h>
//#include <sys/time.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "../gen-cpp/Calculator.h"


using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace boost;

using namespace tutorial;
using namespace shared;

template<typename T>
string thrift_pack(IN const T& sendData)
{
	boost::shared_ptr<TTransport> sendTransport(new TMemoryBuffer());
	boost::shared_ptr<TProtocol> sendProtocal(new TBinaryProtocol(sendTransport));
	sendData.write(sendProtocal.get());
	return ((TMemoryBuffer*)sendTransport.get())->getBufferAsString();
}

template<typename T>
void thrift_unpack(OUT T* recvData , IN const string &recvBuffer)
{
	boost::shared_ptr<TTransport> recvTransport(new TMemoryBuffer((uint8_t*)&recvBuffer[0],recvBuffer.size()));
	boost::shared_ptr<TProtocol> recvProtocal(new TBinaryProtocol(recvTransport));
	recvData->read(recvProtocal.get());
}


int main(int argc, char** argv) {

	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);	// 2.2 버전을 로드합니다.


#if 0 // non blocking sample.
	{
		shared_ptr<TMemoryBuffer> buf(new TMemoryBuffer);
		shared_ptr<MyClient> cl(new MyClient(shared_ptr<TProtocol>(new 
			TBinaryProtocol(buf)));
		cl->send_foo(args);
		uint8_t* bytes;
		uint32_t nbytes;
		buf->getBuffer(&bytes, &nbytes);
		// stash buf and cl somewhere.
		// ship nbytes of bytes off to the server
		// get the server's response
		buf->resetBuffer(response, response_len);
		int ret = cl->recv_foo();
	}
#endif
	void test_VersionTest();
	test_VersionTest();

	{
		tutorial::Work sendWork;
		sendWork.num1 =111;
		sendWork.num2 = 222;
		sendWork.op = tutorial::Operation::ADD;
		sendWork.comment="test";

		string sendBuffer = thrift_pack(sendWork);

		tutorial::Work recvWork;
		thrift_unpack( OUT &recvWork , IN sendBuffer );

		assert(recvWork==sendWork);

	}
#if 1
	void run_client_thread();
	run_client_thread();

#else
	void run_client_cassandra();
	run_client_cassandra();

#endif

	_getch();


}

void run_client_thread()
{
	void run_client();
	for(int i=0; i< 1 ; ++i)
	{
		boost::thread *workerThread = new boost::thread(run_client);  
	}
}
void run_client()
{

  boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  CalculatorClient client(protocol);

	int64_t begin=0;
	int64_t end=0;
	begin = RDTSC();
	DWORD tBegin  = timeGetTime();
	int tot = 1;
	transport->open();
  try {
		for(int i=0; i< tot ;i)
		{

			client.ping();
			printf("ping()\n");

			int32_t sum = client.add(1,1);
			printf("1+1=%d\n", sum);

			Work work;
			work.op = Operation::DIVIDE;
			work.num1 = 1;
			work.num2 = 0;

			try {
				int32_t quotient = client.calculate(1, work);
				printf("Whoa? We can divide by zero!\n");
			} catch (InvalidOperation &io) {
				printf("InvalidOperation: %s\n", io.why.c_str());
			}

			work.op = Operation::SUBTRACT;
			work.num1 = 15;
			work.num2 = 10;
			int32_t diff = client.calculate(1, work);
			static int s_i=0;
			printf("%d , 15-10=%d\n", s_i++, diff);

			// Note that C++ uses return by reference for complex types to avoid
			// costly copy construction
	//     SharedStruct ss;
	//     client.getStruct(ss, 1);
	//     printf("Check log: %s\n", ss.value.c_str());
			Sleep(100);

		}
		transport->close();
  } catch (TException &tx) {
    printf("ERROR: %s\n", tx.what());
  }

	DWORD tEnd = timeGetTime();
	end = RDTSC();

	printf(" total loop = %d , RDTSC = %d \n" , tot, end-begin);
	printf(" total loop = %d , timeGetTime = %d \n" ,tot, tEnd-tBegin);


}

void test_pack_unpack(tutorial::VersionTest sendVersionTest)
{
	//패킹.
	string sendBuffer = thrift_pack(sendVersionTest);

	//언패킹.
	tutorial::VersionTest recvVersionTest;
	thrift_unpack( OUT &recvVersionTest , IN sendBuffer );

	assert(recvVersionTest==sendVersionTest);
}

void test_VersionTest()
{
	tutorial::VersionTest sendVersionTest;
	{
		//sendVersionTest.value ="value";
		sendVersionTest.required_value = "required_value";
		sendVersionTest.optional_value = "optional_value";
		sendVersionTest.value_default ="value_default";
		sendVersionTest.required_value_default = "required_value_default";
		sendVersionTest.optional_value_default = "optional_value_default";

		test_pack_unpack(sendVersionTest);
	}
	{
		sendVersionTest.value ="value";
		//sendVersionTest.required_value = "required_value";
		sendVersionTest.optional_value = "optional_value";
		sendVersionTest.value_default ="value_default";
		sendVersionTest.required_value_default = "required_value_default";
		sendVersionTest.optional_value_default = "optional_value_default";

		test_pack_unpack(sendVersionTest);
	}
	{
		sendVersionTest.value ="value";
		sendVersionTest.required_value = "required_value";
		//sendVersionTest.optional_value = "optional_value";
		sendVersionTest.value_default ="value_default";
		sendVersionTest.required_value_default = "required_value_default";
		sendVersionTest.optional_value_default = "optional_value_default";

		test_pack_unpack(sendVersionTest);
	}
	{
		sendVersionTest.value ="value";
		sendVersionTest.required_value = "required_value";
		sendVersionTest.optional_value = "optional_value";
		//sendVersionTest.value_default ="value_default";
		sendVersionTest.required_value_default = "required_value_default";
		sendVersionTest.optional_value_default = "optional_value_default";

		test_pack_unpack(sendVersionTest);
	}
	{
		sendVersionTest.value ="value";
		sendVersionTest.required_value = "required_value";
		sendVersionTest.optional_value = "optional_value";
		sendVersionTest.value_default ="value_default";
		//sendVersionTest.required_value_default = "required_value_default";
		sendVersionTest.optional_value_default = "optional_value_default";

		test_pack_unpack(sendVersionTest);
	}
	{
		sendVersionTest.value ="value";
		sendVersionTest.required_value = "required_value";
		sendVersionTest.optional_value = "optional_value";
		sendVersionTest.value_default ="value_default";
		sendVersionTest.required_value_default = "required_value_default";
		//sendVersionTest.optional_value_default = "optional_value_default";

		test_pack_unpack(sendVersionTest);
	}

}
