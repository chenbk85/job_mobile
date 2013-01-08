// NRadnom.h : Defines the  PRNG Function Object for random_shuffle

#ifndef __NEORAND_H__
#define __NEORAND_H__


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
