/* file : jMTL_CHUNK.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-12-21 13:42:03
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jMTL_CHUNK_header__
#define __jMTL_CHUNK_header__
#pragma once




// jGameExport/jcHeader.h
struct MTL_CHUNK_DESC_0746
{
	enum {VERSION = 0x0746};
	CHUNK_HEADER	chdr;
	char			name[64];	  //material/shader name 
	char      Reserved[60];
	float			alphaTest;
	MtlTypes		MtlType;	//one of the MtlTypes enum values

	union
	{
		struct
		{
			jcIRGB		col_d;		//diffuse color
			jcIRGB		col_s;		//specular color
			jcIRGB		col_a;		//ambient color
			float     specLevel; // Specular level.
			float     specShininess;
			float			selfIllum;	// self illumination.
			float			opacity;		// Opacity 0-1.

			TextureMap3	tex_a;		//Ambient Texture settings
			TextureMap3	tex_d;		//Diffuse Texture settings
			TextureMap3	tex_s;		//Specular Texture settings
			TextureMap3	tex_o;		//Opacity Texture settings
			TextureMap3	tex_b;		//Bump Texture settings
			TextureMap3	tex_g;		//Gloss Texture settings
			TextureMap3	tex_fl;		//Filter texture (Detail Texture settings)
			TextureMap3	tex_rl;		//Reflection Texture settings
			TextureMap3	tex_subsurf;		//Subsurface scattering Texture settings
			TextureMap3	tex_det;  //Detail Texture settings

			int			flags;

			float		Dyn_Bounce;
			float		Dyn_StaticFriction;
			float		Dyn_SlidingFriction;
		};

		struct
		{
			int		nChildren;
		};
	};
};


#endif // __jMTL_CHUNK_header__
