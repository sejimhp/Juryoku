class Map{ 
	int stage_num;
	int map[40][60];
	int map_all[5][40][60];
public:
	Map();
	void init(int);
	void draw();
	void check_block(int, int, int[2]);
	//0���ʏ�@1���E�@2����@3����
	int check_stage(int, int);
};