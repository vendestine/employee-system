#pragma once
#include<iostream>
#include "worker.h"
using namespace std;


//�ϰ���
class Boss :public Worker
{
public:

	Boss(int id, string name, int dId);

	//��ʾ������Ϣ
	virtual void showInfo();

	//��ȡְ����λ����
	virtual string getDeptName();
};