#pragma once
#include"cocos2d.h"
USING_NS_CC;

/*��ЧĬ�ϳ���ʱ��*/
#define DEFAULT_DURATION 0
/*
*@BoardEffect
*brief a union of effects which can  be used in chessboard,including changes of board,effects manifest on the board.
1.��ͬʱ��Ӷ����Ч
2.��δ������Ч����Ӷ�����������Լ�����
3.��δ�������ʱ�䣬�������Ч����Ĭ�ϳ���ʱ��
*/
class BoardEffect:public Node
{
public:
	virtual void onEnter()override;
	void addEffect(int effectID, float delay=0,float duration = DEFAULT_DURATION, float positionX = 0, float positionY = 0, float positionZ = 0);
	void addEffect(int effectID, Node * target, float delay = 0, float duration = DEFAULT_DURATION, float positionX = 0, float positionY = 0, float positionZ = 0);
private:
	void endCallback(Node* sender); //����Ч�����������������

};