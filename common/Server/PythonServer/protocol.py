import presence_pb2
import gameLogic_pb2
import game_pb2
import ug_pb2 
import db_pb2

def PReqLogin(seqID, svcID, gameID, category):
	req = presence_pb2.PReqProtocol()
	req.command = presence_pb2.LOGIN
	req.seqID = seqID
	req.svcID = svcID
	req.gameID = gameID
	req.category = category
	return req

def PReqLogout(seqID, svcID, gameID, category):
	req = presence_pb2.PReqProtocol()
	req.command = presence_pb2.LOGOUT
	req.seqID = seqID
	req.svcID = svcID
	req.gameID = gameID
	req.category = category
	return req

def PReqGameEnter(seqID, svcID, gameID, category):
	req = presence_pb2.PReqProtocol()
	req.command = presence_pb2.GAMEENTER
	req.seqID = seqID
	req.svcID = svcID
	req.gameID = gameID
	req.category = category
	return req

def PReqGameLeave(seqID, svcID, gameID, category):
	req = presence_pb2.PReqProtocol()
	req.command = presence_pb2.GAMELEAVE
	req.seqID = seqID
	req.svcID = svcID
	req.gameID = gameID
	req.category = category
	return req

def PReqDetach(seqID, svcID, gameID, category):
	req = presence_pb2.PReqProtocol()
	req.command = presence_pb2.DETACH
	req.seqID = seqID
	req.svcID = svcID
	req.gameID = gameID
	req.category = category
	return req

def PReqPlug(seqID, svcID, gameID, category):
	req = presence_pb2.PReqProtocol()
	req.command = presence_pb2.PLUG
	req.seqID = seqID
	req.svcID = svcID
	req.gameID = gameID
	req.category = category
	return req

def PReqCategory(seqID, svcID, gameID, category):
	req = presence_pb2.PReqProtocol()
	req.command = presence_pb2.CATEGORY
	req.seqID = seqID
	req.svcID = svcID
	req.gameID = gameID
	req.category = category
	return req

def UError(mode, code, info):
	req = ug_pb2.UAnsProtocol()
	req.type = ug_pb2.UAnsProtocol.UERROR
	req.ansError.error.errorCode = code
	req.ansError.error.errorInfo = info
	req.ansError.error.reqMode = mode
	return req

def UReqConnect(svcID, gameID, closeTime):
	req = ug_pb2.UReqProtocol()
	req.type = ug_pb2.UReqProtocol.UREQCONNECT
	req.reqConnect.svcID = svcID
	req.reqConnect.gameID = gameID
	req.reqConnect.lastCloseTime = closeTime
	
	version = ug_pb2.Version()
	version.major = 0
	version.minor = 0
	version.sub = 0
		
	req.reqConnect.programVer.CopyFrom(version)
	req.reqConnect.protoVer.CopyFrom(version)
	req.reqConnect.memberInfo.gameID = gameID
	req.reqConnect.memberInfo.avatarUrl = 'test'
	req.reqConnect.memberInfo.nickName = 'test'
	return req

def UReqAutoJoin(cat, chanID):
	req = ug_pb2.UReqProtocol()
	req.type = ug_pb2.UReqProtocol.UREQAUTOJOIN
	req.reqAutoJoin.categoryID = cat
	req.reqAutoJoin.channelID = chanID
	return req

def UAnsConnect(svcID, gameID, status, ip, port, passwd):
	ans = ug_pb2.UAnsProtocol()
	ans.type = ug_pb2.UAnsProtocol.UANSCONNECT
	ans.ansConnect.svcID = svcID
	ans.ansConnect.gameID = gameID
	ans.ansConnect.status = status
	ans.ansConnect.ip = ip
	ans.ansConnect.port = port
	ans.ansConnect.passwd = passwd
	return ans

def UAnsChannel(chanList):
	ans = ug_pb2.UAnsProtocol()
	ans.type = ug_pb2.UAnsProtocol.UANSCHANNEL
	index = 0
	for i in chanList:
		chan = ans.ansChannel.channelInfo.add()
		chan.id = index
		chan.desc = i
		index = index + 1
	return ans

# def UAnsChannel(channelInfo):
#	ans = ug_pb2.UAnsProtocol()
#	ans.type = ug_pb2.UAnsProtocol.UANSCHANNEL
#	for k,v in channelInfo.iteritems():
#		chan = ans.ansChannel.channelInfo.add()
#		chan.id = k
#		chan.desc = v
#	return ans

def UAnsStore(itemInfo):
	ans = ug_pb2.UAnsProtocol()
	ans.type = ug_pb2.UAnsProtocol.UANSSTORE
	store = ug_pb2.UAnsStore()
	ans.ansStore.CopyFrom(store)
	for k,v in itemInfo.iteritems():
		item = ans.ansStore.itemInfo.add()
		item.id = k
		item.desc = v
	return ans

def UAnsInfo(gameInfo):
	print gameInfo
	ans = ug_pb2.UAnsProtocol()
	ans.type = ug_pb2.UAnsProtocol.UANSINFO
	ans.ansInfo.gameInfo.CopyFrom(gameInfo)
	return ans

def UAnsNotice(notice):
	ans = ug_pb2.UAnsProtocol()
	ans.type = ug_pb2.UAnsProtocol.UANSNOTICE
	for i in notice:
		notice = ans.ansNotice.notices.add()
		notice.popup = i[0]
		notice.srl = i[1]
		notice.notice = i[2]
	return ans

def UAnsAutoJoin(gameRoomInfo):
	ans = ug_pb2.UAnsProtocol()
	ans.type = ug_pb2.UAnsProtocol.UANSAUTOJOIN
	ans.ansAutoJoin.gameRoomInfo.CopyFrom(gameRoomInfo)
	return ans


def UAnsLeaveGame(gameID, type):
	ans = ug_pb2.UAnsProtocol()
	ans.type = ug_pb2.UAnsProtocol.UANSLEAVEGAME
	ans.ansLeaveGame.gameID = gameID
	ans.ansLeaveGame.nType = type
	return ans


def UAnsPlug(gameID):
	ans = ug_pb2.UAnsProtocol()
	ans.type = ug_pb2.UAnsProtocol.UANSPLUG
	ans.ansPlug.gameID = gameID
	return ans

def UAnsClose():
	ans = ug_pb2.UAnsProtocol()
	ans.type = ug_pb2.UAnsProtocol.UANSCLOSE
	ans.ansClose.CopyFrom(ug_pb2.UAnsClose())
	return ans

def UAnsPong(seq):
	ans = ug_pb2.UAnsProtocol()
	ans.type = ug_pb2.UAnsProtocol.UANSPONG
	ans.ansPong.seq = seq
	return ans

def UAnsDB(db):
	ans = ug_pb2.UAnsProtocol()
	ans.type = ug_pb2.UAnsProtocol.UANSDB
	ans.ansDB.CopyFrom(db)
	return ans

def GLAnsGameProtocol(ansGameProtocol):
	ans = ug_pb2.UAnsProtocol()
	ans.type = ug_pb2.UAnsProtocol.GLANSGAMEPROTOCOL
	ans.ansGameProtocol.CopyFrom(ansGameProtocol)
	return ans


def GReqGameEnter(category, channel, room, gameUserInfo):
	ans = game_pb2.GReqProtocol()
	ans.type = game_pb2.GReqProtocol.GREQGAMEENTER
	ans.reqGameEnter.categoryID  = category
	ans.reqGameEnter.channelID = channel
	ans.reqGameEnter.roomID = room
	ans.reqGameEnter.gameUserInfo.CopyFrom(gameUserInfo)
	return ans

def GReqGameLeave(gameID, type):
	ans = game_pb2.GReqProtocol()
	ans.type = game_pb2.GReqProtocol.GREQGAMELEAVE
	ans.reqGameLeave.gameID = gameID
	ans.reqGameLeave.kick = type 
	return ans

def GReqDetach(gameID):
	ans = game_pb2.GReqProtocol()
	ans.type = game_pb2.GReqProtocol.GREQDETACH
	ans.reqDetach.gameID = gameID
	return ans

def GReqPlug(gameID):
	ans = game_pb2.GReqProtocol()
	ans.type = game_pb2.GReqProtocol.GREQPLUG
	ans.reqPlug.gameID = gameID
	return ans

def GLReqGameProtocol(reqGameProtocol):
	ans = game_pb2.GReqProtocol()
	ans.type = game_pb2.GReqProtocol.GLREQGAMEPROTOCOL
	ans.reqGameProtocol.CopyFrom(reqGameProtocol)
	return ans

def GAnsDB(db):
	ans = game_pb2.GReqProtocol()
	ans.type = game_pb2.GReqProtocol.GDBANS
	ans.ansDB.CopyFrom(db)
	return ans

def UAnsDB(db):
	ans = ug_pb2.UAnsProtocol()
	ans.type = ug_pb2.UAnsProtocol.UANSDB
	ans.ansDB.CopyFrom(db)
	return ans


def AnsDB(seq, query, retCode, result):
	ans = db_pb2.AnsDB()
	ans.seq = seq
	ans.query = query
	ans.retCode = retCode
	ans.result = result
	return ans
	

def GameUpdateInfo(record):
	ans = gameLogic_pb2.GameUpdateInfo()
	for i in xrange(2):
		idx = i*19
		user = ans.gameInfo.add()
		user.gameID = record[idx+0]
		user.gameIndex = record[idx+1]
		user.level = record[idx+2]
		user.exp = record[idx+3]
		user.money = str(record[idx+4])

		user.winCnt = record[idx+5]
		user.loseCnt = record[idx+6]
		user.allInCnt = record[idx+7]
		user.highMoney = str(record[idx+8])
		user.highPoint = record[idx+9]

		user.todayWin = record[idx+10]
		user.todayLose = record[idx+11]
		user.todayHighPoint = record[idx+12]
		user.todayHighMoney = str(record[idx+13])
		user.todayAllinCnt = record[idx+14]

		user.todayRefill = record[idx+15]
		user.safeMoney = str(record[idx+17])

		money = ans.moneyInfo.add()
		money.gameID = record[idx+0]
		money.money = str(record[idx+18])
	return ans

def GameUpdateInfo2(record):
	ans = gameLogic_pb2.GameUpdateInfo()
	for i in xrange(2):
		idx = i*2
		money = ans.moneyInfo.add()
		money.gameID = record[idx+0]
		money.money = str(record[idx+1])
	return ans


	
