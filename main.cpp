#include <iostream>
#include "workerManager.h"


int main() {

	WorkerManager wm;
	int choice = 0;
	while (true)
	{
		//展示菜单
		wm.showMenu();
		cout << "请输入您的选择:" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0: //退出系统
			wm.exitMenu();
			break;
		case 1: //添加职工
			wm.addWorker();
			break;
		case 2: //显示职工
			wm.showWorker();
			break;
		case 3: //删除职工
			wm.deleteWorker();
			break;
		case 4: //修改职工
			wm.updateWorker();
			break;
		case 5: //查找职工
			wm.findWorker();
			break;
		case 6: //排序职工
			wm.sortWorker();
			break;
		case 7: //清空文件
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