#ifndef primitives_h
#define primitives_h

namespace primitives {

////////////////////////// primitives //////////////////////

	struct primitive {
	};

	struct box : primitive {
		enum entype { type=0 };
		nMech::nMath::matrix3x3f Basis;
		int bOriented;
		nMech::nMath::vectorf center;
		nMech::nMath::vectorf size;
	};

	struct triangle : primitive {
		enum entype { type=1 };
		nMech::nMath::vectorf pt[3];
		nMech::nMath::vectorf n;
	};

	struct indexed_triangle : triangle {
		int idx;
	};

	struct grid : primitive {
		nMech::nMath::matrix3x3f Basis;
		int bOriented;
		nMech::nMath::vectorf origin;
		nMech::nMath::vector2df step,stepr;
		nMech::nMath::vector2di size;
		nMech::nMath::vector2di stride;

		int inrange(int ix, int iy) 
		{	
			return nMech::nMath::isneg(ix-size.x) & nMech::nMath::isnonneg(ix) 
						& nMech::nMath::isneg(iy-size.y) & nMech::nMath::isnonneg(iy); 
		}
		int getcell_safe(int ix,int iy) 
		{ 
			int mask=-inrange(ix,iy); return iy*stride.y+ix*stride.x&mask | size.x*size.y&~mask; 
		}
	};

	struct heightfield : grid {
		enum entype { type=2 };
		heightfield& operator=(const heightfield &src) {
			step = src.step; stepr = src.stepr;
			size = src.size; stride = src.stride;
			pdata = src.pdata; heightscale = src.heightscale;
			pflags = src.pflags; typemask = src.typemask;
			typehole = src.typehole; typepower = src.typepower;
			return *this;
		}

		float getheight(int ix,int iy) const { return getheight(ix*stride.x+iy*stride.y); }
		int gettype(int ix,int iy) const { return gettype(ix*stride.x+iy*stride.y); }
		float getheight(int icell) const { return pdata[icell]*heightscale; }
		int gettype(int icell) const { 
			int itype=pflags[icell]>>typepower & typemask, idelta=itype-typehole;
			return itype | ((idelta-1)>>31 ^ idelta>>31);
		}

		unsigned short *pdata;
		float heightscale;
		unsigned short *pflags;
		unsigned short typemask;
		int typehole;
		int typepower;
	};

	struct ray : primitive {
		enum entype { type=3 };
		nMech::nMath::vectorf origin;
		nMech::nMath::vectorf dir;
	};

	struct sphere : primitive {
		enum entype { type=4 };
		nMech::nMath::vectorf center;
		float r;
	};

	struct cylinder : primitive {
		enum entype { type=5 };
		nMech::nMath::vectorf center;
		nMech::nMath::vectorf axis;
		float r,hh;
	};

	struct plane : primitive {
		enum entype { type=6 };
		nMech::nMath::vectorf n;
		nMech::nMath::vectorf origin;
	};

	struct coord_plane : plane {
		nMech::nMath::vectorf axes[2];
	};
}

struct prim_inters {
	prim_inters() { minPtDist2=0.0f; }
	nMech::nMath::vectorf pt[2];
	nMech::nMath::vectorf n;
	unsigned char iFeature[2][2];
	float minPtDist2;
	short id[2];
	int iNode[2];
	nMech::nMath::vectorf *ptborder;
	int nborderpt,nbordersz;
	nMech::nMath::vectorf ptbest;
	int nBestPtVal;
};

struct contact {
	nMech::real t,taux;
	nMech::nMath::vectorf pt;
	nMech::nMath::vectorf n;
	unsigned int iFeature[2];
};

const int NPRIMS = 8;

///////////////////// geometry contact structures ///////////////////

struct geom_contact_area {
	enum entype { polygon,polyline };
	int type;
	int npt;
	int nmaxpt;
	float minedge;
	int *piPrim[2];
	int *piFeature[2];
	nMech::nMath::vectorf *pt;
	nMech::nMath::vectorf n1; // normal of other object surface (or edge)
};

struct geom_contact {
	nMech::real t;
	nMech::nMath::vectorf pt;
	nMech::nMath::vectorf n;
	nMech::nMath::vectorf dir; // unprojection direction
	int iUnprojMode;
	float vel; // original velocity along this direction, <0 if least squares normal was used
	int id[2]; // external ids for colliding geometry parts
	int iPrim[2];
	int iFeature[2];
	int iNode[2]; // BV-tree nodes of contacting primitives
	nMech::nMath::vectorf *ptborder; // intersection border
	int nborderpt;
	nMech::nMath::vectorf center;
	bool bBorderConsecutive;
	geom_contact_area *parea;
};

#endif