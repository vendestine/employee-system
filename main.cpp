#include <iostream>
#include "workerManager.h"


int main() {

	WorkerManager wm;
	int choice = 0;
	while (true)
	{
		//չʾ�˵�
		wm.showMenu();
		cout << "����������ѡ��:" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0: //�˳�ϵͳ
			wm.exitMenu();
			break;
		case 1: //���ְ��
			wm.addWorker();
			break;
		case 2: //��ʾְ��
			wm.showWorker();
			break;
		case 3: //ɾ��ְ��
			wm.deleteWorker();
			break;
		case 4: //�޸�ְ��
			wm.updateWorker();
			break;
		case 5: //����ְ��
			wm.findWorker();
			break;
		case 6: //����ְ��
			wm.sortWorker();
			break;
		case 7: //����ļ�
			wm.cleanFile();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}