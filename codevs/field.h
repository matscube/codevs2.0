#if !defined(___field)
#define ___field

#include "codevs.h"

class Field{
public:
	int W, H, T, S, N;
	int _P, _A, _B_obs;
	int turn; //���݂̎萔
	int Hf;
	int field[36+5][20], field_ex[36+5][20];
	int pack[5][5];
	int chain_max;
	int game_over;
	LL score_sum;
	string endstr;

		Field();
		Field(string s);
		Field(int w, int h, int t, int s, int n);

		bool input(); //�e�L�X�g�t�@�C������t�B�[���h��ǂݍ���
		bool set_parameter(); //�p�����[�^��ǂݍ���

		bool print(); //�t�B�[���h���R���\�[���ɕ\������
		bool print_ex(); //
		bool output(); //�e�L�X�g�t�@�C���ɏo��
		bool output_ex();

		//�����t�B�[���h�𑀍삷��֐��Q
		bool delete_block(pair<int, int> p); //�����t�B�[���h�u���b�N������
		bool clear_field_ex(); //�����t�B�[���h��������������������������������
		bool down_pack(int pack[5][5], int x); //�p�b�N�𗎂Ƃ�
		bool create_field_ex(); //�����t�B�[���h���쐬
		bool copy_field_ex(); //�����t�B�[���h�����t�B�[���h�ɃR�s�[

		pair<int, LL> chain(); //�`�F�C�������āA�`�F�C�����Ɗl���X�R�A��Ԃ�
		bool update(int pack[5][5], int x); //�t�B�[���h�Ɏ��ۂɗ��Ƃ��ĘA��������

		bool check_over(); //�Q�[���I�[�o���`�F�b�N

		double density(); //�t�B�[���h�̖��x
		int height(int x); //�ʒux�̍���
};

#endif