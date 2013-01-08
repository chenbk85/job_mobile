#ifndef _JCGAME_SYSTEM_H_
#define _JCGAME_SYSTEM_H_

#ifdef WIN32
	#ifdef JC_GAMESYSTEM_EXPORTS
		#define JC_GAMESYSTEM_API __declspec(dllexport)
	#else
		#define JC_GAMESYSTEM_API __declspec(dllimport)
	#endif
#else
	#define JC_GAMESYSTEM_API
#endif

#include "jc/platform.h" // Needed for LARGE_INTEGER (for consoles).

////////////////////////////////////////////////////////////////////////////////////////////////
// Forward declarations
////////////////////////////////////////////////////////////////////////////////////////////////
#include <IXMLDOM.h>
#include <IXml.h>
#include <interface/IValidator.h>
#include "interface/ILog.h"
#include "interface/jIDebugCallStack.h"

		struct IFlash;
		struct IMemoryManager;
		struct XDOM::IXMLDOMDocument;
		struct SFileVersion;


		class CFrameProfilerSection;

#define DEFAULT_GAME_PATH	"jGame"
#define DATA_FOLDER "FCData"

#define PROC_MENU		1
#define PROC_3DENGINE	2

		//ID for script userdata typing (maybe they should be moved into the game.dll)
#define USER_DATA_SOUND			1
#define USER_DATA_TEXTURE		2
#define USER_DATA_OBJECT		3
#define USER_DATA_LIGHT			4
#define USER_DATA_BONEHANDLER	5
#define USER_DATA_POINTER		6

		enum ESystemUpdateFlags
		{
			ESYSUPDATE_IGNORE_AI			= 0x0001,
			ESYSUPDATE_IGNORE_PHYSICS = 0x0002,
			// Special update mode for editor.
			ESYSUPDATE_EDITOR					=	0x0004,
			ESYSUPDATE_MULTIPLAYER		= 0x0008
		};

		enum ESystemConfigSpec
		{
			CONFIG_LOW_SPEC = 0,
			CONFIG_MEDIUM_SPEC = 1,
			CONFIG_HIGH_SPEC = 2,
			CONFIG_VERYHIGH_SPEC = 3,
		};

		// Structure passed to Init method of ISystem interface.
		struct SSystemInitParams
		{
			void *hInstance;											//
			void *hWnd;														//
			char szSystemCmdLine[512];						// command line, used to execute the early commands e.g. -DEVMODE "g_gametype ASSAULT"
			nMech::nUtil::nDebug::ISystemUserCallback *pUserCallback;		//
			ILog *pLog;														// You can specify your own ILog to be used by System.
			nMech::nLOG::IValidator *pValidator;								// You can specify different validator object to use by System.
			const char* sLogFileName;							// File name to use for log.
			bool bEditor;													// When runing in Editor mode.
			bool bPreview;												// When runing in Preview mode (Minimal initialization).
			bool bTestMode;												// When runing in Automated testing mode.
			bool bDedicatedServer;								// When runing a dedicated server.
			ISystem* pSys;											// Pointer to existing ISystem interface, it will be reused if not NULL.
			//	char szLocalIP[256];									// local IP address (needed if we have several servers on one machine)
#if defined(LINUX)
			void (*pCheckFunc)(void*);							// authentication function (must be set).
#else
			void *pCheckFunc;											// authentication function (must be set).
#endif

			// Initialization defaults.
			SSystemInitParams()
			{
				hInstance = 0;
				hWnd = 0;
				memset(szSystemCmdLine,0,sizeof(szSystemCmdLine));
				pLog = 0;
				pValidator = 0;
				pUserCallback = 0;
				sLogFileName = 0;
				bEditor = false;
				bPreview = false;
				bTestMode = false;
				bDedicatedServer = false;
				pCheckFunc = 0;
				pSys = 0;
				//		memset(szLocalIP,0,256);
			}
		};


		// Structure passed to CreateGame method of ISystem interface.
		struct SGameInitParams
		{
			const char *	sGameDLL;							// Name of Game DLL. (Win32 Only)
			IGame *				pGame;								// Pointer to already created game interface.
			bool					bDedicatedServer;			// When runing a dedicated server.
			char					szGameCmdLine[256];		// command line, used to execute the console commands after game creation e.g. -DEVMODE "g_gametype ASSAULT"

			SGameInitParams()
			{
				sGameDLL = NULL;
				pGame = NULL;		
				bDedicatedServer = false;
				memset(szGameCmdLine,0,256);
			}
		};


		////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////
		// Main Engine Interface
		// initialize and dispatch all engine's subsystems 
		struct ISystem
		{ 
			// Loads GameDLL and creates game instance.
			virtual bool CreateGame( const SGameInitParams &params ) = 0;

			// Release ISystem.
			virtual void Release() = 0;

			// Update all subsystems (including the ScriptSink() )
			// @param flags one or more flags from ESystemUpdateFlags sructure.
			// @param boolean to set when in pause or cutscene mode in order to avoid
			// certain subsystem updates 0=menu/pause, 1=cutscene mode
			virtual bool Update( int updateFlags=0,int nPauseMode=0) = 0;

			// update _time, _frametime (useful after loading level to apply the time value)
			virtual void UpdateScriptSink()=0;

			// Begin rendering frame.
			virtual void	RenderBegin() = 0;
			// Render subsystems.
			virtual int Render() = 0;
			// End rendering frame and swap back buffer.
			virtual void	RenderEnd() = 0;

			// Renders the statistics; this is called from RenderEnd, but if the 
			// Host application (Editor) doesn't employ the Render cycle in ISystem,
			// it may call this method to render the essencial statistics
			virtual void RenderStatistics () = 0;

			// Gets current supported CPU features flags. (CPUF_SSE, CPUF_SSE2, CPUF_3DNOW, CPUF_MMX)
			virtual int GetCPUFlags() = 0;

			// Get seconds per processor tick
			virtual double GetSecondsPerCycle() = 0;

			// dumps the memory usage statistics to the log
			virtual void DumpMemoryUsageStatistics() = 0;

			// Quit the appliacation
			virtual void	Quit() = 0;
			// Tells the system if it is relaunching or not
			virtual void	Relaunch(bool bRelaunch) = 0;
			// return true if the application is in the shutdown phase
			virtual bool	IsQuitting() = 0;

			// Display error message.
			// Logs it to console and file and error message box.
			// Then terminates execution.
			virtual void Error( nMech::tcstr sFormat,... ) = 0;

			//DOC-IGNORE-BEGIN
			//[Timur] DEPRECATED! Use Validator Warning instead.
			// Display warning message.
			// Logs it to console and file and display a warning message box.
			// Not terminates execution.
			//__declspec(deprecated) virtual void Warning( const char *sFormat,... ) = 0;
			//DOC-IGNORE-END

			// Report warning to current Validator object.
			// Not terminates execution.
			virtual void Warning( nMech::nLOG::EValidatorModule module
				,nMech::nLOG::EValidatorSeverity severity
				,int flags,const char *file,const char *format,... ) = 0;
			// Compare specified verbosity level to the one currently set.
			// returns true if this is dedicated server application
			virtual bool IsDedicated() {return false;}

			// return the related subsystem interface
			virtual IGame						*GetIGame() = 0;
			virtual IRenderer				*GetIRenderer() = 0;
			virtual nMech::nJC_SOUND::IMusicSystem		*GetIMusicSystem() = 0;
			virtual IPhysicalWorld	*GetIPhysicalWorld() = 0;
			virtual IMovieSystem		*GetIMovieSystem() = 0;
			virtual IMemoryManager	*GetIMemoryManager() = 0;
			virtual jcIFont				*GetjcIFont()	= 0;
			virtual nMech::nJC_stream::IStreamEngine   *GetStreamEngine() = 0;
			virtual nMech::nLOG::IValidator			*GetIValidator() = 0;
			virtual nMech::nJC::IFrameProfileSystem* GetIProfileSystem() = 0;	

			//virtual	const char			*GetGamePath()=0;

			virtual void DebugStats(bool checkpoint, bool leaks) = 0;
			virtual void DumpWinHeaps() = 0;
			virtual int DumpMMStats(bool log) = 0;

			virtual XDOM::IXMLDOMDocument *CreateXMLDocument() = 0;

			//////////////////////////////////////////////////////////////////////////
			// IXmlNode interface.
			//////////////////////////////////////////////////////////////////////////

			// Creates new xml node.
			virtual XmlNodeRef CreateXmlNode( const char *sNodeName="" ) = 0;
			// Load xml file, return 0 if load failed.
			virtual XmlNodeRef LoadXmlFile( const char *sFilename ) = 0;
			// Load xml from string, return 0 if load failed.
			virtual XmlNodeRef LoadXmlFromString( const char *sXmlString ) = 0;

			virtual void SetViewCamera(nMech::nMath::CCamera &Camera) = 0;
			virtual nMech::nMath::CCamera& GetViewCamera() = 0;

			virtual void CreateEntityScriptBinding(IEntity *pEntity)=0;
			// When ignore update sets to true, system will ignore and updates and render calls.
			virtual void IgnoreUpdates( bool bIgnore ) = 0;

			// Set rate of Garbage Collection for script system.
			// @param fRate in seconds
			virtual void SetGCFrequency( const float fRate ) = 0;

			/* Set the active process
			@param process a pointer to a class that implement the IProcess interface
			*/
			virtual void SetIProcess(IProcess *process) = 0;
			/* Get the active process
			@return a pointer to the current active process
			*/
			virtual IProcess* GetIProcess() = 0;

#if defined (WIN32) || defined (PS2)
			virtual IRenderer* CreateRenderer(bool fullscreen, void* hinst, void* hWndAttach = 0) = 0;
#endif	

			// Returns true if system running in Test mode.
			virtual bool IsTestMode() const = 0;

			virtual void ShowDebugger(const char *pszSourceFile, int iLine, const char *pszReason) = 0;

			//////////////////////////////////////////////////////////////////////////
			// Frame profiler functions
			virtual void SetFrameProfiler(bool on, bool display, char *prefix) = 0;

			//////////////////////////////////////////////////////////////////////////
			// VTune Profiling interface.
			// Resume vtune data collection.
			virtual void VTuneResume() = 0;
			// Pauses vtune data collection.
			virtual void VTunePause() = 0;
			//////////////////////////////////////////////////////////////////////////

			virtual void Deltree(const char *szFolder, bool bRecurse) = 0;

			//////////////////////////////////////////////////////////////////////////
			// File version.
			//////////////////////////////////////////////////////////////////////////

			virtual const SFileVersion& GetFileVersion() = 0;
			virtual const SFileVersion& GetProductVersion() = 0;

			// Compressed file read & write
			virtual bool WriteCompressedFile(char *filename, void *data, unsigned int bitlen) = 0;
			virtual unsigned int ReadCompressedFile(char *filename, void *data, unsigned int maxbitlen) = 0;
			virtual unsigned int GetCompressedFileSize(char *filename)=0;

			// Sample:  char str[256];	bool bRet=GetSSFileInfo("C:\\mastercd\\materials\\compound_indoor.xml",str,256);
			// get info about the last SourceSafe action for a specifed file (Name,Comment,Date)
			// @param inszFileName inszFileName!=0, e.g. "c:\\mastercd\\AssMan\\AssManShellExt\\AssManMenu.cpp"
			// @param outszInfo outszInfo!=0, [0..indwBufferSize-1]
			// @param indwBufferSize >0
			// @return true=success, false otherwise (output parameter is set to empty strings)
			virtual bool GetSSFileInfo( const char *inszFileName, char *outszInfo, const DWORD indwBufferSize )=0;

			// Retrieve IDataProbe interface.
			virtual nMech::IDataProbe* GetIDataProbe() = 0;
			//////////////////////////////////////////////////////////////////////////
			// Configuration.
			//////////////////////////////////////////////////////////////////////////
			// Saves system configuration.
			virtual void SaveConfiguration() = 0;
			// Loads system configuration
			virtual void LoadConfiguration(const string &sFilename)=0;

			// Get current configuration specification.
			virtual ESystemConfigSpec GetConfigSpec() = 0;
			virtual void UpdateLoadingScreen() =0;
		};
		inline ISystem* GetjISystem()
		{
			return g_pISystem;
		}

		//////////////////////////////////////////////////////////////////////////
		// jcSystem DLL Exports.
		//////////////////////////////////////////////////////////////////////////
		typedef ISystem* (*PFNCREATESYSTEMINTERFACE)( SSystemInitParams &initParams );

		// Get the system interface (must be defined locally in each module)
		// interface of the DLL
		extern "C" 
		{
			JC_GAMESYSTEM_API ISystem* CreateSystemInterface( SSystemInitParams &initParams );
		}

		extern __declspec(dllimport) ISystem* g_pISystem;

//////////////////////////////////////////////////////////////////////////
// Additional headers.
//////////////////////////////////////////////////////////////////////////
#include <FrameProfiler.h>

#endif //_JCGAME_SYSTEM_H_
