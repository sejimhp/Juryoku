class Ball{
	//座標
	int x, y;
	//加速度
	int ax, ay;
	//加速度の向き
	int way;
	int time;
	int routen;
public:
	void init(int);
	void draw();
	int get_y();
	int get_x();

	void input(int[2]);
	void run(int, int[2]);
	//重力が上下の場合の処理
	void action_ud(int[2]);
	//重力が左右の場合の処理
	void action_rl(int[2]);
};