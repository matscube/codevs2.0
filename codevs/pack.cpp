#include "codevs.h"
#include "pack.h"
#include "field.h"

Pack::Pack(){}

Pack::Pack(int w, int h, int t, int s, int n)
	: W(w), H(h), T(t), S(s), N(n){
		Hf = H + T;
}

//次のパックを読み込む
bool Pack::set_pack_next(){
	for(int i = 0; i < T; i++){
		for(int j = 0; j < T; j++){
			cin >> pack[i][j];
			if(pack[i][j] > S) pack[i][j] = -1;
			pack_next[i][j] = pack[i][j];
		}
	}
	cin >> endstr;

	return 1;
}

//パラーメータを読み込む
bool Pack::set_parameter(){
	cin >> T >> S >> N;

	return 1;
}

//パックをプリント
bool Pack::print(){
	for(int i = 0; i < T; i++){
		for(int j = 0; j < T; j++){
			cout << pack[i][j] << (j == T-1 ? "\n" : " ");
		}
	}

	return 1;
}

//左端
int Pack::left(){
	int left = 0;
	for(int i = 0; i < T; i++){
		for(int j = 0; j < T; j++){
			if(pack[j][i] != 0) goto end;
			if(j == T-1) left = i;
		}
	}
end:;

	return left;
}

//右端
int Pack::right(){
	int right = T-1;
	for(int i = T-1; i >= 0; i--){
		for(int j = 0; j < T; j++){
			if(pack[j][i] != 0) goto end;
			if(j == T-1) right = i;
		}
	}
end:;

	return right;
}

//回転させる
bool Pack::turn(int t){
	int a[5][5];

	//回転用のpackをコピー
	for(int i = 0; i < T; i++){
		for(int j = 0; j < T; j++){
			a[i][j] = pack_next[i][j];
		}
	}

	//回転
	for(int i = 0; i < t; i++){
		for(int j = 0; j < T/2; j++)
			for(int k = 0; k < T; k++) pack[j][k] = a[T-1-k][j];
		for(int j = T/2; j < T; j++)
			for(int k = 0; k < T; k++) pack[j][k] = a[T-1-k][j];
		for(int j = 0; j < T; j++)
			for(int k = 0; k < T; k++) a[j][k] = pack[j][k];
	}

	for(int i = 0; i < T; i++){
		for(int j = 0; j < T; j++){
			pack[i][j] = a[i][j];
		}
	}

	return 1;
}

queue<pair<int, int> > Pack::valid_all(){
	queue<pair<int, int> > res;

	for(int r = 0; r < 4; r++){
		turn(r); //r*pi/4だけ回転
		int Le = left(), Ri = right(); //左端と右端
		//位置X
		for(int j = -Le; j < W-Ri; j++){
			res.push(make_pair(j, r));
		}
	}

	return res;
}

bool Pack::answer(){
	while(!Q.empty()){
		pair<int, int> p = Q.front(); Q.pop();
		printf("%d %d\n", p.first, p.second);
	}

	return 1;
}