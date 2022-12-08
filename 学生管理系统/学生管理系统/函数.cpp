#include"head.h"
void ENUM() {
	cout << "*******************************************" << endl;
	cout << "*              1.初始化                   *" << endl;
	cout << "*              2.添加信息                 *" << endl;
	cout << "*              3.删除信息                 *" << endl;
	cout << "*              4.修改信息                 *" << endl;
	cout << "*              5.查找信息                 *" << endl;
	cout << "*              6.显示所有信息             *" << endl;
	cout << "*              7.清空信息                 *" << endl;
	cout << "*              8.退出                     *" << endl;
	cout << "*                                         *" << endl;
	cout << "*          ### 结束前必须清空 ###         *" << endl;
	cout << "*******************************************" << endl;
	return;
}

void INIT(STU& s) {
	s = new Student;
	if (s != NULL) {
		s->next = NULL;
		cout << "初始化完成" << endl;
	}
	else {
		cout << "初始化失败" << endl;
		exit(0);
	}
	system("pause");
	system("cls");
	return;
}

void ADD(STU& s) {
	if (s == NULL) {
		cout << "数据未初始化\n";
		return;
	}
	int k;
	cout << "请输入添加信息人数:" << endl;
	cin >> k;
	for (int i = 0; i < k; i++) {
		STU p = new Student;
		STU q = s;
		
		ll num;  string na;
		cout << "请输入第" << i + 1 << "个人学号:  ";
		cin >> num;
		cout << "请输入第" << i + 1 << "个人姓名:  ";
		cin >> na;
		p->StudentNumber = num;
		p->Name = na;

		p->next = q->next;
		q->next = p;
		q = p;
		cout << endl;
	}
	cout << "录入成功" << endl;
	system("pause");
	system("cls");
	return;
}

void SHOW(STU s) {
	if (s->next == NULL) {
		cout << "数据为空" << endl;
		return;
	}
	STU p = s->next;
	while (p != NULL) {
		cout << p->StudentNumber << "   " << p->Name << endl;
		p = p->next;
	}
	return;
}

void DELETE(STU& s) {
	if (s->next == NULL) {
		cout << "数据为空\n";
		return;
	}
	ll num;
	cout << "请输入要删除信息学号:  ";
	cin >> num;
	STU p = s->next;
	STU q = s;
	while (p != NULL) {
		if (p->StudentNumber == num) {
			q->next = p->next;
			delete p;
			p = NULL;
			break;
		}
		q = p;
		p = p->next;
	}
	cout << "当前剩余信息:" << endl;
	SHOW(s);
	cout << "删除完成" << endl;
	system("pause");
	system("cls");
	return;
}

void SEARCH(STU s) {
	if (s->next == NULL) {
		cout << "数据为空\n";
		return;
	}
	ll num;
	cout << "请输入查找的学号:" << endl;
	cin >> num;
	STU p = s->next;
	while (p != NULL) {
		if (p->StudentNumber == num) {
			cout << p->StudentNumber << "   " << p->Name << endl;
			break;
		}
		p = p->next;
	}
	cout << "查找完成" << endl;
	system("pause");
	system("cls");
	return;
}

void CLEAR(STU& s) {
	if (s == NULL) {
		cout << "不存在" << endl;
		return;
	}
	while (s->next != NULL) {
		STU p = s;
		STU q = s->next;
		if (q != NULL) {
			p->next = q->next;
			delete q;
			q = NULL;
		}
	}
	delete s;
	s = NULL;
	cout << "清空完成\n";
	system("pause");
	system("cls");
	return;
}

void REPLACE(STU& s) {
	if (s->next == NULL) {
		cout << "未初始化\n";
		return;
	}
	ll num;
	cout << "请输入修改的学号:" << endl;
	cin >> num;
	STU p = s->next;
	while (p != NULL) {
		if (p->StudentNumber == num) {
			string na;
			cout << "请输入修改后姓名:  ";
			cin >> na;
			p->Name = na;
			break;
		}
	}
	cout << "修改完成\n";
	system("pause");
	system("cls");
	return;
}