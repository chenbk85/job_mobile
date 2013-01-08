#ifndef jcphysics_h
#define jcphysics_h
#pragma once

#ifdef WIN32
	#ifdef PHYSICS_EXPORTS
		#define JC_GAMEPHYSICS_API __declspec(dllexport)
	#else
		#define JC_GAMEPHYSICS_API __declspec(dllimport)
	#endif
#else
	#define JC_GAMEPHYSICS_API
#endif
#define vector_class nMech::nMath::jVec3_tpl


#ifndef GAMECUBE
#include <jcSizer.h>
#endif



//#include "utils.h"
#include "jc_Math.h"
#include "primitives.h"
#include "physinterface.h"

extern "C" JC_GAMEPHYSICS_API IPhysicalWorld *CreatePhysicalWorld(struct ISystem *pLog);

#endif