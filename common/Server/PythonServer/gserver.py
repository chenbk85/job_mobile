import socket
import presence_pb2
from struct import *
from presence import *

#from twisted.internet import epollreactor
#epollreactor.install()

from twisted.internet import protocol, reactor

MaxUser = 2
Config = [[("10.25.20.93", 2010, 1000)]]
g_presence = Presence()
g_presence.init( MaxUser, Config)

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
		self.purge(self.gameID)

	def process(self, request):
		req = presence_pb2.PReqProtocol()
		req.ParseFromString(request)
		command = req.command

		# check ppID & gameID

		self.gameID = req.gameID

		seqID = req.seqID
		gameID = req.gameID
		svcID = req.svcID
		category = req.category

		res = False

		if command == presence_pb2.LOGIN:
			res = self.login(gameID, seqID, svcID)
		elif command == presence_pb2.LOGOUT:
			res = self.logout(gameID, seqID, svcID)
		elif command == presence_pb2.GAMEENTER:
			res = self.gameEnter(gameID, seqID, svcID, category)
		elif command == presence_pb2.GAMELEAVE:
			res = self.gameLeave(gameID, seqID, svcID)
		elif command == presence_pb2.DETACH:
			res = self.detach(gameID, seqID, svcID)
		elif command == presence_pb2.PLUG:
			res = self.plug(gameID, seqID, svcID)
		else:
			command = presence_pb2.NONE
			
			
		state = res[1]
		ans = presence_pb2.PAnsProtocol()
		ans.command = command
		ans.seqID = seqID
		ans.gameID = gameID
		ans.svcID = svcID
		ans.category = category

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

	def purge(self, gameID):
		return self.presence.purge(gameID)
	
		

class PPresenceFactory(protocol.Factory):
	def buildProtocol(self, addr):
		return PPresence(g_presence)

reactor.listenTCP(6000, PPresenceFactory())

reactor.run()
