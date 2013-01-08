#pragma once




typedef struct tagCard{
public:
	enum{
		CARD_JOKER=4,
		CARD_BITS_NONE=0,
		CARD_BITS_1=1,
		CARD_BITS_2=2,
		CARD_BITS_3=4,
		CARD_BITS_4=8,
		CARD_BITS_5=16,
		CARD_BITS_6=32,
		CARD_BITS_7=64,
		CARD_BITS_8=128,
		CARD_BITS_9=256,
		CARD_BITS_10=512,
		CARD_BITS_11=1024,
		CARD_BITS_12=2048,
		CARD_BITS_0_13=4096,
		CARD_BITS_S=8,
		CARD_BITS_D=4,
		CARD_BITS_H=2,
		CARD_BITS_C=1,
	};
public:
	tagCard(void){ nType=-1; nNum=-1; }
	tagCard(int ncardvalue){ nType=ncardvalue/13; nNum=ncardvalue%13; }
	tagCard(int ntype, int nnum){ nType=ntype; nNum=nnum; }
public:
	BOOL IsJoker(void){ return (4<=nType); }
	BOOL IsEmpty(void){ return ((-1==nType)||(-1==nNum)); }
	BOOL IsEmptyType(void){ return (-1==nType); }
	BOOL IsEmptyNum(void){ return (-1==nNum); }
	BOOL IsCard(int ncardvalue){ return (CardValue()==ncardvalue); }
	BOOL IsCard(int ntype, int nnum){ return ((ntype==nType)&&(nnum==nNum)); }
	void Clear(void){ nType=nNum=-1; }
	int CardValue(void){ return (13*(nType%4)+nNum); }
	int CardStateValue(void){ if(9<=nNum){ return 10; } return nNum+1; }
	int CardBits(void){
		switch(nNum){
		case 0:
		case 13:
			return CARD_BITS_0_13;
		case 1:
			return CARD_BITS_1;
		case 2:
			return CARD_BITS_2;
		case 3:
			return CARD_BITS_3;
		case 4:
			return CARD_BITS_4;
		case 5:
			return CARD_BITS_5;
		case 6:
			return CARD_BITS_6;
		case 7:
			return CARD_BITS_7;
		case 8:
			return CARD_BITS_8;
		case 9:
			return CARD_BITS_9;
		case 10:
			return CARD_BITS_10;
		case 11:
			return CARD_BITS_11;
		case 12:
			return CARD_BITS_12;
		}
		return CARD_BITS_NONE;
	}
	int CardBitsType(void){
		switch(nType){
		case 0:
			return CARD_BITS_S;
		case 1:
			return CARD_BITS_D;
		case 2:
			return CARD_BITS_H;
		case 3:
			return CARD_BITS_C;
		}
		return CARD_BITS_NONE;
	}
public:
	void SetCardValue(int ncardvalue){ nType=ncardvalue/13; nNum=ncardvalue%13; }
	void SetCardValue(int ntype, int nnum){ nType=ntype; nNum=nnum; }
	void SetCardValue(tagCard* ptCard){
		if(NULL==ptCard) return;
		nType=ptCard->nType;
		nNum=ptCard->nNum;
	}
public:
	int nType;
	int nNum;
}tCard;

typedef struct tagCardArray{
public:
	tagCardArray(void){ Clear(); }
public:
	void Clear(void){ m_tCard.sCard=-1; m_tCard.sArray=-1; }
	void Empty(void){ m_tCard.sCard=-1; m_tCard.sArray=-1; }
public:
	union{
		int m_nCard;
		struct{
			short sCard;
			short sArray;
		}m_tCard;
	};
}tCardArray;

typedef struct tagResultFactor{
public:
	tagResultFactor(void){ Clear(); }
public:
	void Clear(void){ m_nResult=m_nSelect=0; m_tCardArray1=tCardArray(); m_tCardArray2=tCardArray(); }
	void Empty(void){
		m_tResult.cMade=-1; m_tResult.cAnother=-1; m_tResult.cOrder=-1; m_tResult.cReserve=-1; m_tSelect.sSelect=-1; m_tSelect.sMadeSelect=-1; 
		m_tCardArray1.Empty(); m_tCardArray2.Empty();
	}
	void Select(short sSelect, short sMadeSelect, bool bMadeSelect=FALSE){
		m_tSelect.sSelect=sSelect;
		m_tSelect.sMadeSelect=sMadeSelect;
		if(TRUE==bMadeSelect){
			m_tResult.cReserve=(char)m_tSelect.sMadeSelect;
		}
		else{
			m_tResult.cReserve=(char)m_tSelect.sSelect;
		}
	}
public:
	union{
		int m_nResult;
		struct{
			char cOrder;
			char cAnother;
			char cMade;
			char cReserve;
		}m_tResult;
	};
	union{
		int m_nSelect;
		struct{
			short sSelect; 
			short sMadeSelect;
		}m_tSelect;
	};
	tCardArray m_tCardArray1;
	tCardArray m_tCardArray2;
}tResultFactor;

typedef struct tagMade{
public:
	tagMade(void){ Clear(); }
	void Clear(void){ m_tCardArray1=m_tCardArray2=m_tCardArray3=tCardArray(); m_nMade=0; }
public:
	int m_nMade;
	tCardArray m_tCardArray1;
	tCardArray m_tCardArray2;
	tCardArray m_tCardArray3;
}tMade;

typedef struct tagRest{
public:
	tagRest(void){ Clear(); }
	void Clear(void){ m_tCardArray1=m_tCardArray2=tCardArray(); m_nOrder=m_nAnother=0; }
public:
	int m_nOrder;
	int m_nAnother;
	tCardArray m_tCardArray1;
	tCardArray m_tCardArray2;
}tRest;

class CResultFactor : public tResultFactor{
public:
	enum{
		MADETYPE_NONE=0,
		MADETYPE_NOANOTHER=1,
		MADETYPE_MADE=2,
	};
	enum{
		RESULT_NONE=-1,
		RESULT_NOMADE=0,
		RESULT_MADE=1,
		RESULT_NOJJOK=1,
		RESULT_NINE_FOUR=2,
		RESULT_FOOL_NINE_FOUR=3,
		RESULT_THREE_SEVEN=4,
		RESULT_FOUR_SEVEN=5,
		RESULT_JJOK=6,
		RESULT_NINE_FOUR_JJOK=7,
		RESULT_DDAND19=8,
		RESULT_THREE_SEVEN_DDANG=9,
		RESULT_FOOL_NINE_FOUR_DDANG=10,
		RESULT_DDAND10=11,
		RESULT_THREE_SEVEN_DDANG10=12,
		RESULT_GHANGDDANG138=13,
		RESULT_FOUR_SEVEN_GHANGDDANG138=14,
		RESULT_GHANGDDANG38=15,
		RESULT_ZERO=0,
		RESULT_ONE=1,
		RESULT_TWO=2,
		RESULT_THREE=3,
		RESULT_FOUR=4,
		RESULT_FIVE=5,
		RESULT_SIX=6,
		RESULT_SEVEN=7,
		RESULT_EIGHT=8,
		RESULT_NINE=9,
		RESULT_FOUR_SIX=10,
		RESULT_TEN_FOUR=11,
		RESULT_TEN_ONE=12,
		RESULT_ONE_NINE=13,
		RESULT_ONE_FOUR=14,
		RESULT_ONE_TWO=15,
		RESULT_1DDANG=16,
		RESULT_2DDANG=17,
		RESULT_3DDANG=18,
		RESULT_4DDANG=19,
		RESULT_5DDANG=20,
		RESULT_6DDANG=21,
		RESULT_7DDANG=22,
		RESULT_8DDANG=23,
		RESULT_9DDANG=24,
		RESULT_10DDANG=25,
		RESULT_13DDANG=26,
		RESULT_18DDANG=27,
		RESULT_38DDANG=28,
		RESULT_FIND=64,
	};
	enum{
		MADE_NONE=0,
		MADE_118=118,//1
		MADE_127=127,//2
		MADE_136=136,//3
		MADE_145=145,//4
		MADE_190=190,//5
		MADE_226=226,//6
		MADE_235=235,//7
		MADE_280=280,//8
		MADE_334=334,//9
		MADE_370=370,//10
		MADE_389=389,//11
		MADE_442=442,//12
		MADE_460=460,//13
		MADE_479=479,//14
		MADE_550=550,//15
		MADE_569=569,//16
		MADE_578=578,//17
		MADE_668=668,//18
		MADE_776=776,//19
		MADE_884=884,//20
		MADE_992=992,//21
		MADE_000=1000,//22
		MADENUM_NONE=0,
		MADENUM_118=1,
		MADENUM_127=2,
		MADENUM_136=3,
		MADENUM_145=4,
		MADENUM_190=5,
		MADENUM_226=6,
		MADENUM_235=7,
		MADENUM_280=8,
		MADENUM_334=9,
		MADENUM_370=10,
		MADENUM_389=11,
		MADENUM_442=12,
		MADENUM_460=13,
		MADENUM_479=14,
		MADENUM_550=15,
		MADENUM_569=16,
		MADENUM_578=17,
		MADENUM_668=18,
		MADENUM_776=19,
		MADENUM_884=20,
		MADENUM_992=21,
		MADENUM_000=22,
		MADE_TOTAL=22,
	};
public:
	CResultFactor(void):tResultFactor(){ InitResultFactor();  }
	virtual ~CResultFactor(void){ FreeResultFactor(); }
	void InitResultFactor(void){ m_nIndex=0; m_nRule=0; }
	void FreeResultFactor(void){ ClearResultFactor(); }
	void ClearResultFactor(void){ Clear(); m_vCard.clear(); m_vtMade.clear(); m_nIndex=m_nResult=0; m_tSelect.sSelect=m_tSelect.sMadeSelect=0; m_tCardArray1=tCardArray(); m_tCardArray2=tCardArray(); }
public:
	int m_nRule;
	int m_nIndex;
	vector<int> m_vCard;
	vector<tMade> m_vtMade;
public:
	bool GetMadePtr(int nArray, tMade** pptMade){
		if(FALSE==IsUsableMadeArray(nArray)) return FALSE;
		(*pptMade)=&m_vtMade[nArray];
		return TRUE;
	}
	void SetRule(int nRule){ m_nRule=nRule; }
	int GetMadeCount(void){ return (int)m_vtMade.size(); }
public:
	void SetResultIndex(int nIndex){ m_nIndex=nIndex;}
	bool IsUsableArray(int nArray);
	bool IsUsableArray(int nArray1, int nArray2);
	bool IsUsableArray(int nArray1, int nArray2, int nArray3);
	bool IsUsableMadeArray(int nMadeArray);
	void AddResultCard(int nCard);
	void SetResultCard(vector<int> vCard);
	void SetResultCard(vector<long> vCard);
	void ChangeResultCard(int nArray, int nCard);
	void DelResultCard(int nArray);
	void SetResultFactor(CResultFactor* pcResultFactor);
public:
	void SetResultFactorNoMadeToSelect(int nMadeType, short sSelect, int nFindOrder=RESULT_NONE);
	void SetResultFactorNoMadeToArray(int nMadeType, int nArray1, int nArray2, int nFindOrder=RESULT_NONE);
	void SetResultFactorNoMadeToSelect(int nMadeType, short sSelect, int &nArray1, int &nArray2, int nFindOrder=RESULT_NONE);
	void SetResultFactorNoMadeToArray(int nMadeType, short &sSelect, int nArray1, int nArray2, int nFindOrder=RESULT_NONE);
	int FindResultFactorNoMade(int nMadeType, char cAnother, char cOrder, int &nArray1, int &nArray2, int nFindOrder=RESULT_NONE);
	void SetResultFactorMadeToSelect(int nMadeType, short sMadeSelect, int nFindOrder=RESULT_NONE);
	void SetResultFactorMadeToArray(int nMadeType, int nMadeArray1, int nMadeArray2, int nMadeArray3, int nFindOrder=RESULT_NONE);
	void SetResultFactorMadeToRemain(int nMadeType, int nArray1, int nArray2, int nFindOrder=RESULT_NONE);
	void SetResultFactorMadeToSelect(int nMadeType, short sMadeSelect, int &nArray1, int &nArray2, int nFindOrder=RESULT_NONE);
	void SetResultFactorMadeToArray(int nMadeType, int nMadeArray1, int nMadeArray2, int nMadeArray3, int &nArray1, int &nArray2, int nFindOrder=RESULT_NONE);
	void SetResultFactorMadeToRemain(int nMadeType, short &sMadeSelect, int nArray1, int nArray2, int nFindOrder=RESULT_NONE);
	int FindResultFactorMade(int nMadeType, char cAnother, char cOrder, short &sMadeSelect, int &nArray1, int &nArray2, int nFindOrder=RESULT_NONE);
public:
	int HighResultFactor(int nMadeType, int nFindOrder=RESULT_NONE);
	int HighResultFactor(int nMadeType, int &nArray1, int &nArray2, int nFindOrder=RESULT_NONE);
	int ResultFactor(int nMadeType, vector<tMade>* pvtMadeCard, vector<tRest>* pvtRestCard, int nFindOrder=RESULT_NONE);
	bool IsResultFactor(int nMadeType, char cOrder, int nFindOrder=RESULT_NONE);
	void MadeResultFactor(void);
	void MadeResultExceptFactor(vector<tCardArray>* pvExecptCardArray);
	short MadeResultExceptFactor(short sMadeSelect, vector<tCardArray>* pvExecptCardArray);
	short SelectToArray(short sSelect, int &nArray1, int &nArray2);
	short MadeSelectToArray(short sMadeSelect, int &nArray1, int &nArray2);
	short MadeSelectToArray(int nMadeArray1, int nMadeArray2, int nMadeArray3, int &nArray1, int &nArray2);
	short MadeSelectToMadeArray(short sMadeSelect, int &nMadeArray1, int &nMadeArray2, int &nMadeArray3);
	short ArrayToSelect(int nArray1, int nArray2);
	short ArrayToMadeSelect(int nArray1, int nArray2);
	short ArrayToMadeSelect(int nMadeArray1, int nMadeArray2, int nMadeArray3);
public:
	int GetResultFactor(int nMadeType, bool bIsDdang19, bool bIsDdang10, bool bIsGhangDdang138, bool bIsGhangDdang38, bool bIsFool94);
	char GetResultAnother(int nMadeType, bool bIsDdang19, bool bIsDdang10, bool bIsGhangDdang138, bool bIsGhangDdang38, bool bIsFool94);
	string GetResultString(int nMadeType, bool bIsDdang19, bool bIsDdang10, bool bIsGhangDdang138, bool bIsGhangDdang38, bool bIsFool94);
	bool OverResultFactor(int nMadeType, char cAnother, char cOrder);
public:
	static char GetOrder(int nMadeType, vector<long> vtCard, int nFindOrder=RESULT_NONE);
	static char GetAnother(int nMadeType, vector<long> vtCard, int nFindOrder=RESULT_NONE);
	static bool IsFindOrder(int nMadeType, vector<long> vtCard, int nFindOrder=RESULT_NONE);
	static int GetMade(vector<long> vtCard);
	static int GetMadeArray(vector<long> vtCard);
	static bool IsMade(vector<long> vtCard);
	static char GetOrder(int nMadeType, int nCard1, int nCard2, int nFindOrder=RESULT_NONE);
	static char GetAnother(int nMadeType, int nCard1, int nCard2, int nFindOrder=RESULT_NONE);
	static bool IsFindOrder(int nMadeType, int nCard1, int nCard2, int nFindOrder=RESULT_NONE);
	static int GetMade(int nCard1, int nCard2, int nCard3);
	static int GetMadeArray(int nCard1, int nCard2, int nCard3);
	static int IsAnother(char cAnother);
	static int IsAnother(int nMadeType, char cMade, char cAnother);
	static int MadeToArray(int nMade);
	static int MadeFromArray(int nMadeArray);
	static void MadeLineCol(int nMade, vector<long> vtCard, vector<int>* pvtMadePos);
	static void MadeLineCol(vector<long> vtCard, vector<int> vtMadePos[MADE_TOTAL]);
	static void MadeList(vector<int> vtCard, vector<tInt3>* pvtMade, vector<int>* pvMade, int nSortType=0);
	static void MadeList(vector<long> vtCard, vector<tInt3>* pvtMade, vector<int>* pvMade, int nSortType=0);
	static string GetString(int nMadeType, char cAnother, char cOrder);
	static string GetMadeString(int nMade);
	static string GetMadeString_Num(int nMade);
	static string GetMadeArrayString(int nMadeArray);
	static int ArrayToSelect(int nArray1, int nArray2, int nTotal);
	static void SelectToArray(int nSelect, int nTotal, int &nArray1, int &nArray2);
	static void ResultToCard(int nMadeType, char cAnother, char cOrder, int &nCard1, int &nCard2);
	static void ResultToCard(int nMadeType, char cMade, char cAnother, char cOrder, int &nMadeCard1, int &nMadeCard2, int &nMadeCard3, int &nCard1, int &nCard2);
//	static int HighRestCard(vector<tRest>* pvtRestCard, bool b94);
//	static int HighRestCard(int nMadeType, vector<tRest>* pvtRestCard, vector<long> vCard, bool b94);
	static int HighRestCard(vector<tRest>* pvtRestCard, int &nSelect94);
	static int HighRestCard(int nMadeType, vector<tRest>* pvtRestCard, vector<long> vCard, int nFindOrder=RESULT_NONE);
	static int HighRestCard94(int nMadeType, vector<tRest>* pvtRestCard, vector<long> vCard, int &nSelect94, int nFindOrder=RESULT_NONE);
	static bool SameCard(tRest* ptRest, int nCard1, int nCard2);
	static int FindMade(vector<tMade>* pvtMadeCard, int nMade);
	static int OrderAnother(vector<tRest>* pvtRestCard, char aAnother, char aOrder);
};

class CResultOrder : public vector<CResultFactor>
{
public:
	enum{
		RESULT_NONE=0,
		RESULT_ONLY=1,
		RESULT_REMATCH=2,
		RESULT_REMATCH_NOMADE=4|RESULT_REMATCH,
		RESULT_REMATCH_SAME=8|RESULT_REMATCH,
		RESULT_REMATCH_94=16|RESULT_REMATCH,
		RESULT_REMATCH_FOOL94=32|RESULT_REMATCH,
		RESULT_REMATCH_FIND=64|RESULT_REMATCH,
		RESULT_ONLY_DDANG19=128|RESULT_ONLY,
		RESULT_ONLY_DDANG10=256|RESULT_ONLY,
		RESULT_ONLY_GHANGDDANG138=512|RESULT_ONLY,
		RESULT_ONLY_GHANGDDANG38=1024|RESULT_ONLY,
	};
public:
	vector<int> m_vDDang19;
	vector<int> m_vDDang10;
	vector<int> m_vGhangDDang138;
	vector<int> m_vGhangDDang38;
	vector<int> m_vFool94;
	vector<int> m_vtResultIndex;
	vector<int> m_vtResult;
	int m_nMadeType;
	CRangeTable m_cRangeTable;
	int m_nFindOrder;
public:
	CResultOrder(void):vector<CResultFactor>(){ InitResultOrder(); }
	virtual ~CResultOrder(void){ FreeResultOrder(); }
	void InitResultOrder(void){ m_nMadeType=CResultFactor::MADETYPE_NONE; m_nFindOrder=CResultFactor::RESULT_NONE; }
	void FreeResultOrder(void){ m_nMadeType=CResultFactor::MADETYPE_NONE; m_nFindOrder=CResultFactor::RESULT_NONE; ClearResultOrder(); }
	void ClearResultOrder(void){ clear(); m_vDDang19.clear(); m_vDDang10.clear(); m_vGhangDDang138.clear(); m_vGhangDDang38.clear(); m_vtResultIndex.clear(); m_vtResult.clear(); m_vFool94.clear(); }
	bool IsUsableArray(int nArray){ return ((0<=nArray)&&(((int)size()-1)>=nArray)); }
public:
	void SetMadeType(int nMadeType=CResultFactor::MADETYPE_NONE){ m_nMadeType=nMadeType; }
	void AddFindOrder(int nFindOrder, int nRange){ m_cRangeTable.AddRangeTable(nFindOrder, nRange); }
	void DelFindOrder(int nArray){ m_cRangeTable.DelRangeTable(nArray); }
	void DelFindOrder(void){ m_cRangeTable.DelRangeTable(); }
	void MakeFindOrder(void){ m_nFindOrder=m_cRangeTable.RandomRangeTableIdenty(); }
public:
	void AddResultOrderNoMadeToSelect(int nIndex, int nCard, int nSelect=-1);
	void AddResultOrderNoMadeToArray(int nIndex, int nCard, int nArray1=-1, int nArray2=-1);
	void AddSetResultOrderNoMadeToSelect(int nIndex, vector<int> vCard, int nSelect=-1, bool bHigh=FALSE);
	void AddSetResultOrderNoMadeToArray(int nIndex, vector<int> vCard, int nArray1=-1, int nArray2=-1, bool bHigh=FALSE);
	void AddSetResultOrderNoMadeToSelect(int nIndex, vector<long> vCard, int nSelect=-1, bool bHigh=FALSE);
	void AddSetResultOrderNoMadeToArray(int nIndex, vector<long> vCard, int nArray1=-1, int nArray2=-1, bool bHigh=FALSE);
	bool FindResultOrderNoMadeToSelect(int nIndex, int nCard, int nSelect=-1);
	bool FindResultOrderNoMadeToArray(int nIndex, int nCard, int nArray1=-1, int nArray2=-1);
	bool SetResultOrderNoMadeToSelect(int nIndex, vector<int> vCard, int nSelect=-1, bool bHigh=FALSE);
	bool SetResultOrderNoMadeToArray(int nIndex, vector<int> vCard, int nArray1=-1, int nArray2=-1, bool bHigh=FALSE);
	bool SetResultOrderNoMadeToSelect(int nIndex, vector<long> vCard, int nSelect=-1, bool bHigh=FALSE);
	bool SetResultOrderNoMadeToArray(int nIndex, vector<long> vCard, int nArray1=-1, int nArray2=-1, bool bHigh=FALSE);
	bool ChangeFactorResultOrderNoMadeToSelect(int nIndex, int nSelect, int &nArray1, int &nArray2);
	bool ChangeFactorResultOrderNoMadeToArray(int nIndex, int nArray1=-1, int nArray2=-1);
	void AddResultOrderMadeToSelect(int nIndex, int nCard, int nMadeSelect=-1);
	void AddResultOrderMadeToArray(int nIndex, int nCard, int nMadeArray1=-1, int nMadeArray2=-1, int nMadeArray3=-1);
	void AddResultOrderMadeToRemain(int nIndex, int nCard, int nArray1=-1, int nArray2=-1);
	void AddSetResultOrderMadeToSelect(int nIndex, vector<int> vCard, int nMadeSelect=-1, bool bHigh=FALSE);
	void AddSetResultOrderMadeToArray(int nIndex, vector<int> vCard, int nMadeArray1=-1, int nMadeArray2=-1, int nMadeArray3=-1, bool bHigh=FALSE);
	void AddSetResultOrderMadeToRemain(int nIndex, vector<int> vCard, int nArray1=-1, int nArray2=-1, bool bHigh=FALSE);
	void AddSetResultOrderMadeToSelect(int nIndex, vector<long> vCard, int nMadeSelect=-1, bool bHigh=FALSE);
	void AddSetResultOrderMadeToArray(int nIndex, vector<long> vCard, int nMadeArray1=-1, int nMadeArray2=-1, int nMadeArray3=-1, bool bHigh=FALSE);
	void AddSetResultOrderMadeToRemain(int nIndex, vector<long> vCard, int nArray1=-1, int nArray2=-1, bool bHigh=FALSE);
	bool FindResultOrderMadeToSelect(int nIndex, int nCard, int nMadeSelect=-1);
	bool FindResultOrderMadeToArray(int nIndex, int nCard, int nMadeArray1=-1, int nMadeArray2=-1, int nMadeArray3=-1);
	bool FindResultOrderMadeToRemain(int nIndex, int nCard, int nArray1=-1, int nArray2=-1);
	bool SetResultOrderMadeToSelect(int nIndex, vector<int> vCard, int nMadeSelect=-1, bool bHigh=FALSE);
	bool SetResultOrderMadeToArray(int nIndex, vector<int> vCard, int nMadeArray1=-1, int nMadeArray2=-1, int nMadeArray3=-1, bool bHigh=FALSE);
	bool SetResultOrderMadeToRemain(int nIndex, vector<int> vCard, int nArray1=-1, int nArray2=-1, bool bHigh=FALSE);
	bool SetResultOrderMadeToSelect(int nIndex, vector<long> vCard, int nMadeSelect=-1, bool bHigh=FALSE);
	bool SetResultOrderMadeToArray(int nIndex, vector<long> vCard, int nMadeArray1=-1, int nMadeArray2=-1, int nMadeArray3=-1, bool bHigh=FALSE);
	bool SetResultOrderMadeToRemain(int nIndex, vector<long> vCard, int nArray1=-1, int nArray2=-1, bool bHigh=FALSE);
	bool ChangeFactorResultOrderMadeToSelect(int nIndex, int nMadeSelect, int &nArray1, int &nArray2);
	bool ChangeFactorResultOrderMadeToArray(int nIndex, int nMadeArray1, int nMadeArray2, int nMadeArray3, int &nArray1, int &nArray2);
	bool ChangeFactorResultOrderMadeToRemain(int nIndex, int &nMadeSelect, int nArray1=-1, int nArray2=-1);
public:
	bool ResultOrder(int nIndexTotal);
	int ResultOrderValue(int nIndexTotal);
	int ResultOrderToResult(int nIndexTotal);
	void MakeResultOrder(int nIndexTotal, char &cMade, char &cAnother, char &cOrder);
	int MaxMadeResultOrder(void);
public:
	int FindIndexToArrayResultOrder(int nIndex);
	bool FindIndexToArrayResultOrder(int nIndex, int &nArray);
	bool IsResultFactor(int nIndex, char cOrder);
	void SwapResultOrder(int nArray1, int nArray2);
	void DelResultOrder(int nIndex);
	void ClearResultOrder(int nIndex);
	void HighResultOrder(int nIndex);
	void SetResultOrder(void);
	CResultFactor* GetResultOrder(int nIndex);
	int GetResultOrder(int nIndex, CResultFactor** ppcResultFactor);
	int GetResultOrderArray(int nArray, CResultFactor** ppcResultFactor);
	string GetResultOrderString(int nIndex);
	int GetResultOrderTotal(void){ return (int)size(); }
public:
	void AddCheck(char cAnother, int nIndex);
	void DelCheck(char cAnother, int nIndex);
	void DelCheck(int nIndex);
	char FindCheck(int nIndex);
	bool FindCheck(char cAnother, int nIndex);
	void ClearCheck(void);
public:
	void Sort_Index(bool bAscOrDes=FALSE);
	void Sort_Made(bool bAscOrDes=FALSE);
	void Sort_Another(bool bAscOrDes=FALSE);
	void Sort_Order(bool bAscOrDes=FALSE);
	void Sort_MadeOrderAndAnother(bool bAscOrDes=FALSE);
	friend void Swap(void* pVoid, int nArray1, int nArray2);
	friend int Index(void* pVoid, int nArray);
	friend int Made(void* pVoid, int nArray);
	friend int Another(void* pVoid, int nArray);
	friend int Order(void* pVoid, int nArray);
	friend int MadeOrderAndAnother(void* pVoid, int nArray);
};

typedef enum ePokerType{
	POKERTYPE_NONE=0,
	POKERTYPE_ONEPAIR=1,
	POKERTYPE_TWOPAIR=2,
	POKERTYPE_THREE=4,
	POKERTYPE_STRAIGHT=8,
	POKERTYPE_BACKSTRAIGHT=16,
	POKERTYPE_MOUNTAIN=32,
	POKERTYPE_FLUSH=64,
	POKERTYPE_FULLHOUSE=128,
	POKERTYPE_FOUR=256,
	POKERTYPE_STRAIGHTFLUSH=512,
	POKERTYPE_BACKSTRAIGHTFLUSH=1024,
	POKERTYPE_ROYALSTRAIGHTFLUSH=2048,
}ePokerType;

class CPokerRules : public CTVVector<int>
{
public:
	tLineCol m_tLineCol_StraightFlush;
	tLineCol m_tLineCol_Straight;
	ePokerType m_ePokerType;
	CTVector<tCard> m_ctMakeCard;
	CTVector<tCard> m_ctRestCard;
	tHyperInt m_tHyperInt_Level;
	CTVector<tLineCol> m_ctStraightFlush;
	CTVector<tLineCol> m_ctStraight;
	CTVector<int> m_ctVector4;
	CTVector<int> m_ctVector3;
	CTVector<int> m_ctVector2;
public:
	CPokerRules(void):CTVVector<int>(){ InitPokerRules(); }
	virtual ~CPokerRules(void){ FreePokerRules(); }
	void InitPokerRules(void){ m_tLineCol_StraightFlush=m_tLineCol_Straight=tLineCol(-1, -1); m_ePokerType=POKERTYPE_NONE; m_tHyperInt_Level.Clear(); }
	void FreePokerRules(void){ DelVector(); }
public:
	void CreatePokerRules(void);
	void ClearPokerRules(void);
	BOOL SetPokerRulesType(ePokerType eType);
	void SetPokerRules(int nCardValue...);
	void SetPokerRules(CTVector<tCard>* pctCard);
	void SetMakePokerRules(CTVector<tCard>* pctMakeCard, CTVector<tCard>* pctRestCard, int nCardValue...);
	void SetMakePokerRules(CTVector<tCard>* pctMakeCard, CTVector<tCard>* pctRestCard, CTVector<tCard>* pctCard, int nStart=0, int nEnd=0);
	void SetEnablePokerRules(tCard* ptCard, int nCardValue...);
	void SetEnablePokerRules(tCard* ptCard, CTVector<tCard>* pctCard);
	void MakeCheck(void);
	void MakeCheck(CTVector<tCard>* pctMakeCard, CTVector<tCard>* pctRestCard);
	void MakeEnableCheck(tCard* ptCard);
	void CheckPokerRules(void);
	void CheckPokerRules(CTVector<tCard>* pctMakeCard);
	void CheckEnablePokerRules(tCard* ptCard);
	BOOL MakeLineColCard12(tLineCol* ptLineCol, CTVector<tCard>* pctCard, int nCount, BOOL bInverse=TRUE);
	BOOL MakeLineColCard(tLineCol* ptLineCol, CTVector<tCard>* pctCard, int nCount, BOOL bInverse=TRUE);
	BOOL MakeSameLineCard(int nLine, CTVector<tCard>* pctCard, int nCount);
	BOOL MakeSameColCard(int nCol, CTVector<tCard>* pctCard, int nCount);
	BOOL MakeMaxSameColCard(int nLine, int nOver, CTVector<tCard>* pctCard, int nCount);
	BOOL MakeFirstCard(CTVector<tCard>* pctCard, int nCount);
	BOOL MakeFirstCard(CTVector<tCard>* pctCard, CTVector<tCard>* pcRestCard, int nCount);
	BOOL FindCard(CTVector<tCard>* pctCard, int nType, int nNum);
	BOOL FindLineColCard12(tLineCol* ptLineCol, tCard* ptCard);
	BOOL FindLineColCard(tLineCol* ptLineCol, tCard* ptCard);
	BOOL FindSameLineCard(int nLine, tCard* ptCard);
	BOOL FindSameColCard(int nCol, tCard* ptCard);
	BOOL FindMaxSameColCard(int nLine, int nOver, tCard* ptCard);
	BOOL FindFirstSameCard(tCard* ptCard);
	BOOL FindFirstCard(tCard* ptCard);
	tHyperInt MakeLevel(void){ m_tHyperInt_Level=MakeLevel(m_ePokerType, &m_ctMakeCard, &m_ctRestCard); return m_tHyperInt_Level; }
	string MakeString(void){ return MakeString(m_ePokerType, &m_ctMakeCard); }
public:
	static tHyperInt MakeLevel(ePokerType eType, CTVector<tCard>* pctMakeCard, CTVector<tCard>* pctRestCard=NULL);
	static string GetPokerRulesCardString(ePokerType eType);
	static string GetPokerRulesCardAlphaBetString(ePokerType eType);
	static string GetPokerRulesCardValueString(ePokerType eType);
	static string GetCardTypeNumString(int nCardType, int nCardNum);
	static string GetCardNumString(int nCardNum);
	static string GetCardTypeString(int nCardType);
	static string MakeString(ePokerType eType, CTVector<tCard>* pctMakeCard);
};


class CPosInfo
{
public:
	enum{
		InsertType_None=0,
		InsertType_DiffToLeftRight=1,
		InsertType_DiffToTopBottom=2,
		InsertType_DiffToBoth=4,
		InsertType_AreaToCutLeftRight=8,
		InsertType_AreaToCutTopBottom=16,
		InsertType_AreaToCutBoth=32,
		InsertType_AreaFillToLeftRight=64,
		InsertType_AreaFillToTopBottom=128,
		InsertType_AreaFillToBoth=256,
		InsertType_LineCol=512,
		InsertType_PointList=1024,
		InsertType_Num=12,
	};
	enum{
		PosType_None=0,
		PosType_Start=1,
		PosType_User=2,
		PosType_Pan=3,
	};
public:
	POINT m_pPos;
	POINT m_pDiff;
	RECT m_rArea;
	int m_nPosType;
	union{
		unsigned int m_nInsertType;
		struct{
			unsigned short int High;
			unsigned short int Low;
		}m_tInsertType;
	};
	vector<int> m_vLineCol;
	vector<POINT> m_vPointList;
public:
	CPosInfo(void){ InitPosInfo(); }
	virtual ~CPosInfo(void){ FreePosInfo(); }
	void InitPosInfo(void){ m_pPos.x=m_pPos.y=0; m_pDiff.x=m_pDiff.y=0; m_rArea.left=m_rArea.top=m_rArea.right=m_rArea.bottom=0; m_nPosType=PosType_None; m_nInsertType=InsertType_None; }
	void FreePosInfo(void){ ClearPosInfo(); }
	void ClearPosInfo(void){ m_pPos.x=m_pPos.y=0; m_pDiff.x=m_pDiff.y=0; m_rArea.left=m_rArea.top=m_rArea.right=m_rArea.bottom=0; m_nPosType=PosType_None; m_nInsertType=InsertType_None; m_vLineCol.clear(); }
public:
	POINT &GetPos(void){ return m_pPos; }
	POINT &GetDiff(void){ return m_pDiff; }
	RECT &GetArea(void){ return m_rArea; }
	int &GetPosType(void){ return m_nPosType; }
	unsigned int &GetInsertType(void){ return m_nInsertType; }
	unsigned short int &GetInsertTypeHigh(void){ return m_tInsertType.High; }
	unsigned short int &GetInsertTypeLow(void){ return m_tInsertType.Low; }
public:
	void SetPosInfo(POINT pPos){ m_pPos=pPos; }
	void SetPosInfo(int x, int y){ m_pPos.x=x; m_pPos.y=y; }
	void SetPosDiff(POINT pDiff){ m_pDiff=pDiff; }
	void SetPosDiff(int x, int y){ m_pDiff.x=x; m_pDiff.y=y; }
	void SetPosArea(SIZE Size){ m_rArea.left=m_pPos.x; m_rArea.top=m_pPos.y; m_rArea.right=m_pPos.x+Size.cx; m_rArea.bottom=m_pPos.y+Size.cy; }
	void SetPosArea(int cx, int cy){ m_rArea.left=m_pPos.x; m_rArea.top=m_pPos.y; m_rArea.right=m_pPos.x+cx; m_rArea.bottom=m_pPos.y+cy; }
	void SetPosType(int nPosType){ m_nPosType=nPosType; }
	void SetInsertType(unsigned short int nInsertTypeHigh, unsigned short int nInsertTypeLow=0){ m_tInsertType.High=nInsertTypeHigh; m_tInsertType.Low=nInsertTypeLow; }
	void SetPosInfo_Diff(POINT pPos, POINT pDiff){ m_pPos=pPos; m_pDiff=pDiff; }
	void SetPosInfo_Area(RECT rArea){ m_rArea=rArea; m_pPos.x=m_rArea.left; m_pPos.y=m_rArea.top; }
	void SetPosInfo_LineCol(RECT rArea, POINT pDiff, int nLineCol, ...);
public:
	int AddLineCol(int nLineCol){ int nArray=(int)m_vLineCol.size(); m_vLineCol.push_back(nLineCol); return nArray; }
	void DelLineCol(int nArray){ if((0<=nArray)&&((int)m_vLineCol.size()>nArray)) m_vLineCol.erase(&m_vLineCol[nArray]); }
	void DelLineCol(void){ m_vLineCol.clear(); }
	int TotalLineCol(void){ return (int)m_vLineCol.size(); }
	bool GetLineCol(int nArray, int &nLineCol){ if((0<=nArray)&&((int)m_vLineCol.size()>nArray)){ nLineCol=m_vLineCol[nArray]; return TRUE; } return FALSE; }
	int AddPointList(POINT pPos){ int nArray=(int)m_vPointList.size(); m_vPointList.push_back(pPos); return nArray; }
	void DelPointList(int nArray){ if((0<=nArray)&&((int)m_vPointList.size()>nArray)) m_vPointList.erase(&m_vPointList[nArray]); }
	void DelPointList(void){ m_vPointList.clear(); }
	int TotalPointList(void){ return (int)m_vPointList.size(); }
	bool GetPointList(int nArray, POINT &pPos){ if((0<=nArray)&&((int)m_vPointList.size()>nArray)){ pPos=m_vPointList[nArray]; return TRUE; } return FALSE; }
public:
	int StringToInsertType(string str);
	string InsertTypeToString(int InsertType);
public:
	POINT FindPos(int nArray, int nPosCount, int nTotal, SIZE Size, bool bFindLow=TRUE);
	POINT FindPos(int nArray, int nPosCount, int nTotal, int cx, int cy, bool bFindLow=TRUE);
	POINT FindPos(int nArray, int nPosCount, int nTotal, bool bFindLow=TRUE);
	POINT FindPos_DiffToLeftRight(POINT pPos, int nArray);
	POINT FindPos_DiffToTopBottom(POINT pPos, int nArray);
	POINT FindPos_DiffToBoth(POINT pPos, int nArray);
	POINT FindPos_AreaToCutLeftRight(POINT pPos, int nArray, int nTotal, SIZE Size);
	POINT FindPos_AreaToCutTopBottom(POINT pPos, int nArray, int nTotal, SIZE Size);
	POINT FindPos_AreaToCutBoth(POINT pPos, int nArray, int nTotal, SIZE Size);
	POINT FindPos_AreaToCutLeftRight(POINT pPos, int nArray, int nTotal, int cx, int cy);
	POINT FindPos_AreaToCutTopBottom(POINT pPos, int nArray, int nTotal, int cx, int cy);
	POINT FindPos_AreaToCutBoth(POINT pPos, int nArray, int nTotal, int cx, int cy);
	POINT FindPos_AreaToCutLeftRight(POINT pPos, int nArray, int nTotal);
	POINT FindPos_AreaToCutTopBottom(POINT pPos, int nArray, int nTotal);
	POINT FindPos_AreaToCutBoth(POINT pPos, int nArray, int nTotal);
	POINT FindPos_AreaFillToLeftRight(POINT pPos, int nArray, int nTotal, SIZE Size);
	POINT FindPos_AreaFillToTopBottom(POINT pPos, int nArray, int nTotal, SIZE Size);
	POINT FindPos_AreaFillToBoth(POINT pPos, int nArray, int nTotal, SIZE Size);
	POINT FindPos_AreaFillToLeftRight(POINT pPos, int nArray, int nTotal, int cx, int cy);
	POINT FindPos_AreaFillToTopBottom(POINT pPos, int nArray, int nTotal, int cx, int cy);
	POINT FindPos_AreaFillToBoth(POINT pPos, int nArray, int nTotal, int cx, int cy);
	POINT FindPos_AreaFillToLeftRight(POINT pPos, int nArray, int nTotal);
	POINT FindPos_AreaFillToTopBottom(POINT pPos, int nArray, int nTotal);
	POINT FindPos_AreaFillToBoth(POINT pPos, int nArray, int nTotal);
	POINT FindPos_LineCol(POINT pPos, int nArray);
	POINT FindPos_PointList(POINT pPos, int nArray);
};


class CLineCol{
public:
	enum{
		LINE_1=0,
		LINE_2=1,
		LINE_3=2,
		COL_1=1,
		COL_2=5,
		COL_3=10,
		COL_MOL=25,
		COL_TOTAL=3,		
	};
	long m_lLine;
	long m_lCol;
public:
	CLineCol(void){ Clear(); }
	virtual ~CLineCol(void){}
public:
	void Clear(){
		m_lLine = 0;
		m_lCol = 0;
	}
	void SetLineMoney(long lLine, long lCol){
		m_lLine = lLine; m_lCol = lCol;
	}
	bool IsLine(long lLine){
		return (((LINE_1<=lLine)||(LINE_3>=lLine))?(TRUE):(FALSE));
	}
	bool IsCol(long lCol){
		return (((COL_1==lCol)||(COL_2==lCol)||(COL_3==lCol)||(COL_MOL==lCol))?(TRUE):(FALSE));
	}
};

class CBetLog : CTPairVector<int, string>
{
public:
	enum{
		BET_STRING=12,
	};
public:
	CBetLog(void){ InitBetLog(); }
	virtual ~CBetLog(void){ FreeBetLog(); }
	void InitBetLog(void){}
	void FreeBetLog(void){ DelVector(); }
public:
	int AddBetLog(int nIdenty){
		string str;
		str.clear();
		str.resize(BET_STRING, '-');
		return FindBeginAddVector(nIdenty, str);
	}
	bool DelBetLog(int nIdenty){ return (-1!=FindBeginDelVector(nIdenty)); }
	void DelBetLog(void){ DelVector(); }
	bool GetBetLog(int nIdenty, string &str){ return (-1!=FindBeginVector(nIdenty, str)); }
	bool SetBetLog(int nIdenty, string str){ return (-1!=FindBeginAddVector(nIdenty, str)); }
public:
	bool SetBetLogReceive(int nBetIdenty, int nIdenty, int nBetTurn=0, int nBet=0, vector<CLineCol>* pvtSelectLine=NULL);
	char GetBetChar(int nBet);
	char GetBetOrder(int nPos);
};