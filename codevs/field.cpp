#include "codevs.h"
#include "field.h"
#include "lib.h"
#include "pack.h"

Field::Field(){}

Field::Field(string s){
	if(s == "small"){
		W = 10; H = 16; T = 4; S = 10; N = 1000;
		_P = 25; _A = 150; _B_obs = 50;
	}else if(s == "medium"){
		W = 15; H = 23; T = 4; S = 20; N = 1000;
		_P = 30; _A = 80; _B_obs = 150;
	}else if(s == "large"){
		W = 20; H = 36; T = 5; S = 30; N = 1000;
		_P = 35; _A = 90; _B_obs = 360;
	}else{
		cout << "s's format is missmatch" << endl;
	}
	Hf = H + T;
	score_sum = 0; chain_max = 0;
	turn = 1; game_over = 0;
	for(int i = 0; i < Hf; i++){
		for(int j = 0; j < W; j++){
			field[i][j] = field_ex[i][j] = 0;
		}
	}
}

Field::Field(int w, int h, int t, int s, int n)
	:W(w), H(h), T(t), S(s), N(n){
		Hf = H + T;
		score_sum = 0;
		chain_max = 0;
		turn = 1;
		game_over = 0;

		//�t�B�[���h������
		for(int i = 0; i < Hf; i++){
			for(int j = 0; j < W; j++){
				field[i][j] = field_ex[i][j] = 0;
			}
		}

		//�����p���[���[�^�̐ݒ�
		switch(W){
		case 10:{
			_P = 25; _A = 150; _B_obs = 50;
				}
		case 15:{
			_P = 30; _A = 80; _B_obs = 150;
				}
		case 20:{
			_P = 35; _A = 90; _B_obs = 360;
				}
		}
}

//�e�L�X�g�t�@�C������t�B�[���h��ǂݍ���
bool Field::input(){
	ifstream ifs("field.txt");
	for(int i = 0; i < Hf; i++){
		for(int j = 0; j < W; j++){
			int temp; ifs >> temp;
			field[i][j] = (temp > S ? -1 : temp);
		}
	}

	return 1;
}

//�p�����[�^��ǂݍ���
bool Field::set_parameter(){
	cin >> W >> H >> T >> S >> N;

	return 1;
}

//�t�B�[���h���R���\�[���ɓǂݍ���
bool Field::print(){
	for(int i = 0; i < Hf; i++){
		for(int j = 0; j < W; j++){
			cout << field[i][j] << (j < W-1 ? " " : "\n");
		}
	}

	return 1;
}

//
bool Field::print_ex(){
	for(int i = 0; i < Hf; i++){
		for(int j = 0; j < W; j++){
			cout << field_ex[i][j] << (j < W-1 ? " " : "\n");
		}
	}

	return 1;
}

//�e�L�X�g�t�@�C���ɓǂݍ���
bool Field::output(){
	ofstream ofs("output.txt", ios::trunc);
	for(int i = 0; i < Hf; i++){
		for(int j = 0; j < W; j++){
			ofs << field[i][j] << (j < W-1 ? "\t" : "\n");
		}
	}

	return 1;
}

//�e�L�X�g�t�@�C���ɓǂݍ���
bool Field::output_ex(){
	ofstream ofs("output.txt", ios::trunc);
	for(int i = 0; i < Hf; i++){
		for(int j = 0; j < W; j++){
			ofs << field_ex[i][j] << (j < W-1 ? "\t" : "\n");
		}
	}

	return 1;
}

//�u���b�N������
bool Field::delete_block(pair<int, int> p){
	int mh = 0; //�u���b�N���ςݏオ���Ă���ő�̍���
	for(int i = p.first-1; i >= 0; i--){
		if(field_ex[i][p.second] == 0){
			mh = i+1;
			break;
		}
	}

	//�u���b�N�����炷
	for(int i = p.first; i >= mh; i--){
		if(i == 0) field_ex[i][p.second] = 0;
		else field_ex[i][p.second] = field_ex[i-1][p.second];
	}

	return 1;
}

//�����t�B�[���h���N���A����
bool Field::clear_field_ex(){
	for(int i = 0; i < Hf; i++){
		for(int j = 0; j < W; j++){
			field_ex[i][j] = 0;
		}
	}

	return 1;
}

//�p�b�N�𗎂Ƃ�
bool Field::down_pack(int pack[5][5], int x){
	for(int j = 0; j < T; j++){
		for(int i = T-1; i >= 0; i--){
			if(pack[i][j] != 0){
				if(x+j < 0 || x+j >= W) return 0; //�t�B�[���h�O�ɗ��Ƃ���
				for(int k = 0; k < Hf; k++){
					if(field_ex[k][x+j] != 0){
						field_ex[k-1][x+j] = pack[i][j];
						break;
					}
					if(k == Hf-1) field_ex[k][x+j] = pack[i][j];
				}
			}
		}
	}

	return 1; //���܂����Ƃ���
}

//�����t�B�[���h���쐬
bool Field::create_field_ex(){
	for(int i = 0; i < Hf; i++){
		for(int j = 0; j < W; j++){
			field_ex[i][j] = field[i][j];
		}
	}

	return 1;
}

//�����t�B�[���h�����t�B�[���ɃR�s�[
bool Field::copy_field_ex(){
	for(int i = 0; i < Hf; i++){
		for(int j = 0; j < W; j++){
			field[i][j] = field_ex[i][j];
		}
	}

	return 1;
}

//�`�F�C�������āA�`�F�C�����Ɗl���X�R�A��Ԃ�
pair<int, LL> Field::chain(){
	int chain = 0;
	LL score = 0;
	priority_queue<pair<int, int>, vector<pair<int, int> >, pair_first_greater > prqp; //�A���ŏ�����u���b�N�̍��W
	while(1){

		//�P��
		for(int i = 0; i < Hf; i++)
			for(int j = 0; j < W; j++)
				if(field_ex[i][j] == S) prqp.push(make_pair(i, j));

		//�c
		for(int j = 0; j < W; j++){
			for(int i = 0; i < Hf; i++){
				int cnt = 0;
				for(int k = i; k < Hf; k++){
					if(field_ex[k][j] == 0 || field_ex[k][j] == -1) break;
					cnt += field_ex[k][j];
					//�P�Ƃ͐����Ȃ�
					if(k > i && cnt == S){
						for(int l = i; l <= k; l++){
							prqp.push(make_pair(l, j));
						}
						break;
					}else if(cnt > S) break;
				}
			}
		}

		//��
		for(int i = 0; i < Hf; i++){
			for(int j = 0; j < W; j++){
				int cnt = 0;
				for(int k = j; k < W; k++){
					if(field_ex[i][k] == 0 || field_ex[i][k] == -1) break;
					cnt += field_ex[i][k];
					//�P�Ƃ͐����Ȃ�
					if(k > j && cnt == S){
						for(int l = j; l <= k; l++){
							prqp.push(make_pair(i, l));
						}
						break;
					}else if(cnt > S) break;
				}
			}
		}

		//�ȂȂ�
		for(int i = 0; i < Hf; i++){
			for(int j = 0; j < W; j++){
				//�E�����
				int cnt= 0;
				for(int k = i, l = j; k >= 0 && l < W; k--, l++){
					if(field_ex[k][l] == 0 || field_ex[k][l] == -1) break;
					cnt += field_ex[k][l];
					if(k < i && cnt == S){
						for(int m = i, n = j; m >= k && n <= l; m--, n++){
							prqp.push(make_pair(m, n));
						}
						break;
					}else if(cnt > S) break;
				}

				//�������
				cnt= 0;
// l < W 
				for(int k = i, l = j; k >= 0 && l >= 0; k--, l--){
					if(field_ex[k][l] == 0 || field_ex[k][l] == -1) break;
					cnt += field_ex[k][l];
					if(k < i && cnt == S){
						for(int m = i, n = j; m >= k && n >= l; m--, n--){
							prqp.push(make_pair(m, n));
						}
						break;
					}else if(cnt > S) break;
				}
			}
		}

		if(prqp.empty()) break;
		else chain++;

		int cnt = 0; //�������u���b�N�̐�
		while(!prqp.empty()){
			cnt++;
			pair<int, int> p = prqp.top(); prqp.pop();
			while(!prqp.empty() && p == prqp.top()) prqp.pop(), cnt++;
			delete_block(p);
		}

		//�X�R�A�v�Z
		int c = min(chain, _P+turn/100) - 1;
		LL s = max(1, chain-(_P+turn/100)+1)*cnt;
		while(c-- > 0) s *= 2;
		score += s;
		
	}

	return make_pair(chain, score);
}

//�t�B�[���h�Ɏ��ۂɗ��Ƃ��ĘA��������
bool Field::update(int pack[5][5], int x){
	create_field_ex();
	down_pack(pack, x);

	pair<int, LL> p = chain();
	copy_field_ex();

	if(check_over()) return 0; //�Q�[���I�[�o�[
	score_sum += p.second;
	ofstream ofs("temp.txt", ios::app);
	ofs << turn+1 << " " << score_sum << endl;
	chain_max = max(chain_max, p.first);

	return 1;
}

//�Q�[���I�[�o���`�F�b�N
bool Field::check_over(){
	for(int i = 0; i < T; i++){
		for(int j = 0; j < W; j++){
			if(field_ex[i][j] != 0) return 1;
		}
	}

	return 0;
}

//�t�B�[���h�̖��x
double Field::density(){
	int cnt = 0;
	for(int i = T; i < Hf; i++){
		for(int j = 0; j < W; j++){
			if(field_ex[i][j] != 0) cnt++;
		}
	}

	return double(H*W)/double(cnt);
}

//�ʒux�̍���
int Field::height(int x){
	int h = Hf;
	while(h-1 >= 0 && field_ex[h-1][x] != 0) h--;
	
	return Hf-h;
}