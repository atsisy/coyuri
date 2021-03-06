#include "../include/prot.hpp"
#include "../include/value.hpp"
#include <iostream>
#include <cmath>

/*
 *wcm関数内では通常の将棋の盤面を操作する感じで行う
 */

//何もしないwcm関数
std::vector<Point> null_wcm(Point p){
	std::vector<Point> points;
	return points;
}

//歩のwcm関数
std::vector<Point> hu_wcm(Point point){
	std::vector<Point> points;

	/*
	 *一つ前方を確認
	 */
	jands_one_wcm(point.get_x(), point.get_y()-1, &points);

	return points;
}

std::vector<Point> kyousha_wcm(Point point){
	std::vector<Point> points;
	int y = point.get_y()-1;
	while(jands_one_wcm(point.get_x(), y, &points)){
		y--;
	}
	return points;
}

//桂馬のwcm関数
std::vector<Point> keima_wcm(Point p){
	std::vector<Point> points;

	/*
	 *２つ前に進めない位置にいる場合移動できない
	 */
	if(p.get_y() <= 2) return points;

	if(can_target(p.get_x() + 1, p.get_y() - 2))
		points.push_back(Point(p.get_x() + 1, p.get_y() - 2));

	if(can_target(p.get_x() - 1, p.get_y() - 2))
		points.push_back(Point(p.get_x() - 1, p.get_y() - 2));

	return points;
}

//銀のwcm関数
std::vector<Point> gin_wcm(Point p){
	std::vector<Point> points;

	/*
	 *前方方向の移動可能判定
	 */
	jands_one_wcm(p.get_x()-1, p.get_y()-1, &points);
	jands_one_wcm(p.get_x(), p.get_y()-1, &points);
	jands_one_wcm(p.get_x()+1, p.get_y()-1, &points);

	/*
	 *後方方向の移動可能判定
	 */
	jands_one_wcm(p.get_x()-1, p.get_y()+1, &points);
	jands_one_wcm(p.get_x()+1, p.get_y()+1, &points);

	return points;
}

//銀のwcm関数
std::vector<Point> kin_wcm(Point p){
	std::vector<Point> points;

	/*
	 *前方方向の移動可能判定
	 */
	jands_one_wcm(p.get_x()-1, p.get_y()-1, &points);
	jands_one_wcm(p.get_x(), p.get_y()-1, &points);
	jands_one_wcm(p.get_x()+1, p.get_y()-1, &points);

	/*
	 *横方向の移動可能判定
	 */
	jands_one_wcm(p.get_x()-1, p.get_y(), &points);
	jands_one_wcm(p.get_x()+1, p.get_y(), &points);

	/*
	 *後方方向の移動可能判定
	 */
	jands_one_wcm(p.get_x(), p.get_y()+1, &points);

	return points;
}

//飛車のwcm関数
std::vector<Point> hisha_wcm(Point p){
	std::vector<Point> points;
	int x = p.get_x()-1, y;

	/*
	 *左方向の移動可能判定
	 */
	while(jands_one_wcm(x, p.get_y(), &points)){
		x--;
	}

	/*
	 *左方向の移動可能判定
	 */
	x = p.get_x()+1;
      while(jands_one_wcm(x, p.get_y(), &points)){
		x++;
	}

	/*
	 *下方向の移動可能判定
	 */
	y = p.get_y()+1;
      while(jands_one_wcm(p.get_x(), y, &points)){
		y++;
	}

	/*
	 *上方向の移動可能判定
	 */
	y = p.get_y()-1;
	while(jands_one_wcm(p.get_x(), y, &points)){
		y--;
	}

	return points;
}

//角のwcm関数
std::vector<Point> kaku_wcm(Point p){
	std::vector<Point> points;

	int x = p.get_x()-1, y = p.get_y()-1;
	/*
	 *右上方向の移動可能判定
	 */
      while(jands_one_wcm(x, y, &points)){
		x--;
		y--;
	}

	x = p.get_x()+1;
	y = p.get_y()-1;
	/*
	 *左上方向の移動可能判定
	 */
	while(jands_one_wcm(x, y, &points)){
		x++;
		y--;
	}

      x = p.get_x()-1;
	y = p.get_y()+1;
	/*
	 *右下方向の移動可能判定
	 */
	while(jands_one_wcm(x, y, &points)){
		x--;
		y++;
	}

	x = p.get_x()+1;
	y = p.get_y()+1;
	/*
	 *右下方向の移動可能判定
	 */
	while(jands_one_wcm(x, y, &points)){
		x++;
		y++;
	}

	return points;
}

//王将のwcm関数
std::vector<Point> ou_wcm(Point p){
	std::vector<Point> points;

	//前方方向の移動可能判定
	jands_one_wcm(p.get_x(), p.get_y()-1, &points);
	jands_one_wcm(p.get_x()-1, p.get_y()-1, &points);
	jands_one_wcm(p.get_x()+1, p.get_y()-1, &points);

	//横方向の移動可能判定
	jands_one_wcm(p.get_x()+1, p.get_y(), &points);
	jands_one_wcm(p.get_x()-1, p.get_y(), &points);

	//後方方向の移動可能判定
	jands_one_wcm(p.get_x(), p.get_y()+1, &points);
	jands_one_wcm(p.get_x()-1, p.get_y()+1, &points);
	jands_one_wcm(p.get_x()+1, p.get_y()+1, &points);

	return points;
}

//龍のwcm関数
std::vector<Point> ryu_wcm(Point p){
	std::vector<Point> points;
	int x = p.get_x()-1, y;

	/*
	 *左方向の移動可能判定
	 */
	while(jands_one_wcm(x, p.get_y(), &points)){
		x--;
	}

	/*
	 *左方向の移動可能判定
	 */
	x = p.get_x()+1;
      while(jands_one_wcm(x, p.get_y(), &points)){
		x++;
	}

	/*
	 *下方向の移動可能判定
	 */
	y = p.get_y()+1;
      while(jands_one_wcm(p.get_x(), y, &points)){
		y++;
	}

	/*
	 *上方向の移動可能判定
	 */
	y = p.get_y()-1;
	while(jands_one_wcm(p.get_x(), y, &points)){
		y--;
	}

	//斜め上方向の移動可能判定
	jands_one_wcm(p.get_x()-1, p.get_y()-1, &points);
	jands_one_wcm(p.get_x()+1, p.get_y()-1, &points);

	//斜め下方向の移動可能判定
	jands_one_wcm(p.get_x()-1, p.get_y()+1, &points);
	jands_one_wcm(p.get_x()+1, p.get_y()+1, &points);

	return points;
}

//馬のwcm関数
std::vector<Point> uma_wcm(Point p){
	std::vector<Point> points;

	int x = p.get_x()-1, y = p.get_y()-1;
	/*
	 *右上方向の移動可能判定
	 */
      while(jands_one_wcm(x, y, &points)){
		x--;
		y--;
	}

	x = p.get_x()+1;
	y = p.get_y()-1;
	/*
	 *左上方向の移動可能判定
	 */
	while(jands_one_wcm(x, y, &points)){
		x++;
		y--;
	}

      x = p.get_x()-1;
	y = p.get_y()+1;
	/*
	 *右下方向の移動可能判定
	 */
	while(jands_one_wcm(x, y, &points)){
		x--;
		y++;
	}

	x = p.get_x()+1;
	y = p.get_y()+1;
	/*
	 *右下方向の移動可能判定
	 */
	while(jands_one_wcm(x, y, &points)){
		x++;
		y++;
	}

	//横方向の移動可能判定
	jands_one_wcm(p.get_x()+1, p.get_y(), &points);
	jands_one_wcm(p.get_x()-1, p.get_y(), &points);

	//前方の移動可能判定
	jands_one_wcm(p.get_x(), p.get_y()-1, &points);

	//後方方向の移動可能判定
	jands_one_wcm(p.get_x(), p.get_y()+1, &points);

	return points;
}


//敵の歩のwcm関数
std::vector<Point> en_hu_wcm(Point point){
	std::vector<Point> points;

	/*
	 *一つ前方を確認
	 */
	ai_jands_one_wcm(point.get_x(), point.get_y()+1, &points);

	return points;
}

//敵の香車のwcm関数
std::vector<Point> en_kyousha_wcm(Point point){
	std::vector<Point> points;
	int y = point.get_y()+1;
	while(ai_jands_one_wcm(point.get_x(), y, &points)){
		y++;
	}
	return points;
}

//敵の桂馬のwcm関数
std::vector<Point> en_keima_wcm(Point p){
	std::vector<Point> points;

	/*
	 *２つ前に進めない位置にいる場合移動できない
	 */
	if(p.get_y() >= 8) return points;

	if(ai_can_target(p.get_x() + 1, p.get_y() + 2))
		points.push_back(Point(p.get_x() + 1, p.get_y() + 2));

	if(ai_can_target(p.get_x() - 1, p.get_y() + 2))
		points.push_back(Point(p.get_x() - 1, p.get_y() + 2));

	return points;
}

//敵の銀のwcm関数
std::vector<Point> en_gin_wcm(Point p){
	std::vector<Point> points;

	/*
	 *前方方向の移動可能判定
	 */
	ai_jands_one_wcm(p.get_x()-1, p.get_y()+1, &points);
	ai_jands_one_wcm(p.get_x(),   p.get_y()+1, &points);
	ai_jands_one_wcm(p.get_x()+1, p.get_y()+1, &points);

	/*
	 *後方方向の移動可能判定
	 */
	ai_jands_one_wcm(p.get_x()-1, p.get_y()-1, &points);
	ai_jands_one_wcm(p.get_x()+1, p.get_y()-1, &points);

	return points;
}

//敵の金のwcm関数
std::vector<Point> en_kin_wcm(Point p){
	std::vector<Point> points;

	/*
	 *前方方向の移動可能判定
	 */
	ai_jands_one_wcm(p.get_x()-1, p.get_y()+1, &points);
	ai_jands_one_wcm(p.get_x(),   p.get_y()+1, &points);
	ai_jands_one_wcm(p.get_x()+1, p.get_y()+1, &points);

	/*
	 *横方向の移動可能判定
	 */
	ai_jands_one_wcm(p.get_x()-1, p.get_y(), &points);
	ai_jands_one_wcm(p.get_x()+1, p.get_y(), &points);

	/*
	 *後方方向の移動可能判定
	 */
	ai_jands_one_wcm(p.get_x(), p.get_y()-1, &points);

	return points;
}

//敵の飛車のwcm関数
std::vector<Point> en_hisha_wcm(Point p){
	std::vector<Point> points;
	int x = p.get_x()-1, y;

	/*
	 *左方向の移動可能判定
	 */
	while(ai_jands_one_wcm(x, p.get_y(), &points)){
		x--;
	}

	/*
	 *左方向の移動可能判定
	 */
	x = p.get_x()+1;
      while(ai_jands_one_wcm(x, p.get_y(), &points)){
		x++;
	}

	/*
	 *下方向の移動可能判定
	 */
	y = p.get_y()-1;
      while(ai_jands_one_wcm(p.get_x(), y, &points)){
		y--;
	}

	/*
	 *上方向の移動可能判定
	 */
	y = p.get_y()+1;
	while(ai_jands_one_wcm(p.get_x(), y, &points)){
		y++;
	}

	return points;
}

//敵の角のwcm関数
std::vector<Point> en_kaku_wcm(Point p){
	std::vector<Point> points;

	int x = p.get_x()-1, y = p.get_y()-1;
	/*
	 *右上方向の移動可能判定
	 */
      while(ai_jands_one_wcm(x, y, &points)){
		x--;
		y--;
	}

	x = p.get_x()+1;
	y = p.get_y()-1;
	/*
	 *左上方向の移動可能判定
	 */
	while(ai_jands_one_wcm(x, y, &points)){
		x++;
		y--;
	}

      x = p.get_x()-1;
	y = p.get_y()+1;
	/*
	 *右下方向の移動可能判定
	 */
	while(ai_jands_one_wcm(x, y, &points)){
		x--;
		y++;
	}

	x = p.get_x()+1;
	y = p.get_y()+1;
	/*
	 *右下方向の移動可能判定
	 */
	while(ai_jands_one_wcm(x, y, &points)){
		x++;
		y++;
	}

	return points;
}

//敵の王将のwcm関数
std::vector<Point> en_ou_wcm(Point p){
	std::vector<Point> points;

	//前方方向の移動可能判定
	ai_jands_one_wcm(p.get_x(), p.get_y()-1, &points);
	ai_jands_one_wcm(p.get_x()-1, p.get_y()-1, &points);
	ai_jands_one_wcm(p.get_x()+1, p.get_y()-1, &points);

	//横方向の移動可能判定
	ai_jands_one_wcm(p.get_x()+1, p.get_y(), &points);
	ai_jands_one_wcm(p.get_x()-1, p.get_y(), &points);

	//後方方向の移動可能判定
	ai_jands_one_wcm(p.get_x(), p.get_y()+1, &points);
	ai_jands_one_wcm(p.get_x()-1, p.get_y()+1, &points);
	ai_jands_one_wcm(p.get_x()+1, p.get_y()+1, &points);

	return points;
}


//龍のwcm関数
std::vector<Point> en_ryu_wcm(Point p){
	std::vector<Point> points;
	int x = p.get_x()-1, y;

	/*
	 *左方向の移動可能判定
	 */
	while(jands_one_wcm(x, p.get_y(), &points)){
		x--;
	}

	/*
	 *左方向の移動可能判定
	 */
	x = p.get_x()+1;
      while(jands_one_wcm(x, p.get_y(), &points)){
		x++;
	}

	/*
	 *下方向の移動可能判定
	 */
	y = p.get_y()+1;
      while(jands_one_wcm(p.get_x(), y, &points)){
		y++;
	}

	/*
	 *上方向の移動可能判定
	 */
	y = p.get_y()-1;
	while(jands_one_wcm(p.get_x(), y, &points)){
		y--;
	}

	//斜め上方向の移動可能判定
	jands_one_wcm(p.get_x()-1, p.get_y()-1, &points);
	jands_one_wcm(p.get_x()+1, p.get_y()-1, &points);

	//斜め下方向の移動可能判定
	jands_one_wcm(p.get_x()-1, p.get_y()+1, &points);
	jands_one_wcm(p.get_x()+1, p.get_y()+1, &points);

	return points;
}

//馬のwcm関数
std::vector<Point> en_uma_wcm(Point p){
	std::vector<Point> points;

	int x = p.get_x()-1, y = p.get_y()-1;
	/*
	 *右上方向の移動可能判定
	 */
      while(jands_one_wcm(x, y, &points)){
		x--;
		y--;
	}

	x = p.get_x()+1;
	y = p.get_y()-1;
	/*
	 *左上方向の移動可能判定
	 */
	while(jands_one_wcm(x, y, &points)){
		x++;
		y--;
	}

      x = p.get_x()-1;
	y = p.get_y()+1;
	/*
	 *右下方向の移動可能判定
	 */
	while(jands_one_wcm(x, y, &points)){
		x--;
		y++;
	}

	x = p.get_x()+1;
	y = p.get_y()+1;
	/*
	 *右下方向の移動可能判定
	 */
	while(jands_one_wcm(x, y, &points)){
		x++;
		y++;
	}

	//横方向の移動可能判定
	jands_one_wcm(p.get_x()+1, p.get_y(), &points);
	jands_one_wcm(p.get_x()-1, p.get_y(), &points);

	//前方の移動可能判定
	jands_one_wcm(p.get_x(), p.get_y()-1, &points);

	//後方方向の移動可能判定
	jands_one_wcm(p.get_x(), p.get_y()+1, &points);

	return points;

}

//手駒のwcm関数
std::vector<Point> tegoma_wcm(Point p){
	std::vector<Point> points;
	for(int y = 0;y < 9;y++)
		for(int x = 0;x < 9;x++)
			if(main_ban[x][y] == EMPTY)
				points.push_back(Point(std::abs(x-9), y+1));
	return points;
}

//打つときに、二歩にならないためのwcm関数
std::vector<Point> nihu_wcm(){
	std::vector<Point> points;
	bool nihu = false;

	for(int x = 0;x < 9;x++){
		for(int y = 0;y < 9;y++){
			if(main_ban[x][y] == HU){
				/*
				 *歩があった
				 */
				nihu = true;
			}
		}
		if(!nihu){
			/*
			 *歩が見つからない場合、その一行を追加
			 */
			for(int y = 1;y < 9;y++){
				if(main_ban[x][y] == EMPTY && main_ban[x][y-1] != EN_OU){
					points.push_back(Point(std::abs(x-9), y+1));
				}
			}
		}
		nihu = false;
	}

	return points;
}

//打つときに、二歩にならないためのwcm関数(ai用)
std::vector<Point> ai_nihu_wcm(){
	std::vector<Point> points;
	bool nihu = false;

	for(int x = 0;x < 9;x++){
		for(int y = 0;y < 9;y++){
			if(main_ban[x][y] == EN_HU){
				/*
				 *歩があった
				 */
				nihu = true;
			}
		}
		if(!nihu){
			/*
			 *歩が見つからない場合、その一行を追加
			 */
			for(int y = 0;y < 8;y++){
				if(main_ban[x][y] == EMPTY && main_ban[x][y+1] != OU){
					points.push_back(Point(std::abs(x-9), y+1));
				}
			}
		}
		nihu = false;
	}

	return points;
}
