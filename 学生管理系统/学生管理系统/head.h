#pragma once
#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;

// ��ʼ�� �� ɾ �� �� ���� ��ʾ����ѧ����Ϣ �˵�
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