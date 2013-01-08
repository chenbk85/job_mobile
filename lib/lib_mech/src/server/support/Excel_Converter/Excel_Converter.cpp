// Excel_Converter.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Excel_Converter.h"
#include "util/jUtil.h"
#include "util/juFileEnum.h"

Excel_Converter* g_Excel_Converter=0;
jE g_eTYPE_INFO;
jE g_eTYPE_INFO_NS;// ���� ���ӽ����̽����� ����Ǵ� �ڷ�����.
jE Get_TYPE_INFO(tcstr szType)
{
	jE e = g_eTYPE_INFO_NS(szType);
	if(e.empty())
	{
		return g_eTYPE_INFO(szType);
	}
	return e;
}

nXML::jE g_Cfg;

for_each_jCV_my(jCV_DEF);

Excel_Converter::~Excel_Converter()
{
	g_Excel_Converter=0;
}
//--------------------------------------------------------------------------
Excel_Converter::Excel_Converter(std::tstring & buf)
//--------------------------------------------------------------------------
{
	g_Excel_Converter=this;
	m_peDocEbum=0;
	std::vector<std::tstring> o;
	nString::jSplit(buf, _T("\n"),m_lineList);

	if(m_lineList.size()<1)
	{
		jMB(_T("%s ������ ������ ����"), buf.c_str());
		exit(1);
	}
	m_it = m_lineList.begin();
	nString::jSplit_Str(*m_it, jSEP , o);
	if(o.size()!=3)
	{
		jMB(_T("namespace�� �н�����"), m_lineList[0].c_str() );
		exit(1);
	}
	_init(o[0],o[1],o[2]);
	++m_it;// ���� �Ľ̵ɶ����� ����
}


//--------------------------------------------------------------------------
void Excel_Converter::make_to_xml_SUB_add_table_to_xml(nXML::jE eCFG_Prototype, vector<std::tstring>& o)
//--------------------------------------------------------------------------
{
	jASSERT0(o.size()==3);
	jE eTableRoot = m_eDoc[eCFG_Prototype->GetTagID()];
	jE eTable = eTableRoot[o[TABLE_NAME_IDX]];
	eTable.AttrP(jS(HELP)).T() = o[TABLE_HELP_IDX];
	tstring itemName = o[0] + _T("Item");
	jE ePrevInsertItem;
	for( ;m_it!=m_lineList.end();	++m_it)
	{
		tstring str = *m_it;
		vector<std::tstring> out;
		nString::jSplit_Str(str,jSEP, out);
		if(out[0]!=itemName) 
		{
			if(out.size()==1)
			{
				if(ePrevInsertItem.full())
				{
					jVar v = ePrevInsertItem(jS(help));
					assert(v.full());
					fname_t buf;
					jt_sprintf(buf, _T("%s -[%s]-"),v->Get_cstr(),out[0].c_str());
					v.T() = buf;
					continue;
				}
			}
			break;
		}

		if(eCFG_Prototype->size()+1 != out.size())
		{
			eCFG_Prototype->DebugPrint(nInterface::g_pjILog);
			Debug_Print(out);
			jERROR(_T("%s �� �ʵ尹�� ��ġ ����(�ʵ忡�� ���๮�ڸ� Ȯ���ϼ���): %s"),eTable->GetTagName(),str.c_str());
		}

		int idx = eCFG_Prototype(jS(name_eng))->GetOrder()+1;
		tstring &name_eng = out[idx];
		if(!name_eng.size())
		{
			jWARN_T("name_eng not found -> %s ",str.c_str());
			++m_it;
			continue;
		}

		jE eNewItem;

		if(jt_strncmp(name_eng.c_str(), _T("<<"), 2)==0 )
		{
			nSTL::replace(name_eng,_T("<<"),_T(""));
			nSTL::replace(name_eng,_T(">>"),_T(""));
			eNewItem = eTable[name_eng];
			eNewItem[jS(inherit)].T() = true;
		}
		else
			eNewItem = eTable[name_eng];

		jIE* it = eCFG_Prototype->begin();
		jrFOR(it)
		{
			idx = it->GetOrder()+1;
			eNewItem[it->GetTagID()].T() = out[idx];

			// data_type���� NULL�϶��� ó��
			jE eDataType = eNewItem(jS(data_type));
			if(eDataType.full())
			{
				jVar v = eDataType.Var();
				if(!v->IsType(jIVar::EDcstr) || !jt_strlen(v->Get_cstr()))
				{
					v.T() = _T("undefined_t");
				}
				
				//--------------------------------------------------------------------------
				// Sys_T_Test3* , Sys_T_Test3*[] , Sys_T_Test3*[3] ���� �ٸ����̺� ������ �迭 �ʵ�ó��
				//--------------------------------------------------------------------------

				// ���� �迭ó������.
				tname256_t szName;
				jt_strcpy(szName, v->Get_cstr());
				TCHAR* ch = jt_strchr(szName,'[');
				if(ch)
				{
					*ch=0;
					++ch;
					tname256_t szNum;
					jt_strcpy(szNum,ch);
					ch = jt_strchr(szNum,']');
					if(!ch)
					{
						//eDataType->DebugPrint(true);
						jWARN_T("�迭ó���ʵ� %s �� [ ] ¦�� �Ȑ���", v->Get_cstr() );
						continue;
					}
					*ch=0;
					int iArrayLen = 0;
					if(jt_strlen(szNum))
					{
						iArrayLen= jt_atoi(szNum);
					}
					eNewItem.AttrP(jS(array_field)).T()=iArrayLen;
					v->Set_cstr(szName);
					m_Array_Ref.insert(eNewItem.BaseI());
				}
				// �ٸ� ���̺� ���� �ʵ�
				ch = jt_strchr(szName,'*');
				if(ch)
				{
					eNewItem.AttrP(jS(ref_field)).T() = true;
					*ch=0;
					v->Set_cstr(szName);
					m_Array_Ref.insert(eNewItem.BaseI());
				}
			}
		}

		ePrevInsertItem = eNewItem;
	}
	//eTable->DebugPrint(nInterface::g_pjILog);
}

//--------------------------------------------------------------------------
void Excel_Converter::make_to_xml()
//--------------------------------------------------------------------------
{
	jLIST_TYPEDEF_vector(std::tstring, o);
	int i=0;
	for(;m_it!=m_lineList.end();++i)
	{
		tstring &thisLine = *m_it;
		nString::jSplit_Str(thisLine , jSEP, o);
		++m_it; // ���� �Ľ̵ɶ����� ����

		nXML::jE eFind = g_Cfg->FindByDepth(1,o[0].c_str());
		if(eFind.empty())
		{
			Debug_Print(o);
			jWARN(_T("�Ľ��Ҽ� ���� ��Ʈ�� �߰� :thisLine= %s ,o[0]=%s"),thisLine.c_str() , o[0].c_str());

			continue;
		}
		make_to_xml_SUB_add_table_to_xml(eFind, o);
		jLOG(_T(" [%d] OK! convert to xml: %s"), i,o[1].c_str());
	}
	m_eDoc->GetDoc()->Save();

}
void Excel_Converter::_init(std::tstring &sNamespace, std::tstring &s,std::tstring &f)
{
	g_eTYPE_INFO_NS = g_eTYPE_INFO(-1)(sNamespace);
	if(g_eTYPE_INFO_NS.empty())
	{
		g_isGen_table_type=true;
		g_eTYPE_INFO_NS = g_eTYPE_INFO(-1)[sNamespace];
	}
	jASSERT0(g_eTYPE_INFO_NS.full());

	m_Namespace = sNamespace;
	m_save_file_path=s;
	m_FileName = f;

	m_eDoc = GetjIXml()->GetObj(_T("_Excel_Converter_"));
	if(m_eDoc.full()) 
		GetjIXml()->UnLoad(m_eDoc->GetDoc());

	filesystem::tpath file(m_save_file_path);
	f += jS(.xml);
	file /= f ;

	tstring sDoc = jT(file.string());
	GetjIXml()->NewFile(sDoc.c_str());

	nFileSystem::jFileName fn(sDoc.c_str());
	jID* pD = GetjIXml()->Load(sDoc.c_str());
	m_eDoc = pD;
	assert(m_eDoc->GetDoc() == pD);
	g_LoadedXml[fn.fname]= pD;
	if(m_FileName!= pv_excel_enum_file_name->Get_cstr())
	{
		fname_t szAQ;
		jt_sprintf(szAQ,_T("%s\\%s.xml"),m_save_file_path.c_str(),pv_excel_enum_file_name->Get_cstr());
		jID* pD = GetjIXml()->Load(szAQ);
		if(!pD)
		{
			jWARN(_T("%s is not found. %s�� ���Ե� xls������ ���� �����ϼ���."),szAQ, pv_excel_enum_file_name->Get_cstr());
		}
		else
		{
			m_peDocEbum = pD->BaseI()->Find(jS(enum));
			if(!m_peDocEbum)
			{
				jMB("asdf","asdf");
				int i=0;
				++i;
			}
		}
	}
}

cstr Excel_Converter::_jGetterType(cstr sz)
{
	jE e = Get_TYPE_INFO(sz);
	if(e.empty()) return sz;
	return e.Attr(jS(Getter))->Get_cstr();
}
cstr Excel_Converter::_jSetterType(cstr sz)
{
	jE e = Get_TYPE_INFO(sz);
	if(e.empty()) return sz;
	return e.Attr(jS(Setter))->Get_cstr();
}
tcstr Excel_Converter::_jSimpleType(tcstr sz)
{
	jE e = Get_TYPE_INFO(sz);
	if(e.empty()) return sz;
	return e.Attr(jS(Tag))->Get_cstr();
}


jE Excel_Converter::_IsEnumValue(jE max)
{
	if( jt_strchr(max->Get_cstr(), '=') ) return jE();

	if( m_eEnum.empty()) 
	{
		if(m_peDocEbum)
			return m_peDocEbum->FindByDepth(1,max->Get_cstr());
	}

	jIE* pE = m_eEnum->FindByDepth(1,max->Get_cstr());
	if(!pE)
	{
		if(m_peDocEbum)
			pE = m_peDocEbum->FindByDepth(1,max->Get_cstr());
	}
	return pE;
}

