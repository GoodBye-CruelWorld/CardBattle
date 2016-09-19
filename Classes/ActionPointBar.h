#pragma once
#include"BoardChess.h"
/*
*@ActionPoint
*@brief 行动点数
*/
class ActionPoint :public Node
{
public:
	virtual void onEnter()override;
	void explode();  //使整个行动点数爆炸消失
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
*@brief:行动点数条,提供了对行动点数进行操作的方法.
*/
class ActionPointBar :public BoardChess
{
public:
	virtual void onEnter()override;
	//获取当前行动上限
	int getNumofTotalActionPoint(); 
	//获取可利用的行动点数
	int getNumofAvailActionPiint();
	//增加可利用的行动点数
	void addAvailActionPoint(int delta = 1); 
	//增加可利用的行动点数至上限
	void fullAvailActionPoint();
	//增加行动点数上限
	int addTotalActionPoint(int delta = 1);
	//减少可利用的行动点数
	int reduceAvailActionPoint(int delta = 1);
	//减少行动点数上限
	int reduceTotalActionPoint(int delta = 1);
	//移除溢出的行动点数，由流程类在下回合开始时调用
	void removeTempActionPoint();    
private:
	Sprite* _bar;   //行点点数框
	ActionPoint* _actionPoint[MAX_ACTIONPOINT];  //行动点数
	int _curTotalActionPoint;  //当前行动点数上限
	int _curAvailActionPoint;  //当前可利用的行动点数
	int _curTempActionPoint;  //当前溢出的行动点数，若可利用的行动点数大于行动点数上限，其为两者差值，否则为0
};