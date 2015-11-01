#include <Siv3D.hpp>

#include "func.h"

void title(int &num, int time[][5]){
	static Font font1(50);
	static Font font2(30);
	//点滅用
	static int timer = Time::GetMillisec();
	font1(L"グラビティーゲーム").draw(260, 70, Palette::Lightgreen);

	for (int i = 1; i <= 3; i++)
		font2(L"ステージ",DecimalPlace(0), i).draw(200, 150 + i*100);
	font1(L"⇒").draw(130, 230 + num * 100);

	for (int i = 0; i<5; i++){
		font2(DecimalPlace(1), i+1, L"位").draw(650, 230 + i * 80);
		font2(DecimalPlace(5), time[num][i] / 1000.0, L"秒").draw(750, 230 + i * 80);
	}

	if (1000 > Time::GetMillisec()-timer)
		font2(L"Startでゲームスタート").draw(350, 670);
	else if (2000 < Time::GetMillisec()-timer)
		timer = Time::GetMillisec();


	if (Input::KeyUp.clicked)
		num--;
	else if (Input::KeyDown.clicked)
		num = (num+1)%3;
	if (num < 0)
		num = 2;
}

void record(int num, int time[][5], int timer){
	int k=4;
	while (k >= 0 && time[num][k] > timer)
		k--;
	for (int i = 4; i > k + 1; i--)
		time[num][i] = time[num][i - 1];
	time[num][k + 1] = timer;
}