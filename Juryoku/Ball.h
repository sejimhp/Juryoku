class Ball{
	//���W
	int x, y;
	//�����x
	int ax, ay;
	//�����x�̌���
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
	//�d�͂��㉺�̏ꍇ�̏���
	void action_ud(int[2]);
	//�d�͂����E�̏ꍇ�̏���
	void action_rl(int[2]);
};