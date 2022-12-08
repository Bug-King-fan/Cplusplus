#include<iostream>
#include<conio.h>  //包含函数  GetAsyncKeyState() 
#include<time.h>
#include<graphics.h> // 简单图形库 easyx
using namespace std;
const int MAX = 10; //时间计时器最大个数

enum My {
	WIDTH = 591, //窗口宽
	HEIGHT = 764, //高
	BULLET_NUM = 30,  //子弹数量
	SHIP_SPEED = 1,  //飞机移速
	BULLET_SPEED = 2,  //子弹速度
	BULLET_FIRE_TIME = 300,  //飞机两子弹发射延迟
	ENEMY_NUM = 5,  //敌机数量
	BIG,
	SMALL,  //敌机类型
	ENEMY_SPEED = 1,  //敌机速度
	DECREACE_BLOOD = 25 //飞机碰撞后，损失生命值
};

typedef struct plance {  //飞机
	int x;  //位置
	int y;
	bool live;  //是否存活
	/*敌机额外包含的*/
	int width;
	int height;
	int befor_hp; //用于飞机爆炸检测
	int hp;  //血量
	int type; //敌机类型 big / small
};
plance player;
plance bullet[BULLET_NUM];
plance enemy[ENEMY_NUM];

//背景图片
IMAGE BK;
//玩家图片
IMAGE img_role[2];
//保存子弹
IMAGE img_bullet[2];
//保存敌机图片
IMAGE img_enemy[2][2];
//保存玩家爆炸图片
IMAGE img_role_boom[2];

void loadImage() {  //加载图片591*864
	loadimage(&BK, "./images/background.jpg"); //属性 高级 字符集 使用多自节字符集
	loadimage(&img_role[0], "./images/planeNormal_1.jpg");
	loadimage(&img_role[1], "./images/planeNormal_2.jpg");
	loadimage(&img_bullet[0], "./images/bullet1.jpg");
	loadimage(&img_bullet[1], "./images/bullet2.jpg");
	loadimage(&img_enemy[0][0], "./images/enemy_1.jpg");
	loadimage(&img_enemy[0][1], "./images/enemy_2.jpg");
	loadimage(&img_enemy[1][0], "./images/enemyPlane1.jpg");
	loadimage(&img_enemy[1][1], "./images/enemyPlane2.jpg");
	loadimage(&img_role_boom[0], "./images/planeBoom_1.jpg");
	loadimage(&img_role_boom[1], "./images/planeBoom_2.jpg");
}

//生成敌机血量
void enemyHP(int i) {
	int flag = rand() % 10;
	if (flag > 0 && flag < 2) {
		enemy[i].type = BIG;
		enemy[i].hp = 3;
		enemy[i].width = 104;
		enemy[i].height = 148;
	}
	else {
		enemy[i].type = SMALL;
		enemy[i].hp = 1;
		enemy[i].width = 50;
		enemy[i].height = 39;
	}
}

//时间戳 定时器
bool Timer(int ms, int id) {
	static DWORD t[MAX];
	if (clock() - t[id] > ms) {
		t[id] = clock();
		return true;
	}
	return false;
}

//游戏初始化
void game_init() {  //初始化游戏
	//加载图像
	loadImage();
	//设置飞机初始状态
	player.x = WIDTH / 2;
	player.y = HEIGHT - 120;
	player.live = true;
	player.hp = 100;
	player.befor_hp = player.hp;
	//初始化子弹
	for (int i = 0; i < BULLET_NUM; i++) {
		bullet[i].x = 0;
		bullet[i].y = 0;
		bullet[i].live = false;
	}
	//初始化敌机
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy[i].live = false;
		enemyHP(i);
	}
}

//游戏绘制函数
void gamedraw() {
	//将背景图片贴到窗口上
	putimage(0, 0, &BK);
	//玩家飞机图片
	if (player.hp < player.befor_hp) {  //如果血量减少，贴爆炸图片
		putimage(player.x, player.y, &img_role_boom[0], NOTSRCERASE);
		putimage(player.x, player.y, &img_role_boom[1], SRCINVERT);
		player.befor_hp = player.hp;
	}
	else {
		putimage(player.x, player.y, &img_role[0], NOTSRCERASE);
		putimage(player.x, player.y, &img_role[1], SRCINVERT);
	}
	//绘制子弹
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullet[i].live) {
			putimage(bullet[i].x, bullet[i].y, &img_bullet[0], NOTSRCERASE);
			putimage(bullet[i].x, bullet[i].y, &img_bullet[1], SRCINVERT);
		}
	}
	//绘制敌机
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemy[i].live) {
			if (enemy[i].type == BIG) {
				putimage(enemy[i].x, enemy[i].y, &img_enemy[1][0], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &img_enemy[1][1], SRCINVERT);
			}
			else {
				putimage(enemy[i].x, enemy[i].y, &img_enemy[0][0], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &img_enemy[0][1], SRCINVERT);
			}
		}
	}
}

//创建子弹
void creatbullet() {
	for (int i = 0; i < BULLET_NUM; i++) {
		if (!bullet[i].live) {
			bullet[i].x = player.x + 45;
			bullet[i].y = player.y;
			bullet[i].live = true;
			break;
		}
	}
}

//子弹移动
void Bulletmove() {
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullet[i].live) {
			bullet[i].y -= BULLET_SPEED;
			if (bullet[i].y < 0) {  //子弹的死亡
				bullet[i].live = false;
			}
		}
	}
}

//角色移动 获取键盘响应
void playermove() {
#if 0
	//两种方式
	//1._getch函数  阻塞函数和scanf一样没有输入就会卡住，一直等待输入
	//char key = _getch();
	//可以通过检测键盘是否按下 按下返回真，反之为假去解决阻塞问题
	if (_kbhit()) {
		char key = _getch();
		switch (key) {
		case 'w':
		case 'W':
			player.y += SHIP_SPEED;
			break;
		case 's':
		case 'S':
			player.y -= SHIP_SPEED;
			break;
		case 'a':
		case 'A':
			player.x -= SHIP_SPEED;
			break;
		case 'd':
		case 'D':
			player.x += SHIP_SPEED;
			break;
		}
	}
#elif 1
	//2.使用windows函数获取键盘输入
	//非阻塞会很流畅 （优先）
	//检测字母键必须用大写，大写可以检测大或小写 ，如果是小写全部检测不到
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) { 
		if (player.y >= 0) {
			player.y -= SHIP_SPEED;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) {
		if (player.y + 120 < HEIGHT) {
			player.y += SHIP_SPEED;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) {
		if (player.x > 0) {
			player.x -= SHIP_SPEED;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) {
		if (player.x + 90 < WIDTH) {
			player.x += SHIP_SPEED;
		}
	}
#endif  //0
	if (GetAsyncKeyState(VK_SPACE) && Timer(BULLET_FIRE_TIME,1)) {  //两次创建子弹时间大于BULLET——FIRE_TIME
		//创建一个子弹
		creatbullet();
	}
//	t2 = GetTickCount(); //获取从操作系统启动所经过的毫秒数，它的返回值是DWORD。
}

//产生敌机
void creatEnemy() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (!enemy[i].live){
			enemy[i].live = true;
			enemy[i].x = rand() % (WIDTH - 60);
			enemy[i].y = 0;
			enemyHP(i);
			break;
		}
	}
}

//敌机移动
void enemymove() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemy[i].live) {
			enemy[i].y += ENEMY_SPEED;
			if (enemy[i].y > HEIGHT) {
				enemy[i].live = false;
			}
		}
	}
}

//击中飞机
void playplane() {
	 for (int i = 0; i < ENEMY_NUM; i++){
		 if (!enemy[i].live) { //敌机不存在
			 continue;
		 }
		 for (int j = 0; j < BULLET_NUM; j++) {
			 if (!bullet[j].live) {  //子弹不存在
				 continue;
			 }
			 if (bullet[j].x > enemy[i].x && bullet[j].x<enemy[i].x + enemy[i].width
				 && bullet[j].y>enemy[i].y && bullet[j].y < enemy[i].y + enemy[i].height) { // 子弹在敌机图片中间时
				bullet[j].live = false;
				enemy[i].hp--;
			 }
		 }
		 if (enemy[i].hp == 0) {
			 enemy[i].live = false;
		 }
	 }
}

//检测碰撞
void collision() {
	 for (int i = 0; i < ENEMY_NUM; i++) {
		 if (!enemy[i].live) {  //敌机不存在 继续
			 continue;
		 }
		 if ((player.x > enemy[i].x && player.x<enemy[i].x + enemy[i].width && player.y>enemy[i].y && player.y < enemy[i].y + enemy[i].height)
			 || (player.x + 45 > enemy[i].x && player.x + 45 < enemy[i].x + enemy[i].width && player.y > enemy[i].y && player.y < enemy[i].y + enemy[i].height)
			 || (player.x + 90 > enemy[i].x && player.x + 90 < enemy[i].x + enemy[i].width && player.y > enemy[i].y && player.y < enemy[i].y + enemy[i].height)
			 || (player.x > enemy[i].x && player.x<enemy[i].x + enemy[i].width && player.y + 60>enemy[i].y && player.y + 60 < enemy[i].y + enemy[i].height)
			 || (player.x + 45 > enemy[i].x && player.x + 45 < enemy[i].x + enemy[i].width && player.y + 60 > enemy[i].y && player.y + 60 < enemy[i].y + enemy[i].height)
			 || (player.x + 90 > enemy[i].x && player.x + 90 < enemy[i].x + enemy[i].width && player.y + 60 > enemy[i].y && player.y + 60 < enemy[i].y + enemy[i].height)
			 || (player.x > enemy[i].x && player.x<enemy[i].x + enemy[i].width && player.y + 120>enemy[i].y && player.y + 120 < enemy[i].y + enemy[i].height)
			 || (player.x + 45 > enemy[i].x && player.x + 45 < enemy[i].x + enemy[i].width && player.y + 120 > enemy[i].y && player.y + 120 < enemy[i].y + enemy[i].height)
			 || (player.x + 90 > enemy[i].x && player.x + 90 < enemy[i].x + enemy[i].width && player.y + 120 > enemy[i].y && player.y + 120 < enemy[i].y + enemy[i].height)) { //区域中 发生碰撞
			 //飞机减少生命值
			 player.hp -= DECREACE_BLOOD;
			 //碰撞到的敌机消失
			 enemy[i].hp = 0;
			 enemy[i].live = false;
			 //检测飞机血量 判断是否结束
			 if (player.hp <= 0) {
				player.live = false;
				exit(0);
			 }
		 }
	 }
}

int main() {
	 //创建图形窗口
	 initgraph(WIDTH, HEIGHT, SHOWCONSOLE); //第三个参数 SHOWCONSOLE 调出控制台看数据
	 //初始化游戏
	 game_init();
	 //双缓冲绘图 解决频闪
	 BeginBatchDraw();
	 while (true) { //窗口一直存在
		 //绘图		
		 gamedraw();
		 //刷新双缓冲绘图
		 FlushBatchDraw();
		 //玩家移动
		 if (Timer(1, 3)) {
			 playermove();
		 }
		 //子弹移动
		 Bulletmove();
		 //产生敌机
		 if (Timer(500, 0)) { //每500ms产生一个敌机
			 creatEnemy();
		 }
		 //敌机移动
		 if (Timer(30, 2)) {  //每30ms敌机移动一次
			 enemymove();
		 }
		 //打飞机
		 playplane();
		 //检测碰撞
		 collision();
	 }
	 EndBatchDraw();
	 return 0;
}