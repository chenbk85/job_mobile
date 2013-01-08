//
//  main.cpp
//  DualGoServer
//
//  Created by jin young park on 11. 11. 23..
//  Copyright (c) 2011년 집. All rights reserved.
//

#include "DualGoInclude.h"

int main (int argc, const char * argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: async_tcp_echo_server <port>\n";
            return 1;
        }
        
        boost::asio::io_service io_service;
        
        using namespace std; // For atoi.
        CMultiGoManager server(io_service, atoi(argv[1]));
        
        std::cerr << "Server Start................ \n";
        
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}

