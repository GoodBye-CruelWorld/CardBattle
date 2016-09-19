#pragma once
#include"cocos2d.h"
USING_NS_CC;

#define CAMP_FRIEND 0      //友方
#define CAMP_ENEMY  1      //敌对
#define CAMP_NEUTRALITY 2  //中立（野）
#define CAMP_UNDEFINE   3  //未定义

/*
*@Chess
*@brief 为面板上所有对象的父类,提供了一些共性的方法
*包含棋盘上所有元素的共性方法和变量，待开发
*/
class BoardChess :public Node
{
public:
	virtual void onEnter()override;
	void setCamp(int campID);
	int getCamp();
	int getID();

	virtual void turnSide();//翻转
	
	virtual void displayDescription();
	virtual void hideDescription();
protected:
	virtual void turnSideCallback();
	int _chessID;
	int _camp; //阵营
	Sprite* _face;
	Sprite* _back;
	Sprite* _face2;
	Sprite* _description;
};

