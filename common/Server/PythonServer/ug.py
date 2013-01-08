# -*- coding:utf-8 -*-

import socket
import select
import errno
from struct import *

import db_pb2
import presence_pb2
import gameLogic_pb2
import game_pb2
import ug_pb2
import db_pb2

from protocol import *


import database

def makeAcceptor():
	try:
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		sock.bind(('',0))
		sock.listen(5)
		return sock
	except:
		return False

class UGError(Exception):
	def __init__(self, errreq, errnum, errstr, ret=False):
		self.errreq = errreq
		self.errnum = errnum
		self.errstr = errstr
		self.errret = ret

class IConnection:
	def __init__(self, sock):
		
		self.sock = sock
		self.sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
		self.rbuf = ''
		self.wbuf = ''

	def _read(self):
		try: 
			data = self.sock.recv(1024)
			if len(data) == 0:
				return False
			self.rbuf += data
			return True
				
		except socket.error as (ernum,errstr):
			if ernum == errno.EAGAIN or ernum == errno.EWOULDBLOCK:
				return True

		return False

	def _getPacket(self):
		if len(self.rbuf) > 4:
			(size, ) =  unpack('I', self.rbuf[0:4])
			if size == 0: return False
			size += 4
			if len(self.rbuf) >= size:
				packet = self.rbuf[4:size]
				self.rbuf = self.rbuf[size:]
				return packet 
		return ''

	def handleRead(self, state):
		if self._read() == True:
			# packet = self._getPacket()
			while True:
				packet = self._getPacket()
				if packet == False: 
					return False
				if len(packet) > 0:
					print "read..", self.conType, len(packet)
					if self.handler(packet, state) == False:
						return False
				else:
					return True
			return False
				
		else:
			return False

	def handleWrite(self):
		if len(self.wbuf) == 0: 
			return True

		try:
			written = self.sock.send(self.wbuf)
			if written == 0:
				return False
			self.wbuf = self.wbuf[written:]
			return True
		except socket.error as (ernum,errstr):
			if ernum == errno.EAGAIN or ernum == errno.EWOULDBLOCK:
				return True
		return False

	def write(self, data):
		print "write..", self.conType, len(data)
		self.wbuf += data





class Client(IConnection):
	def __init__(self, sock, plugged, authKey):
		IConnection.__init__(self, sock)
		self.conType = 'C'

		self.plugged = plugged
		self.logged = False

		self.authKey = authKey
		
		self.handlerMap = {
			ug_pb2.UReqProtocol.UREQCONNECT:
				('reqConnect', Client.reqConnect),
			ug_pb2.UReqProtocol.UREQCHANNEL:
				('reqChannel', Client.reqChannel),
			ug_pb2.UReqProtocol.UREQSTORE:
				('reqStore', Client.reqStore),
			ug_pb2.UReqProtocol.UREQINFO:
				('reqInfo', Client.reqInfo),
			ug_pb2.UReqProtocol.UREQNOTICE:
				('reqNotice', Client.reqNotice),
			ug_pb2.UReqProtocol.UREQAUTOJOIN:
				('reqAutoJoin', Client.reqAutoJoin),
			ug_pb2.UReqProtocol.UREQLEAVEGAME:
				('reqLeaveGame', Client.reqLeaveGame),
			ug_pb2.UReqProtocol.UREQCLOSE:
				('reqClose', Client.reqClose),
			ug_pb2.UReqProtocol.UREQPLUG:
				('reqPlug', Client.reqPlug),
			ug_pb2.UReqProtocol.UREQDB:
				('reqDB', Client.reqDB),
			ug_pb2.UReqProtocol.GLREQGAMEPROTOCOL:
				('reqGameProtocol', Client.reqGameProtocol)
		}
	def reqConnect(self, proto, state):
		req = proto.reqConnect
		if state.status != 'U':
			return True
		if self.logged != False or self.plugged != False:
			return False
		# already tried to connect, not finished
		if self.authKey in state.authKeys:
			return True
		try:
			# check sanity
			# pp login
			# load database
			print req
			state.userInfo = database.loadUserInfo(req.gameID, req.memberInfo)
			if state.userInfo==False: 
				raise UGError(ug_pb2.UReqProtocol.UREQCONNECT, 2, 'DATABASE Error')

			state.gameID = req.gameID

			# forward to presence
			if state.presence == False:
				raise UGError(ug_pb2.UReqProtocol.UREQCONNECT, 3, 'Internal Server Error')

			state.authAdd(self.authKey, self)
			preq = PReqLogin(self.authKey, req.svcID, req.gameID, 0)
			packet = preq.SerializeToString()
			header = pack("I", len(packet))
			header += packet
			state.presence.write(header)

		except UGError as e:
			ans = UError(e.errreq, e.errnum, e.errstr)
			packet = ans.SerializeToString()
			header = pack("I", len(packet))
			header += packet
			self.write(header)
			return e.errret
		return True

	def reqChannel(self, proto, state):
		req = proto.reqChannel
		if self.logged == False or state.status == 'U':
			return False

		packet = PReqCategory(1, database.getSvcID(), state.gameID, 0).SerializeToString()
		
		header = pack("I", len(packet))
		header += packet
		state.presence.write(header)

		return True
		
	def reqStore(self, proto, state):
		req = proto.reqStore
		if self.logged == False or state.status == 'U':
			return False

		item = database.getItemInfo()
		packet = UAnsStore(item).SerializeToString()
		print "size of uansstore:", len(packet)
		header = pack("I", len(packet))
		header += packet
		self.write(header)
		return True

	def reqInfo(self, proto, state):
		req = proto.reqInfo
		if self.logged == False or state.status == 'U':
			return False
		packet = UAnsInfo(state.userInfo.gameInfo).SerializeToString()
		header = pack("I", len(packet))
		header += packet
		self.write(header)
		return True
	def reqNotice(self, proto, state):
		req = proto.reqNotice
		notice = database.getNotice()
		packet = UAnsNotice(notice).SerializeToString()
		header = pack("I", len(packet))
		header += packet
		self.write(header)
		return True
		
	def reqAutoJoin(self, proto, state):
		req = proto.reqAutoJoin
		if self.logged == False or state.status == 'U':
			return False

		try:
			if state.presence == False:
				raise UGError(ub_pb2.UReqProtocol.UREQAUTOJOIN, 3, 'internal server error')
			if state.status == 'G':
				raise UGError(ub_pb2.UReqProtocol.UREQAUTOJOIN, 6, 'already playing game')
			packet = PReqGameEnter(1, database.getSvcID(), state.gameID, req.categoryID).SerializeToString()
			header = pack("I", len(packet))
			header += packet
			state.presence.write(header)
		except UGError as e:
			packet = UError(e.errreq, e.errnum, e.errstr).SerializeToString()
			header = pack("I", len(packet))
			header += packet
			self.write(header)
			return e.errret
		return True
			
	def reqLeaveGame(self, proto, state):
		req = proto.reqLeaveGame
		print 'got client leave req'
		if self.logged == False or state.status == 'U':
			return False
		try:
			if state.presence == False or state.game == False:
				raise UGError(ug_pb2.UReqProtocol.UREQLEAVEGAME, 3, 'internal server error')
			if state.status == 'L':
				raise UGError(ug_pb2.UReqProtocol.UREQLEAVEGAME, 7, 'already not playing game')
			# client can't kick connetion
			packet = GReqGameLeave(state.gameID, False).SerializeToString()
			header = pack("I", len(packet))
			header += packet
			state.game.write(header)
		except UGError as e:
			packet = UError(e.errreq, e.errnum, e.errstr).SerializeToString()
			header = pack("I", len(packet))
			header += packet
			self.write(header)
			return e.errret
		return True

	def reqClose(self, proto, state):
		req = proto.reqClose
		try:
			if self.logged == False or state.status == 'U':
				raise UGError(ug_pb2.UReqProtocol.UREQCLOSE, 5, 'u are not logged')
			if state.presence == False:
				raise UGError(ug_pb2.UReqProtocol.UREQCLOSE, 3, 'internal server error')
			if state.status == 'G':
				raise UGError(ug_pb2.UReqProtocol.UREQCLOSE, 6, 'playing game')
			packet = PReqLogout(0, database.getSvcID(), state.gameID, 0).SerializeToString()
			header = pack("I", len(packet))
			header += packet
			state.presence.write(header)
		except UGError as e:
			if e.errret == False:
				packet = UAnsClose()
				header = pack("I", len(packet))
				header += packet
				self.write(header)
				return e.errret
		return True

	def reqPlug(self, proto, state):
		req = proto.reqPlug
		if self.logged == True or state.status == 'U':
			return False
		if state.gameID != req.gameID:
			return False
		print 'got plugged', self
		print state.gameID

		state.eofExcept(self)

		if state.status == 'L' or state.game == False:
			print 'lobby suicide'
			packet = UError(ug_pb2.UReqProtocol.UREQPLUG, 8, 'plug failed by game server').SerializeToString()
			header = pack("I", len(packet))
			header += packet
			self.write(header)
			state.shutdown = True
			return False

		self.logged = True
		packet = GReqPlug(state.gameID).SerializeToString()
		header = pack("I", len(packet))
		header += packet
		state.game.write(header)
		print 'sent game request to GS'
		return True

	def reqDB(self, proto, state):
		req = proto.reqDB
		if self.logged == True and state.status == 'L':
			packet = database.executeUserDB(req, state.userInfo).SerializeToString()
			header = pack("I", len(packet))
			header += packet
			self.write(header)
		else:
			print 'Client DB Request failed'
		return True
		

			
	def reqGameProtocol(self, proto, state):
		req = proto.reqGameProtocol
		if self.logged == False or state.status == 'U':
			return False
		try:
			if state.presence == False or state.game == False:
				raise UGError(ug_pb2.UReqProtocol.GLREQGAMEPROTOCOL, 3, 'System Error')
			if state.status == 'L':
				raise UGError(ug_pb2.UReqProtocol.GLREQGAMEPROTOCOL, 7, 'not plying game')
			packet = GLReqGameProtocol(req).SerializeToString()
			header = pack("I", len(packet))
			header += packet
			state.game.write(header)
		except UGError as e:
			return e.errret
		return True
		
	def handler(self, packet, state):
		req = ug_pb2.UReqProtocol()
		req.ParseFromString(packet)

		if req.IsInitialized():
			if req.type in self.handlerMap.keys():
				v = self.handlerMap[req.type]
				if req.HasField(v[0]):
					print req.type
					return v[1](self, req, state)
				else:
					print 'handler field error..'
			else:
				print 'protocol not initialized.'
		return False

	def handleClose(self, state):
		print 'closing..'
		if self.plugged:
			state.delClient2(self)
		else:
			state.delClient(self)
		self.sock.close()
		return True

class Presence(IConnection):
	def __init__(self, sock):
		IConnection.__init__(self, sock)
		self.conType = 'P'
		self.handlerMap = {
			presence_pb2.LOGIN:
				Presence.login,
			presence_pb2.LOGOUT:
				Presence.logout,
			presence_pb2.GAMEENTER:
				Presence.gameEnter,
			presence_pb2.GAMELEAVE:
				Presence.gameLeave,
			presence_pb2.DETACH:
				Presence.detach,
			presence_pb2.PLUG:
				Presence.plug,
			presence_pb2.CATEGORY:
				Presence.category
		}

	def login(self, ans, state):
		if ans.result == True:
			if ans.seqID in state.authMap.keys():
				state.acceptor = makeAcceptor()
				client = state.authMap[ans.seqID]
				client.logged = True
				ip = state.cfg["UGIP"]
				port = state.acceptor.getsockname()[1]
				passwd = 'test'
				if state.acceptor != False:
					packet = UAnsConnect(database.getSvcID(), state.gameID, 0, ip, port, passwd).SerializeToString()
				else:
					packet = UAnsConnect(database.getSvcID(), state.gameID, 0, '', 0, '').SerializeToString()
				header = pack("I", len(packet))
				header += packet
				client.write(header)
			state.status = ans.status
			state.detached = ans.detached
			state.authDel(ans.seqID)
		else:
			if ans.seqID in state.authMap.keys():
				client = state.authMap[ans.seqID]
				packet = UError(ug_pb2.UReqProtocol.UREQCONNECT, 4, 'another connection logged').SerializeToString()
				header = pack("I", len(packet))
				header += packet
				client.write(header)
			state.authDel(ans.seqID)
		return True

	def logout(self, ans, state):
		if ans.result == True:
			state.status = ans.status
			state.detached = state.detached

			state.room = False
			state.shutdown = True

			packet = UAnsClose().SerializeToString()
			header = pack("I", len(packet))
			header += packet
			state.sendToClients(header, False)
		return False
			
			
	def gameEnter(self, ans, state):
		if ans.result == True:
			gsock = createGameSock(ans.ip, ans.port)
			print "game connecting..", gsock
			if gsock==False:
				state.shutdown = True
				
				packet = UAnsClose().SerializeToString()
				header = pack("I", len(packet))
				header += packet
				state.sendToClients(header, False)
			else:
				state.addGame(gsock)
				packet = GReqGameEnter(ans.category, 0, ans.roomID, state.userInfo).SerializeToString()
				header = pack("I", len(packet))
				header += packet
				state.game.write(header)
			
				state.status = ans.status
				state.detached = ans.detached
				state.room = (ans.ip, ans.port, ans.roomID)
				print 'room assigned:', state.room
		return True
			
	def gameLeave(self, ans, state):
		if ans.result == True:
			state.eof.add(state.game)
			state.status = ans.status
			state.detached = ans.detached
			state.room = False
			packet = UAnsLeaveGame(state.gameID, ans.seqID).SerializeToString()
			header = pack("I", len(packet))
			header += packet
			state.sendToClients(header)
		return True

	def detach(self, ans, state):
		return True

	def plug(self, ans, state):
		return True

	def category(self, ans, state):
		catlist =[]
		catlist.extend(state.cfg["Category"])
		
		catUsers = ans.info.split(',')
		for i in xrange(len(catlist)):
			catlist[i] += ':person=%s'%catUsers[i]
		
		database.category(catlist, state.userInfo.gameInfo)
		packet = UAnsChannel(catlist).SerializeToString()
		print 'category:', catlist
		header = pack("I", len(packet))
		header += packet
		state.sendToClients(header)
		return True

	def handler(self, packet, state):
		ans = presence_pb2.PAnsProtocol()
		ans.ParseFromString(packet)

		if ans.IsInitialized():
			if ans.command in self.handlerMap.keys():
				v = self.handlerMap[ans.command]
				print ans.command
				return v(self, ans, state)
		return False

	def handleClose(self, state):
		state.delPresence(self)
		self.sock.close()
		return True

class Game(IConnection):
	def __init__(self,sock):
		IConnection.__init__(self, sock)
		self.conType = 'G'
		self.handlerMap = {
			game_pb2.GAnsProtocol.GANSGAMEENTER:
				('ansGameEnter', Game.gameEnter),
			game_pb2.GAnsProtocol.GANSGAMELEAVE:
				('ansGameLeave', Game.gameLeave),
			game_pb2.GAnsProtocol.GANSDETACH:
				('ansDetach', Game.detach),
			game_pb2.GAnsProtocol.GANSPLUG:
				('ansPlug', Game.plug),
			game_pb2.GAnsProtocol.GDBREQ:
				('reqDB', Game.reqDB),
			game_pb2.GAnsProtocol.GANSUSERUPDATE:
				('ansUpdate', Game.ansUpdate),
			game_pb2.GAnsProtocol.GLANSGAMEPROTOCOL:
				('ansGameProtocol', Game.gameProtocol)
			
		}
	def gameEnter(self, proto, state):
		ans = proto.ansGameEnter
		print ans.gameRoomInfo
		packet = UAnsAutoJoin(ans.gameRoomInfo).SerializeToString()
		header = pack("I", len(packet))
		header += packet
		state.sendToClients(header)
		return True

	def gameLeave(self, proto, state):
		ans = proto.ansGameLeave
		print "leaving comparison:", ans.gameID, state.gameID
		if ans.gameID == state.gameID:
			packet = PReqGameLeave(ans.nType, database.getSvcID(), state.gameID, 0).SerializeToString()
			header = pack("I", len(packet))
			header += packet
			if state.presence != False:
				state.presence.write(header)
			return True
		else:
			packet = UAnsLeaveGame(ans.gameID, ans.nType).SerializeToString()
			header = pack("I", len(packet))
			header += packet
			state.sendToClients(header)
			return True

	def detach(self, proto, state):
		return True

	def plug(self, proto, state):
		ans = proto.ansPlug
		packet = UAnsPlug(ans.gameID).SerializeToString()
		header = pack("I", len(packet))
		header += packet
		state.sendToClients(header)
		return True

	def reqDB(self, proto, state):
		req = proto.reqDB
		packet = database.executeGameDB(req, state.userInfo).SerializeToString()
		header = pack("I", len(packet))
		header += packet
		state.sendToGame(header)
		return True

	def ansUpdate(self, proto, state):
		req = proto.ansUpdate
		database.updateGamedata(req.type, req.updateInfo , state.userInfo.gameInfo)
		return True

	def errPlug(self, proto, state):
		ans = proto.errPlug
		packet = UError(ug_pb2.UReqProtocol.UREQPLUG, 8, 'plug failed by game server').SerializeToString()
		header = pack("I", len(packet))
		header += packet
		state.sedToClients(header)
		state.shutdown = True
		return False
		
	def gameProtocol(self, proto, state):
		ans = proto.ansGameProtocol
		packet = GLAnsGameProtocol(ans).SerializeToString()
		header = pack("I", len(packet))
		header += packet
		state.sendToClients(header)
		return True

	def handler(self, packet, state):
		ans = game_pb2.GAnsProtocol()
		ans.ParseFromString(packet)

		if ans.IsInitialized()==False:
			print "inproper - packet"
			print ans.__str__()

		if ans.type in self.handlerMap.keys():
			v = self.handlerMap[ans.type]
			ret =  v[1](self, ans, state)
			if ret == False:
				print "handler error", v
			return ret
		return False


	def handleClose(self, state):
		state.delGame(self)
		self.sock.close()
		return True


class Connections:
	def __init__(self):
		self.sock2Con = dict()
		self.client = False
		self.client2 = set()
		self.presence = False
		self.game = False

		self.authKeys = set(range(10))
		self.authMap = {}
		self.eof = set()

		self.gameID = 0

		self.status = 'U'
		self.detached = False
		self.room = False

		self.userInfo = False

		self.shutdown = False

	def _addConnection(self, connection):
		self.sock2Con[connection.sock] = connection
	def _delConnection(self, connection):
		if connection.sock in self.sock2Con.keys():
			del self.sock2Con[connection.sock]
			return True
		return False

	def authAdd(self, authKey, con):
		self.authMap[authKey] = con
	def authDel(self, authKey):
		if authKey in self.authMap.keys():
			del self.authMap[authKey]

	def addClient(self, sock):
		if len(self.authKeys) > 0:
			authKey = self.authKeys.pop()
			con = Client(sock, False, authKey)
			self.client = con
			self._addConnection(con)
			return True
		return False

	def addClient2(self, sock):
		if len(self.authKeys) > 0:
			authKey = self.authKeys.pop()
			con = Client(sock, True, authKey)
			self.client2.add(con)
			self._addConnection(con)
			return True
		return False

	def addPresence(self, sock):
		con = Presence(sock)
		self.presence = con
		self._addConnection(con)
		return True
	def addGame(self, sock):
		con = Game(sock)
		self.game = con
		self._addConnection(con)
		return True

	def delClient(self, con):
		if self._delConnection(con):
			self.client = False
			self.authDel(con.authKey)
			self.authKeys.add(con.authKey)
	def delClient2(self, con):
		if self._delConnection(con):
			self.client2.discard(con)
			self.authDel(con.authKey)
			self.authKeys.add(con.authKey)

	def delPresence(self, con):
		if self._delConnection(con):
			self.presence = False
	def delGame(self, con):
		if self._delConnection(con):
			self.game = False

	def sendToClients(self, packet, logged=True):
		if self.client!=False:
			if logged != True or self.client.logged==True:
				self.client.write(packet)
		for cl in self.client2:
			if logged != True or cl.logged==True:
				cl.write(packet)
		return True
	def sendToGame(self, packet):
		if self.game!=False:
			self.game.write(packet)

	def eofExcept(self, con):
		if self.client!=False and self.client!=con:
			self.eof.add(self.client)
		for cl in self.client2:
			if cl!=False and cl != con:
				self.eof.add(cl)


	
def createPresenceSock(address):
	try:
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		sock.connect(address)
		return sock
	except socket.error as (errnum,errstr): 
		return False

def createGameSock(ip, port):
	try:
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		sock.connect((ip, port))
		return sock
	except:
		return False




class UserGateway:
	def __init__(self,clisock,cfg):

		self.state = Connections()

		self.state.cfg = cfg
		self.state.acceptor = False
		self.state.numcli = 0
		self.state.addClient(clisock)

		database.initDBName(cfg["DBName"])
		psock = createPresenceSock(cfg["Presence"])
		if psock!=False:
			self.state.addPresence(psock)
			self.state.shutdown = False
		else:
			self.state.shutdown = True

	def _accept(self):
		if self.state.acceptor != False:
			rd,wr,ex = select.select([self.state.acceptor],[], [self.state.acceptor], 0.001)
			if len(rd) > 0:
				try:
					clisock, addr = self.state.acceptor.accept()
					return clisock
				except socket.error as (err, errstr):
					pass
		return False

	def finalize(self):
		if self.state.presence == False:
			print 'going shutdown - no presence'
			return True
		if self.state.shutdown==True:
			print 'going shutdown - shutdown flag'
			return True
		numcli = len(self.state.client2)
		if self.state.client != False:
			numcli = numcli + 1

		if numcli == 0:
			if self.state.status != 'G':
				print 'going shutdown - no client'
				return True
			elif self.state.numcli > 0:
				print 'changed to no client'
				packet = GReqDetach(self.state.gameID).SerializeToString()
				header = pack("I", len(packet))
				header += packet
				self.state.sendToGame(header)
		self.state.numcli = numcli
		return False
	
	def loop(self):
		while self.finalize()==False:
			clisock = self._accept()
			if clisock!= False: 
				self.state.addClient2(clisock)
			

			rset = [ k for k in self.state.sock2Con.keys() ]
			xset = rset

			rd,wr,ex = select.select(rset, [], [], 0.01) 
			
			for sock in rd:
				con = self.state.sock2Con[sock]
				ret = con.handleRead(self.state)
				if ret == False:
					print "handler exception.."
					print con
					self.state.eof.add(con)

			wset = [ k for k,v in self.state.sock2Con.iteritems() if len(v.wbuf) > 0]
			rd,wr,ex = select.select([], wset, xset, 0.01)

			for sock in wr:
				con = self.state.sock2Con[sock]
				ret = con.handleWrite()
				if ret == False:
					print "send exception.."
					print con
					self.state.eof.add(con)

			for sock in ex:
				con = self.state.sock2Con[sock]
				self.state.eof.add(con)

			if len(self.state.eof) > 0:
				print "eof..", self.state.eof

			for con in self.state.eof:
				con.handleClose(self.state)
			self.state.eof.clear()
			
