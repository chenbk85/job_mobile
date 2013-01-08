import socket
import sys
import presence_pb2
from struct import *
from presence import *

#from twisted.internet import epollreactor
#epollreactor.install()

from twisted.internet import protocol, reactor

# Presence protocol
class PPresence(protocol.Protocol):
	def __init__(self, presence):
		self.buffer = ""
		self.presence = presence
		self.gameID = False

	def dataReceived(self, data):
		self.buffer += data
		while len(self.buffer) > 4:
			(size, ) = unpack('I', self.buffer[0:4])
			size += 4
			if len(self.buffer) >= size :
				request = self.buffer[4:size]
				self.process(request)
				self.buffer = self.buffer[size:]
			else:
				break
	def connectionLost(self, reason):
		if self.gameID!=False:
			self.purge(self.gameID)

	def process(self, request):
		req = presence_pb2.PReqProtocol()
		req.ParseFromString(request)
		command = req.command

		# check ppID & gameID

		seqID = req.seqID
		gameID = req.gameID
		svcID = req.svcID
		category = req.category

		res = False
	
		print 'req:', command, gameID, seqID, svcID

		if self.gameID == False:
			if command == presence_pb2.LOGIN:
				res = self.login(gameID, seqID, svcID)
				if res[0]!= False: 
					self.gameID = gameID
		elif self.gameID == gameID:
			if command == presence_pb2.LOGOUT:
				res = self.logout(gameID, seqID, svcID)
			elif command == presence_pb2.GAMEENTER:
				res = self.gameEnter(gameID, seqID, svcID, category)
			elif command == presence_pb2.GAMELEAVE:
				res = self.gameLeave(gameID, seqID, svcID)
			elif command == presence_pb2.DETACH:
				res = self.detach(gameID, seqID, svcID)
			elif command == presence_pb2.PLUG:
				res = self.plug(gameID, seqID, svcID)
			elif command == presence_pb2.CATEGORY:
				res = self.category(gameID, seqID, svcID)
			else:
				command = presence_pb2.NONE
		else:
			command = presence_pb2.NONE
			
			
			
		ans = presence_pb2.PAnsProtocol()
		ans.command = command
		ans.seqID = seqID
		ans.gameID = gameID
		ans.svcID = svcID
		ans.category = category

		if command == presence_pb2.CATEGORY:
			print 'ans:', command, gameID, seqID, svcID, res
			ans.result = True
			ans.status = ''
			ans.detached = False
			ans.info = res
		elif command == presence_pb2.NONE:
			ans.result = False
			ans.status = ''
			ans.detached = False
		else:
			state = res[1]
			print 'ans:', command, gameID, seqID, svcID, state[0]

			ans.result = res[0]
			ans.status = state[0]
			ans.detached = state[1]
			if state[0] == 'G':
				ans.ip = state[2][0]
				ans.port = state[2][1]
				ans.roomID = state[2][2]

		packet = ans.SerializeToString()
		header = pack("I", len(packet))
		header += packet
		self.transport.write(header)

	def login(self, gameID, seqID, svcID):
		return self.presence.login(gameID)

	def logout(self, gameID, seqID, svcID):
		return self.presence.logout(gameID)

	def gameEnter(self, gameID, seqID, svcID, category):
		return self.presence.gameEnter(gameID, category)

	def gameLeave(self, gameID, seqID, svcID):
		return self.presence.gameLeave(gameID)

	def detach(self, gameID, seqID, svcID):
		return self.presence.detach(gameID)

	def plug(self, gameID, seqID, svcID):
		return self.presence.plug(gameID)

	def category(self, gameID, seqID, svcID):
		return self.presence.category()

	def purge(self, gameID):
		return self.presence.purge(gameID)
	
		

class PPresenceFactory(protocol.Factory):
	def buildProtocol(self, addr):
		return PPresence(g_presence)


if len(sys.argv) < 2:
	print 'config file: config.py'
	config = __import__('config')
else:
	print 'config file:', sys.argv[1]
	config = __import__(sys.argv[1].split('.')[0])

g_presence = Presence()
g_presence.init( config.cfg["MaxUser"], config.cfg["Category"], config.cfg["GameList"])


reactor.listenTCP(config.cfg["Presence"][1], PPresenceFactory())

reactor.run()
