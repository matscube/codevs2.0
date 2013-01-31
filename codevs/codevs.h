#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <cfloat>
#include <map>
#include <utility>
#include <set>
#include <iostream>
#include <memory>
#include <algorithm>
#include <functional>
#include <sstream>
#include <complex>
#include <stack>
#include <queue>
#include <ctime>
#include <fstream>

using namespace std;
typedef long long LL;

#if !defined(___lord)
#define ___lord

struct Status{
	int x_min, r_min;
	int x_max, r_max;
	int x, r;
	int status, chain;
	int chain_min, chain_max;
	LL score_min, score_max;
	double density;
	Status(){
		x = -1, r = -1, status = -1;
		x_min = -1; r_min = -1;
		x_max = -1; r_max = -1;
		chain_min = -1; chain_max = -1;
		score_min = -1; score_max = -1;
		density = 0.0;
	}
};

void create_template();
#endif