#pragma once
#include"cocos2d.h"
USING_NS_CC;

/*特效默认持续时间*/
#define DEFAULT_DURATION 0
/*
*@BoardEffect
*brief a union of effects which can  be used in chessboard,including changes of board,effects manifest on the board.
1.可同时添加多个特效
2.若未给出特效的添加对象，则添加至自己本身
3.若未定义持续时间，则采用特效本身默认持续时间
*/
class BoardEffect:public Node
{
public:
	virtual void onEnter()override;
	void addEffect(int effectID, float delay=0,float duration = DEFAULT_DURATION, float positionX = 0, float positionY = 0, float positionZ = 0);
	void addEffect(int effectID, Node * target, float delay = 0, float duration = DEFAULT_DURATION, float positionX = 0, float positionY = 0, float positionZ = 0);
private:
	void endCallback(Node* sender); //当特效结束后会调用这个函数

};