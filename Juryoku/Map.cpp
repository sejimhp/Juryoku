#include <Siv3D.hpp>

#include "Map.h"

void Map::init(int num){
	for (int i = 0; i < 40; i++){
		for (int j = 0; j < 60; j++){
			map[i][j] = map_all[num][i][j];
		}
	}
	stage_num = num;
}

Map::Map(){
	TextReader reader(L"item/stage.txt");

	String s;

	int i = 0, k = 0;
	while (reader.readLine(s))
	{
		if (s.length != 60)
			continue;
		for (int j = 0; j < 60; j++){
			map_all[k][i][j] = (int)(s[j] - '0');
		}
		i++;
		if (i == 40){
			i = 0;
			k++;
		}
	}
}

void Map::check_block(int y, int x, int block[2]){
	/*
		3
		4 2
		1
		*/
	int xx[5] = { 0, 1, 0, -1, 0 };
	int yy[5] = { 1, 0, -1, 0, 0 };
	//2か所以上接している可能性を考慮
	int t = 0;
	block[0] = 0; block[1] = -1;
	Circle circle(x, y, 15);
	//接しているか判定
	for (int i = 0; i < 5; i++){
		int X = x / 20 + xx[i];
		int Y = y / 20 + yy[i];
		if (X < 0 || X >= 60 || Y < 0 || Y >= 40)
			continue;
		Rect rect(X * 20, Y * 20, 20, 20);
		if (circle.intersects(rect) && map[Y][X] == 1){
			switch (i)
			{
			case 0:
				block[t] = 1;
				break;
			case 1:
				block[t] = 2;
				break;
			case 2:
				block[t] = 3;
				break;
			case 3:
				block[t] = 4;
				break;
			case 4:
				//めり込んだ場合
				block[t] = 5;
				break;
			}
			t++;
			if (t == 2)
				break;
		}
	}
}

int Map::check_stage(int y, int x){
	//初期化
	Rect rect1, rect2, rect3, rect4, rect5, rect6, rect7, rect8, rect9, rect10;
	Line line1, line2;
	/*
	1は→
	2は↑
	3は←
	5はクリア
	7はループ
	10はゲームオーバ
	*/
	Circle circle(x, y, 1);
	Circle circle1(x, y, 15);
	switch (stage_num){
	case 0:
		//ステージ１
		rect1 = Rect(200, 20, 800, 400);
		rect2 = Rect(200, 420, 300, 400);
		rect3 = Rect(700, 420, 300, 400);
		rect4 = Rect(1120, 720, 60, 60);
		line1 = Line(800, 500, 800, 760);
		if (circle1.intersects(line1))
			return 10;
		else if (circle.intersects(rect1))
			return 2;
		else if (circle.intersects(rect2))
			return 1;
		else if (circle.intersects(rect3))
			return 3;
		else if (circle.intersects(rect4))
			return 5;
		break;
	case 1:
		//ステージ２
		rect1 = Rect(250, 380, 300, 400);
		rect2 = Rect(920, 20, 270, 430);
		rect3 = Rect(920, 450, 270, 100);
		rect4 = Rect(920, 550, 270, 500);
		//クリア
		rect5 = Rect(20, 300, 60, 60);
		rect6 = Rect(20, 20, 640, 40);
		rect7 = Rect(600, 60, 60, 220);
		rect8 = Rect(120, 200, 20, 160);
		if (circle.intersects(rect1))
			return 2;
		else if (circle.intersects(rect2))
			return 2;
		else if (circle.intersects(rect3))
			return 3;
		else if (circle.intersects(rect4))
			return 1;
		else if (circle.intersects(rect5))
			return 5;
		else if (circle.intersects(rect6))
			return 2;
		else if (circle.intersects(rect7))
			return 3;
		else if (circle1.intersects(rect8))
			return 10;
		break;
	case 2:
		//ステージ３
		rect1 = Rect(1080, 20, 100, 250);
		rect2 = Rect(1080, 270, 100, 150);
		rect3 = Rect(700, 460, 500, 500);
		rect4 = Rect(1120, 720, 60, 60);
		rect5 = Rect(260, 80, 360, 700);
		rect6 = Rect(400, 80, 20, 500);
		rect7 = Rect(580, 20, 40, 40);
		rect8 = Rect(20, 20, 40, 600);
		line1 = Line(1070, 90, 1070, 300);
		line2 = Line(1170, 470, 1170, 720);
		if (circle1.intersects(line1))
			return 10;
		if (circle1.intersects(line2))
			return 10;
		else if (circle1.intersects(rect6))
			return 10;
		else if (circle1.intersects(rect4))
			return 7;
		else if (circle.intersects(rect1))
			return 1;
		else if (circle.intersects(rect2))
			return 3;
		else if (circle.intersects(rect3))
			return 1;
		else if (circle.intersects(rect5))
			return 2;
		else if (circle.intersects(rect7))
			return 5;
		else if (circle.intersects(rect8))
			return 3;
		break;
	}
	return 0;
}

void Map::draw(){
	switch (stage_num){
	case 0:
		//ステージ１
		Rect(200, 20, 800, 400).draw({ Palette::Aqua, 120 });
		Rect(200, 420, 300, 400).draw({ Palette::Orange, 120 });
		Rect(700, 420, 300, 400).draw({ Palette::Yellow, 120 });
		Rect(1120, 720, 60, 60).draw({ Palette::Green, 120 });
		Rect(1138, 738, 24, 24).draw({ Palette::Lightgreen, 120 });
		Line(800, 500, 800, 760).draw(5, Palette::Red);
		break;
	case 1:
		//ステージ２
		Rect(250, 380, 300, 400).draw({ Palette::Aqua, 120 });
		Rect(920, 20, 270, 430).draw({ Palette::Aqua, 120 });
		Rect(920, 450, 270, 100).draw({ Palette::Yellow, 120 });
		Rect(920, 550, 270, 500).draw({ Palette::Orange, 120 });
		Rect(20, 300, 60, 60).draw({ Palette::Green, 120 });
		Rect(38, 318, 24, 24).draw({ Palette::Lightgreen, 120 });
		Rect(20, 20, 640, 40).draw({ Palette::Aqua, 120 });
		Rect(600, 60, 60, 220).draw({ Palette::Yellow, 120 });
		Rect(120, 200, 20, 160).draw(Palette::Red);
		break;
	case 2:
		//ステージ３
		Rect(1080, 20, 100, 250).draw({ Palette::Orange, 120 });
		Rect(1080, 270, 100, 150).draw({ Palette::Yellow, 120 });
		Rect(700, 460, 500, 500).draw({ Palette::Orange, 120 });
		Rect(260, 80, 360, 700).draw({ Palette::Aqua, 120 });
		Rect(580, 20, 40, 40).draw({ Palette::Green, 120 });
		Rect(20, 20, 40, 600).draw({ Palette::Yellow, 120 });
		Rect(400, 80, 20, 500).draw(Palette::Red);
		Line(1070, 90, 1070, 300).draw(20, Palette::Red);
		Line(1170, 470, 1170, 710).draw(5, Palette::Red);
		//ループ
		Rect(1120, 720, 60, 60).draw({ Palette::Green, 120 });
		Rect(20, 720, 60, 60).draw({ Palette::Green, 120 });
		break;
	}
	//ブロックの表示
	for (int i = 0; i < 40; i++){
		for (int j = 0; j < 60; j++){
			if (map[i][j] == 1){
				Rect(j * 20, i * 20, 20, 20).draw();
			}
		}
	}
}

