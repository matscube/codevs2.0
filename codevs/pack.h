#if !defined(___pack)
#define ___pack

#include "codevs.h"
#include "field.h"

class Pack{
public:
	int W, H, T, S, N;
	int Hf;
	int pack[5][5]; //実際に落とすパック
	int pack_next[5][5]; //回転前のパック
	int X, R; //位置と回転
	queue<pair<int, int> > Q;
	string endstr;

		Pack();
		Pack(int w, int h, int t, int s, int n);

		bool set_pack_next(); //次のパックを読み込む
		bool set_parameter(); //パラメータを読み込む
		bool print(); //packをプリント

		int left(); //左端
		int right(); //右端

		bool turn(int t); //回転させる
		queue<pair<int, int> > valid_all(); //有効な手をすべて返す

		bool decide(Field F); //次の手を決める
		bool answer(); //答えを出力

};

#endif