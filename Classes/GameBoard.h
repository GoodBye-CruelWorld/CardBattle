//finished at 16/7/26
//by Yan Yifan at SEU

#pragma once
#include"cocos2d.h"
#include"BoardBG.h"
#include"BoardEffect.h"
#include"BoardChess.h"
#include"ActionPointBar.h"
#include"BoardCard.h"
#include"BoardRole.h"
#include"ActionQueue.h"
USING_NS_CC;


#define POOL_DECK 0 //�ƿ��
#define POOL_HAND 1 //���Ƴ�
#define POOL_BATTLE 2 //ս����
#define POOL_CEME 3 //Ĺ�س�
/*
*@GameBoard
*@brief ��Ϸ�������Ҫ�����й���Ϸ����ʾ.
*composed by six part:BG,Effect,Role,ActionPointBar,Card,AnimationManager.
*/
class GameBoard:public Node
{
	/****************************************************��ʼ��********************************************/
public:
	GameBoard();
	virtual void onEnter()override;

	/****************************************************get�ӿ�********************************************/
public:
	/**@getCard:��ȡ��忨�ƶ���.
	*@cardPool:Ŀ�꿨�Ƴ�.
	*@num:Ŀ��λ��.
	*@camp Ŀ����Ӫ.
	*/
	BoardCard *getCard(int cardPool, int num, int camp);

	/**@getBG:��ȡ��Ϸ����,װ������ڱ���֮��.
	*��������뱳��\װ����Ľ���.
	*/
	BoardBG *getBG();

	/*@getEffect:��ȡ��Ϸ��Ч.
	*ʹ��addEffect����Ϊ����������Ԫ������Ӿ���Ч.
	*/
	BoardEffect *getEffect();

	/**@getRole():��ȡ��ɫ.
	*�ɷ��ʽ�ɫ��Ľӿ�.
	*@camp:0=������ɫ,1=�Է���ɫ.
	*/
	BoardRole *getRole(int camp);

	/**@getActionPointBar():��ȡ�ж�������
	*�ɷ����ж���������Ľӿ�
	*@camp:0=������ɫ,1=�Է���ɫ.
	*/
	ActionPointBar *getActionPointBar(int camp);

	/**@getActionQueue():��ȡ�������й�����
	*�ɷ��ʶ������й�����Ľӿ�
	*/
	ActionQueue *getActionQueue();
	/**@getSize():��ȡ��Ϸ����С
	*@return:Size--һ����λ����
	*/
	Size getSize();

	/************************************************��ս�������йصķ�����****************************************/
public:
	/*����Ϸ��ʼʱ,������Ч�붯��*/
	void gameBegin();
	/*����Ϸʤ��ʱ,������Ч�붯��*/
	void gameWin();
	/*����Ϸʧ��ʱ,������Ч�붯��*/
	void gameLose();
	/*����һغϿ�ʼʱ,������Ч�붯��*/
	void startPlayerTurn();
	/*���Է��غϿ�ʼʱ,������Ч�붯��*/
	void startAiTurn();

	/************************************************��BoardCard�йصķ�����****************************************/
public:
	/**@cardTransfer
	*��ԭ���������еĵ�SrcOrder����ת�Ƶ���һ�����������ĵ�DestOrder���λ��
	*@srcPool:ԭ���������Ƴ�
	*@destPool:Ŀ�꿨�Ƴ�
	*@srcOrder:ԭ������ԭ�Ƴص�λ��
	*@destOrder:Ŀ�꿨�Ƴص�Ŀ��λ��
	*@srcCamp:ԭ���Ƴص���Ӫ
	*@card:�½���CCard����
	*@battlePlace:��Ŀ�꿨�Ƴ�Ϊս����ʱ,��Ҫһ��ս��λ��(0~4),�����������
	*/
	void cardTransfer(int srcPool, int destPool, int srcOrder, int destOrder, int srcCamp,CCard &card,int battlePlace=0);//UNFINISHED:����destCamp

	/**@addCard:��Ŀ�꿨�Ƴصĵ�num���λ��������һ����.
	*@card:�½���CCard����
	*@destPool:Ŀ�꿨�Ƴ�
	*@num:Ŀ��λ��
	*@camp:Ŀ����Ӫ
	*@delay:�ӳ�ִ��ʱ��
	*#addCard��ƾ�ղ�������,��cardTransfer��ͬ.
	*/
	void addCard(CCard &card, int destPool,int num,int camp,float delay=0.f);//UNFINISHED:ֻ���������ƿ���������ƵĶ�����������,ս��,Ĺ��.

	/**@addCard:��Ŀ�꿨�Ƴصĵ�DestOrder���λ����ɾ��һ����.
	*@destPool:Ŀ�꿨�Ƴ�
	*@num:Ŀ��λ��
	*@camp:Ŀ����Ӫ
	*@delay:�ӳ�ִ��ʱ��
	*/
	void removeCard(int destPool, int num, int camp = 0, float delay =0.f);


	/**@selectCard��ĳ���Ʊ�ѡ�в�������ʾ�ϵı仯.
	*@cardPool:Ŀ�꿨�Ƴ�.
	*@num:Ŀ��λ��.
	*/
	void selectCard(int cardPool,int num);

	/**@setCardOraginState:ʹѡ�е��ƻָ�ԭ״̬.
	*/
	void setCardOraginState();

	/**@showCardDescribe:��ʾ������Ϣ.
	*@cardPool:Ŀ�꿨�Ƴ�.
	*@num:Ŀ��λ��.
	*/
	void showCardDescribe(int cardPool ,int num);//

	/**@cardAttack:���ɵĹ�������.
	*@srcOrder ��������ս���ص�λ��.
	*@srcCamp ����������Ӫ.
	*@srcHealth ������������������ֵ
	*@destOrder ����������ս���ص�λ��.
	*@destCamp ������������Ӫ.
	*@srcHealth ��������������������ֵ
	*#hero Order=-1ʱ����hero.
	*/
	void cardAttack(int srcOrder, int srcCamp,int srcHealth ,int destOrder, int destCamp,int destHealth);




	/************************************************˽�з���****************************************/
private:
	/*����ָ���Ƴص������Ƶ�λ��*/
	void adjustPool(int CardPool,int camp,int delay);
	/*��ʼ����ɫ*/
	void initRole(int RoleID, int camp/*,Library library*/);    //UNFINISHED:ʹ�����ݿ�

	void addCardCallBack(CCard &card, int destPool, int num, int camp);
	void cardTransferCallBack(int srcPool, int destPool, int srcOrder, int destOrder, int srcCamp, CCard &card, int battlePlace);//UNFINISHED:����destCamp
	void cardAttackCallBack(int srcOrder, int srcCamp, int srcHealth, int destOrder, int destCamp, int destHealth);
	/************************************************��Ա����****************************************/
	/*��Ա����*/
private:
	Size _size;            //���̴�С
	BoardBG *_bg;		   //���̵ı�����������������װ����
	BoardEffect *_effect;  //����Ϊ������Ӹ�����Ч����ͬʱ��Ӷ����Ч
	ActionPointBar *_actionPointBar[2]; //0��ʾ������1��ʾ�з�
	BoardRole *_role[2]; //0��ʾ������1��ʾ�з�
	Sprite*_winbg, *_losebg;//ʤ����ʧ�ܵı���
	ActionQueue*_actionQueue;
	Vector<BoardCard*>_cardPools[8];/*8��������ʾ�������*/
public:
	/*�غϽ�����ť*/
	Button *_endTurnButton;
	/*��һ�β�������*/
private:
	int _oNum; //ԭ�����������λ��
	float _oRotation, _oScale;//ԭ���ƵĽǶ�������
	Vec2 _oPos;//ԭ���Ƶ�λ��

};