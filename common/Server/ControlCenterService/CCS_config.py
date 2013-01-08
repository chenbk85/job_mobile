# -*- coding: cp949 -*-

SVR_PORT = 9000
RUNLOOP_INTERVAL = 0.1      # 해당 주기마다 runloop를 looping

#server info
SERVER_LIST = [ ['PRESENCE',        '10.25.20.147|7000'],
                ['GATEWAY',         '10.25.20.147|8000'],
                ['GAME_SERVER1',    '10.25.20.147|9001'],
                ['GAME_SERVER2',    '10.25.20.147|9002'],
                ['GAME_SERVER3',    '10.25.20.147|9003'] ]

#heartbeat
HEARTBEAT_INTERVAL = 2.0                            # 해당 주기마다 heartbeat가 오지 않으면 miss
HEARTBEAT_CHECK_INTERVAL = 1.0                      # 해당 주기마다 heartbeat check
MAX_HEARTBEAT_COUNT_TO_CONSIDER_SERVER_DEAD = 10    # heartbeat 가 해당 횟수만큼 miss일 경우, 해당 서버가 죽었다고 판단

#file writing
FILE_WRITE_INTERVAL = 1.0   # 해당 주기마다 파일을 write한다

### enum ###

#server State enum
SERVER_OFFLINE = 0
SERVER_ONLINE = 1
SERVER_HEARTBEAT_MISSING = 2

#packet Type enum
CMD_START_OF_SERVICE = 0x01
CMD_RESPONSE_OF_START_OF_SERVICE = 0x81
CMD_END_OF_SERVICE = 0x02
CMD_HEART_BEAT = 0x10
CMD_LOGGING = 0x20


