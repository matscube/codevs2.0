#include "codevs.h"
#include "field.h"
#include "pack.h"

int main(){
//	create_template();

	int w, h, t, s, n;
	cin >> w >> h >> t >> s >> n;
//	w = 10; h = 16; t = 4; s = 10; n = 1000;
//  w = 20; h = 36; t = 5; s = 30; n = 1000;
	Field F(w, h, t, s, n);
	Pack P(w, h, t, s, n);
#if 0
	F.input();
	F.create_field_ex();
	F.print_ex();
	cout << F.chain().first << endl;
	F.print_ex();
#endif
	for(int i = 0; i < n; i++){
		P.set_pack_next();

		//ゲームオーバーしても出力は行う
		if(P.decide(F) == 1){
			if(F.update(P.pack, P.X) == 0){
				F.game_over = 1;
			}else{
				F.turn++;
			}
		}
	}
	P.answer();

	F.print();
	cout << F.turn << endl;
	cout << F.score_sum << endl;
	cout << F.chain_max << endl;
	return 0;
}