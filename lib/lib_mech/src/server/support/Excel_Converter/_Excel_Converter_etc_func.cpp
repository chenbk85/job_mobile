/* file : _Excel_Converter_etc_func.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-03-22 19:13:52
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "Excel_Converter.h"
// 주 루틴에서 



void Excel_Converter::_print_help_tostring(tofstream &of,print_help_tstring_ft *pRefFunc,print_help_tstring_ft *pNotRefFunc)
{

	//--------------------------------------------------------------------------
	// FromString와 ToString핼프 함수 출력
	//--------------------------------------------------------------------------
	{// ref , arrary형 필드 전방 선언
		AutoTab a(this);
		{
			m_Array_Ref_it it = m_Array_Ref.begin(), ie = m_Array_Ref.end();
			std::set<tstring> listType;
			for(;it!=ie;++it)
			{
				jIE* peField= *it;
				jIVar* data_type = peField->GetAttrVar(jS(org_data_type_for_arr_ref));
				cstr szMax = jC5(peField,max);
				cstr szKey= data_type->Get_cstr();
				if(szMax && jt_strlen(szMax))
				{
					szKey=szMax;
				}
				else
				{
					szMax =0;
				}

				jvCONTINUE(data_type , _T("peField->GetAttrVar(jS(org_data_type_for_arr_ref)) is NULL!! : "), peField->GetTagName());

				if(listType.count(szKey) )
					continue;

				listType.insert(szKey);

				jIVar* pvRef = peField->GetAttrVar(jS(ref_field));
				jIVar* pvArray = peField->GetAttrVar(jS(array_field));
				if(pvRef)
				{
					if(pRefFunc)
					{
						pRefFunc(of, szKey , jC5(peField,max));
						of<<endl;

					}
				}
				else if(pNotRefFunc)
				{
					if(!pvArray)
					{
						peField->DebugPrint(false);
						jERROR(_T("데이타 무결성 깨짐, pvArray가 NULL!"));
						continue;
					}
					else
					{
						pNotRefFunc(of, szKey , jC5(peField,max));
						of<<endl;
					}
				}
			}
		}
	}

}



// 해당 필드이름으로 맴버 변수명을 리턴.
cstr Excel_Converter::_GetMemeberName(tcstr eng_name,tcstr data_type, fname_t buf,bool isArray,bool isRef)
{
	if(isRef || isArray)
	{
		if(isRef)
		{
			if(isArray)
				jt_sprintf(buf,_T("m_%s_ptr_vec"),eng_name);
			else
				jt_sprintf(buf,_T("m_%s_ptr"),eng_name);
		}
		else
		{
			jt_sprintf(buf,_T("m_%s_vec"),eng_name);
		}
		return buf;
	}

// 	if(pv_IsAddSimpleTypeTag->Get_bool())
// 	{
// 		tstring szType = _jSimpleType(data_type);
// 		if(szType[szType.size()-1] == '*')
// 		{
// 			jt_sprintf(buf,_T("m_%s"),eng_name);
// 		}
// 		else
// 			jt_sprintf(buf,_T("m_%s_%s"),eng_name, szType.c_str() );
// 	}
// 	else
	{
		jt_sprintf(buf,_T("m_%s"),eng_name);
	}
	return buf;
}

void Excel_Converter::_print_set_get_ref_array_Field(tofstream &of,tstring data_type, tstring table_name , tstring eng_name,tstring varName,tstring sRef)
{
	of<<_jF("%1%%4% %2%::Get_%3%()") % data_type % table_name % eng_name %sRef;
	of<<Tab()<<_T("{");
	{
		AutoTab a(this);
		of<<_jF("\treturn %1%;") % varName;
	}
	of<<_T("}\n");

	of<<_jF("void %2%::Set_%3%(%1%%4% v)\n") % data_type % table_name % eng_name %sRef;
	of<<Tab()<<_T("{\n");
	{
		AutoTab a(this);
		of<<_jF("%1% = v;") % varName;
		of<<endl;
	}
	of<<Tab()<<_T("}\n");
	of<<endl;
}

namespace nInherit
{
	jLIST_TYPEDEF_map(tstring,jID*,g_LoadedXml);

	static void _load_xml_files(tcstr szFile,void*)
	{
		nFileSystem::jFileName fn(szFile);
		if( jt_strcmp(fn.ext,_T(".xml") ) ) return;
		if(g_LoadedXml.count(fn.fname)) return;
		g_LoadedXml[fn.fname] = GetjIXml()->Load(szFile);
	}
	static jIE* _find_Interit_Table_from_allxml(jIE* peField)
	{
		g_LoadedXml_it it = g_LoadedXml.begin() , ie = g_LoadedXml.end();
		jIE* peInherit =0;
		for(; it!=ie ; ++it)
		{
			peInherit = it->second->BaseI()->FindByDepth(2, peField->GetTagID());
			if(peInherit) return peInherit;
		}
#if 0
		//아직도 못찾았다
		nFileSystem::for_each_folder( peField->GetDoc()->GetPath() ,_load_xml_files,0);

		it = g_LoadedXml.begin() , ie = g_LoadedXml.end();
		for(; it!=ie ; ++it)
		{
			peInherit = it->second->BaseI()->FindByDepth(2, peField->GetTagID());
			if(peInherit) return peInherit;
		}
#endif
		return 0;
	}

	jIE* find_Field_Inherit_Table(jIE* peField)
	{
		jIE* pE = peField->Find(jS(inherit));
		if( pE &&  pE->GetVar()->Get_bool())
		{
			jIE* peInherit = peField->GetParent()->GetParent()->FindByDepth(1, peField->GetTagID());
			if(!peInherit)
			{
				peInherit = _find_Interit_Table_from_allxml(peField);
				if(!peInherit)
				{
					//peField->GetParent()->DebugPrint(true);
					jWARN_T("not found Inherit TABLE : %s", peField->GetTagName());

					jCALL_RUNTIME(1)
					{
						g_LoadedXml_it it = g_LoadedXml.begin(),ie=g_LoadedXml.end();
						for(;it!=ie;++it)
						{
							tname256_t szURL;
							jWARN_T("\tloaded xml : %s : %s", it->first.c_str(), it->second->GetURL(szURL));
						}
					}
					return 0;
				}
			}
			return peInherit;
		}
		return 0;
	}

	bool is_inherit_node(jIE* it)
	{
		jIE* peInherit= it->Find(jS(inherit));
		return (peInherit && peInherit->GetVar()->Get_bool());
	}

	void get_inherit_list(std::vector<jIE*>& out, jIE* pE)
	{
		jIE* it = pE->begin();
		jrFOR(it)
		{
			if(is_inherit_node(it))
				out.push_back(it);
		}
	}

	// 해당 테이블에서 상속받는 필드정보를 통해 상속 테이블 포인터를 찾아 리턴.
	bool get_Inherit_Info(vector<nXML::jE> &listInherit, jIE* peTable)
	{
		jIE* peField = peTable->begin();
		jrFOR(peField)
		{
			jIE* peInherit = find_Field_Inherit_Table(peField);
			if(peInherit)
				listInherit.push_back(peInherit);
		}
		return listInherit.size();
	}

	jIE* get_name_field_from_inherit_class( jIE* peTable )
	{
		jIE* peName = peTable->Find(jS(name), 1);
		if(peName) return peName;

		std::vector<jE> out;
		nInherit::get_Inherit_Info(out, peTable);
		for(size_t i = 0 ; i< out.size() ; ++i)
		{
			peName = out[i]->Find(jS(name), 1);
			if(peName) return peName;

			peName = get_name_field_from_inherit_class(out[i]);
			if(peName) return peName;
		}
		return peName;
	}

}//namespace nInherit
