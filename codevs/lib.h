#if !defined(___lib)
#define ___lib

#include "codevs.h"

//pair‚Ì‘å¬ŠÖŒWAfirst:less, second:less
struct pair_first_greater{
	bool operator() (const pair<int, int>& x, pair<int, int>& y) const {
		if(x.first == y.first) return x.second > y.second;
		return x.first > y.first;
	}
};

#endif