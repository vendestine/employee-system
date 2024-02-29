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

	//���캯��
	WorkerManager();

	//��������
	~WorkerManager();

	// ��ʾ����
	void showMenu();

	// �˳�����
	void exitMenu();

	//����ְ��
	void addWorker();

	//�����ļ�
	void save();

	//ͳ������
	int getWorkerNum();

	//��ʼ��Ա��
	void initWorker();

	//��ʾְ��
	void showWorker();

	//ɾ��ְ��
	void deleteWorker();

	//����ְ������ж�ְ���Ƿ����,�����ڷ���ְ����������λ�ã������ڷ���-1
	int isExist(int id);

	//�޸�ְ��
	void updateWorker();

	//����ְ��
	void findWorker();

	//����ְ��
	void sortWorker();

	//����ļ�
	void cleanFile();



	//��¼�ļ��е���������
	int worker_size;

	//Ա�������ָ��
	Worker** worker_array;

	//��־�ļ��Ƿ�Ϊ��
	bool is_file_empty;
};