#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <iostream>
#include "../include/koma.hpp"
#include "../include/prot.hpp"

const int IMAGE_SIDE = 45;
Fl_Box *visual_ban[9][9];
Koma *main_ban[9][9];
Fl_PNG_Image *images[17];

int main(int argc, char **argv){

	fl_register_images();
	Fl_Window win(710, 800, "Coyuri");

      for(int y = 1;y < 10;y++){
		for(int x = 1;x < 10;x++){
			/*
			 *visual_banのためのboxを確保
			 */
			Fl_Box *fl_box = new Fl_Box(x*IMAGE_SIDE, y*IMAGE_SIDE, x*IMAGE_SIDE+70, y*IMAGE_SIDE+70);
			/*
			 *画像は最初何も入れない
			 */
			fl_box->image(NULL);
			/*
			 *裏で動く盤面変数もすべてNULLで初期化
			 */
			main_ban[x-1][y-1]   = NULL;
			/*
			 *visual_banにNULLの画像が入ったboxを代入していく
			 */
			visual_ban[x-1][y-1] = fl_box;
		}
	}

	/*
	 *入力ホームと実行ボタン
	 */
	Fl_Input *input = new Fl_Input(250, 740, 70, 30, "手:");
	Fl_Button *button = new Fl_Button(350, 730, 50, 50, "打つ");

	void* v[] = {input};
	button->callback(draw_koma, v);
	init();
	win.end();
	win.show(argc, argv);

	return Fl::run();
}


/*
 *駒を描画する関数
 */
void draw_koma(Fl_Widget* widget, void *v){
	std::string input = ((Fl_Input*)((void**)v)[0])->value();
	int x, y;
	x = ctoi(input.c_str()[0])-1;
	y = ctoi(input.c_str()[1])-1;
	set_and_redraw(Point(x, y), KYOUSHA);
}

/*
 *charからintへ変換
 */
int ctoi(char ch){
	if('0' <= ch && ch <= '9') return (ch-'0');
	else return -1;
}

/*
 *駒を版にセットし再描画する関数
 */
void set_and_redraw(Point p, KOMA_TYPE type){
	visual_ban[8-p.get_x()][p.get_y()]->image(images[type]);
	visual_ban[8-p.get_x()][p.get_y()]->redraw();
}