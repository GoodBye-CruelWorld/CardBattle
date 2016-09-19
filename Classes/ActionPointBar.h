#pragma once
#include"BoardChess.h"
/*
*@ActionPoint
*@brief �ж�����
*/
class ActionPoint :public Node
{
public:
	virtual void onEnter()override;
	void explode();  //ʹ�����ж�������ը��ʧ
	void setAvailable();
	void setUnavailable();
	bool IsAvailable();
private:
	bool _available;
	Sprite* _unavail, *_avail;
};


#define MAX_ACTIONPOINT 12
/*
*@ActionPointBar
*@brief:�ж�������,�ṩ�˶��ж��������в����ķ���.
*/
class ActionPointBar :public BoardChess
{
public:
	virtual void onEnter()override;
	//��ȡ��ǰ�ж�����
	int getNumofTotalActionPoint(); 
	//��ȡ�����õ��ж�����
	int getNumofAvailActionPiint();
	//���ӿ����õ��ж�����
	void addAvailActionPoint(int delta = 1); 
	//���ӿ����õ��ж�����������
	void fullAvailActionPoint();
	//�����ж���������
	int addTotalActionPoint(int delta = 1);
	//���ٿ����õ��ж�����
	int reduceAvailActionPoint(int delta = 1);
	//�����ж���������
	int reduceTotalActionPoint(int delta = 1);
	//�Ƴ�������ж������������������»غϿ�ʼʱ����
	void removeTempActionPoint();    
private:
	Sprite* _bar;   //�е������
	ActionPoint* _actionPoint[MAX_ACTIONPOINT];  //�ж�����
	int _curTotalActionPoint;  //��ǰ�ж���������
	int _curAvailActionPoint;  //��ǰ�����õ��ж�����
	int _curTempActionPoint;  //��ǰ������ж��������������õ��ж����������ж��������ޣ���Ϊ���߲�ֵ������Ϊ0
};