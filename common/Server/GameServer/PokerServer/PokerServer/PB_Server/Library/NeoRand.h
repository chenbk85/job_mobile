// NRadnom.h : Defines the  PRNG Function Object for random_shuffle

#ifndef __NEORAND_H__
#define __NEORAND_H__

#include "config_all_server.h"

class NeoRand 
{
public:
	NeoRand();
	ptrdiff_t operator() (ptrdiff_t max);
		
protected:
	static long			_pool[3];	// entropy pool
	static unsigned int	_nIndex ;	// entropy pool chooser 0, 1, 2
};

#endif 
