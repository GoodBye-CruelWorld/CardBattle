#pragma once
#include "cocos2d.h"
#include"GameBoard.h"
#include "Battle.h"
#include"Card.h"
using std::vector;

using namespace cocos2d::ui;
USING_NS_CC;

#define AIM 0		//�ж��Ƿ���ָ����
#define ATTACK 1	//�ж�����Ƿ��ܹ�����

/*@BeginID/EndID
*@brief:��ʾ������ʼ�������Ӧ����
*@λ��:3λ
*@��λ
*��ʾ�ж�����
*0=��Ч��
*1=�ҷ�����
*2=�з�����
*3=�ҷ����
*4=�з����
*5=Ұ��
*6=�ҷ�Ӣ��
*7=�з�Ӣ��
*8=����Ӣ�ۼ���
*9=�з�Ӣ�ۼ���
*10=����װ����
*11==�з�
*12==�غϽ���
*13=�ҷ��ƿ�
*14=�з��ƿ�
*@ʮλ
*������
*�����ҷ�Ӣ�ۣ�0��1��ʾ�ܷ񹥻������ڻ���ֻ���ܷ񹥻����ڼ������ܺ��������ӣ�
*@��λ
*��ʾ���к�
*0-9��ʾ�������еĵڼ�λ������װ���ȷ��صڼ�����
*/
/*@BattleID
*@brief:������battle��ͨ��
*@λ��:8λ
*@��ʽ:
����      ʹ����λ��     Ŀ��λ��  ����ָ����Ŀ��λ��Ϊ00 0��
����      ����   ��      ����   ��
*@���ͣ�
*����ٻ�                01
*����װ���ȵ���          02
*����					03
*����					04

*@λ��:
��������ʾ������   ������ʾ�ڼ����ƣ�����λ�ã���
*@����
*01������
*02���ҷ����
*03���з����
*04��Ұ��
*05���ҷ�Ӣ��
*06���з�Ӣ��
*07���ҷ�����
*/



/*@BattleTool2D
*@brief:�������û�����Ϊ---����Ϸ��彻���Լ��ʹ��û�ָ��.
*/
class BattleTool2D : public cocos2d::Node
{
	/***************************************************����������ʼ��********************************************/
public:
	BattleTool2D(GameBoard * gameboard, CBattle* battleMy, CBattle* battleIt, int *battleID, bool *battleState);
	virtual void onEnter() override;
	/*****************************************************�������************************************************/
public:
	/**@onTouchBegan:��������ʼ
	*/
	bool onTouchBegan(Touch* touch, Event* event);
	/**@onTouchBegan:�������ƶ�
	*/
	void onTouchMoved(Touch* touch, Event* event);
	/**@onTouchBegan:����������
	*/
	void onTouchEnded(Touch* touch, Event* event);
	/*****************************************************˽�з���************************************************/
private:
	/**@collisionCheck:��ײ���
	*@p:������
	*@node:������ײ������
	*@return:true=��ײ,false=δ��ײ
	*/
	bool collisionCheck(Point p, Node *node);
	int judgeTouchPoint(cocos2d::Point tp, int PartID);
	int judgeCard(CCard *_card, int JudgeType);//�жϿ��Ƶ�һЩ����

	//��������
	/*�����ж��Ƿ񵥻�һ�£������ǳ�ʱ�䰴ס*/
	void resetOneTouch(float dt);	
	/*������ʾ���ܵ�����*/
	void disSkilldiscribe(float dt);					


	bool judgePointIn(Vec2 p, Vec2 p0);
	int judgePointIn(Vec2 p, Vec2 p0, Vec2 p1, Vec2 p2);
	int judgePointIn(Vec2 p, Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3);

	/*****************************************************��Ա����************************************************/
private:
	bool *_battleState;			// �û���Ϣ��Ӧ�ı�־
	int *_battleID;				//������battle��ͨ�ŵ�battleID��ָ��,��׼����ͨ��ʱ��ʹ��
private:
	GameBoard * _gameboard;     //���ָ��
	CBattle	*_battleMy,*_battleIt; //ս�����̶���ָ��
private:
	int _beginID, _endID;		//��ʾ������ʼ�������Ӧ����
	int _t_battleID;			//battleID���ڲ�����
	bool _mouseDown;			//�ж���up����down
	int _sight;					//�ж��Ƿ�����ĳ�׼�ǣ���������������ƶ���1Ϊ��׼�ǣ�2Ϊ����������ƶ�
	bool _isOneTouch;			//�����ж��Ƿ񵥻�һ�£������ǳ�ʱ�䰴ס
	int _roleWord;				//�����ж��Ƿ��Ѿ�����һ��Ӣ�ۣ���������ѡ��,1��ʾ�ҷ�Ӣ�۱��飬2��ʾ�з�Ӣ�۱���
	Sprite* _mouseSprite;		//ʹ��ָ���Կ���ʱ���ı仯
	BoardCard* _cardSel;		//��ѡ�еĿ���
};

