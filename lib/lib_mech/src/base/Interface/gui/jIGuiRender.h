/* file : jIGuiRender.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-07-06 11:13:05
title : 
desc : 

*/

#ifndef __jIGuiRender_header__
#define __jIGuiRender_header__
#pragma once
#ifndef RENDER_DEVICE_t
#define RENDER_DEVICE_t void*
#endif
//#define RENDER_TARGET_DEVICE_t IDirect3DDevice9*
#include <math.h>

namespace nMech
{
	namespace nGUI
	{

#ifndef jD3DCOLOR_ARGB
		typedef DWORD jD3DCOLOR;
#define jD3DCOLOR_ARGB(a,r,g,b) ((jD3DCOLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#endif


#define jMAKELONG(low, hi)      ((LONG)(((WORD)((DWORD_PTR)(low) & 0xffff)) | ((DWORD)((WORD)((DWORD_PTR)(hi) & 0xffff))) << 16))
#define jLOWORD(l)           ((WORD)((DWORD_PTR)(l) & 0xffff))
#define jHIWORD(l)           ((WORD)((DWORD_PTR)(l) >> 16))

		inline int RectWidth( RECT &rc ) { return ( (rc).right - (rc).left ); }
		inline int RectHeight( RECT &rc ) { return ( (rc).bottom - (rc).top ); }

		typedef DWORD jGUICOLOR;


		enum jGUI_CTRL_STATE
		{
			jGUI_CTRL_STATE_BEGIN,
			eGUI_STATE_NORMAL,
			eGUI_STATE_DISABLED,
			eGUI_STATE_HIDDEN,
			eGUI_STATE_FOCUS,
			eGUI_STATE_MOUSEOVER,
			eGUI_STATE_PRESSED,
			jGUI_CTRL_STATE_END
		};

		struct _jGuiTextureNode
		{
			//jIE* m_pE;
			TCHAR strFilename[MAX_PATH];
			void* m_iTextureHadle;
			DWORD dwWidth;
			DWORD dwHeight;
		};

		struct _jGuiFontNode
		{
			jIE* m_pE; // gui_prototype.xml에서 FONT리스트의 항목
			void* m_iFontHandle;
			LONG  nHeight;
			LONG  nWeight;
			_jGuiFontNode(){ memset(this ,0 , sizeof(*this) ); }
		};

		struct jGuiRenderStateObj
		{
		public:
			virtual void Begin(RENDER_DEVICE_t)=0;
			virtual void End(RENDER_DEVICE_t)=0;
		};


		//d3dx9math.h D3DXCOLOR
		//d3dx9math.inl INLINE FUNC
		struct jGuiColor
		{
			float r, g, b, a;

			operator DWORD () const
			{
				DWORD dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (DWORD) (r * 255.0f + 0.5f);
				DWORD dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (DWORD) (g * 255.0f + 0.5f);
				DWORD dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (DWORD) (b * 255.0f + 0.5f);
				DWORD dwA = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (DWORD) (a * 255.0f + 0.5f);
				return (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
			}
			void Init( DWORD dw )
			{
				CONST FLOAT f = 1.0f / 255.0f;
				r = f * (FLOAT) (unsigned char) (dw >> 16);
				g = f * (FLOAT) (unsigned char) (dw >>  8);
				b = f * (FLOAT) (unsigned char) (dw >>  0);
				a = f * (FLOAT) (unsigned char) (dw >> 24);
			}

		};
		inline jGuiColor* jGuiColorLerp (jGuiColor *pOut, const jGuiColor *pC1, const jGuiColor *pC2, FLOAT s)
		{
			pOut->r = pC1->r + s * (pC2->r - pC1->r);
			pOut->g = pC1->g + s * (pC2->g - pC1->g);
			pOut->b = pC1->b + s * (pC2->b - pC1->b);
			pOut->a = pC1->a + s * (pC2->a - pC1->a);
			return pOut;
		}

		struct jVECTOR2{ float x,y;};
		struct jILineManager
		{
			virtual int AddLine( jVECTOR2* pVertexList, DWORD dwVertexListCount, jGUICOLOR Color, float fWidth=1.f, float fScaleRatio=1.f, bool bAntiAlias=false )=0;
			virtual int AddRect( RECT rc, jGUICOLOR Color, float fWidth=1.f, float fScaleRatio=1.f, bool bAntiAlias=false )=0;
			virtual void RemoveLine( int nLineID )=0;
			virtual void RemoveAllLines()=0;
			virtual void OnRender()=0;

		};

		//--------------------------------------------------------------------------
		struct jIGuiResManager
			//--------------------------------------------------------------------------
		{
			virtual _jGuiFontNode* AddFont( jIE* peFont )=0;
			virtual _jGuiTextureNode* AddTexture( LPCTSTR strFilename )=0;
			virtual RENDER_DEVICE_t GetRenderDevice()=0;
			virtual HRESULT     OnCreateDevice( HWND hWnd, RENDER_DEVICE_t pd3dDevice )=0;
			virtual HRESULT     OnResetDevice()=0;
			virtual void        OnLostDevice()=0;
			virtual void        OnDestroyDevice()=0;

			virtual HRESULT CreateFont( UINT index )=0;
			virtual HRESULT CreateTexture( UINT index )=0;
			//* *_* by ALo : 2006-01-25
			virtual RENDER_DEVICE_t GetSprite()=0;
			/**/ //*_* by ALo : 2006-01-25

			virtual void SetDeviceCursor( _jGuiTextureNode* pTex , jIE* peCursorNode)=0;
			virtual void SetSystemCursor()=0;
			virtual void OnResetDeviceCursor()=0;
		};


		//---------------------------------------------------------------
		struct  _jGuiBlendColor
			//----------------------------------------------------------------
		{
			jIVar* States[ jGUI_CTRL_STATE_END ]; // Modulate colors for all possible control states
			jGuiColor Current;
			_jGuiBlendColor(){ memset(States,0,sizeof(States) );}
			//--------------------------------------------------------------------------------------
			void Blend( UINT iState, float fElapsedTime, float fRate= 0.7f )
			{
				jGuiColor destColor;
				destColor.Init((DWORD)States[ iState ]->Get_ARGB() );
				jGuiColorLerp( &Current, &Current, &destColor, 1.0f - powf( fRate, 30 * fElapsedTime ) );
			}

		};


		//-----------------------------------------------------------------------------
		// Contains all the display tweakables for a sub-control
		//-----------------------------------------------------------------------------
		struct _jGuiElement
		{
		public:
			void _jGuiElement::Refresh()
			{
				jIVar* pV = TextureColor.States[ eGUI_STATE_HIDDEN ];
				if(pV)	TextureColor.Current.Init(pV? pV->Get_ARGB():jD3DCOLOR_ARGB(255,0,0,0));

				pV = FontColor.States[ eGUI_STATE_HIDDEN ];
				if(pV)	FontColor.Current.Init(pV? pV->Get_ARGB(): jD3DCOLOR_ARGB(255,0,0,0) );
			}

			_jGuiElement::_jGuiElement()
			{
				m_pEorg=0;
				m_pE=0;
				m_peTexture=0;
				m_peFontList=0;
				m_pvTextFormat=0;
				m_pvTexRect=0;
			}

			//--------------------------------------------------------------------------------------
			RECT* GetTexRect()
			{ 
				assert(m_pvTexRect->GetType()==jIVar::EDint4); 
				return (RECT*)m_pvTexRect->GetIntP();
			}
			//--------------------------------------------------------------------------------------

			jIE* m_pEorg; //gui_prototype 의 항목
			jIE* m_pE; /// ctrl마다 생성된 gui_prototype 의 항목에 대한 메모리상에 존재하는 복사본에대한 node
			jIE* m_peTexture;          // Index of the texture for this Element 
			jIE* m_peFontList;             // Index of the font for this Element

			jIVar* m_pvTextFormat;     // The format argument to jDrawTextA 
			DWORD GetTextFormat() { return (DWORD)m_pvTextFormat->GetUserData();	}
			//DWORD GetTextFormat() { return m_pvTextFormat->uintValue();	}


			jIVar* m_pvTexRect;
			//RECT rcTexture;         // Bounding rect of this element on the composite texture
			_jGuiBlendColor TextureColor;
			_jGuiBlendColor FontColor;

		};
		typedef jIVar* jIVarP;

		struct jIGuiRender
		{
			virtual jIGuiResManager* GetResManager()=0;
			virtual jILineManager* GetLineManager()=0;

			virtual void CreateDevice(HWND hWnd, RENDER_DEVICE_t pd3dDevice)=0;	
			virtual void OnResetDevice()=0;
			virtual void OnLostDevice()=0;
			virtual void OnDestroyDevice()=0;
			virtual bool OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)=0;
			virtual void ChangeCursor(_jGuiTextureNode* pTexCursor , _jGuiElement*)=0;
			virtual void SetCursorShow(bool is)=0;
			virtual void StageRenderBegin()=0;
			virtual void StageRenderEnd()=0;
			virtual void SpriteRenderBegin(int iFlag =-1)=0;
			virtual void SpriteRenderEnd()=0;
			virtual void DialogRenderBegin(jIVar* pvXY, jIVar* pvWH,jIVarP pvBGCol[4])=0;
			virtual void DialogRenderEnd()=0;
			virtual void RenderStateBegin(jGuiRenderStateObj* pRS)=0;
			virtual void RenderStateEnd(jGuiRenderStateObj* pRS)=0;

			virtual void StateBlockCaptureBegin()=0;
			virtual void StateBlockCaptureEnd()=0;


			virtual void ReLoadFont(_jGuiFontNode*)=0;
			virtual HDC GetFontDC(_jGuiFontNode* pFnt)=0;
			virtual POINT GetScreenSize()=0;
			//---------------------------------------------------------------	
			// Render helpers
			//----------------------------------------------------------------
			virtual HRESULT jDrawRect( RECT* pRect, jGUICOLOR color )=0;
			virtual HRESULT jDrawPolyLine(POINT &poOffset,  POINT* apPoints
				, UINT nNumPoints, jGUICOLOR color )=0;
			virtual HRESULT jDrawSprite( jGuiColor* texColor ,RECT* prcTex 
				, RECT* prcDest , _jGuiTextureNode* pTex  )=0;
			virtual HRESULT jDrawSprite_SRP( jGuiColor* texColor ,RECT* prcTex 
				, const POINT& poTexCenter , void* pTexHandle
				, const POINT& pScreePos,float* pRotQuat, float* pScale )=0;
			virtual HRESULT jDrawSpriteWrap(jGuiColor* texColor, RECT* prcSrc
				, RECT* prcDest , _jGuiTextureNode* pTex  )=0;
			virtual HRESULT jCalcTextRectA( LPCTSTR strText, _jGuiElement* pElement
				, RECT* prcDest, _jGuiFontNode* pFontNode,int nCount = -1 )=0;
			virtual HRESULT jCalcTextRectW( LPCWSTR strText, _jGuiElement* pElement
				, RECT* prcDest,_jGuiFontNode* pFontNode, int nCount = -1 )=0;
			virtual HRESULT jDrawTextA( LPCTSTR strText, _jGuiElement* pElement, RECT* prcDest
				, _jGuiFontNode* pFontNode,bool bShadow = false, int nCount = -1 )=0;
			virtual HRESULT jDrawTextW( LPCWSTR strText, _jGuiElement* pElement, RECT* prcDest
				, _jGuiFontNode* pFontNode,bool bShadow=false, int nCount = -1 )=0;
			virtual HRESULT jDrawText( LPCTSTR strText, _jGuiElement* pElement, RECT* prcDest
				,_jGuiFontNode* pFontNode, bool bShadow=false, int nCount = -1 )=0;

			virtual HRESULT jCalcTextRect( LPCTSTR strText, _jGuiElement* pElement
				, RECT* prcDest, _jGuiFontNode* pFontNode,int nCount = -1 )=0;

		};


	}
}


#endif // __jIGuiRender_header__
