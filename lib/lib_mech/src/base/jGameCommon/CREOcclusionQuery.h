 
#ifndef __CREOCCLUSIONQUERY_H__
#define __CREOCCLUSIONQUERY_H__

//=============================================================

class CREOcclusionQuery : public CRendElement
{
  friend class CRender3D;
public:

  int m_nVisSamples;
  int m_nCheckFrame;
  int m_nDrawFrame;
	nMech::nMath::jVec3 m_vBoxMin;
	nMech::nMath::jVec3 m_vBoxMax;
#ifdef OPENGL
	nMech::uint m_nOcclusionID;
#if defined(WIN64) || defined(LINUX64)
	nMech::uint m_nOcclusionID2; // this is the safety dummy value to make the occlusion id extendable to 64-bit
#endif
#else
  UINT_PTR m_nOcclusionID; // this will carry a pointer LPDIRECT3DQUERY9, so it needs to be 64-bit on WIN64 
#endif
		

  CREOcclusionQuery()
  {
    m_nOcclusionID = 0;
    m_nVisSamples = 800*600;
    m_nCheckFrame = 0;
    m_nDrawFrame = 0;
		m_vBoxMin=nMech::nMath::jVec3(0,0,0);
		m_vBoxMax=nMech::nMath::jVec3(0,0,0);

		mfSetType(eDATA_OcclusionQuery);
    mfUpdateFlags(FCEF_TRANSFORM);
  }

  virtual ~CREOcclusionQuery();

  virtual void mfPrepare();
  virtual bool mfDraw(SShader *ef, SShaderPass *sfm);
  virtual void mfReset();
};

#endif  // __CREOCCLUSIONQUERY_H__
