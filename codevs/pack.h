#if !defined(___pack)
#define ___pack

#include "codevs.h"
#include "field.h"

class Pack{
public:
	int W, H, T, S, N;
	int Hf;
	int pack[5][5]; //���ۂɗ��Ƃ��p�b�N
	int pack_next[5][5]; //��]�O�̃p�b�N
	int X, R; //�ʒu�Ɖ�]
	queue<pair<int, int> > Q;
	string endstr;

		Pack();
		Pack(int w, int h, int t, int s, int n);

		bool set_pack_next(); //���̃p�b�N��ǂݍ���
		bool set_parameter(); //�p�����[�^��ǂݍ���
		bool print(); //pack���v�����g

		int left(); //���[
		int right(); //�E�[

		bool turn(int t); //��]������
		queue<pair<int, int> > valid_all(); //�L���Ȏ�����ׂĕԂ�

		bool decide(Field F); //���̎�����߂�
		bool answer(); //�������o��

};

#endif