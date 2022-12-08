#include"head.h"
void ENUM() {
	cout << "*******************************************" << endl;
	cout << "*              1.��ʼ��                   *" << endl;
	cout << "*              2.�����Ϣ                 *" << endl;
	cout << "*              3.ɾ����Ϣ                 *" << endl;
	cout << "*              4.�޸���Ϣ                 *" << endl;
	cout << "*              5.������Ϣ                 *" << endl;
	cout << "*              6.��ʾ������Ϣ             *" << endl;
	cout << "*              7.�����Ϣ                 *" << endl;
	cout << "*              8.�˳�                     *" << endl;
	cout << "*                                         *" << endl;
	cout << "*          ### ����ǰ������� ###         *" << endl;
	cout << "*******************************************" << endl;
	return;
}

void INIT(STU& s) {
	s = new Student;
	if (s != NULL) {
		s->next = NULL;
		cout << "��ʼ�����" << endl;
	}
	else {
		cout << "��ʼ��ʧ��" << endl;
		exit(0);
	}
	system("pause");
	system("cls");
	return;
}

void ADD(STU& s) {
	if (s == NULL) {
		cout << "����δ��ʼ��\n";
		return;
	}
	int k;
	cout << "�����������Ϣ����:" << endl;
	cin >> k;
	for (int i = 0; i < k; i++) {
		STU p = new Student;
		STU q = s;
		
		ll num;  string na;
		cout << "�������" << i + 1 << "����ѧ��:  ";
		cin >> num;
		cout << "�������" << i + 1 << "��������:  ";
		cin >> na;
		p->StudentNumber = num;
		p->Name = na;

		p->next = q->next;
		q->next = p;
		q = p;
		cout << endl;
	}
	cout << "¼��ɹ�" << endl;
	system("pause");
	system("cls");
	return;
}

void SHOW(STU s) {
	if (s->next == NULL) {
		cout << "����Ϊ��" << endl;
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
		cout << "����Ϊ��\n";
		return;
	}
	ll num;
	cout << "������Ҫɾ����Ϣѧ��:  ";
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
	cout << "��ǰʣ����Ϣ:" << endl;
	SHOW(s);
	cout << "ɾ�����" << endl;
	system("pause");
	system("cls");
	return;
}

void SEARCH(STU s) {
	if (s->next == NULL) {
		cout << "����Ϊ��\n";
		return;
	}
	ll num;
	cout << "��������ҵ�ѧ��:" << endl;
	cin >> num;
	STU p = s->next;
	while (p != NULL) {
		if (p->StudentNumber == num) {
			cout << p->StudentNumber << "   " << p->Name << endl;
			break;
		}
		p = p->next;
	}
	cout << "�������" << endl;
	system("pause");
	system("cls");
	return;
}

void CLEAR(STU& s) {
	if (s == NULL) {
		cout << "������" << endl;
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
	cout << "������\n";
	system("pause");
	system("cls");
	return;
}

void REPLACE(STU& s) {
	if (s->next == NULL) {
		cout << "δ��ʼ��\n";
		return;
	}
	ll num;
	cout << "�������޸ĵ�ѧ��:" << endl;
	cin >> num;
	STU p = s->next;
	while (p != NULL) {
		if (p->StudentNumber == num) {
			string na;
			cout << "�������޸ĺ�����:  ";
			cin >> na;
			p->Name = na;
			break;
		}
	}
	cout << "�޸����\n";
	system("pause");
	system("cls");
	return;
}