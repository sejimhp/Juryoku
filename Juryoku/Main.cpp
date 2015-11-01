
# include <Siv3D.hpp>

#include "func.h"
#include "Map.h"
#include "Ball.h"

void Main()
{
	const Font font(30);
	const Font font1(10);
	Window::Resize(1200, 800);
	font(L"ようこそ、Siv3D の世界へ！").draw();
	Circle(Mouse::Pos(), 50).draw({ 255, 0, 0, 127 });

	int number_map=0;
	int game_state = 0;
	Map map;
	Ball ball;
	//Mapに渡すデータ
	int ball_x, ball_y;
	//Ballにわたすデータ
	int stage, block[2];
	//測るやつ
	int timer;
	//時間
	int time[5][5];
	for (int i = 0; i < 25; i++)
		time[i / 5][i % 5] = 99999;

	while (System::Update())
	{
		switch (game_state){
		case 0:
			title(number_map, time);
			if (Input::KeySpace.clicked)
			{
				map.init(number_map);
				ball.init(number_map);
				timer = Time::GetMillisec();
				game_state = 1;;
			}
			break;
		case 1:
			//ボールの位置を取る
			ball_y = ball.get_y();
			ball_x = ball.get_x();
			//ボールの当たり判定
			stage = map.check_stage(ball_y, ball_x);
			map.check_block(ball_y, ball_x, block);
			//ボールの調整
			ball.run(stage, block);
			//表示
			map.draw();
			ball.draw();
			font1(DecimalPlace(5), (Time::GetMillisec() - timer) / 1000.0, L"秒").draw(100, 780, {Palette::Black});
			if (stage == 5){
				timer = Time::GetMillisec() - timer;
				record(number_map, time, timer);
				game_state = 2;
			}
			else if (stage == 10)
				game_state = 3;
			if (Input::KeyEnter.clicked)
				game_state = 0;
			break;
		case 2:
			font(L"クリア").draw(550, 100);
			font(L"あなたのタイムは").draw(250, 400);
			font(DecimalPlace(5), timer / 1000.0, L"秒です").draw(650, 400);
			font(L"Startでゲームスタート").draw(700, 670);
			if (Input::KeySpace.clicked)
				game_state = 0;
			break;
		case 3:
			map.draw();
			ball.draw();
			font(L"ゲームオーバー").draw(50, 620);
			font(L"Startでタイトルへ").draw(50, 670);
			if (Input::KeySpace.clicked)
				game_state = 0;
			break;
		}
	}
}
