#pragma once
#include<iostream>
#include "worker.h"
#include "boss.h"
#include "manager.h"
#include "employee.h"
#include <fstream>


#define  FILENAME "empFile.txt"


using namespace std;


class WorkerManager
{
public:

	//构造函数
	WorkerManager();

	//析构函数
	~WorkerManager();

	// 显示界面
	void showMenu();

	// 退出界面
	void exitMenu();

	//增加职工
	void addWorker();

	//保存文件
	void save();

	//统计人数
	int getWorkerNum();

	//初始化员工
	void initWorker();

	//显示职工
	void showWorker();

	//删除职工
	void deleteWorker();

	//按照职工编号判断职工是否存在,若存在返回职工在数组中位置，不存在返回-1
	int isExist(int id);

	//修改职工
	void updateWorker();

	//查找职工
	void findWorker();

	//排序职工
	void sortWorker();

	//清空文件
	void cleanFile();



	//记录文件中的人数个数
	int worker_size;

	//员工数组的指针
	Worker** worker_array;

	//标志文件是否为空
	bool is_file_empty;
};