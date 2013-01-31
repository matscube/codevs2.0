#include "codevs.h"
#include "pack.h"
#include "field.h"

Pack::Pack(){}

Pack::Pack(int w, int h, int t, int s, int n)
	: W(w), H(h), T(t), S(s), N(n){
		Hf = H + T;
}

//���̃p�b�N��ǂݍ���
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

//�p���[���[�^��ǂݍ���
bool Pack::set_parameter(){
	cin >> T >> S >> N;

	return 1;
}

//�p�b�N���v�����g
bool Pack::print(){
	for(int i = 0; i < T; i++){
		for(int j = 0; j < T; j++){
			cout << pack[i][j] << (j == T-1 ? "\n" : " ");
		}
	}

	return 1;
}

//���[
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

//�E�[
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

//��]������
bool Pack::turn(int t){
	int a[5][5];

	//��]�p��pack���R�s�[
	for(int i = 0; i < T; i++){
		for(int j = 0; j < T; j++){
			a[i][j] = pack_next[i][j];
		}
	}

	//��]
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
		turn(r); //r*pi/4������]
		int Le = left(), Ri = right(); //���[�ƉE�[
		//�ʒuX
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