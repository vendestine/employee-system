#include "workerManager.h"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在情况
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl; //测试输出
		this->worker_size = 0;  //初始化人数
		this->is_file_empty = true; //初始化文件为空标志
		this->worker_array = NULL; //初始化数组
		ifs.close(); //关闭文件
		return;
	}


	//文件存在，并且没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空!" << endl;
		this->worker_size = 0;
		this->is_file_empty = true;
		this->worker_array = NULL;
		ifs.close();
		return;
	}


	// 文件存在，有记录
	int num = this->getWorkerNum();
	this->worker_size = num;  //更新成员属性 
	//根据职工数创建数组
	this->worker_array = new Worker * [this->worker_size];
	//初始化职工
	initWorker();
}

WorkerManager::~WorkerManager()
{
	if (this->worker_array != NULL)
	{
		delete[] this->worker_array;
	}
}

void WorkerManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::exitMenu()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::addWorker()
{
	cout << "请输入增加职工数量： " << endl;

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//计算新空间大小
		int newSize = this->worker_size + addNum;

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原空间下内容存放到新空间下
		if (this->worker_array != NULL)
		{
			for (int i = 0; i < this->worker_size; i++)
			{
				newSpace[i] = this->worker_array[i];
			}
		}

		//输入新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "请输入第 " << i + 1 << " 个新职工编号：" << endl;
			cin >> id;


			cout << "请输入第 " << i + 1 << " 个新职工姓名：" << endl;
			cin >> name;


			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;


			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1: //普通员工
				worker = new Employee(id, name, 1);
				break;
			case 2: //经理
				worker = new Manager(id, name, 2);
				break;
			case 3:  //老板
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}


			newSpace[this->worker_size + i] = worker;
		}

		//释放原有空间
		delete[] this->worker_array;

		//更改新空间的指向
		this->worker_array = newSpace;

		//更新新的个数
		this->worker_size = newSize;

		//更新职工不为空标志
		this->is_file_empty = false;

		//提示信息
		cout << "成功添加" << addNum << "名新职工！" << endl;

		// 保存
		this->save();
	}
	else
	{
		cout << "输入有误" << endl;
	}

	system("pause");
	system("cls");
}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);


	for (int i = 0; i < this->worker_size; i++)
	{
		ofs << this->worker_array[i]->m_Id << " "
			<< this->worker_array[i]->m_Name << " "
			<< this->worker_array[i]->m_DeptId << endl;
	}

	ofs.close();
}

int WorkerManager::getWorkerNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//记录人数
		num++;
	}
	ifs.close();

	return num;
}

void WorkerManager::initWorker()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		//根据不同的部门Id创建不同对象
		if (dId == 1)  // 1普通员工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) //2经理
		{
			worker = new Manager(id, name, dId);
		}
		else //总裁
		{
			worker = new Boss(id, name, dId);
		}
		//存放在数组中
		this->worker_array[index] = worker;
		index++;
	}
}

void WorkerManager::showWorker()
{
	if (this->is_file_empty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < worker_size; i++)
		{
			//利用多态调用接口
			this->worker_array[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

int WorkerManager::isExist(int id)
{
	int index = -1;

	for (int i = 0; i < this->worker_size; i++)
	{
		if (this->worker_array[i]->m_Id == id)
		{
			index = i;

			break;
		}
	}

	return index;
}

void WorkerManager::deleteWorker()
{
	if (this->is_file_empty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		//按职工编号删除
		cout << "请输入想要删除的职工号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->isExist(id);

		if (index != -1)  //说明index上位置数据需要删除
		{
			for (int i = index; i < this->worker_size - 1; i++)
			{
				this->worker_array[i] = this->worker_array[i + 1];
			}
			this->worker_size--;

			this->save(); //删除后数据同步到文件中
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::updateWorker()
{
	if (this->is_file_empty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号：" << endl;
		int id;
		cin >> id;

		int ret = this->isExist(id);
		if (ret != -1)
		{
			//查找到编号的职工

			delete this->worker_array[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到： " << id << "号职工，请输入新职工号： " << endl;
			cin >> newId;

			cout << "请输入新姓名： " << endl;
			cin >> newName;

			cout << "请输入岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			//更改数据 到数组中
			this->worker_array[ret] = worker;

			cout << "修改成功！" << endl;

			//保存到文件中
			this->save();
		}
		else
		{
			cout << "修改失败，查无此人" << endl;
		}
	}

	//按任意键 清屏
	system("pause");
	system("cls");
}

void WorkerManager::findWorker()
{
	if (this->is_file_empty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cin >> select;


		if (select == 1) //按职工号查找
		{
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;

			int ret = isExist(id);
			if (ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->worker_array[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2) //按姓名查找
		{
			string name;
			cout << "请输入查找的姓名：" << endl;
			cin >> name;

			bool flag = false;  //查找到的标志
			for (int i = 0; i < worker_size; i++)
			{
				if (worker_array[i]->m_Name == name)
				{
					cout << "查找成功,职工编号为："
						<< worker_array[i]->m_Id
						<< " 号的信息如下：" << endl;

					flag = true;

					this->worker_array[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//查无此人
				cout << "查找失败，查无此人" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}
	}


	system("pause");
	system("cls");
}

void WorkerManager::sortWorker()
{
	if (this->is_file_empty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式： " << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;

		int select = 0;
		cin >> select;


		for (int i = 0; i < worker_size; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < worker_size; j++)
			{
				if (select == 1) //升序
				{
					if (worker_array[minOrMax]->m_Id > worker_array[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else  //降序
				{
					if (worker_array[minOrMax]->m_Id < worker_array[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}

			if (i != minOrMax)
			{
				Worker* temp = worker_array[i];
				worker_array[i] = worker_array[minOrMax];
				worker_array[minOrMax] = temp;
			}

		}

		cout << "排序成功,排序后结果为：" << endl;
		this->save();
		this->showWorker();
	}

}

void WorkerManager::cleanFile()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//打开模式 ios::trunc 如果存在删除文件并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->worker_array != NULL)
		{
			for (int i = 0; i < this->worker_size; i++)
			{
				if (this->worker_array[i] != NULL)
				{
					delete this->worker_array[i];
				}
			}
			this->worker_size = 0;
			delete[] this->worker_array;
			this->worker_array = NULL;
			this->is_file_empty = true;
		}
		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}

