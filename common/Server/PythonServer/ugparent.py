import signal, os
import time
import sys
import socket
import select
import errno
import ug


g_max_process_cnt = 3000
g_cur_process_cnt = 0

if len(sys.argv) < 2:
	print 'config file: config.py'
	config = __import__('config')
else:
	print 'config file:', sys.argv[1]
	config = __import__(sys.argv[1].split('.')[0])

service_port =  config.cfg["UGPort"]


def handleSIGCHLD(signum, frame):
	global g_cur_process_cnt
	g_cur_process_cnt -= 1

signal.signal(signal.SIGCHLD, handleSIGCHLD)


msock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

msock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
msock.setblocking(0)

msock.bind(('', service_port))
msock.listen(128)


MAX_ACCEPT = 16


while True:
	error = False
	for i in xrange(MAX_ACCEPT):
		if g_cur_process_cnt == g_max_process_cnt: 
			break
		try:
			clisock, addr = msock.accept()
			pid = os.fork()

			if pid==0:
				print 'new ug'
				ugate = ug.UserGateway(clisock, config.cfg)
				ugate.loop()
				print 'quit ug'
				sys.exit(0)
			else:
				clisock.close()
				g_cur_process_cnt += 1

		except socket.error as (err,estr):
			if err!= errno.EAGAIN:
				error = True
			break

	try:
		select.select([], [], [], 0.01)
	except select.error:
		pass
			

		

	
