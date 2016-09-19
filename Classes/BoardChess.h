#pragma once
#include"cocos2d.h"
USING_NS_CC;

#define CAMP_FRIEND 0      //�ѷ�
#define CAMP_ENEMY  1      //�ж�
#define CAMP_NEUTRALITY 2  //������Ұ��
#define CAMP_UNDEFINE   3  //δ����

/*
*@Chess
*@brief Ϊ��������ж���ĸ���,�ṩ��һЩ���Եķ���
*��������������Ԫ�صĹ��Է����ͱ�����������
*/
class BoardChess :public Node
{
public:
	virtual void onEnter()override;
	void setCamp(int campID);
	int getCamp();
	int getID();

	virtual void turnSide();//��ת
	
	virtual void displayDescription();
	virtual void hideDescription();
protected:
	virtual void turnSideCallback();
	int _chessID;
	int _camp; //��Ӫ
	Sprite* _face;
	Sprite* _back;
	Sprite* _face2;
	Sprite* _description;
};

