import socket
import sys
import presence_pb2
import time
from struct import *

HOST, PORT = "localhost", 6000

class PresenceClient:
	def __init__(self, host, port):
		self.buffer = ""
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.sock.connect((host, port))

	def _buildRequest(self, command, gameID, category=0):
		req = presence_pb2.PReqProtocol()
		req.gameID = gameID
		req.command = command
		req.seqID = 0
		req.svcID = 100
		req.category = category
		return req
		

	def rcvAns(self):
		self.buffer += self.sock.recv(1024)
		if len(self.buffer) > 4:
			(size, ) = unpack('I', self.buffer[0:4])
			size += 4
			if len(self.buffer) >= size:
				ans = self.buffer[4:size]
				self.buffer = self.buffer[size:]
				if size > 4:
					ret = presence_pb2.PAnsProtocol()
					ret.ParseFromString(ans)
					return ret
		return False

	def sendReq(self, command, gameID, category=0):
		req = self._buildRequest(command, gameID, category)
		packet = req.SerializeToString()
		header = pack("I", len(packet))
		header += packet
		self.sock.send(header)


c = PresenceClient(HOST, PORT)

c.sendReq(presence_pb2.LOGIN, 101)
a = c.rcvAns()
print a
c.sendReq(presence_pb2.GAMEENTER, 101)
a = c.rcvAns()
print a
while(True):
	pass
