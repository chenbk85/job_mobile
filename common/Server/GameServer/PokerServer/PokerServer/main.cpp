#pragma warning(disable : 4819)

//
//  main.cpp
//  DualGoServer
//
//  Created by jin young park on 11. 11. 23..
//  Copyright (c) 2011년 집. All rights reserved.
//
#include "stdafx.h"
#include "PK_header.h"


int main (int argc, const char * argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: PokerServer <port>\n";
            return 1;
        }
		int port =atoi(argv[1]);
		nMOB::run_tcp_server(&g_PK_Plugin_NetIOModel,port );

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}

