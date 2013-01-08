/* file : Namespace.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-08-08 13:00:29
comp.: jgame.co.kr
title : 
desc : 

*/

#ifndef __Namespace_header__
#define __Namespace_header__
#pragma once


struct I3DEngine;

struct IAISystem;
struct jIAniManager;

struct IConsole;

struct IEntitySystem;
struct IEntityRender;
struct IEntityCharacter;
struct IEntityContainer;
struct IEntitySystemSink;

struct jcIFont;
struct IFFont;

struct IGame;

struct ILog;


struct IMatInfo;
struct IMovieSystem;

struct INetwork;

struct IProcess;
class IPhysicalWorld;
class IPhysicalEntity;

struct IRenderer;

struct ISystem;
struct IStatObj;

struct ITexPic;
struct jcICharInstance;
struct IVisArea;


namespace nMech
{
	class jcISizer;
	struct IDataProbe;

	namespace nCONSOLE
	{
		struct ICVar;
	}
	namespace nEVENT
	{
		struct jIMessage;
		struct jIMsgManager;
		struct jEventMessage;
	}

	namespace nINPUT
	{
		struct IInput;
		struct IKeyboard;
		struct SInputEvent;
		struct IMouse;

	}
	namespace nJC
	{
		class CjcFile;
		struct IFrameProfileSystem;

	}
	namespace nJC_stream
	{
		class CStream;
		struct ICompressionHelper;
		struct IStreamEngine;
		struct	IBitStream;
		struct StreamEngineParams;
		class IStreamCallback;
	}


	namespace nLUA1
	{
		struct IScriptSystem;
		struct IScriptObject;
	}

	namespace nJC_SOUND
	{
		struct ISoundSystem;
		struct ISound;
		struct IMusicSystem;

		struct SMusicTheme;
		struct SMusicMood;
		struct SPatternDef;
		struct SMusicPatternSet;

	}
	
	namespace nPAK
	{
		struct jIPak;
	}


	namespace nMath
	{
		class CCamera;
	}
	

	namespace nTIME
	{
		struct ITimer;

	}

	namespace nXML_ORB
	{
		struct jIORB;
	}
	
	namespace nORB
	{
		struct jIOrbNode;
		struct jIOrb;
	}

}




#endif // __Namespace_header__
