# -*- coding:utf-8 -*-
import protocol
import random

random.seed()

g_itemInfo = {}
g_svcID = 100

g_notice =[ 
	(True, 1, u'테스트 팝업 공지'),
	(False, 2, u'안녕하세요. 피망 안드로이드 맞고에 오신것을 환영합니다')
	]


def canEnter(category, memberInfo):
	return True

def gameUpdate(updates):
	return False


def category(catlist, gameInfo):
	idx = 0
	for i in catlist:
		items = i.split(':')
		lmoney = 0
		for j in items:
			lmoney = 0
			if j[:10]== 'limitmoney':
				lmoney  = int(j.split('=')[1])
				break
		if lmoney <= int(gameInfo.money):
			catlist[idx] += ':Enter=1'
		else:
			catlist[idx] += ':Enter=0'
		idx=idx+1
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


