#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <iostream>
#include "../include/koma.hpp"
#include "../include/prot.hpp"

const int IMAGE_SIDE = 45;
Fl_Box *ban[9][9];
Fl_PNG_Image *images[17];

int main(int argc, char **argv){

	fl_register_images();
	Fl_Window win(610, 700, "Coyuri");

      for(int y = 0;y < 9;y++){
		for(int x = 0;x < 9;x++){
			Fl_Box *fl_box = new Fl_Box(x*IMAGE_SIDE, y*IMAGE_SIDE, x*IMAGE_SIDE+70, y*IMAGE_SIDE+70);
			fl_box->image(NULL);
			ban[x][y] = fl_box;
		}
	}

	Fl_Input *input = new Fl_Input(200, 640, 70, 30, "手:");
	Fl_Button *button = new Fl_Button(300, 630, 50, 50, "打つ");

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
	x = ctoi(input.c_str()[0]);
	y = ctoi(input.c_str()[1]);
	ban[x-1][y-1]->image(new Fl_PNG_Image("/home/takai/Pictures/coyuri/kyousha.png"));
	ban[x-1][y-1]->redraw();
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
void set_and_redraw(Point p, Fl_PNG_Image *image){
	ban[p.get_x()][p.get_y()]->image(image);
	ban[p.get_x()][p.get_y()]->redraw();
}
