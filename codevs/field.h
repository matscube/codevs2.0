#if !defined(___field)
#define ___field

#include "codevs.h"

class Field{
public:
	int W, H, T, S, N;
	int _P, _A, _B_obs;
	int turn; //現在の手数
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

		bool input(); //テキストファイルからフィールドを読み込む
		bool set_parameter(); //パラメータを読み込む

		bool print(); //フィールドをコンソールに表示する
		bool print_ex(); //
		bool output(); //テキストファイルに出力
		bool output_ex();

		//実験フィールドを操作する関数群
		bool delete_block(pair<int, int> p); //実験フィールドブロックを消す
		bool clear_field_ex(); //実験フィールドをおそうじおそうじルンルンルン♪
		bool down_pack(int pack[5][5], int x); //パックを落とす
		bool create_field_ex(); //実験フィールドを作成
		bool copy_field_ex(); //実験フィールドを実フィールドにコピー

		pair<int, LL> chain(); //チェインさせて、チェイン数と獲得スコアを返す
		bool update(int pack[5][5], int x); //フィールドに実際に落として連鎖させる

		bool check_over(); //ゲームオーバをチェック

		double density(); //フィールドの密度
		int height(int x); //位置xの高さ
};

#endif