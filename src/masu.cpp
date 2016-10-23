#include "../include/type.hpp"
#include "../include/prot.hpp"
#include "../include/value.hpp"
#include <iostream>
#include <cmath>

Masu::Masu(int x, int y, int width, int height) : Fl_Box(x, y, width, height, 0){
	X = x;
	Y = y;
}

int Masu::handle(int event){
	if(event == FL_RELEASE){
		int x = (X/70) - 1, y = (Y/70) - 1;
		std::cout << "KOMA_TYPE" << main_ban[x][y] << std::endl;
		if(target_ban[x][y]->image() == images[TARGET]){
			std::cout << "MOVE_IF_IN\n";
			move(Point(std::abs(x-9), y+1));
			target_clear();
			/*
			 *AIのターン
			 */
			BANMEN *banmen = new BANMEN;

			for(int x = 0;x < 9;x++)
				for(int y = 0;y < 9;y++)
					banmen->set_type(x, y, main_ban[x][y]);

			Node *root = new Node(banmen, NULL);

			ai_turn(root);
			destroy_tree(root);
			return 0;
		}
		target_clear();
		TARGET_KOMA.set_x(x);
		TARGET_KOMA.set_y(y);
		std::cout << "masu_cpp 25 " << x << ":" << y << std::endl;
		std::cout << "EVENT!!!!\n";
		for(Point point : wcm_ftable[main_ban[x][y]](Point(std::abs(x-9), y+1))){
			target_masu(point);
		}

	}

	return 1;
}
