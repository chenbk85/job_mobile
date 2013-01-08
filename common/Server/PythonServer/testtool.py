# -*- coding:utf-8 -*-
import socket
import MySQLdb
import sys
from twisted.internet import protocol,reactor
from twisted.protocols.basic import LineReceiver

if len(sys.argv) < 2:
	print 'config file: config.py'
	config = __import__('config')
else:
	print 'config file:', sys.argv[1]
	config = __import__(sys.argv[1].split('.')[0])

def executeDB(query, params):
	conn = False
	cursor = False
	rows = False
	try:
		conn = MySQLdb.connect(host = '10.25.20.93', port=8889, user = 'root', passwd = 'root', db=config.cfg["DBName"])
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

	conn.commit()

	if cursor!=False:
		cursor.close()
	if conn!=False:
		conn.close()

	return rows

def getPlayerData(gameID):
	res = executeDB("""
		select 
		game_id,
		game_index,
		game_level,
		game_exp,
		game_money,

		win_cnt,
		lose_cnt,
		allin_cnt,
		high_money,
		high_point,

		today_win,
		today_lose,
		today_high_point,
		today_high_money,
		today_allin_cnt,

		refill_cnt,
		today_date,
		safe_money,
		attend_check,
		attend_date
		from TBL_players where game_id=%s
		""", gameID)
	if len(res) == 1 and len(res[0])==1:
		return res[0][0]
	return False

def savePlayerData(args):
	res = executeDB("""
		update TBL_players SET
		game_level = %s,
		game_exp = %s,
		game_money = %s,
		win_cnt = %s,
		lose_cnt = %s,
		allin_cnt = %s,
		high_money = %s,
		high_point = %s,
		today_win  = %s,
		today_lose = %s,
		today_high_point = %s,
		today_high_money = %s,
		today_allin_cnt = %s,
		refill_cnt = %s,
		safe_money = %s,
		attend_date = %s
		WHERE game_id = %s
		""", args)
	print res
	return True

def process(line):
	try:
		parsed = line.split(":")
		print parsed
		if (len(parsed)==2):
			if parsed[0].strip() == "load":
				ret  = getPlayerData(int(parsed[1].strip()))
				if ret!=False:
					sret = [ str(x) for x in ret ]
					out = 'ok:' + ','.join(sret) + '\r\n'
					return out

			if parsed[0].strip() == "update":
				args = [ x.strip() for x in parsed[1].split(',')]
				sargs = args[1:] + args[:1]
				print sargs
				savePlayerData(sargs)
				return 'ok\r\n'
	except:
		print 'error: ', line.strip()
	return 'error\r\n'

	

class PPlayer(LineReceiver):
	def __init__(self):
		pass
	def lineReceived(self, line):
		ret = process(line)
		self.transport.write(ret)


class PPlayerFactory(protocol.Factory):
	def buildProtocol(self, addr):
		return PPlayer()


reactor.listenTCP(config.cfg["AdminPort"], PPlayerFactory())

reactor.run()
