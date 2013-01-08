# -*- coding:utf-8 -*-
import gameLogic_pb2
import protocol
import db_pb2
import random
import MySQLdb

random.seed()

g_itemInfo = {}
g_svcID = 100

g_notice =[ 
	(True, 1, u'테스트 팝업 공지'),
	(False, 2, u'안녕하세요. 피망 안드로이드 맞고에 오신것을 환영합니다')
	]

def initDBName(db):
	global g_DB
	g_DB = db

def executeDB(query, params):
	conn = False
	cursor = False
	rows = False
	global g_DB
	try:
		conn = MySQLdb.connect(host = 'localhost', user = 'root', passwd = 'test99', db=g_DB)
		cursor = conn.cursor()
		cursor.execute(query, params)
		rows = []
		while True:
			result = cursor.fetchall()
			if len(result) > 0:
				rows.append(result)

			if cursor.nextset()==None:
				break

	except MySQLdb.Error as e:
		print "MySQL error:", e.args[0], e.args[1]

	if cursor!=False:
		cursor.close()
	if conn!=False:
		conn.close()

	return rows

def updateGamedata(idx, data, gameInfo):
	print 'gameInfo update:', idx
	prevMoney = gameInfo.money
	if idx == 1:
		gameInfo.ParseFromString(data)
		print "gameInfo update money change:", prevMoney, gameInfo.money	


def canEnter(category, i, gameInfo):

	if i>=len(category) or i<0: return 0

	args = category[i].split(":")
	lmoney = 0
	for i in args:
		if i[:10] == 'limitmoney':
			lmoney = int(i.split('=')[1])
	smoney = int(gameInfo.safeMoney)
	dmoney = (smoney*10)/100
	smoney = smoney - dmoney
	if lmoney <= int(gameInfo.money):
		return 1
	elif lmoney <= (int(gameInfo.money) + smoney):
		return 2
	return 0

def gameUpdate(updates):
	return False

def loadUserInfo(gameID, memberInfo):
	info = gameLogic_pb2.GameUserInfo()

	info.memberInfo.CopyFrom(memberInfo)

	args = ( gameID, )
	res = executeDB("call usp_login(%s)", args)
	
	print "login result", res
	if res==False or len(res)==0 or len(res[0])!=1:
		return False

	record = res[0][0]

	info.gameInfo.gameID = record[0]
	info.gameInfo.gameIndex = record[1]
	info.gameInfo.level = record[2]
	info.gameInfo.exp = record[3]
	info.gameInfo.money = str(record[4])

	info.gameInfo.winCnt = record[5]
	info.gameInfo.loseCnt = record[6]
	info.gameInfo.allInCnt = record[7]
	info.gameInfo.highMoney = str(record[8])
	info.gameInfo.highPoint = record[9]

	info.gameInfo.todayWin = record[10]
	info.gameInfo.todayLose = record[11]
	info.gameInfo.todayHighPoint = record[12]
	info.gameInfo.todayHighMoney = str(record[13])
	info.gameInfo.todayAllinCnt = record[14]

	info.gameInfo.todayRefill = record[16]
	info.gameInfo.safeMoney = str(record[18])
	return info

def updateGameInfoFromRes(gameInfo, record, idx):

	# gameInfo.gameID = record[idx+0]
	# gameInfo.gameIndex = record[idx+1]

	gameInfo.level = record[idx+2]
	gameInfo.exp = record[idx+3]
	gameInfo.money = str(record[idx+4])

	gameInfo.winCnt = record[idx+5]
	gameInfo.loseCnt = record[idx+6]
	gameInfo.allInCnt = record[idx+7]
	gameInfo.highMoney = str(record[idx+8])
	gameInfo.highPoint = record[idx+9]

	gameInfo.todayWin = record[idx+10]
	gameInfo.todayLose = record[idx+11]
	gameInfo.todayHighPoint = record[idx+12]
	gameInfo.todayHighMoney = str(record[idx+13])
	gameInfo.todayAllinCnt = record[idx+14]

	gameInfo.todayRefill = record[idx+15]
	gameInfo.safeMoney = str(record[idx+17])
		
	return
	

# update result
# update event
def executeGameDB(req, userInfo):
	gameInfo = userInfo.gameInfo
	idstr = str(userInfo.gameInfo.gameID)
	query = int(req.query)
	print req, len(req.params)
	if query == 101:
		if len(req.params)>=9 and (req.params[3].val==idstr or req.params[6].val==idstr):
			if int(req.params[4].val) == 1:
				args = (
					req.params[0].val,
					req.params[1].val,
					req.params[2].val,

					req.params[3].val,
					req.params[5].val,

					req.params[6].val,
					req.params[8].val )
			else:
				args = (
					req.params[0].val,
					req.params[1].val,
					req.params[2].val,

					req.params[6].val,
					req.params[8].val,

					req.params[3].val,
					req.params[5].val )

			print args
			res = executeDB("call usp_result_update(%s,%s,%s,%s,%s,%s,%s)", args)
			print 'result update', res
			if len(res)==1 and len(res[0])==1:
				updates = GameUpdateInfo(res[0][0]).SerializeToString()
				ans = protocol.AnsDB(req.seq, req.query, 1, updates)
				gans = protocol.GAnsDB(ans)			
				return gans
	 
	elif query == 102:
		if len(req.params)>=5 and (req.params[1].val==idstr or req.params[3].val==idstr):
			if int(req.params[2].val) == 1:
				args = (
					req.params[0].val,
					req.params[1].val,
					req.params[3].val )
			else:
				args = (
					req.params[0].val,
					req.params[3].val,
					req.params[1].val )
			print args
			res = executeDB("call usp_event_update(%s,%s,%s)", args)
			
			print 'mission update', res
			if len(res)==1 and len(res[0])==1:
				updates = GameUpdateInfo2(res[0][0]).SerializeToString()
				ans = protocol.AnsDB(req.seq, req.query, 1, updates)
				gans = protocol.GAnsDB(ans)
				return gans
					
	
	print 'db error'

	msg = 'error'
	ans = protocol.AnsDB(req.seq, req.query, 0, msg)
	gans = protocol.GAnsDB(ans)
	return gans

def executeUserDB(req, userInfo):
	gameInfo = userInfo.gameInfo
	idstr = str(gameInfo.gameID)
	query = int(req.query)
	print req, len(req.params)
	if query == 201:
		if len(req.params)>=1 and req.params[0].val==idstr:
			args = (req.params[0].val)
			print args
			res = executeDB("call usp_event_money(%s)", args)

			print 'event money', res
			if len(res)==1 and len(res[0])==1:
				record = res[0][0]
				updates = SafeEventMoneyUpdate( record[0], record[1], 0, record[2]).SerializeToString()
				gameInfo.money = str(record[0])
				
				ans = protocol.AnsDB(req.seq, req.query, 1, updates)
				uans = protocol.UAnsDB(ans)
				return uans
	elif query == 202 and req.params[0].val==idstr:
		if len(req.params)>=1:
			args = (req.params[0].val)
			print args
			res = executeDB("call usp_refill_money(%s)", args)

			print 'refill money', res
			if len(res)==1 and len(res[0])==1:
				record = res[0][0]
				updates = RefillMoneyUpdate( record[0], record[1], record[2], record[3], record[4]).SerializeToString()
				gameInfo.money = str(record[0])
				gameInfo.todayRefill = record[3]
				ans = protocol.AnsDB(req.seq, req.query, 1, updates)
				uans = protocol.UAnsDB(ans)
				return uans
	elif query == 251:
		if len(req.params)>=2 and req.params[0].val==idstr:
			args = (
				req.params[0].val,
				req.params[1].val )
			print args
			res = executeDB("call usp_deposit_safe(%s, %s)", args)

			print 'safe deposit', res
			if len(res)==1 and len(res[0])==1:
				record = res[0][0]
				updates = SafeEventMoneyUpdate( record[0], record[1], 0, 0).SerializeToString()
				gameInfo.money = str(record[0])
				gameInfo.safeMoney = str(record[1])
				ans = protocol.AnsDB(req.seq, req.query, 1, updates)
				uans = protocol.UAnsDB(ans)
				return uans
	elif query == 252:
			args = (
				req.params[0].val,
				req.params[1].val )
			print args
			res = executeDB("call usp_withdraw_safe(%s, %s)", args)

			print 'safe withdraw', res
			if len(res)==1 and len(res[0])==1:
				record = res[0][0]
				limitFlag = 0
				if record[3]==2:
					limitFlag = 1
				updates = SafeEventMoneyUpdate( record[0], record[1], record[2], limitFlag).SerializeToString()
				gameInfo.money = str(record[0])
				gameInfo.safeMoney = str(record[1])
				ans = protocol.AnsDB(req.seq, req.query, 1, updates)
				uans = protocol.UAnsDB(ans)
				return uans
	print 'db error'

	msg = 'error'
	ans = protocol.AnsDB(req.seq, req.query, 0, msg)
	uans = protocol.UAnsDB(ans)
	return uans


def category(catlist, gameInfo):
	for i in xrange(len(catlist)):
		if canEnter(catlist, i, gameInfo)!=0:
			catlist[i] += ':Enter=1'
		else:
			catlist[i] += ':Enter=0'

	return True
	

def getNotice():
	global g_notice
	return g_notice

def getItemInfo():
	global g_itemInfo
	return g_itemInfo

def updateGameResult(updateData):
	pass

def getSvcID():
	global g_svcID
	return g_svcID

def test():
	return g_svcID


def GameUpdateInfo(record):
	ans = gameLogic_pb2.GameUpdateInfo()
	for i in xrange(2):
		idx = i*22
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
		money.totalMoney = str(record[idx+4]);
		money.upMoney = str(record[idx+18])
		money.levelMoney = str(record[idx+19])
		if record[idx+20]==1:
			money.allIn = True
		else:
			money.allIn = False

		if record[idx+21]==1:
			money.limitMoney = True
		else:
			money.limitMoney = False

	return ans

def GameUpdateInfo2(record):
	ans = gameLogic_pb2.GameUpdateInfo()
	for i in xrange(2):
       		idx = i*2
		money = ans.moneyInfo.add()
		money.gameID = record[idx+0]
		money.totalMoney = str(record[idx+1]);
		money.upMoney = str(record[idx+2])
		money.levelMoney = '0'
		money.allIn = False
		if record[idx+3]==1:
			money.limitMoney = True
		else:
			money.limitMoney = False
	return ans

def SafeEventMoneyUpdate(totalMoney, deltaMoney, dealMoney, limitMoney):
	ans = gameLogic_pb2.SafeEventMoneyUpdate()
	ans.totalMoney = str(totalMoney)
	ans.deltaMoney = str(deltaMoney)
	ans.dealMoney = str(dealMoney)
	if limitMoney==1:
		ans.limitMoney = True
	else:
		ans.limitMoney = False
	return ans
	
def RefillMoneyUpdate( totalMoney, refillMoney, bonusMoney, refillCount, errorCode):
	ans = gameLogic_pb2.RefillMoneyUpdate()
	ans.totalMoney = str(totalMoney)
	ans.refillMoney = str(refillMoney)
	ans.bonusMoney = str(bonusMoney)
	ans.refillCount = refillCount
	ans.errorCode = errorCode
	return ans
	
