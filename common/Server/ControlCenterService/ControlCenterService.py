# -*- coding: cp949 -*-
from socket import *
from struct import *
import select
import time
import thread
import os
from CCS_config import *

class ServerState:  
    ip = '0.0.0.0'
    port = 0
    serverName = ''
    condition = SERVER_OFFLINE
    lastHeartBeat = 0
    heartBeatMissingCount = 0

    def getStateString( self ):
        stateString = 'UNKNOWN'
        if( self.condition == SERVER_OFFLINE ):
            stateString = 'SERVER_OFFLINE'
        elif( self.condition == SERVER_ONLINE ):
            stateString = 'SERVER_ONLINE'
        elif( self.condition == SERVER_HEARTBEAT_MISSING ):
            stateString = 'SERVER_HEARTBEAT_MISSING'
        return stateString

    
            
       
    
class MyServer:
    m_svrSock = 0
    m_serverStateDict = dict()
    
    #multi-Thread Lock
    m_logLock = 0
    m_serverStateLock = 0

    #logFile Handle
    m_errorLogFile = 0
    m_debugLogFile = 0
    m_warningLogFile = 0

    #timer
    m_writeLogTimer = 0
    m_heartbeatTimer = 0
    
    def __init__( self ):
        self.InitServerDict()
        # 로그 폴더 생성
        dirList = os.listdir('.')
        isDirExist = 'log' in dirList
        if( isDirExist == False ):
            os.mkdir('log')
        
        # 로그파일 초기화
        timeString = time.strftime('%Y-%m-%d')
        self.m_errorLogFile = file('log/error-%s.log' % timeString, 'a')
        self.m_debugLogFile = file('log/debug-%s.log' % timeString, 'a')
        self.m_warningLogFile = file('log/warning-%s.log' % timeString, 'a')

        # thread 초기화
        self.m_logLock = thread.allocate_lock()
        self.m_serverStateLock = thread.allocate_lock()
        
        thread.start_new_thread(self.RunLoop, (0,) )
        
        self.RunLoopNetwork()

    def __del__( self ):
        print '__del__'
        m_svrSock.close()
        self.m_errorLogFile.close()
        self.m_debugLogFile.close()
        self.m_warningLogFile.close()

    def RunLoop( self, id ):
        while 1:
            nowTime = time.time()
            if( nowTime - self.m_writeLogTimer > FILE_WRITE_INTERVAL ):
                self.WriteLogFiles()
                self.m_writeLogTimer = nowTime
            if( nowTime - self.m_heartbeatTimer > HEARTBEAT_CHECK_INTERVAL ):
                self.HeartbeatCheck()
                self.m_heartbeatTimer = nowTime        
            time.sleep( RUNLOOP_INTERVAL )

    def RunLoopNetwork( self ):
        print('Network Runloop Start')
        self.m_svrSock = socket( AF_INET, SOCK_DGRAM )
        self.m_svrSock.setsockopt( SOL_SOCKET, SO_REUSEADDR, 1 )
        self.m_svrSock.bind(('', SVR_PORT))
        args = [self.m_svrSock], [], []
        while 1:
            reti, retw, rete = select.select(*args)
            print 'receive'
            for sock in reti:
                self.PacketProcess( sock )

    def InitServerDict( self ):
        i = 0
        numServer = len( SERVER_LIST )
        while i < numServer:
            serverState = ServerState()
            serverInfo = SERVER_LIST[i]
            if( len( serverInfo ) == 2 ):
                serverName = SERVER_LIST[i][0]
                serverInfoString = SERVER_LIST[i][1]
                serverInfoStringParsedArray = serverInfoString.split( '|', 99 )
                if( len( serverInfoStringParsedArray ) > 1 ):
                    serverState.ip = serverInfoStringParsedArray[0]
                    serverState.port = serverInfoStringParsedArray[1]
                    serverState.serverName = serverName
                    self.m_serverStateDict[serverName] = serverState
                else:
                    # 서버 설정값 오류 예외처리
                    pass
            else:
                # 서버 설정값 오류 예외처리
                pass
            i = i + 1

    def PacketProcess( self, sock ):
        packet, addr = sock.recvfrom(1024)

        payLoadSize = len( packet ) - 5
        unpackedPacket = unpack('=Bi%ds' % payLoadSize, packet)
        cmdType = unpackedPacket[0]
        timeStamp = unpackedPacket[1]
        payLoad = unpackedPacket[2]
        
        if( cmdType == CMD_START_OF_SERVICE ):
            print('CMD_START_OF_SERVICE')
            self.RcvStartOfService( sock, addr, timeStamp, payLoad )

        elif( cmdType == CMD_END_OF_SERVICE ):
            print('CMD_END_OF_SERVICE')
            self.RcvEndOfService( timeStamp, payLoad )

        elif( cmdType == CMD_HEART_BEAT ):
            print('CMD_HEART_BEAT')
            self.RcvHeartBeat( timeStamp, payLoad )
            
        elif( cmdType == CMD_LOGGING ):
            print('CMD_LOGGING')
            self.RcvLogging( timeStamp, addr, payLoad )

    def RcvStartOfService( self, sock, addr, iTimeStamp, sPayLoad ):
        splitArray = sPayLoad.split( '|', 99 )
        if( len( splitArray ) == 2 ):
            serverName = splitArray[0]
            version = splitArray[1]
            self.m_serverStateLock.acquire()
            server = 0
            
            if( ( serverName in self.m_serverStateDict ) == True ):
                server = self.m_serverStateDict[serverName]
            
            if( server != 0 ):
                # 서버정보 패킷 보내기
                timeStamp = time.time()
                serverInfo = '%s|%s' % ( server.ip, server.port )
                msg = pack( '=Bi%ds' % len( serverInfo ), CMD_RESPONSE_OF_START_OF_SERVICE, timeStamp, serverInfo )
                sock.sendto( msg, addr )
                server.condition = SERVER_ONLINE
                server.lastHeartBeat = iTimeStamp
            else:
                # 잘못된 서버-ip 조합에 대한 예외처리
                pass
            self.m_serverStateLock.release()
            
        else:
            pass  # 잘못된 패킷에 대한 예외처리

   
    def RcvEndOfService( self, iTimeStamp, sPayLoad ):
        self.m_serverStateLock.acquire()
        server = 0
        serverName = sPayLoad
        if( ( serverName in self.m_serverStateDict ) == True ):
            server = self.m_serverStateDict[serverName]
        else:
            #잘못된 서버 이름에 대한 예외처리
            pass
        server.condition = SERVER_OFFLINE
        self.m_serverStateLock.release()


    def RcvHeartBeat( self, iTimeStamp, sPayLoad ):
        self.m_serverStateLock.acquire()
        server = 0
        serverName = sPayLoad
        if( ( serverName in self.m_serverStateDict ) == True ):
            server = self.m_serverStateDict[serverName]
            server.lastHeartBeat = iTimeStamp
            server.heartBeatMissingCount = 0
            server.condition = SERVER_ONLINE
        else:
            #잘못된 서버 이름에 대한 예외처리
            pass
        self.m_serverStateLock.release()


    def RcvLogging( self, iTimeStamp, addr, sPayLoad ):
        self.m_logLock.acquire()
        splitArray = sPayLoad.split( '|', 2 )
        if( len( splitArray ) > 2 ):
            timeValue = time.localtime( iTimeStamp )
            logTime = time.strftime('%Y-%m-%d %H:%M:%S', timeValue )
            logIP = addr[0]
            logPort =  addr[1]
            logServerName = splitArray[1]
            logBody = splitArray[2]
            
            logString = '[%s] %s:%s %s - %s' % ( logTime, logIP, logPort, logServerName, logBody )
 
            if( splitArray[0] == 'E' ):
                self.m_errorLogFile.write( '%s\r\n' % ( logString ) )
            elif( splitArray[0] == 'D' ):
                self.m_debugLogFile.write( '%s\r\n' % ( logString ) )
            elif( splitArray[0] == 'W' ):
                self.m_warningLogFile.write( '%s\r\n' % ( logString ) )
            else:
                pass
        self.m_logLock.release()

    def HeartbeatCheck( self ):
        self.m_serverStateLock.acquire()

        nowTime = time.time()
        stateDictKeyList = self.m_serverStateDict.keys()
        for key in stateDictKeyList:
            serverInfo = self.m_serverStateDict[key]
  
            if( serverInfo.condition != SERVER_OFFLINE ):
                heartBeatInterval = nowTime - serverInfo.lastHeartBeat
                if( heartBeatInterval > HEARTBEAT_INTERVAL ):
                    serverInfo.heartBeatMissingCount = serverInfo.heartBeatMissingCount + 1
                    serverInfo.lastHeartBeat = nowTime
                    serverInfo.condition = SERVER_HEARTBEAT_MISSING
                if( serverInfo.heartBeatMissingCount >= MAX_HEARTBEAT_COUNT_TO_CONSIDER_SERVER_DEAD ):
                    serverInfo.condition = SERVER_OFFLINE
            print('%s : %s' % (serverInfo.serverName, serverInfo.getStateString() ) )
        print('\r\n')
        
        self.m_serverStateLock.release()
    
    def WriteLogFiles( self ):
        self.m_logLock.acquire()
            
        self.m_errorLogFile.close()
        self.m_debugLogFile.close()
        self.m_warningLogFile.close()

        timeString = time.strftime('%Y-%m-%d')
        self.m_errorLogFile = file('log/error-%s.log' % timeString, 'a')
        self.m_debugLogFile = file('log/debug-%s.log' % timeString, 'a')
        self.m_warningLogFile = file('log/warning-%s.log' % timeString, 'a')
            
        self.m_logLock.release()
#run
    
server = MyServer()









