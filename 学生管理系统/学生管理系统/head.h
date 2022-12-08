#pragma once
#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;

// 初始化 增 删 查 改 销毁 显示所有学生信息 菜单
typedef struct Student {
	ll StudentNumber;
	string Name;
	Student* next;
}*STU;

void INIT(STU& s);
void ADD(STU& s);
void DELETE(STU& s);
void SEARCH(STU s);
void REPLACE(STU& s);
void SHOW(STU s);
void CLEAR(STU& s);
void ENUM();