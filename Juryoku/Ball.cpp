#include <Siv3D.hpp>

#include "Ball.h"

void Ball::init(int num){
	ax = 0;
	ay = 0;
	//ステージによって初期位置を変える
	switch (num){
	case 0:
		x = 100;
		y = 400;
		break;
	case 1:
		x = 100;
		y = 400;
		break;
	case 2:
		x = 700;
		y = 30;
		break;
	case 3:
		x = 100;
		y = 100;
		break;
	case 4:
		x = 100;
		y = 100;
		break;
	}
	routen = 0;
	way = 0;
	time = Time::GetMillisec();
}

void Ball::run(int stage, int block[2]){
	if (stage == 7){
		y = 760;
		x = 40;
		return;
	}
	if (stage != way && (Time::GetMillisec() - time) > 200){
		if (way != stage){
			if (way % 2 == 0 && stage % 2 == 0 || way % 2 == 1 && stage % 2 == 1){
				//上下OR左右でエリアが切り替わったときの初期化
				ay = 0;
					if (ax >= 40)
						ax = -ax / 3 * 2;
					else
						ax = -ax;
			}
			else {
				//上下から左右、左右から上下でエリアが切り替わったときの初期化
				int a;
				a = ay;
				if (!(way == 0 && stage == 3 || way == 3 && stage == 2)){
					ay = ax / 5;
					ax = -a / 2;
				}
				else{
					ax = a / 2;
					ay = -ax / 5;
				}
			}
		}
		way = stage;
		time = Time::GetMillisec();
	}
	//入力
	input(block);

	if (way % 2 == 0)
		action_ud(block);
	else
		action_rl(block);


	if (x >= 1180)
		x = 1165;
	if (y >= 780)
		y = 765;
}

void Ball::action_ud(int block[2]){
	//どこかに接触していた場合の判定
	//3は上に重力1は普通
	for (int i = 0; i < 2; i++){
		switch (block[i]){
		case 1:
			//下
			y = (y / 20) * 20 + 5;
			if (ay > 0 && way == 0)
				ay = 0;
			if (way == 2){
				if (ay < 0);
				ay = 0;
				ay++;
			}
			break;
		case 2:
			//右
			x = (x / 20) * 20 + 5;
			if (ax > 0 && way == 0)
				ax = 0;
			if (ax < 0 && way == 2)
				ax = 0;
			break;
		case 3:
			//上
			y = (y / 20 + 1) * 20 - 5;
			if (ay > 0 && way == 2)
				ay = 0;
			if (way == 0){
				if (ay < 0);
				ay = 0;
				ay++;
			}
			break;
		case 4:
			//左
			x = (x / 20 + 1) * 20 - 5;
			if (ax < 0 && way == 0)
				ax = 0;
			if (ax > 0 && way == 2)
				ax = 0;
			break;
		}
	}
	ay++;

	if (way == 0){
		x += ax / 10;
		y += ay / 2;
	}
	else if (way == 2){
		x -= ax / 10;
		y -= ay / 2;
	}
}

void Ball::action_rl(int block[2]){
	//どこかに接触していた場合の判定
	//3は上に重力1は普通
	for (int i = 0; i < 2; i++){
		switch (block[i]){
		case 1:
			//下
			y = (y / 20) * 20 + 5;
			if (ax < 0 && way == 1)
				ax = 0;
			else if (ax > 0 && way == 3)
				ax = 0;
			break;
		case 2:
			//右
			x = (x / 20) * 20 + 5;
			if (ay > 0 && way == 1)
				ay = 0;
			if (way == 3){
				if (ay < 0);
				ay = 0;
				ay++;
			}
			break;
		case 3:
			//上
			y = (y / 20 + 1) * 20 - 5;
			if (ax > 0 && way == 1)
				ax = 0;
			else if (ax < 0 && way == 3)
				ax = 0;;
			break;
		case 4:
			//左
			x = (x / 20 + 1) * 20 - 5;
			if (ay > 0 && way == 3)
				ay = 0;
			if (way == 1){
				if (ay < 0);
				ay = 0;
				ay++;
			}
			break;
		}
	}
	ay++;

	if (way == 1){
		y -= ax / 10;
		x += ay / 2;
	}
	else if (way == 3){
		y += ax / 10;
		x -= ay / 2;
	}
}

void Ball::draw(){
	//円の中の棒
	routen += ax / 4;
	routen %= 360;
	double cos = Sin(routen / 360.0*3.1415 * 2);
	double sin = Cos(routen / 360.0*3.1415 * 2);
	Line(x + sin * 10, y + cos * 10, x - sin * 10, y - cos * 10).draw(3);
	cos = Sin((routen + 90) / 360.0*3.1415 * 2);
	sin = Cos((routen + 90) / 360.0*3.1415 * 2);
	Line(x + sin * 10, y + cos * 10, x - sin * 10, y - cos * 10).draw(3);
	//円
	Circle(x, y, 15).draw({ 255, 0, 0, 127 });
}

void Ball::input(int block[2]){
	//左右
	if (Input::KeyRight.pressed)
		if (ax < 0)
			ax += 2;
		else
			ax++;
	else if (Input::KeyLeft.pressed)
		if (ax > 0)
			ax -= 2;
		else
			ax--;
	else if (ax > 0) {//減速
		ax--;
	}
	else if (ax < 0){
		ax++;
	}
	//ジャンプ
	if (Input::KeySpace.clicked && (way+1 == block[0] || way+1 == block[1]))
		ay = -25;

	if (ax > 50)
		ax = 50;
	else if (ax < -50)
		ax = -50;
}

int Ball::get_x(){
	return x;
}

int Ball::get_y(){
	return y;
}
