#include"head.h"
int main() {
	STU head = NULL;
	int cont = 1;
	while (cont) {
		ENUM();
		cin >> cont;
		switch (cont){
			case 1:
				INIT(head);
				break;
			case 2:
				ADD(head);
				break;
			case 3:
				DELETE(head);
				break;
			case 4:
				REPLACE(head);
				break;
			case 5:
				SEARCH(head);
				break;
			case 6:
				if (head != NULL) {
					SHOW(head);
				}
				else {
					cout << "heal==NULL" << endl;
				}
				break;
			case 7:
				CLEAR(head);
				break;
			case 8:
			default:
				cont = 0;
				break;
		}
	}
	return 0;
}