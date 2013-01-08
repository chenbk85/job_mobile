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
	int m_iGroup;	// ȭ�� �׷� (1��,2��ȭ,3�����,4��θ�...)
	int m_iClass;	// ȭ�� ��� (��,��,��,��)
	int m_iType;	// ȭ�� Ÿ�� (��,����,���,û��,ȫ��,����)
	int m_iAbility;
};