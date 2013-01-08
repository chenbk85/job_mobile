#pragma once

class CHT 
{
public:
	CHT() { 
		m_iGroup = GROUP_DEFAULT;
		m_iClass = HC_ONE;
		m_iType = HT_NONE;
		m_iAbility = HA_NONE;
	}
	virtual ~CHT() {}

public:
	void SetHT(int idx) {
		m_iGroup = gHT[idx][HM_GROUP];
		m_iClass = gHT[idx][HM_CLASS];
		m_iType  = gHT[idx][HM_TYPE];
		m_iAbility = gHT[idx][HM_ABILITY];
	}

public:
	int GetGroup() { return m_iGroup; }
	int GetClass() { return m_iClass; }
	int GetType()  { return m_iType;  }
	int	GetAbility() { return m_iAbility; }

protected:
	int m_iGroup;	// 화투 그룹 (1솔,2매화,3사쿠라,4흑싸리...)
	int m_iClass;	// 화투 계급 (광,십,오,일)
	int m_iType;	// 화투 타입 (광,고도리,쿠사,청단,홍단,쌍피)
	int m_iAbility;
};