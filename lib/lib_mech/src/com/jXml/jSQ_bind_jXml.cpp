#include "stdafx.h"
#include "jXml.h"

#define SQPLUS_CONST_OPT

#include "interface/Squirrel/jISquirrel.h"
#include "base/jSQ_bind.h"


DECLARE_ENUM_TYPE(jIVar::EElementType);
DECLARE_ENUM_TYPE(jIE::EReturnType);

//DECLARE_INSTANCE_TYPE(StringID);
DECLARE_INSTANCE_TYPE(jIE);
DECLARE_INSTANCE_TYPE(jID);
DECLARE_INSTANCE_TYPE(jIXml);
DECLARE_INSTANCE_TYPE(jIAttributeList);


namespace nMech
{
	namespace nXML
	{
		extern jXml* g_pXml;
	}
}

namespace nSQ_jIA
{
	jIA* test_Get_jIA()
	{
		jIE* pE = nGLOBAL::g_pDocApp->BaseI();
		pE = pE->Find(jS(LANGAGE_FILES));
		return pE->GetAttrNode(jS(USING));
	}

	static tcstr _jIA__tostring(jIA* v)
	{
		static fname_t buf;
		fname_t buf2;
		//ScriptStringVar256
		const int imax = ARRAY_SIZE(buf);
		jt_snprintf(buf, imax,_T("%s=%s"),v->GetTagName() , v->GetVar()->ToString(buf2));
		buf[imax] = 0;
		return buf;
	}

	void init_SQ()
	{
		jSQ_Interface(jIA)
			jSQ_fn(GetRight,"","���� �Ӽ�. null�̸� ��")
			jSQ_fn(GetLeft,"","�����Ӽ�. null�̸� �ڽ��� ó��")
			jSQ_fn(GetVar,"","jIVar*����")
			jSQ_fn(GetTagID,"","")
			jSQ_fn(GetTagName,"","")
			jSQ_fn(IsName,"tcstr �񱳺���","")
			jSQ_fn(GetHandle,"","")
			jSQ_fn(ChangeTagName,"tcstr name","�ױ׸��� �ٲ�")
			jSQ_gfn(jIA,_tostring,"","")
		jSQ_end();


		RegisterGlobal(test_Get_jIA, _T("test_Get_jIA"));
	}

}



namespace nSQ_jIE
{
	jIE* test_Get_jIE()
	{
		return nGLOBAL::g_pDocApp->BaseI();
	}

//peFind , arg_FindStr, type_FindStr ,arg_Start=3
#define jSQ_jIE_INIT_peFind() \
	jIE*						peFind=0;\
	const int				arg_FindStr = 2;\
	++arg_Start;\
	tagSQObjectType type_FindStr = (tagSQObjectType)sa.GetType(arg_FindStr);

//paFind , arg_FindStr, type_FindStr , arg_Start=3
#define jSQ_jIE_INIT_paFind() \
	++arg_Start;\
	jIA*						paFind=0;\
	const int				arg_FindStr = 2;\
	++arg_Start;\
	tagSQObjectType type_FindStr = (tagSQObjectType)sa.GetType(arg_FindStr);

	template<typename ret_t, class _Predicate>
	ret_t _jIE_find_template(HSQUIRRELVM v,_Predicate fn)
	{			
		jSQ_init_pThis(jIE);// paramCount ,arg_This ,pThis , arg_Start=2

		const int				arg_FindStr = arg_Start++;
		tagSQObjectType type_FindStr = (tagSQObjectType)sa.GetType(arg_FindStr);
		ret_t pRet =0;

		fn._Init(v,sa,pThis,arg_Start);
		switch(type_FindStr)
		{
		case OT_STRING:
			{
				tcstr sz  =sa.GetString(arg_FindStr);
				pRet = fn(sz);
			}
			break;
		case OT_INSTANCE:
			{
				StringID &id = *jSQ_GetArg(StringID,arg_FindStr);
				pRet = fn(id);
			}
			break;
		default:		GetjISQ()->sq_throwerror(v, _T("find arg type error"));		break;
		}
		return pRet;
	}

	struct _jxFind_Functor_base
	{
		static const int				arg_FindStr = 2;
		int arg_Start;
		HSQUIRRELVM v;
		StackHandler* pSA;
		jIE* pThis;
		void _Init(HSQUIRRELVM v1,StackHandler& st,jIE* pE,int i)
		{
			pThis = pE;
			pSA = &st;
			v = v1;
			arg_Start =i;
		}
		jIVar* Get_jIVar(int argIdx){return jSQ_GetArg(jIVar,argIdx);	}
		jIE* Get_jIE(int argIdx){return jSQ_GetArg(jIE,argIdx);	}
		jID* Get_jID(int argIdx){return jSQ_GetArg(jID,argIdx);	}
	};
	#define _jxFind_FUNC_BASE_sz(RETURN_TYPE, NAME,base)	struct _jx##NAME :base {RETURN_TYPE operator() (tcstr sz)
	#define _jxFind_FUNC_sz(RETURN_TYPE, NAME)	struct _jx##NAME :_jxFind_Functor_base{RETURN_TYPE operator() (tcstr sz)
	#define _jxFind_FUNC_id(RETURN_TYPE, NAME)			RETURN_TYPE operator() (StringID id)
	#define _jxFind_FUNC_END(RETURN_TYPE, NAME)		}; jSQ_gfn_DEF(RETURN_TYPE,jIE,NAME){	return _jIE_find_template<RETURN_TYPE>(v,_jx##NAME()); }

	//--------------------------------------------------------------------------
	_jxFind_FUNC_sz(jIE* ,Find)
	//--------------------------------------------------------------------------
	{
		if(pSA->GetParamCount()==2)		return pThis->Find(sz);
		if(!CheckDepth())							return 0;
		return pThis->Find(sz, pSA->GetInt(arg_Depth) );
	}
	_jxFind_FUNC_id(jIE* ,Find)
	{
		if(pSA->GetParamCount()==2)		return pThis->Find(id);
		if(!CheckDepth())							return 0;
		return pThis->Find(id, pSA->GetInt(arg_Depth) );
	}
		static const int arg_Depth = 3;
		bool CheckDepth(){	return (pSA->GetType(arg_Depth)==OT_INTEGER);	}
	_jxFind_FUNC_END(jIE* ,Find);

	
	//--------------------------------------------------------------------------
	_jxFind_FUNC_sz(jIE*,FindFromParent)
	//--------------------------------------------------------------------------
	{	
		return pThis->FindFromParent( sz );	
	}
	_jxFind_FUNC_id(jIE*,FindFromParent)
	{ 
		return pThis->FindFromParent( id ); 
	}
	_jxFind_FUNC_END(jIE*,FindFromParent);


	//--------------------------------------------------------------------------
	_jxFind_FUNC_sz(jIE*,GetAttrFromParent)
	//--------------------------------------------------------------------------
	{	
		return pThis->GetAttrFromParent( sz ,&m_pV);
	}
	_jxFind_FUNC_id(jIE*,GetAttrFromParent)
	{ 
		return pThis->GetAttrFromParent( id  ,&m_pV);
	}
		jIVar* m_pV;
	_jxFind_FUNC_END(jIE*,GetAttrFromParent);


	//--------------------------------------------------------------------------
	_jxFind_FUNC_sz(jIE*,FindByContents)
	//--------------------------------------------------------------------------
	{	
		return pThis->FindByContents( sz ,Get_jIVar(arg_Start++));	
	}
	_jxFind_FUNC_id(jIE*,FindByContents)
	{ 
		return pThis->FindByContents( id ,Get_jIVar(arg_Start++)); 
	}
	_jxFind_FUNC_END(jIE*,FindByContents);


	//--------------------------------------------------------------------------
	_jxFind_FUNC_sz(jIE*,FindByFirstAttr)
	//--------------------------------------------------------------------------
	{	
		if(pSA->GetParamCount()==3)
			return pThis->FindByFirstAttr( sz ,Get_jIVar(3) );
		else if(pSA->GetParamCount()==4)
			return pThis->FindByFirstAttr( sz ,Get_jIVar(3) ,pSA->GetInt(4));
		return pThis->FindByFirstAttr( sz );
	}
	_jxFind_FUNC_id(jIE*,FindByFirstAttr)
	{ 
		if(pSA->GetParamCount()==3)
			return pThis->FindByFirstAttr( id,Get_jIVar(3) );
		else if(pSA->GetParamCount()==4)
			return pThis->FindByFirstAttr( id ,Get_jIVar(3) ,pSA->GetInt(4));
		return pThis->FindByFirstAttr( id );
	}
	_jxFind_FUNC_END(jIE*,FindByFirstAttr);


	//--------------------------------------------------------------------------
	_jxFind_FUNC_sz(jIA*,GetAttrNode)
	//--------------------------------------------------------------------------
	{	
		return pThis->GetAttrNode( sz);
	}
	_jxFind_FUNC_id(jIA*,GetAttrNode)
	{ 
		return pThis->GetAttrNode( id);
	}
	_jxFind_FUNC_END(jIA*,GetAttrNode);

	//--------------------------------------------------------------------------
	jSQ_gfn_DEF(tcstr,jIE, GetAttr)
	//--------------------------------------------------------------------------
	{
		jIA* pA = _jIE_GetAttrNode(v);
		if(!pA)  return 0;
		return pA->GetVar()->Get_cstr();
	}
	
	//--------------------------------------------------------------------------
	jSQ_gfn_DEF(jIVar*,jIE, GetAttrVar)
	//--------------------------------------------------------------------------
	{
		jIA* pA = _jIE_GetAttrNode(v);
		if(!pA)  return 0;
		return pA->GetVar();
	}

	// e.InsertChild(jS(asdf)); e�� �Ǹ������� ���ο� element�߰�
	// e.InsertChild("asdf", 3); e�� 3��° �ڽ����� "asdf"��� element�� �߰�
	//--------------------------------------------------------------------------
	_jxFind_FUNC_sz(jIE*,InsertChild){	return pThis->InsertChildElement( sz ,GetOrder()); }
	_jxFind_FUNC_id(jIE*,InsertChild)		{ return 0; }
		int GetOrder()
		{
			if(pSA->GetParamCount()==3 && pSA->GetType(arg_Order)==OT_INTEGER) 
				return pSA->GetInt(arg_Order);
			return -1;
		}
		static const int arg_Order=3;
	_jxFind_FUNC_END(jIE*,InsertChild);

	
	//--------------------------------------------------------------------------
	// e.Persist("asdf",jIVar::ETelement);
	// e.Persist("asdf", jIVar::EDint , "234");
	_jxFind_FUNC_sz(jIE*,Persist)
	{	
		if(init_PersistParam())
			return pThis->Persist( sz ,m_eType,m_sValue.c_str());	
		return pThis->Persist(sz,m_eType);
	}
	_jxFind_FUNC_id(jIE*,Persist)// e.FindByContents("asdf", pVar);
	{ 
		if(init_PersistParam())
			return pThis->Persist( id , m_eType,m_sValue.c_str());	
		return pThis->Persist(id,m_eType);
	}
	jIVar::EElementType m_eType;
	tstring m_sValue;
	static const int arg_TYPE=3;
	static const int arg_VALUE=4;
	bool init_PersistParam()
	{
		m_eType = (jIVar::EElementType)pSA->GetInt(arg_TYPE);
		if( pSA->GetParamCount()!=4)  return false;
		m_sValue = pSA->GetString(arg_VALUE);
		return true;
	}
	_jxFind_FUNC_END(jIE*,Persist);


	// e.PersistAttr("asdf",jIVar::ETelement);
	// e.PersistAttr("asdf", jIVar::EDint , "234");
	_jxFind_FUNC_BASE_sz(jIVar*,PersistAttr,_jxPersist)
	{	
		if(init_PersistParam())
			return pThis->PersistAttr( sz ,m_eType,m_sValue.c_str());	
		return pThis->PersistAttr(sz,m_eType);
	}
	_jxFind_FUNC_id(jIVar*,PersistAttr)// e.FindByContents("asdf", pVar);
	{ 
		if(init_PersistParam())
			return pThis->PersistAttr( id , m_eType,m_sValue.c_str());	
		return pThis->PersistAttr(id,m_eType);
	}
	_jxFind_FUNC_END(jIVar*,PersistAttr);

	struct _jx_jIE_for_each
	{
		SquirrelObject func;
		_jx_jIE_for_each(HSQOBJECT & f1): func(f1){}
		void operator()(jIE* it)
		{
			SquirrelObject param(it);
			GetjISQ()->VM_BeginCall(func);
			GetjISQ()->VM_PushParam( param);
			GetjISQ()->VM_EndCall();
		}
		void operator()(jIA* it)
		{
			SquirrelObject param(it);
			GetjISQ()->VM_BeginCall(func);
			GetjISQ()->VM_PushParam( param);
			GetjISQ()->VM_EndCall();
		}
	};
	struct _jx_jIE_find_if : public _jx_jIE_for_each
	{
		_jx_jIE_find_if(HSQOBJECT &f1): _jx_jIE_for_each(f1){}
		bool operator()(jIE* it)
		{
			SquirrelObject param(it);
			GetjISQ()->VM_BeginCall(func);
			GetjISQ()->VM_PushParam( param);
			SquirrelObject oRet = GetjISQ()->VM_EndCall();
			return oRet.ToBool();
		}
	};

	struct _jx_jIE_for_each_if: public _jx_jIE_for_each
	{
		_jx_jIE_for_each_if(HSQOBJECT & f1): _jx_jIE_for_each(f1){}
		jIE::EReturnType operator()(jIE* it)
		{
			SquirrelObject param(it);
			GetjISQ()->VM_BeginCall(func);
			GetjISQ()->VM_PushParam( param);
			SquirrelObject oRet = GetjISQ()->VM_EndCall();
			jIE::EReturnType ret = (jIE::EReturnType)oRet.ToInteger();
			return ret;
		}
	};

	#define jSQ_jIE_foreach_find(name,functorName) pThis->name(functorName(sa.GetObjectHandle(2) ))

	jSQ_gfn_DEF(jIE*,jIE, find_if_child)
	{
		jSQ_init_pThis(jIE);
		return jSQ_jIE_foreach_find(find_if_child,_jx_jIE_find_if);
	}
	jSQ_gfn_DEF(jIE*,jIE, find_if)
	{
		jSQ_init_pThis(jIE);
		return jSQ_jIE_foreach_find(find_if,_jx_jIE_find_if);
	}
	jSQ_gfn_DEF(jIE*,jIE, for_each_child)
	{
		jSQ_init_pThis(jIE);
		jSQ_jIE_foreach_find(for_each_child,_jx_jIE_for_each);
		return pThis;
	}
	// e.for_each( func_name);
	jSQ_gfn_DEF(jIE*,jIE, for_each)
	{
		jSQ_init_pThis(jIE);
		jSQ_jIE_foreach_find(for_each,_jx_jIE_for_each);
		return pThis;
	}
	jSQ_gfn_DEF(jIE*,jIE, for_each_depth)
	{
		jSQ_init_pThis(jIE);
		jSQ_jIE_foreach_find(for_each_depth,_jx_jIE_for_each);
		return pThis;
	}
	jSQ_gfn_DEF(jIE*,jIE, for_each_attr)
	{
		jSQ_init_pThis(jIE);
		jSQ_jIE_foreach_find(for_each_attr,_jx_jIE_for_each);
		return pThis;
	}
	jSQ_gfn_DEF(jIE*,jIE, for_each_if)
	{
		jSQ_init_pThis(jIE);
		jSQ_jIE_foreach_find(for_each_if,_jx_jIE_for_each_if);
		return pThis;
	}

	static tcstr _jIE__tostring(jIE* e)
	{
		static fname_t buf;
		fname_t buf2;
		buf2[0]=0;
		e->GetVar()->ToString(buf2);
		if(jt_strlen(buf2))
			jt_snprintf(buf, ARRAY_SIZE(buf),_T("%s(%s)=%s"),e->GetTagName() , e->GetVar()->GetTypeString() ,buf2);
		else
			jt_snprintf(buf, ARRAY_SIZE(buf),_T("%s(%s) "),e->GetTagName() , e->GetVar()->GetTypeString() );
		buf[ARRAY_SIZE(buf)] = 0;
		return buf;
	}
	bool _jIE__cmp(jIE* e,jIE* e2)
	{
		return (e == e2);
	}

	void init_SQ()
	{
		jSQ_Interface(jIE)
			jSQ_enum_init(EReturnType)
			jSQ_enum(jIE,eCONTINUE,"")
			jSQ_enum(jIE,eSKIP_CHILD,"")
			jSQ_enum(jIE,eEXIT,"")
			jSQ_fn(IsName,"","")
			jSQ_fn(IsContents,"","")
			jSQ_fn(Get_cstr,"","")
			jSQ_fn(GetType,"","EElementType")
			jSQ_fn(GetDepth,"","���� �θ�κ����� ����. �ڽ��� ��Ƽ�̸� 0�� ����")
			jSQ_fn(GetVar,"","")
			jSQ_fn(GetTagID,"","")
			jSQ_fn(GetTagName,"","")
			jSQ_fn(GetHandle,"","�����޸� �ε���")
			jSQ_fn(ChangeTagName,"","")
			jSQ_gfn(jIE,Find,"tcstr szName [, int depth]","")
			jSQ_fn(FindByPath,"tcstr szPath","szPath = -3:ABC:3:DFG �̸� 3�ܰ��� �θ𿡼� ABC�� ã�� 3�����ڽĿ��� DFG�� ã��")
			jSQ_gfn(jIE,FindFromParent,"tcstr szName","")
			jSQ_gfn(jIE,GetAttrFromParent,"tcstr szName","")
			jSQ_gfn(jIE,FindByContents,"tcstr szName, jIVar* pFindData","pFindData�� ��ġ�ϴ� ����Ÿ�� ã��")
			jSQ_gfn(jIE,FindByFirstAttr,"tcstr szAttName [, jIVar* pV , int iDepth]","")
			jSQ_gfn(jIE,GetAttr,"tcstr sz | StringID id","���� EDcstr�϶� ��Ʈ���� ����")
			jSQ_gfn(jIE,GetAttrVar,"tcstr sz | StringID id","jIVar�� ����")
			jSQ_gfn(jIE,GetAttrNode,"tcstr sz | StringID id","jIA�� ����")
			jSQ_fn(GetDoc,"","")
			jSQ_fn(SetContents,"tcstr sz","")
			jSQ_fn(Set_cstr,"tcstr sz","")
			jSQ_fn(MovePosition,"int iOrder","")
			jSQ_gfn(jIE,InsertChild,"tcstr szName [,int iOrder]","���ο� element�� iOrder��°�� �߰�")
			jSQ_fn(InsertAttr,"tcstr szName","")
			jSQ_fn(DeleteAttr,"tcstr szName","")
			jSQ_fn(IsXmlFileNode,"","")
			jSQ_fn(IsFileNode,"tcstr szExt","�ش� Ȯ���ڸ������� ���ϵ���Ÿ����")
			// e.Persist("asdf",jIVar::ETelement);
			// e.Persist("asdf", jIVar::EDint , "234");

			jSQ_gfn(jIE,Persist,"tcstr szName, EElementType eType [, tcstr szData]"
			,"�ش� �̸����� element�� �����ϰ� �Ѵ�. �����߰��ϰ�� �ش簪���� �ʱ�ȭ��Ŵ")
			jSQ_gfn(jIE,PersistAttr,"tcstr szName, EElementType eType [, tcstr szData]"
			,"�ش� �̸����� �Ӽ��� �����ϰ� �Ѵ�. �����߰��ϰ�� �ش簪���� �ʱ�ȭ��Ŵ")
			jSQ_fn(FindByOrder,"int iOrder","�ش� ������ �ڽ�������")
			jSQ_fn(GetOrder,"","")
			jSQ_fn(isRoot,"","")
			jSQ_fn(isBegin,"","")
			jSQ_fn(isEnd,"","")
			jSQ_fn(GetRight,"","���� ���� element")
			jSQ_fn(GetLeft,"","���� �� element")
			jSQ_fn(GetParent,"","�θ�")
			jSQ_fn(begin,"","�θ�")
			jSQ_fn(end,"","0�� ����")
			jSQ_fn(size,"","�ڽ��� ��")
			jSQ_fn(GetRoot,"","�ֻ��� document�� ����")
			jSQ_fn(CopyTo,"jIE* peDest","peDest�� ���ɺ���")
			jSQ_fn(CopyTo_Child,"jIE* peDest","peDest �ڽ��� ������ ���ΰ� �ڽĵ鸸 ����")
			jSQ_fn(Erase,"","�ڽ��� �����Ͽ� ��� ����. �ڽ��� NULL�� �ʱ�ȭ�ؾ���.")
			jSQ_fn(EraseChild,"","�ڽĵ鸸 ��� ����")
			jSQ_fn(Lerp,"jIE* pE1 , jIE* pE2, float fLerpRatio","")
			jSQ_gfn(jIE,find_if_child,"function fn","bool func(jIE* it) �� Closur�� �´�.")
			jSQ_gfn(jIE,find_if,"function fn","bool func(jIE* it) �� Closur�� �´�.")
			jSQ_gfn(jIE,for_each_child,"function fn","void func(jIE* it) �� Closur�� �´�.")
			jSQ_gfn(jIE,for_each,"function fn","void func(jIE* it) �� Closur�� �´�.")
			jSQ_gfn(jIE,for_each_depth,"function fn","bool func(jIE* it) �� Closur�� �´�.")
			jSQ_fn(DebugPrint,"bool isCR","")
			jSQ_gfn(jIE,for_each_attr,"function fn","bool func(jIA* it) �� Closur�� �´�.")
			jSQ_gfn(jIE,for_each_if,"function fn","EReturnType func(jIE* it)�� Closur�� �´�.")
			jSQ_gfn(jIE,_tostring,"","")
			jSQ_gfn(jIE,_cmp,"","")
		jSQ_end();

		RegisterGlobal(test_Get_jIE, _T("test_Get_jIE"));
	}
}//namespace nSQ_jIE

namespace nSQ_jID
{
	tcstr _jID_GetURL(jID* pD)
	{
		static fname_t buf;
		return pD->GetURL(buf);
	}
	jIE* _jID_Find(jID* pD,tcstr szName)
	{
		return pD->Find(szName);
	}

	void init_SQ()
	{
		jSQ_Interface(jID)
			jSQ_fn(BaseI,"","�ڽ��� jIE*�� ����")
			jSQ_fn(GetPath,"","�ڽ��� ���� ��� ����")
			jSQ_gfn(jID, GetURL,"","�ڽ��� ������ ����")
			jSQ_gfn(jID,Find,"jIE*(tcstr)","�ڽ�element�� ã��")
			jSQ_fn(CopyTo,"jID* pDest","")
			jSQ_fn(ReLoad,"","���� �ȵ�")
			jSQ_fn(Save,"","")
			jSQ_fn(SaveJXML,"","")
			jSQ_fn(SaveAsJXML,"tcstr jxml","")
			jSQ_fn(SaveXML,"","")
			jSQ_fn(SaveAsXML,"tcstr xml","")
			//jSQ_fn(FindByBlood,"","")
			jSQ_fn(DebugPrint,"bool isCR","")
			//jSQ_gfn(jID, GetXPathNode,"","")
			//jSQ_gfn(jID, GetSXPathNode,"","")
			jSQ_fn(GetFlag,"","")
			jSQ_fn(SetComment,"jIE* pE, tcstr help","")
			//jSQ_gfn(jID, FindComment,"","")
			jSQ_fn(GetParentLink,"","�ڽŹ����� �ε��� xml������ node : jIE*�� ����")
			jSQ_fn(SetParentLink,"jIE* peParentDocNode","")
		jSQ_end();
	}

}//namespace nSQ_jID

namespace nSQ_jIXml
{
	jSQ_gfn_DEF(jID*,jIXml, Load)
	{
		jSQ_init_pThis(jIXml);// paramCount ,arg_This ,pThis , arg_Start=2
		jID* pD = 0;
		if( sa.GetParamCount() < 2) return 0;
		tcstr szName = sa.GetString(arg_Start++);
		if(sa.GetParamCount() >=3)
		{
			tcstr szBuffer = sa.GetString(arg_Start++);
			pD = pThis->Load(szName, szBuffer);
		}
		else
		{
			pD = pThis->Load(szName);
		}
		return pD;
	}
	struct _jxSetCallbackFunctor
	{
		SquirrelObject func;
		_jxSetCallbackFunctor(HSQOBJECT & f1):func(f1) { }
		void operator() (boost::any& anyDoc)
		{
			jID* pD = boost::any_cast<jID*>(anyDoc);
			SquirrelObject param(pD);
			GetjISQ()->VM_BeginCall(func);
			GetjISQ()->VM_PushParam( param);
			GetjISQ()->VM_EndCall();
		}
	};
	jSQ_gfn_DEF(jIXml*,jIXml, SetCallback)
	{
		jSQ_init_pThis(jIXml);// paramCount ,arg_This ,pThis , arg_Start=2
		if(sa.GetParamCount()!=3) return pThis;
		cstr szName = sa.GetString(2);
		pThis->GetCallBackManager()->SetCallback(szName, _jxSetCallbackFunctor(sa.GetObjectHandle(3)));
		return pThis;
	}
	

	void init_SQ()
	{
		jSQ_Interface(jIXml)
			jSQ_gfn(jIXml,Load,"tcstr fileName [,tcstr szXmlBuffer]","���ϸ����� �ε��ϴ��� �ƴϸ� ���ϸ����� �ش���۷κ��� �ε�")
#if 0
			jSQ_fn(GetIndex,"","")
			jSQ_fn(GetName,"","")
#endif
			jSQ_fn(size,"","�ε��� ���� ��ü ����")
			jSQ_fn(RegistXML,"","��� ����")
			jSQ_fn(CreateMemoryDoc,"tcstr szDocName","�޸𸮻󿡼��� �����ϴ� xml��������")
			jSQ_fn(Clone,"jID* pDocTarget","pDocTarget�� ���纻�� ����")
			jSQ_fn(UnLoad,"jID* pDoc","pDoc�� ��ε�")
			jSQ_fn(NewFile,"tcstr szFile","szFile�̸����� ��xml���� ����")
			jSQ_fn(GetObj,"tcstr szDocName","")
			jSQ_fn(GetFlag,"","")
			//jSQ_fn(GetData,"","")
			jSQ_fn(CreatejVar,"","")
			jSQ_fn(DeletejVar,"jIVar* pDelVar","")
			jSQ_fn(CreateElement,"","")
			jSQ_fn(DeleteElement,"jIE* pDel","")
			jSQ_fn(GetVersion,"","")
			jSQ_fn(FindElementByHandle,"uint iElementHandle","jIE::GetHandle()���� ������ �ڵ�� �ڽ��� ã��")
			jSQ_gfn(jIXml,SetCallback,"tcstr szName,  void func(jID*) ","szName : UnLoad , Save")
			//jSQ_fn(GetXmlUtil,"","")
			jSQ_fn(GetTypeByString,"tcstr szType","\"EDint\" -> EDint ")
		jSQ_end();
		jSQ_g_var((jIXml*)g_pXml,g_pjIXml);


		//SquirrelObject sqXmlCode = GetjISQ()->VM_CompileBuffer("\
		//GetjISQ()->VM_RunScript
	}
}


namespace nMech
{
	namespace nXML
	{
		jSQ_REGIST_BIND(nXML)
		{
			nSQ_jIA::init_SQ();
			nSQ_jIE::init_SQ();
			nSQ_jID::init_SQ();
			nSQ_jIXml::init_SQ();

		}

	}//namespace nXML
}
