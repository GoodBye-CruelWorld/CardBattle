#pragma once
#include"BoardChess.h"
#include"Card.h"
/*����״̬*/
#define CARD_STATE_STOKE 0  //�������ƿ�
#define CARD_STATE_HAND 1   //����������
#define CARD_STATE_BATTLE 2 //������ս����
#define CARD_STATE_DEAD 3   //������Ĺ��
#define CARD_STATE_UNDEFINE 4 //����״̬δ����
/*
*@BoardCard
*@brief Card in board.�����Ƶ���ʾ
*@״̬:
*���ƿ�� CARD_STATE_STOKE 
*�����Ƴ� CARD_STATE_HAND
*��ս���� CARD_STATE_BATTLE
*��Ĺ�س� CARD_STATE_DEAD
*����	  CARD_STATE_UNDEFINE
*@���ƹ���:
*�ɿ��ƿ��,���Ʒ���ͼƬ1,2,��������
*/
class BoardCard :public BoardChess
{
	friend class GameBoard;
public:
	virtual void onEnter()override;
private:
	//���ݿ�����Ķ�������������
	static BoardCard*create(CCard &card);

	//���ÿ��Ƶ�ǰ����
	void setCurrentHealth(int curhealth);

	//���ÿ��Ƶ�ǰ����
	void setCurrentAttack(int curattack);

	//���ÿ��Ƶ�ǰ����
	void setCurrentCost(int curcost);  
	

	//���Ʊ���Ĭ,ɾȥ��������
	void silent(); 

	//��������,�����ٶ���,��ͬ��die()
	void exploside();  

	//��������,�����ٶ���
	void die();

	//���Ʒ���
	virtual void turnSide();

	//*���ƿ��Ƶ�������Ķ�����Ŀǰд��2�ſ��Ƶ����
	//*��������1s
	float transFromDeckToHand(int PosOrder, int TotalNum, int Camp = 0);
	//�������Ƶ�ս�� ��1s
	float transFromHandToBattle(int PosOrder,int Camp=0); 

	void removeToHand(int posOrder);


	//����
	float attack(Vec2 Position);
	float attackHero(int Dest_Camp);
	float attackCard(int Place, int Dest_Camp);
	float attackCard(BoardCard* Dest_Card);
	//get��set�����������Ժ�																
	//void setAttack(int attcak);
	//int  getAttack();

	void setCardState(int state);
	int getCardState();

	CCard *_card;

	Sprite *_frame;
//private:
	void calculatePosAndAngle(int place,int size,float &angle,float &x,float &y,int camp=0);
private:
	int _state;  //״̬
	Sprite  *_normal,*_battle, *_cardBack;//��ͨ,ս��������
	//int _ID,_attack, _health, _cost;//5������
	//const char*_description;   //����
	Label *_laAttack, *_laHealth, *_laCost, *_laDescription,*_laName;


	void turnSideCallback();
};