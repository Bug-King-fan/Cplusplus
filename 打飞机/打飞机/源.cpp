#include<iostream>
#include<conio.h>  //��������  GetAsyncKeyState() 
#include<time.h>
#include<graphics.h> // ��ͼ�ο� easyx
using namespace std;
const int MAX = 10; //ʱ���ʱ��������

enum My {
	WIDTH = 591, //���ڿ�
	HEIGHT = 764, //��
	BULLET_NUM = 30,  //�ӵ�����
	SHIP_SPEED = 1,  //�ɻ�����
	BULLET_SPEED = 2,  //�ӵ��ٶ�
	BULLET_FIRE_TIME = 300,  //�ɻ����ӵ������ӳ�
	ENEMY_NUM = 5,  //�л�����
	BIG,
	SMALL,  //�л�����
	ENEMY_SPEED = 1,  //�л��ٶ�
	DECREACE_BLOOD = 25 //�ɻ���ײ����ʧ����ֵ
};

typedef struct plance {  //�ɻ�
	int x;  //λ��
	int y;
	bool live;  //�Ƿ���
	/*�л����������*/
	int width;
	int height;
	int befor_hp; //���ڷɻ���ը���
	int hp;  //Ѫ��
	int type; //�л����� big / small
};
plance player;
plance bullet[BULLET_NUM];
plance enemy[ENEMY_NUM];

//����ͼƬ
IMAGE BK;
//���ͼƬ
IMAGE img_role[2];
//�����ӵ�
IMAGE img_bullet[2];
//����л�ͼƬ
IMAGE img_enemy[2][2];
//������ұ�ըͼƬ
IMAGE img_role_boom[2];

void loadImage() {  //����ͼƬ591*864
	loadimage(&BK, "./images/background.jpg"); //���� �߼� �ַ��� ʹ�ö��Խ��ַ���
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

//���ɵл�Ѫ��
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

//ʱ��� ��ʱ��
bool Timer(int ms, int id) {
	static DWORD t[MAX];
	if (clock() - t[id] > ms) {
		t[id] = clock();
		return true;
	}
	return false;
}

//��Ϸ��ʼ��
void game_init() {  //��ʼ����Ϸ
	//����ͼ��
	loadImage();
	//���÷ɻ���ʼ״̬
	player.x = WIDTH / 2;
	player.y = HEIGHT - 120;
	player.live = true;
	player.hp = 100;
	player.befor_hp = player.hp;
	//��ʼ���ӵ�
	for (int i = 0; i < BULLET_NUM; i++) {
		bullet[i].x = 0;
		bullet[i].y = 0;
		bullet[i].live = false;
	}
	//��ʼ���л�
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy[i].live = false;
		enemyHP(i);
	}
}

//��Ϸ���ƺ���
void gamedraw() {
	//������ͼƬ����������
	putimage(0, 0, &BK);
	//��ҷɻ�ͼƬ
	if (player.hp < player.befor_hp) {  //���Ѫ�����٣�����ըͼƬ
		putimage(player.x, player.y, &img_role_boom[0], NOTSRCERASE);
		putimage(player.x, player.y, &img_role_boom[1], SRCINVERT);
		player.befor_hp = player.hp;
	}
	else {
		putimage(player.x, player.y, &img_role[0], NOTSRCERASE);
		putimage(player.x, player.y, &img_role[1], SRCINVERT);
	}
	//�����ӵ�
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullet[i].live) {
			putimage(bullet[i].x, bullet[i].y, &img_bullet[0], NOTSRCERASE);
			putimage(bullet[i].x, bullet[i].y, &img_bullet[1], SRCINVERT);
		}
	}
	//���Ƶл�
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

//�����ӵ�
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

//�ӵ��ƶ�
void Bulletmove() {
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullet[i].live) {
			bullet[i].y -= BULLET_SPEED;
			if (bullet[i].y < 0) {  //�ӵ�������
				bullet[i].live = false;
			}
		}
	}
}

//��ɫ�ƶ� ��ȡ������Ӧ
void playermove() {
#if 0
	//���ַ�ʽ
	//1._getch����  ����������scanfһ��û������ͻῨס��һֱ�ȴ�����
	//char key = _getch();
	//����ͨ���������Ƿ��� ���·����棬��֮Ϊ��ȥ�����������
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
	//2.ʹ��windows������ȡ��������
	//������������� �����ȣ�
	//�����ĸ�������ô�д����д���Լ����Сд �������Сдȫ����ⲻ��
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
	if (GetAsyncKeyState(VK_SPACE) && Timer(BULLET_FIRE_TIME,1)) {  //���δ����ӵ�ʱ�����BULLET����FIRE_TIME
		//����һ���ӵ�
		creatbullet();
	}
//	t2 = GetTickCount(); //��ȡ�Ӳ���ϵͳ�����������ĺ����������ķ���ֵ��DWORD��
}

//�����л�
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

//�л��ƶ�
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

//���зɻ�
void playplane() {
	 for (int i = 0; i < ENEMY_NUM; i++){
		 if (!enemy[i].live) { //�л�������
			 continue;
		 }
		 for (int j = 0; j < BULLET_NUM; j++) {
			 if (!bullet[j].live) {  //�ӵ�������
				 continue;
			 }
			 if (bullet[j].x > enemy[i].x && bullet[j].x<enemy[i].x + enemy[i].width
				 && bullet[j].y>enemy[i].y && bullet[j].y < enemy[i].y + enemy[i].height) { // �ӵ��ڵл�ͼƬ�м�ʱ
				bullet[j].live = false;
				enemy[i].hp--;
			 }
		 }
		 if (enemy[i].hp == 0) {
			 enemy[i].live = false;
		 }
	 }
}

//�����ײ
void collision() {
	 for (int i = 0; i < ENEMY_NUM; i++) {
		 if (!enemy[i].live) {  //�л������� ����
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
			 || (player.x + 90 > enemy[i].x && player.x + 90 < enemy[i].x + enemy[i].width && player.y + 120 > enemy[i].y && player.y + 120 < enemy[i].y + enemy[i].height)) { //������ ������ײ
			 //�ɻ���������ֵ
			 player.hp -= DECREACE_BLOOD;
			 //��ײ���ĵл���ʧ
			 enemy[i].hp = 0;
			 enemy[i].live = false;
			 //���ɻ�Ѫ�� �ж��Ƿ����
			 if (player.hp <= 0) {
				player.live = false;
				exit(0);
			 }
		 }
	 }
}

int main() {
	 //����ͼ�δ���
	 initgraph(WIDTH, HEIGHT, SHOWCONSOLE); //���������� SHOWCONSOLE ��������̨������
	 //��ʼ����Ϸ
	 game_init();
	 //˫�����ͼ ���Ƶ��
	 BeginBatchDraw();
	 while (true) { //����һֱ����
		 //��ͼ		
		 gamedraw();
		 //ˢ��˫�����ͼ
		 FlushBatchDraw();
		 //����ƶ�
		 if (Timer(1, 3)) {
			 playermove();
		 }
		 //�ӵ��ƶ�
		 Bulletmove();
		 //�����л�
		 if (Timer(500, 0)) { //ÿ500ms����һ���л�
			 creatEnemy();
		 }
		 //�л��ƶ�
		 if (Timer(30, 2)) {  //ÿ30ms�л��ƶ�һ��
			 enemymove();
		 }
		 //��ɻ�
		 playplane();
		 //�����ײ
		 collision();
	 }
	 EndBatchDraw();
	 return 0;
}