import presence_pb2

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


