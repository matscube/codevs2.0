#include "codevs.h"
#include "pack.h"
#include "field.h"
#include "template.h"

//連鎖数の少ないものを選ぶ
pair<int, int> more_chain(Status St){
	if(St.score_max > 1.4e8 || St.density > 75.0){
		return make_pair(St.x_max, St.r_max);
	}else{
		return make_pair(St.x_min, St.r_min);
	}

	return make_pair(0, 0);
}

//最大連鎖
pair<int, int> most_chain(Status *St){
	//例外
	if(St->x_max == -1 && St->r_max == -1){
		return make_pair(0, 0);
	}
	return make_pair(St->x_max, St->r_max);
}

pair<int, int> normal(Status St){
	//手が更新されなかった
	if(St.x == -1 && St.r == -1){
		return make_pair(0, 0);
	}

	return make_pair(St.x, St.r);
}
	
//
int match(Field *F, Status *St, pair<int, LL> *piL){
	int Hf = F->Hf, W = F->W;
	int flg = 1, cnt = 0;
	for(int i = 0; i < Hf; i++){
		for(int j = 0; j < W; j++){
			//何も置いてはいけないブロック
			if(template_field[i][j] == -2){
				if(F->field_ex[i][j] == -1) cnt++;
				else if(F->field_ex[i][j] != 0) flg = 0;
			//なんでもいいブロック
			}else if(template_field[i][j] == 0){
				
			}else if(template_field[i][j] == -3){
				if(F->field_ex[i][j] != 0) flg = 0; //発火点に余計なブロックがある
			//指定のあるブロック
			}else{
				if(F->field_ex[i][j] == template_field[i][j]) cnt++;
				else if(F->field_ex[i][j] == 0) continue;
				else flg = 0;
			}
		}
	}

	int grad = 4;
	int a = 0, b = 1, c = 2, d = 3;
	if(abs(F->height(a) - F->height(b)) > grad) return 0;
	if(abs(F->height(a) - F->height(c)) > grad) return 0;
	if(abs(F->height(a) - F->height(d)) > grad) return 0;
	if(abs(F->height(b) - F->height(c)) > grad) return 0;
	if(abs(F->height(b) - F->height(d)) > grad) return 0;
	if(abs(F->height(c) - F->height(d)) > grad) return 0;

	//マッチングを壊さない場合
	if(flg){
		//マッチングが増える場合に更新
		if(St->status < cnt || St->status == -1){
			St->status = cnt; St->chain = piL->first;
			return 2;
		}
		//マッチングが増えなくても、連鎖が増えれば更新
		if(St->status == cnt && St->chain < piL->first){
			St->chain = piL->first;
			return 1;
		}
	}

	//たくさん発火できた場合
	if(piL->first >= 28){
		St->chain = piL->first; St->status = 1<<29;
		return 2;
	}

	return 0;
}


bool Pack::decide(Field F){
	X = 0; R = 0;
	
	if(F.game_over == 1){
		Q.push(make_pair(X, R));
		return 0;
	}

	Status status;
	status.density = F.density();

	queue<pair<int, int> > que = valid_all();
	while(!que.empty()){
		//------------------------------
		//すべての手を調べる
		pair<int, int> pii = que.front(); que.pop();
		turn(pii.second);
		F.create_field_ex();
		F.down_pack(pack, pii.first);
		pair<int, LL> piL = F.chain();

		//------------------------------
		//ゲームオーバーをスルー
		if(F.check_over() == 1) continue;

		//------------------------------
		//評価
		if(match(&F, &status, &piL)){
			status.x = pii.first;
			status.r = pii.second;
		}

		//------------------------------
		//ステータスの最大・最小を保存
		if(status.chain_max < piL.first){
			status.chain_max = piL.first;
			status.score_max = piL.second;
			status.x_max = pii.first;
			status.r_max = pii.second;
		}

		if(status.chain_min == -1 || status.chain_min > piL.first){
			status.chain_min = piL.first;
			status.score_min = piL.second;
			status.x_min = pii.first;
			status.r_min = pii.second;
		}
	}

	//ステータスから手を選ぶ
	pair<int, int> pii = normal(status);
//	pair<int, int> pii = more_chain(status);
	X = pii.first; R = pii.second;
	turn(R);
	Q.push(make_pair(X, R));

	return 1;
}

//=============================================================================
//テンプレートの作成
void create_template_steps(){
	//limited small
	int a[2][5] = {{1, 2, 3, 4, 5}, {9, 8, 7, 6, 5}};
	ofstream clear("template.txt", ios::trunc);
	ofstream ofs("template.txt", ios::app);
	Field F("small");

	int turn = 0, cnt = 0;
	for(int i = 0; i < (1<<4) + (4<<4); i++){
		vector<int> v;
		int dif = 0;
		for(int j = 0; j < 4; j++){
			if(j == (i&(1<<4))) dif++;
			v.push_back(a[(i&(1<<j))>>j][j+dif]);
		}

		sort(v.begin(), v.end());
		do{
			turn++; cout << turn << endl;
			F.clear_field_ex();
			int a[9] = {0, v[0], v[1], v[2], v[3]};
			for(int j = 1; j <= 4; j++) a[4+j] = F.S - a[j];
			
			F.field_ex[F.Hf-1][0] = a[1];
			F.field_ex[F.Hf-1][1] = a[2];
			F.field_ex[F.Hf-1][2] = a[3];
			F.field_ex[F.Hf-1][3] = a[5];
			F.field_ex[F.Hf-1][4] = -1;

			F.field_ex[F.Hf-2][0] = a[8];
			F.field_ex[F.Hf-2][1] = a[7];
			F.field_ex[F.Hf-2][2] = a[6];
			F.field_ex[F.Hf-2][3] = a[4];
			F.field_ex[F.Hf-2][4] = -1;

			F.field_ex[F.Hf-3][0] = -1;
			F.field_ex[F.Hf-3][1] = a[5];
			F.field_ex[F.Hf-3][2] = a[3];
			F.field_ex[F.Hf-3][3] = a[2];
			F.field_ex[F.Hf-3][4] = a[1];

			F.field_ex[F.Hf-4][0] = -1;
			F.field_ex[F.Hf-4][1] = a[4];
			F.field_ex[F.Hf-4][2] = a[6];
			F.field_ex[F.Hf-4][3] = a[7];
			F.field_ex[F.Hf-4][4] = a[8];

			for(int j = 1; j <= 3; j++){
				for(int k = 0; k < 5; k++){
					for(int m = 0; m < 4; m++){
						F.field_ex[F.Hf-1-m-j*4][0+k] = F.field_ex[F.Hf-1-m][0+k];
					}
				}
			}
			int temp = F.chain().first;
			printf("chain : %d\n", temp);
			if(temp == 0) cnt++;

		}while(next_permutation(v.begin(), v.end()));
	ofs << v[0] << v[1] << v[2] << v[3] << endl;
	}
	F.print_ex();
	cout << cnt << endl;
}


void create_template_special(){
	//limited small
	int a[2][5] = {{1, 2, 3, 4, 5}, {9, 8, 7, 6, 5}};
	ofstream clear("template.txt", ios::trunc);
	ofstream ofs("template.txt", ios::app);
	Field F("small");
	int b[4][2];
	vector<vector<int> > vv;

	int turn = 0, cnt = 0;
	for(int i = 0; i < (1<<4) + (4<<4); i++){
		vector<int> v;
		int dif = 0;
		for(int j = 0; j < 4; j++){
			if(j == (i&(1<<4))) dif++;
			v.push_back(a[(i&(1<<j))>>j][j+dif]);
		}

		sort(v.begin(), v.end());
		do{
			int flg = 0;
			b[2][0] = v[0]; b[0][1] = F.S - v[0];
			b[3][0] = v[1]; b[1][1] = F.S - v[1];
			b[2][1] = v[2]; b[0][0] = F.S - v[2];
			b[3][1] = v[3]; b[1][0] = F.S - v[3];

			for(int j = 0; j < 4; j++){
				int k = j, sum = 0;
				//縦の和がない
				while(k < 4 && sum < F.S){
					sum += b[k][0]; k++;
					if(sum == F.S) flg = 1;
				}
				k = j, sum = 0;
				while(k < 4 && sum < F.S){
					sum += b[k][1]; k++;
					if(sum == F.S) flg = 1;
				}

				//横の和がない
				if(b[j][0] + b[j][1] == F.S) flg = 1;
	
				//斜めの和がない
				if(j != 3){
					if(b[j][0] + b[j+1][1] == F.S) flg = 1;
					if(b[j][1] + b[j+1][0] == F.S) flg = 1;
				}

				//飛びの和がない
				sum = 0;
				for(int k = 0; k < 4; k++){
					if(k != j) sum += b[k][0];
					if(sum == F.S) flg = 1;
				}

				sum = 0;
				for(int k = 0; k < 4; k++){
					if(k != j) sum += b[k][1];
					if(sum == F.S) flg = 1;
				}


			}

			if(flg == 0){
				for(int j = 0; j < 4; j++){
					ofs << b[j][0] << b[j][1] << "\n";
				}
				ofs << "\n";
				vv.push_back(v);
			}
		}while(next_permutation(v.begin(), v.end()));
	}

	//それぞれのブロックの組み合わせを返す
	ofstream clear2("template2.txt", ios::trunc);
	ofstream ofs2("template2.txt", ios::app);
	int sz = vv.size(), Hf = F.Hf, W = F.W, S = F.S;
	turn = 0;
	for(int i = 0; i < sz; i++){
		for(int j = 0; j < sz; j++){
			if(i == j) continue;
			turn++;

			F.field_ex[Hf-2][0] = vv[i][0]; F.field_ex[Hf-4][1] = S-vv[i][0];
			F.field_ex[Hf-1][0] = vv[i][1]; F.field_ex[Hf-3][1] = S-vv[i][1];
			F.field_ex[Hf-2][1] = vv[i][2]; F.field_ex[Hf-4][0] = S-vv[i][2];
			F.field_ex[Hf-1][1] = vv[i][3]; F.field_ex[Hf-3][0] = S-vv[i][3];

			F.field_ex[Hf-2][2] = vv[j][0]; F.field_ex[Hf-4][3] = S-vv[j][0];
			F.field_ex[Hf-1][2] = vv[j][1]; F.field_ex[Hf-3][3] = S-vv[j][1];
			F.field_ex[Hf-2][3] = vv[j][2]; F.field_ex[Hf-4][2] = S-vv[j][2];
			F.field_ex[Hf-1][3] = vv[j][3]; F.field_ex[Hf-3][2] = S-vv[j][3];
	
			for(int k = 1; k <= 3; k++){
				for(int L = 0; L < 4; L++){
					for(int m = 0; m < 4; m++){
						F.field_ex[Hf-1-4*k-L][m] = F.field_ex[Hf-1-L][m];
					}
				}
			}

			F.field_ex[Hf-1][2] = -1; F.field_ex[Hf-1][3] = -1; //台
			F.field_ex[4][0] = S - F.field_ex[5][1]; //発火点
			if(0 >= (F.field_ex[Hf-2][1] = S - F.field_ex[Hf-2][2] - F.field_ex[Hf-3][3])) continue;
			F.copy_field_ex(); //チェイン前の盤面を実フィールドにコピー

			int temp = F.chain().first;
			if(temp > 20){
				cout << temp << endl;
				F.output();
			}
		}
	}

	printf("Finished\n");
}

//実験フィールドをコードに埋め込める形で出力
void create_template_matrix(){
	Field F("small");
	F.input();
	F.create_field_ex();

	ofstream clear("template.txt", ios::trunc);
	ofstream ofs("template.txt", ios::app);

	for(int i = 0; i < F.Hf; i++){
		ofs << "{";
		for(int j = 0; j < F.W; j++){
			ofs << F.field_ex[i][j] << (j == F.W - 1 ? "}" : ", ");
		}
		ofs << (i == F.Hf - 1 ? "" : ",\n");
	}

	printf("Finished! \"template.txt\" was overwrited...\n");
}

//作成したいテンプレートを指定して実行
void create_template(){
//	create_template_steps();
//	create_template_special();
	create_template_matrix();
}