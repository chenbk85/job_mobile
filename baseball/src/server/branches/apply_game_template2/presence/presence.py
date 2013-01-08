import sys

class UserStash:
	# self.status 
	# - key = userid, value = (state, isDetached(False/True), where)
	# - state = ('U'), 'L', 'G' 
	# - where = (ip, port, roomid)
	def __init__(self):
		self.status = dict()

	def getState(self, uid):
		if uid in self.status.keys():
			return self.status[uid]
		return ('U', False, False)

	def setState(self, uid, state):
		if state == 'U':
			del self.status[uid]
		else:
			self.status[uid] = state

	def isDetached(self, uid):
		return self.getState(uid)[1]

	def setDetached(self, uid):
		state = self.getState(uid)
		if state[0] != 'U':
			self.state[uid] = (state[0], False, state[2])

	
class RoomStash:
	def init(self, maxuser, catlist, servers):
		# servers = [[(ip,port,# of rooms), ...], ... ]
		# servers = [[(ip,port,start room, end room), ...], ... ]
		# self.container[category][# of user] = set((ip,port,rmid))
		# self.room[(ip,port,rmid)] = (category, set(uid))
		category = len(catlist)
		self.category = category
		self.catUsers = [0] * category
		self.maxuser = maxuser

		self.container = [[set() for i in range(maxuser+1)] for j in range(category)]
		self.room = {}

		total = 0
		for i in servers.keys():
			if i < 0  or self.category <= i:
				print 'server config is invlid'
				sys.exit(0)
			for j in servers[i]:
				print 'cat:', i, 'room:', j[2], j[3]
				for k in xrange(j[2], j[3]):
					rm = (j[0], j[1], k)
					total = total+1
					self.container[i][0].add(rm)
					self.room[rm] = (i, set()) 

	def addUser(self, gameID, category):
		if 0<=category and category < self.category :
			for i in range(self.maxuser - 1, -1, -1):
				if len(self.container[category][i]) > 0:
					rm = self.container[category][i].pop()
					self.container[category][i+1].add(rm)
					self.room[rm][1].add(gameID)
					self.catUsers[category] = self.catUsers[category] + 1
					return rm
		else:
			print 'cat invalid'
			return False
			
	
	def delUser(self, gameID, rm):
		category = self.room[rm][0]
		level = len(self.room[rm][1])
		self.room[rm][1].remove(gameID)
		self.container[category][level].remove(rm)
		level = len(self.room[rm][1])
		self.container[category][level].add(rm)
		self.catUsers[category] = self.catUsers[category] - 1
		
class Presence:
	def init(self, maxuser, catlist, servers):
		self.users = UserStash()
		self.rooms = RoomStash()
		self.rooms.init(maxuser, catlist, servers)

	def getState(self, gameID):
		return self.users.getState(gameID)

	def login(self, gameID):
		state = self.getState(gameID)
		if state[0] == 'U':
			state = ('L', False, False)
			self.users.setState(gameID, state)
			return (True, state)
		return (False, state)

	def logout(self, gameID):
		state = self.getState(gameID)
		if state[0] != 'G':
			state = ('U', False, False)
			self.users.setState(gameID, state)
			return (True, state)
		# playing game
		return (False, state)
	def purge(self, gameID):
		state = self.getState(gameID)
		if state[0] == 'G':
			self.gameLeave(gameID)

		state = ('U', False, False)
		self.users.setState(gameID, state)
		return (True, state)

	def gameEnter(self, gameID, category):
		state = self.getState(gameID)
		if state[0] == 'L' and state[1]==False:
			rm = self.rooms.addUser(gameID, category)
			if rm!=False:
				state = ('G', False, rm)
				self.users.setState(gameID, state)
				return (True, state)
		return (False, state)

	def gameLeave(self, gameID):
		state = self.getState(gameID)
		if state[0] == 'G':
			rm = state[2]
			self.rooms.delUser(gameID, rm)
			state = ('L', False, False)
			self.users.setState(gameID, state)
			return (True, state)
		return (False, state)

	def detach(self, gameID):
		state = self.getState(gameID)
		if state[0] == 'G':
			state = ('G', True, state[2])
			self.users.setState(gameID, state)
			return (True, state)
		return (False, state)

	def plug(self, gameID):
		state = self.getState(gameID)
		if state[0] != 'U' and state[1]!=False:
			state = (state[0], False, state[2])
			self.users.setState(gameID, state)
			return (True, state)
		return (False, state)

	def category(self):
		players = self.rooms.catUsers
		res = [ str(i) for i in players ]
		return ','.join(res)
		
		

