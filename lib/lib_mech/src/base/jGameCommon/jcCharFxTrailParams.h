#ifndef _JCGAME_COMMON_JCGAME_CHAR_FX_TRAIL_PARAMS_HDR_
#define _JCGAME_COMMON_JCGAME_CHAR_FX_TRAIL_PARAMS_HDR_

struct jcCharFxTrailParams
{
	jcCharFxTrailParams(){}

	jcCharFxTrailParams (int nBone, int nTextureId = -1, float fLength = 0.25f, const nMech::nMath::jVec3d& vStart = nMech::nMath::jVec3d(0,0,0), const nMech::nMath::jVec3d& vEnd = nMech::nMath::jVec3d(0,0,1), unsigned numMaxQuads = 24)
	{
		this->nBone      = nBone;
		this->nTextureId = nTextureId;
		this->vLine[0]   = vStart;
		this->vLine[1]   = vEnd;
		this->fLength    = fLength;
		this->numMaxQuads = numMaxQuads;
	}

	int nBone;			        // bone to which to attach the trail
	int nTextureId;         // tid of the trail
	enum {numVerts = 2};    // number of vertices in the line strip
	nMech::nMath::jVec3d vLine[numVerts];  // the line strip to extrude, in the coordinate frame of the bone
	float fLength;          // length of the trail, in SECONDS
	unsigned numMaxQuads;   // max number of quads constituting the strape
};

#endif