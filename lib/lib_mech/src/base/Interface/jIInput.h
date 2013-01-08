/* file : jIInput.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-07-20 18:00:31
title : 
desc : 

*/

#ifndef __jIInput_header__
#define __jIInput_header__
#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////
//! Keys' code names
////////////////////////////////////////////////////////////////////////////////////////////////
//#ifndef _XBOX


#ifndef KEYS_DEF
#define KEYS_DEF

#ifndef jNOTUSE_JC_PLATFORM

#ifndef _WIN64
#include "jc/platform.h"
#include "jc/jc_Math.h"
#endif
#include <vector>

#endif // jNOTUSE_JC_PLATFORM

#define IS_NULL_KEY(key)			((key)==XKEY_NULL)
#define IS_MOUSE_KEY(key)			((key)&0x00FF0000)
#define IS_JOYPAD_KEY(key)		((key)&0xFF000000)
#define IS_GAMEPAD_KEY(key)		((key)&0xFF000000)
#define IS_KEYBOARD_KEY(key)	((key)&0x0000FFFF)



namespace nMech
{
	struct SInputEvent;
	namespace nINPUT
	{


		//////////////////////////////////////////////////////////////////////////
		enum EKeyModifiersFlags
		{
			XKEY_MOD_NONE = 0,
			XKEY_MOD_LCONTROL	= 0x01,
			XKEY_MOD_RCONTROL	= 0x02,
			XKEY_MOD_LALT	= 0x04,
			XKEY_MOD_RALT	= 0x08,
			XKEY_MOD_LSHIFT = 0x010,
			XKEY_MOD_RSHIFT = 0x020,
			XKEY_MOD_CAPSLOCK = 0x040,
			XKEY_MOD_NUMLOCK = 0x080,

			XKEY_MOD_CONTROL = (0x01 | 0x02),
			XKEY_MOD_ALT = (0x04 | 0x08),
			XKEY_MOD_SHIFT = (0x010 | 0x020),
		};

		//JOYPAD	MOUSE		KEYBOARD
		//	00			00		0000
		enum KeyCodes {
			XKEY_NULL          = 0x00000000, //forbidden

			XKEY_BACKSPACE     = 0x00000001,
			XKEY_TAB           = 0x00000002,
			XKEY_RETURN        = 0x00000003,
			XKEY_CONTROL       = 0x00000004,
			XKEY_ALT           = 0x00000005,
			XKEY_SHIFT         = 0x00000006,
			XKEY_PAUSE         = 0x00000007,
			XKEY_CAPSLOCK      = 0x00000008,
			XKEY_ESCAPE        = 0x00000009,
			XKEY_SPACE         = 0x0000000a,
			XKEY_PAGE_DOWN     = 0x0000000b,
			XKEY_PAGE_UP       = 0x0000000c,
			XKEY_END           = 0x0000000d,
			XKEY_HOME          = 0x0000000e,
			XKEY_LEFT          = 0x0000000f,
			XKEY_UP            = 0x00000010,
			XKEY_RIGHT         = 0x00000011,
			XKEY_DOWN          = 0x00000012,
			XKEY_PRINT         = 0x00000013,
			XKEY_INSERT        = 0x00000014,
			XKEY_DELETE        = 0x00000015,
			XKEY_HELP          = 0x00000016,
			XKEY_0             = 0x00000017,
			XKEY_1             = 0x00000018,
			XKEY_2             = 0x00000019,
			XKEY_3             = 0x0000001a,
			XKEY_4             = 0x0000001b,
			XKEY_5             = 0x0000001c,
			XKEY_6             = 0x0000001d,
			XKEY_7             = 0x0000001e,
			XKEY_8             = 0x0000001f,
			XKEY_9             = 0x00000020,
			XKEY_A             = 0x00000021,
			XKEY_B             = 0x00000022,
			XKEY_C             = 0x00000023,
			XKEY_D             = 0x00000024,
			XKEY_E             = 0x00000025,
			XKEY_F             = 0x00000026,
			XKEY_G             = 0x00000027,
			XKEY_H             = 0x00000028,
			XKEY_I             = 0x00000029,
			XKEY_J             = 0x0000002a,
			XKEY_K             = 0x0000002b,
			XKEY_L             = 0x0000002c,
			XKEY_M             = 0x0000002d,
			XKEY_N             = 0x0000002e,
			XKEY_O             = 0x0000002f,
			XKEY_P             = 0x00000030,
			XKEY_Q             = 0x00000031,
			XKEY_R             = 0x00000032,
			XKEY_S             = 0x00000033,
			XKEY_T             = 0x00000034,
			XKEY_U             = 0x00000035,
			XKEY_V             = 0x00000036,
			XKEY_W             = 0x00000037,
			XKEY_X             = 0x00000038,
			XKEY_Y             = 0x00000039,
			XKEY_Z             = 0x0000003a,
			XKEY_TILDE         = 0x0000003b,
			XKEY_MINUS         = 0x0000003c,
			XKEY_EQUALS        = 0x0000003d,
			XKEY_LBRACKET      = 0x0000003e,
			XKEY_RBRACKET      = 0x0000003f,
			XKEY_BACKSLASH     = 0x00000040,
			XKEY_SEMICOLON     = 0x00000041,
			XKEY_APOSTROPHE    = 0x00000042,
			XKEY_COMMA         = 0x00000043,
			XKEY_PERIOD        = 0x00000044,
			XKEY_SLASH         = 0x00000045,
			XKEY_NUMPAD0       = 0x00000046,
			XKEY_NUMPAD1       = 0x00000047,
			XKEY_NUMPAD2       = 0x00000048,
			XKEY_NUMPAD3       = 0x00000049,
			XKEY_NUMPAD4       = 0x0000004a,
			XKEY_NUMPAD5       = 0x0000004b,
			XKEY_NUMPAD6       = 0x0000004c,
			XKEY_NUMPAD7       = 0x0000004d,
			XKEY_NUMPAD8       = 0x0000004e,
			XKEY_NUMPAD9       = 0x0000004f,
			XKEY_MULTIPLY      = 0x00000050,
			XKEY_ADD           = 0x00000051,
			XKEY_SEPARATOR     = 0x00000052,
			XKEY_SUBTRACT      = 0x00000053,
			XKEY_DECIMAL       = 0x00000054,
			XKEY_DIVIDE        = 0x00000055,
			XKEY_NUMPADENTER   = 0x00000056,  
			XKEY_F1            = 0x00000057,
			XKEY_F2            = 0x00000058,
			XKEY_F3            = 0x00000059,
			XKEY_F4            = 0x0000005a,
			XKEY_F5            = 0x0000005b,
			XKEY_F6            = 0x0000005c,
			XKEY_F7            = 0x0000005d,
			XKEY_F8            = 0x0000005e,
			XKEY_F9            = 0x0000005f,
			XKEY_F10           = 0x00000060,
			XKEY_F11           = 0x00000061,
			XKEY_F12           = 0x00000062,
			XKEY_F13           = 0x00000063,
			XKEY_F14           = 0x00000064,
			XKEY_F15           = 0x00000065,
			XKEY_F16           = 0x00000066,
			XKEY_F17           = 0x00000067,
			XKEY_F18           = 0x00000068,
			XKEY_F19           = 0x00000069,
			XKEY_F20           = 0x0000006a,
			XKEY_F21           = 0x0000006b,
			XKEY_F22           = 0x0000006c,
			XKEY_F23           = 0x0000006d,
			XKEY_F24           = 0x0000006e,
			XKEY_NUMLOCK       = 0x0000006f,
			XKEY_SCROLLLOCK    = 0x00000070,
			XKEY_LCONTROL      = 0x00000071,
			XKEY_RCONTROL      = 0x00000072,
			XKEY_LALT          = 0x00000073,
			XKEY_RALT          = 0x00000074,
			XKEY_LSHIFT        = 0x00000075,
			XKEY_RSHIFT        = 0x00000076,
			XKEY_WIN_LWINDOW   = 0x00000077,
			XKEY_WIN_RWINDOW   = 0x00000078,
			XKEY_WIN_APPS      = 0x00000079,
			XKEY_OEM_102       = 0x00000080,
			XKEY_BUTTON0       = 0x00000100,
			XKEY_BUTTON1       = 0x00000101,
			XKEY_BUTTON2       = 0x00000102,
			XKEY_BUTTON3       = 0x00000103,
			XKEY_BUTTON4       = 0x00000104,
			XKEY_BUTTON5       = 0x00000105,
			XKEY_BUTTON6       = 0x00000106,
			XKEY_BUTTON7       = 0x00000107,
			XKEY_BUTTON8       = 0x00000108,
			XKEY_BUTTON9       = 0x00000109,
			XKEY_BUTTON10      = 0x0000010A,
			XKEY_BUTTON11      = 0x0000010B,
			XKEY_BUTTON12      = 0x0000010C,
			XKEY_BUTTON13      = 0x0000010D,
			XKEY_BUTTON14      = 0x0000010E,
			XKEY_BUTTON15      = 0x0000010F,
			XKEY_BUTTON16      = 0x00000110,
			XKEY_BUTTON17      = 0x00000111,
			XKEY_BUTTON18      = 0x00000112,
			XKEY_BUTTON19      = 0x00000113,
			XKEY_BUTTON20      = 0x00000114,
			XKEY_BUTTON21      = 0x00000115,
			XKEY_BUTTON22      = 0x00000116,
			XKEY_BUTTON23      = 0x00000117,
			XKEY_BUTTON24      = 0x00000118,
			XKEY_BUTTON25      = 0x00000119,
			XKEY_BUTTON26      = 0x0000011A,
			XKEY_BUTTON27      = 0x0000011B,
			XKEY_BUTTON28      = 0x0000011C,
			XKEY_BUTTON29      = 0x0000011D,
			XKEY_BUTTON30      = 0x0000011E,
			XKEY_BUTTON31      = 0x0000011F,
			//MOUSE
			XKEY_MOUSE1				 = 0x00010000,
			XKEY_MOUSE2				 = 0x00020000,
			XKEY_MOUSE3				 = 0x00030000,
			XKEY_MOUSE4				 = 0x00040000,
			XKEY_MOUSE5				 = 0x00050000,
			XKEY_MOUSE6				 = 0x00060000,
			XKEY_MOUSE7				 = 0x00070000,
			XKEY_MOUSE8				 = 0x00080000,
			XKEY_MWHEEL_UP		 = 0x00090000,
			XKEY_MWHEEL_DOWN	 = 0x000A0000,
			XKEY_MAXIS_X			 = 0x000B0000,
			XKEY_MAXIS_Y			 = 0x000C0000,

			//JOYPAD

			//GAMEPAD
			XKEY_GP_A   	    		= 0x01000000,
			XKEY_GP_B       			= 0x02000000,
			XKEY_GP_X   	    		= 0x03000000,
			XKEY_GP_Y   	    		= 0x04000000,
			XKEY_GP_BLACK       	= 0x05000000,
			XKEY_GP_WHITE       	= 0x06000000,
			XKEY_GP_LEFT_TRIGGER  = 0x07000000,
			XKEY_GP_RIGHT_TRIGGER = 0x08000000,

			XKEY_GP_DPAD_UP       = 0x11000000,
			XKEY_GP_DPAD_DOWN     = 0x12000000,
			XKEY_GP_DPAD_LEFT     = 0x13000000,
			XKEY_GP_DPAD_RIGHT    = 0x14000000,
			XKEY_GP_START         = 0x15000000,
			XKEY_GP_BACK          = 0x16000000,
			XKEY_GP_LEFT_THUMB    = 0x17000000,
			XKEY_GP_RIGHT_THUMB   = 0x18000000,

			XKEY_GP_STHUMBLUP     = 0x19000000,
			XKEY_GP_STHUMBLDOWN   = 0x1a000000,
			XKEY_GP_STHUMBLLEFT   = 0x1b000000,
			XKEY_GP_STHUMBLRIGHT  = 0x1c000000,

			XKEY_GP_STHUMBLX      = 0x21000000,
			XKEY_GP_STHUMBLY      = 0x22000000,
			XKEY_GP_STHUMBRX      = 0x23000000,
			XKEY_GP_STHUMBRY      = 0x24000000,
		};

#endif  //KEYS_DEF


		enum XActionActivationMode
		{
			aamOnPress,
			aamOnDoublePress,
			aamOnPressAndRelease,
			aamOnRelease,
			aamOnHold
		};

		enum XActivationEvent
		{
			etPressing,
			etHolding,
			etReleasing,
			etDoublePressing
		};

		struct XBind
		{
			XBind()
			{
				nKey=XKEY_NULL;
				nModifier=XKEY_NULL;
				//		aam=aamOnPress;
				//		bConfigurable=false;
				//		bReplicate=false;
			}
			int nKey;
			int nModifier;
			//	XActionActivationMode aam;
			//	bool bConfigurable;
			//	bool bReplicate;
		};
		//////////////////////////////////////////////////////////////////////
		// Input interface for the XBox controller
		//////////////////////////////////////////////////////////////////////

		/*! InputEvents are generated by input system and broadcasted to all event listeners.
		*/

		//////////////////////////////////////////////////////////////////////////
		/* Input event listeners registered to input system and recieve input events when they are generated.
		*/
		struct IInputEventListener
		{
			//! Called every time input event is generated.
			//! @return if return True then broadcasting of this event should be aborted and the rest of input 
			//! listeners should not recieve this event.
			virtual bool OnInputEvent( const SInputEvent &event ) = 0;
		};


#define jINTERFACE_IKeyboard(x) public:	\
	virtual void	ShutDown() ##x \
	/*! allow to force a key code value */ \
	/*/ virtual void    SetKey(int p_key, int value) = 0; */ \
	/*! allow to force a key code value*/ \
	/*virtual inline  void    SetPrevKey(int p_key, int value) = 0;*/ \
	/*! check for key pressed and held */ \
	virtual bool	KeyDown(int p_key) ##x \
	/* ! check for key pressed only once */ \
	virtual bool	KeyPressed(int p_key) ##x \
	/* ! check if the key has been released*/ \
	virtual bool	KeyReleased(int p_key) ##x \
	/* ! clear the key status*/ \
	virtual void ClearKey(int p_key) ##x \
	/* ! return the code of the key pressed*/ \
	virtual int		GetKeyPressedCode() ##x \
	/* ! return the name of the key pressed */ \
	virtual acstr GetKeyPressedName() ##x \
	/* ! return the code of the key down*/ \
	virtual int		GetKeyDownCode() ##x \
	/* ! return the name of the key down*/ \
	virtual acstr GetKeyDownName() ##x \
	/* ! set/unset directinput to exclusive mode*/ \
	virtual void	SetExclusive(bool value,void *hwnd=0) ##x \
	/* ! wait for a key pressed*/ \
	virtual void	WaitForKey() ##x \
	/* ! clear the key (pressed) state*/ \
	virtual void	ClearKeyState() ##x \

		jINTERFACE_END(IKeyboard);

#define jINTERFACE_IMouse(x) public:	\
	virtual void Shutdown() ##x \
	/* ! check for a mouse button pressed and held */ \
	virtual bool MouseDown(int p_numButton) ##x \
	/* ! check for a mouse button pressed only once*/ \
	virtual bool MousePressed(int p_numButton) ##x \
	/* ! check if the mouse button has been released*/ \
	virtual bool MouseReleased(int p_numButton) ##x \
	/* ! force the mouse wheel rotation to a certain value*/ \
	virtual void SetMouseWheelRotation(int value) ##x \
	/* ! set/reset Directinput to exclusive mode*/ \
	virtual bool SetExclusive(bool value,void *hwnd=0) ##x \
	/* ! get mouse X delta (left-right)*/ \
	virtual float GetDeltaX() ##x \
	/* ! get mouse Y delta (up-down)*/ \
	virtual float GetDeltaY() ##x \
	/* ! get mouse Z delta (mouse wheel)*/ \
	virtual float GetDeltaZ() ##x \
	/* ! set mouse inertia*/ \
	virtual void SetInertia(float) ##x \
	/* ! set mouse X screen corrdinate*/ \
	virtual void	SetVScreenX(float fX) ##x \
	/* ! set mouse Y screen corrdinate*/ \
	virtual void	SetVScreenY(float fY) ##x \
	/* ! get mouse X screen corrdinate*/ \
	virtual float	GetVScreenX() ##x \
	/* ! get mouse Y screen corrdinate*/ \
	virtual float	GetVScreenY() ##x \
	/* ! set the mouse sensitivity*/ \
	virtual void SetSensitvity(float fSensitivity) ##x \
	/* ! get the mouse sensitivity*/ \
	virtual float GetSensitvity() ##x \
	/* ! set the mouse sensitivity scale (from 0 to 1)*/ \
	virtual void SetSensitvityScale(float fSensScale) ##x \
	/* ! get the mouse sensitivity scale*/ \
	virtual float GetSensitvityScale() ##x \
	/* ! clear the key states*/ \
	virtual void ClearKeyState() ##x \

		jINTERFACE_END(IMouse);



#define BEGIN_INPUTACTIONMAP() void OnAction(nMech::nINPUT::XACTIONID nActionID\
							, float fValue,nMech::nINPUT::XActivationEvent ae) { switch(nActionID) {
#define END_INPUTACTIONMAP() default: break; } }
#define REGISTER_INPUTACTIONMAP(actionid, handler) case actionid: handler(fValue,ae); break;
#define MAX_BINDS_PER_ACTION 2

		struct IInput;
		typedef int XACTIONID;
		struct IActionMapSink
		{
			virtual void OnAction(XACTIONID nActionID, float fValue, XActivationEvent ae) = 0;
		};

		struct IActionMap
		{
			virtual void ResetAllBindings() = 0;
			virtual void ResetBinding(XACTIONID nActionID) = 0;
			virtual void RemoveBind(XACTIONID nActionID, XBind &NewBind, XActionActivationMode aam) = 0;
			virtual void BindAction(XACTIONID nActionID,XBind &NewBind, int iKeyPos = -1)=0;//int nKey,int nModifier=XKEY_NULL) = 0;
			virtual void BindAction(XACTIONID nActionID,int nKey, int nModifier=XKEY_NULL, int iKeyPos = -1) = 0;//, bool bConfigurable=false, bool bReplicate=false) = 0;
			virtual void BindAction(XACTIONID nActionID, acstr sKey,acstr sModifier=NULL, int iKeyPos = -1) = 0;
			virtual void GetBinding(XACTIONID nActionID, int nKeyPos, XBind &Bind) = 0;
			virtual void GetBinding(XACTIONID nActionID, int nKeyPos, int &nKey, int &nModifier) = 0;
			virtual void GetBinding(XACTIONID nActionID, int nKeyPos, char *pszKey, char *pszModifier) = 0;
			// compare this action map with the one passed and store the key differences in keys
			virtual void GetBindDifferences(IActionMap *pActionMap, std::vector<int>& keys) = 0;
		};

		struct IActionMapDumpSink
		{
			virtual void OnElementFound(acstr pszActionMapName, IActionMap *pActionMap) = 0;
		};

		struct IActionMapManager
		{
			virtual void SetInvertedMouse(bool bEnable)=0;
			virtual bool GetInvertedMouse()=0;;

			virtual void RemoveBind(XACTIONID nActionID, XBind &NewBind, XActionActivationMode aam) = 0;

			virtual void SetSink(IActionMapSink *pSink) = 0;
			virtual void CreateAction(XACTIONID nActionID,acstr sActionName,XActionActivationMode aam=aamOnPress) = 0;

			virtual IActionMap *CreateActionMap(acstr s) = 0;
			virtual IActionMap *GetActionMap(acstr s) = 0;

			virtual void ResetAllBindings() = 0;

			virtual void GetActionMaps(IActionMapDumpSink *pCallback) = 0;

			virtual void SetActionMap(acstr s) = 0;

			virtual bool CheckActionMap(XACTIONID nActionID) = 0;
			virtual bool CheckActionMap(acstr sActionName) = 0;
			virtual void Reset() = 0;
			virtual void Update(unsigned int nTimeMSec) = 0;
			virtual void Release() = 0;

			virtual void Enable() = 0;
			virtual void Disable() = 0;
			virtual bool IsEnabled() = 0;
		};
		//////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////
		typedef unsigned char INPUTACTIONID;

		//@{ Helper macros to implement the action triggers callback interface
#define BEGIN_INPUTACTIONTRIGGERS() void OnAction(INPUTACTIONID nActionID, float fValue) { switch(nActionID) {
#define END_INPUTACTIONTRIGGERS() default: break; } }
#define REGISTER_INPUTACTIONTRIGGER(actionid, handler) case actionid: handler(fValue); break;
		//@}

		// Action triggers callback interface
		struct IInputActionTriggerSink
		{
			virtual void OnAction(INPUTACTIONID nActionID, float fValue) = 0;
		};

		//! Action map interface
		struct IInputActionMap
		{
			virtual void SetSink(IInputActionTriggerSink *pIActionTrigger) = 0;

			virtual void Release() = 0;

			//! Check all actions
			virtual void Update() = 0;

			// Call the action trigger
			virtual void CallActionTrigger(INPUTACTIONID nActionID, float fValue) = 0;

			//! Return the amount of pressing of the action input if the action is
			//! currently done
			virtual float CheckAction(const INPUTACTIONID nActionID) = 0;

			/*! Set a new action
			@param nActionID id that identity the action[eg. ACTION_JUMP]
			@param bCheckPressed if true the action event is triggered only once when a button is pressed
			else the action is send every frame until the button is released
			@param szCodes key identifiers [eg. "MBT_1" mouse button]
			@param szMods key modifier [eg. "SHIFT"]
			@return true=succeded,false=failed*/

			virtual bool SetAction(const INPUTACTIONID nActionID,bool bCheckPressed, cstr szCodes, cstr szMods=NULL) = 0;

			virtual void ClearAction(const INPUTACTIONID nActionID) = 0;
		};

		struct jIInputActionMap;

		struct SInputEvent
		{
			//! Input Event types.
			enum EType
			{
				UNKNOWN,
				KEY_PRESS,
				KEY_RELEASE,
				MOUSE_MOVE,
			};

			//! Type of input event.
			EType type;
			//! Key which was pressed or released, one of the XKeys.
			//! @see KeyCodes
			int key;
			//! Timestamp of the event, (GetTickCount compatable).
			unsigned int timestamp;

			//! Key modifiers enabled at the time of this event.
			//! @see EKeyModifiersFlags
			int moidifiers;

			//! Name of the event key.
			nMech::acstr keyname;

			//! For mouse axises.
			float value;

			SInputEvent()
			{
				moidifiers = nINPUT::XKEY_MOD_NONE;
				key = 0;
				type = UNKNOWN;
				timestamp = 0;
				keyname = 0;
				value = 0;
			}
		};


#ifndef jNOTUSE_JC_PLATFORM
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	/*! Main Input system interface.
	*/

	#define jINTERFACE_IInput(x) public:	\
		/*! Register new input events listener. */ \
		virtual void AddEventListener( IInputEventListener *pListener ) ##x \
		virtual void RemoveEventListener( IInputEventListener *pListener ) ##x \
		virtual void EnableEventPosting ( bool bEnable ) ##x \
		/*! Register new console input event listeners. console input listeners receive all events, no matter what.*/ \
		virtual void AddConsoleEventListener( IInputEventListener *pListener ) ##x \
		virtual void RemoveConsoleEventListener( IInputEventListener *pListener ) ##x \
		virtual void SetExclusiveListener( IInputEventListener *pListener ) ##x \
		virtual IInputEventListener *GetExclusiveListener() ##x \
		/*! update Keyboard, Mouse and Joystick. Set bFocus to true if window has focus and input is enabled.*/ \
		virtual void	Update(bool) ##x \
		/*! clear all subsystems*/ \
		virtual void	ShutDown() ##x \
		/*! @see IMouse::SetExclusive*/ \
		virtual void	SetMouseExclusive(bool exclusive,void *hwnd=0) ##x \
		/*! @see IKeyboard::SetExclusive*/ \
		virtual void	SetKeyboardExclusive(bool exclusive,void *hwnd=0) ##x \
		/*! @see IKeyBoard::KeyDown*/ \
		virtual bool	KeyDown(int p_key) ##x \
		/*! @see IKeyBoard::KeyPressed*/ \
		virtual bool	KeyPressed(int p_key) ##x \
		/*! @see IKeyBoard::KeyRelease*/ \
		virtual bool	KeyReleased(int p_key) ##x \
		/*! @see IMouse::MouseDown*/ \
		virtual bool	MouseDown(int p_numButton) ##x \
		/*! @see IMouse::MousePressed*/ \
		virtual bool	MousePressed(int p_numButton) ##x \
		/*! @see IMouse::MouseDblClick*/ \
		virtual bool	MouseDblClick(int p_numButton) ##x \
		/*! @see IMouse::MouseReleased*/ \
		virtual bool	MouseReleased(int p_numButton) ##x \
		/*! @see IMouse::GetDeltaX*/ \
		virtual float	MouseGetDeltaX() ##x \
		/*! @see IMouse::GetDeltaY*/ \
		virtual float	MouseGetDeltaY() ##x \
		/*! @see IMouse::GetDeltaZ*/ \
		virtual float	MouseGetDeltaZ() ##x \
		/*! @see IMouse::GetVScreenX*/ \
		virtual float	MouseGetVScreenX() ##x \
		/*! @see IMouse::GetVScreenY*/ \
		virtual float MouseGetVScreenY() ##x \
		/*! Converts a key-name to the key-id*/ \
		virtual int GetKeyID(acstr sName) ##x \
		virtual void EnableBufferedInput(bool bEnable) ##x \
		virtual void FeedVirtualKey(int nVirtualKey,long lParam,bool bDown) ##x \
		virtual int GetBufferedKey() ##x \
		virtual const char* GetBufferedKeyName() ##x \
		virtual void PopBufferedKey() ##x \
		/*! @see IMouse::SetInertia*/ \
		virtual void SetMouseInertia(float) ##x \
		/*! check if the joystick button has been pressed*/ \
		virtual bool	JoyButtonPressed(int p_numButton) ##x \
		/*! check the joystick direction*/ \
		virtual int		JoyGetDir() ##x \
		/*! check the joy hat direction*/ \
		virtual int		JoyGetHatDir() ##x \
		virtual nMech::nMath::jVec3	JoyGetAnalog1Dir(unsigned int joystickID) const  ##x \
		virtual nMech::nMath::jVec3	JoyGetAnalog2Dir(unsigned int joystickID) const  ##x \
		/*! return the keyboard interface */ \
		virtual IKeyboard *GetIKeyboard() ##x \
		/*! return the mouse interface */ \
		virtual IMouse * GetIMouse() ##x \
		/*! Convert key code to the key name.*/ \
		/*! @param nKey one of xkey codes.*/ \
		/*! @param modifiers current modifiers (shift,ctrl,..).*/ \
		/*! @see KeyCodes.*/ \
		virtual acstr GetKeyName(int nKey,int modifiers=0, bool bGUI = 0) ##x \
		virtual bool GetOSKeyName(int nKey, wchar_t *szwKeyName, int iBufSize) ##x \
		/*! @see IKeyBoard::GetKeyPressedCode*/ \
		virtual int		GetKeyPressedCode() ##x \
		/*! @see IKeyBoard::GetKeyPressedName*/ \
		virtual acstr GetKeyPressedName() ##x \
		/*! @see IKeyBoard::GetKeyDownCode*/ \
		virtual int		GetKeyDownCode() ##x \
		/*! @see IKeyBoard::GetKeyDownName*/ \
		virtual acstr GetKeyDownName() ##x \
		/*! @see IKeyBoard::WaitForKey*/ \
		virtual void	WaitForKey() ##x \
		/*! action mapper*/ \
		virtual struct IActionMapManager* CreateActionMapManager() ##x \
		/*! return the name of the current XKEY(both mouse and keyboard excluding mouse delta)*/ \
		/*! useful for the GUI to retrieve the first key pressed during the key configuration*/ \
		virtual acstr GetXKeyPressedName() ##x \
		/*! clear key states of all devices*/ \
		virtual void ClearKeyState() ##x \
		virtual unsigned char GetKeyState(int nKey) ##x \
		virtual jIInputActionMap* GetInputActionMap() ##x\
		virtual bool Init(HINSTANCE hinst,HWND hwnd,bool dinput) ##x \

		jINTERFACE_END(IInput);
#endif //jNOTUSE_JC_PLATFORM


	}//namespace nINPUT

	namespace nInterface
	{
		extern JBASE_API nINPUT::IInput* g_pIInput;
	}


}//namespace nMech


#endif // __jIInput_header__
