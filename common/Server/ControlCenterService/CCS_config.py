# -*- coding: cp949 -*-

SVR_PORT = 9000
RUNLOOP_INTERVAL = 0.1      # �ش� �ֱ⸶�� runloop�� looping

#server info
SERVER_LIST = [ ['PRESENCE',        '10.25.20.147|7000'],
                ['GATEWAY',         '10.25.20.147|8000'],
                ['GAME_SERVER1',    '10.25.20.147|9001'],
                ['GAME_SERVER2',    '10.25.20.147|9002'],
                ['GAME_SERVER3',    '10.25.20.147|9003'] ]

#heartbeat
HEARTBEAT_INTERVAL = 2.0                            # �ش� �ֱ⸶�� heartbeat�� ���� ������ miss
HEARTBEAT_CHECK_INTERVAL = 1.0                      # �ش� �ֱ⸶�� heartbeat check
MAX_HEARTBEAT_COUNT_TO_CONSIDER_SERVER_DEAD = 10    # heartbeat �� �ش� Ƚ����ŭ miss�� ���, �ش� ������ �׾��ٰ� �Ǵ�

#file writing
FILE_WRITE_INTERVAL = 1.0   # �ش� �ֱ⸶�� ������ write�Ѵ�

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


