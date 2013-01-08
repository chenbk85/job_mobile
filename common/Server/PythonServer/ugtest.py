import socket
import sys
import ug_pb2
import gameLogic_pb2
import time
import select
from struct import *
from protocol import *

HOST, PORT = "localhost", 8000

class UGClient:
	def __init__(self, host, port):
		self.buffer = ""
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.sock.connect((host, port))

	def sendReq(self, packet):
		self.sock.send(packet)

	def rcvAns(self):
		self.buffer += self.sock.recv(1024)
		print len(self.buffer)
		if len(self.buffer) > 4:
			(size, ) = unpack('I', self.buffer[0:4])
			size += 4
			if len(self.buffer) >= size:
				ans = self.buffer[4:size]
				self.buffer = self.buffer[size:]
				if size > 4:
					ret = ug_pb2.UAnsProtocol()
					ret.ParseFromString(ans)
					return ret
		return False

def reqToPacket(req):
	packet = req.SerializeToString()
	header = pack("I", len(packet))
	header += packet
	return header
	


c = UGClient(HOST, PORT)

packet = reqToPacket(UReqConnect(100, 1001, 0))
c.sendReq(packet)
a = c.rcvAns()
print a
packet = reqToPacket(UReqAutoJoin(0,0))
c.sendReq(packet)
a = c.rcvAns()
print a

while(True):
	pass

