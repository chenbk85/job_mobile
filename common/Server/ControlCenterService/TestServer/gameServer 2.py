# -*- coding: cp949 -*-
from socket import *
from struct import *
import time

def sendLog( logStr ):
    print 'sendLog'
    msg = pack( '=Bi%ds' % len( logStr ), 0x20, time.time(), logStr )
    csock.sendto( msg, ( HOST, SVR_PORT ) )
 
#setting Value
HOST = '10.25.20.147'
SVR_PORT = 9000
CLNT_PORT = 9002
LOOP_INTERVAL = 1.0
SERVER_NAME = 'GAME_SERVER2'
LOG_STRING = 'W|%s|test' % SERVER_NAME



# 네트워크 설정
csock = socket( AF_INET, SOCK_DGRAM )
csock.setsockopt( SOL_SOCKET, SO_REUSEADDR, 1 )
csock.bind(('', CLNT_PORT))
print '네트워크 초기화 성공'

# 서버 초기화
initString = '%s|%d' % ( SERVER_NAME, CLNT_PORT )
msg = pack( '=Bi%ds' % len( initString ), 0x01, time.time(), initString )
csock.sendto( msg, ( HOST, SVR_PORT ) )
print '서버 start send 성공'

# 초기화 정보 받기
msg, addr = csock.recvfrom( 1024 )
payLoadSize = len( msg ) - 5
payLoad = unpack('=Bi%ds' % payLoadSize, msg)[2]
print '서버 start rcv 성공\r\npayLoad = %s addr = %s\r\n' % ( payLoad, addr )

# heartBeat
while 1:
    msg = pack( '=Bi%ds' % len( SERVER_NAME ), 0x10, time.time(), SERVER_NAME )
    csock.sendto( msg, ( HOST, SVR_PORT ) )
    sendLog(LOG_STRING)
    print 'send'
    
    time.sleep(LOOP_INTERVAL)
    LOOP_INTERVAL = LOOP_INTERVAL * 2
