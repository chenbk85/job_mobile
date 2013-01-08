//////////////////////////////////////////////////////////////////////
//
//  jcEngine Source code
//	
//	File:jc/jcSizer.h
//  Declaration and definition of the jcSizer class, which is used to
//  calculate the memory usage by the subsystems and components, to help
//  the artists keep the memory budged low.
//
//	History:
//	December 03, 2002 : Created by Sergiy Migdalskiy <sergiy@jcGame.de>
//
//////////////////////////////////////////////////////////////////////

#ifndef _JCGAME_COMMON_JCGAME_SIZER_INTERFACE_HDR_
#define _JCGAME_COMMON_JCGAME_SIZER_INTERFACE_HDR_

#ifdef GAMECUBE
#include "GCDefines.h"
#endif

#ifdef WIN64
#include <string.h> // workaround for Amd64 compiler
#endif

namespace nMech
{

	// prerequisities 
	//#include <string>
	//#include <vector>

	// flags applicable to the jcISizer (retrieved via getFlags() method)
	//
	enum jcISizerFlagsEnum
	{
		// if this flag is set, during getSize(), the subsystem must count all the objects
		// it uses in the other subsystems also
		CSF_RecurseSubsystems = 1 << 0,

		CSF_Reserved1 = 1 << 1,
		CSF_Reserved2 = 1 << 2
	};


	//////////////////////////////////////////////////////////////////////////
	// interface jcISizer
	// USAGE
	//   An instance of this class is passed down to each and every component in the system.
	//   Every component it's passed to optionally pushes its name on top of the 
	//     component name stack (thus ensuring that all the components calculated down
	//     the tree will be assigned the correct subsystem/component name)
	//   Every component must Add its size with one of the Add* functions, and Add the
	//     size of all its subcomponents recursively
	//   In order to push the component/system name on the name stack, the clients must
	//     use the SIZER_COMPONENT_NAME macro or jcSizerComponentNameHelper class:
	//
	//   void X::getSize (jcISizer* pSizer)
	//   {
	//     SIZER_COMPONENT_NAME(pSizer, X);
	//     if (!pSizer->Add (this))
	//       return;
	//     pSizer->Add (m_arrMySimpleArray);
	//     pSizer->Add (m_setMySimpleSet);
	//     m_pSubobject->getSize (pSizer);
	//   }
	//
	//   The Add* functions return bool. If they return true, then the object has been added
	//   to the set for the first time, and you should go on recursively adding all its children.
	//   If it returns false, then you can spare time and rather not go on into recursion;
	//   however it doesn't reflect on the results: an object that's added more than once is
	//   counted only once.
	//
	// WARNING:
	//   If you have an array (pointer), you should Add its size with addArray

	class jcISizer
	{
	public:
		// this class is used to push/pop the name to/from the stack automatically
		// (to exclude stack overruns or underruns at runtime)
		friend class jcSizerComponentNameHelper;

		jcISizer ():
		m_nFlags(0)
		{
		}

		virtual ~jcISizer () {}

		// adds an object identified by the unique pointer (it needs not be
		// the actual object position in the memory, though it would be nice,
		// but it must be unique throughout the system and unchanging for this object)
		// RETURNS: true if the object has actually been added (for the first time)
		//          and calculated
		virtual bool AddObject (const void* pIdentifier, size_t nSizeBytes) = 0;

		template <typename T>
			bool Add (const T* pId, size_t num)
		{
			return AddObject(pId, num * sizeof(T));
		}

		template <class T>
			bool Add (const T& rObject)
		{
			return AddObject (&rObject, sizeof(T));
		}

		bool Add (const char* szText)
		{
			return AddObject(szText, strlen(szText)+1);
		}

		template <class String>
			bool AddString (const String& strText)
		{
			if (!strText.empty())
				return AddObject (strText.c_str(), strText.length()+1);
			else
				return false;
		}
#ifdef _XSTRING_
		template <class Elem, class Traits, class Allocator>
			bool Add (const std::basic_string<Elem, Traits, Allocator>& strText)
		{
			AddString (strText);
		}
#endif

#ifdef _STRING_
		bool Add (const std::string& strText)
		{
			AddString(strText);
		}
#endif

		template <class Container>
			bool AddContainer (const Container& rContainer)
		{
			if (!rContainer.empty())
				return AddObject (&(*rContainer.begin()),rContainer.size()*sizeof(typename Container::value_type));
			return false;
		}

		// returns the flags
		unsigned GetFlags()const {return m_nFlags;}

	protected:
		// these functions must operate on the component name stack
		// they are to be only accessible from within class jcSizerComponentNameHelper
		// which should be used through macro SIZER_COMPONENT_NAME
		virtual void Push (const char* szComponentName) = 0;
		// pushes the name that is the name of the previous component . (dot) this name
		virtual void PushSubcomponent (const char* szSubcomponentName) = 0;
		virtual void Pop () = 0;

		unsigned m_nFlags;
	};

	//////////////////////////////////////////////////////////////////////////
	// This is on-stack class that is only used to push/pop component names
	// to/from the sizer name stack.
	// 
	// USAGE:
	//
	//   Create an instance of this class at the start of a function, before
	//   calling Add* methods of the sizer interface. Everything added in the
	//   function and below will be considered this component, unless
	//   explicitly set otherwise.
	//
	class jcSizerComponentNameHelper
	{
	public:
		// pushes the component name on top of the name stack of the given sizer
		jcSizerComponentNameHelper (jcISizer* pSizer, const char* szComponentName, bool bSubcomponent):
				m_pSizer(pSizer)
				{
					if (bSubcomponent)
						pSizer->PushSubcomponent (szComponentName);
					else
						pSizer->Push (szComponentName);
				}

				// pops the component name off top of the name stack of the sizer 
				~jcSizerComponentNameHelper()
				{
					m_pSizer->Pop();
				}

	protected:
		jcISizer* m_pSizer;
	};

	// use this to push (and automatically pop) the sizer component name at the beginning of the
	// getSize() function
#define SIZER_COMPONENT_NAME(pSizerPointer, szComponentName) jcSizerComponentNameHelper __sizerHelper(pSizerPointer, szComponentName, false)
#define SIZER_SUBCOMPONENT_NAME(pSizerPointer, szComponentName) jcSizerComponentNameHelper __sizerHelper(pSizerPointer, szComponentName, true)
}//namespace nMech

#endif //_JCGAME_COMMON_JCGAME_SIZER_INTERFACE_HDR_
