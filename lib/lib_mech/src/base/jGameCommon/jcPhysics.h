#ifndef jcphysics_h
#define jcphysics_h
#pragma once

#ifndef _XBOX
	#ifdef PHYSICS_EXPORTS
		#define JC_GAMEPHYSICS_API __declspec(dllexport)
	#else
		#define JC_GAMEPHYSICS_API __declspec(dllimport)
		#define vector_class nMech::nMath::jVec3d
	#endif
#else
	#define JC_GAMEPHYSICS_API
#endif

#include "utils.h"
#include "primitives.h"
#include "physinterface.h"

extern "C" JC_GAMEPHYSICS_API IPhysicalWorld *CreatePhysicalWorld();

#endif