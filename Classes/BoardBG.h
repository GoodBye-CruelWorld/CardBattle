/* finished at 16/2/8. */
/* by YanYifan at SEU*/
#pragma once
#include"cocos2d.h"
USING_NS_CC;

#define BOARD_DECORATIONS_MAXSIZE 4 

/*
*@BoardDecoration 
*@brief the node use to decorate the chessboard,and it cannot be operated currently.
*But it maybe respond to player's operator.
*/
class BoardDecoration :public Node
{
public:
	static BoardDecoration *create(int DecorationID);
};

/*
*@BoardBG
*@brief background.
*it is composed by a bg and decorations.
*/
class BoardBG:public Node
{
public:
	virtual void onEnter()override;
	/**@addDecoration:����屳����������װ��.
	*@decorationID:װ����ID.
	*@posX,@posY:װ�����λ��.
	*#0<posX,posY<1
	*/
	bool addDecoration(int decorationID,float posX=0,float posY=0);
	/**@getDecoration:��ȡװ����.
	*@decorationID:װ����ID.
	*/
	BoardDecoration* getDecoration(int decorationID);
private:
	Sprite *_mainbg;  //������        //UNFINISHED:��ͼ������
	BoardDecoration *_decoration[BOARD_DECORATIONS_MAXSIZE]; //װ��������
	int _curDecoration; //��ǰװ��������
};