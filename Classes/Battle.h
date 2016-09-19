#pragma once
#include<vector>
#include"Card.h"
#include"GameBoard.h"


using namespace std;

class CAIEnemy;

enum GameState{
	GAME_BEGIN,
	GAME_RUN,  //�Լ��Ļغ�
	GAME_WAIT, //�Է��Ļغ�
	GAME_WIN,
	GAME_LOSE
};

class CBattle: public cocos2d::Node
{
public:
	CBattle(GameBoard *gameboard, int *battleID, bool * battleState,int *cardId,int camp);
	~CBattle();

	CAIEnemy* ai;

	void setEnemy(CBattle*enemy);
	/*
	ս������
		��Ϸ��ʼ-׼���ƿ�-���ʼ��
		��Ϸ��
		��Ϸ����
	*/
	CBattle *_enemy;//���ݶ���ս�����ָ��

	void GameStart();
	void GameOver();
	void Gaming();


	/*
	�������� ##
		�غϿ�ʼ����-ˮ������-����ˮ��-����

		���
		��Ӽ������-�Ƴ�
		Ӣ�ۼ������-�Ƴ� to be writen
		

		����
		��ӹ���
		�ٻ����
		����
		�غϽ���
	*/
	/*
	*/
	void TurnStart();
	void TurnOver();

	virtual void Turning();

	void ActionChange(int num);
	vector<CCard>& CheckPosition(CCard &card);//����Ƶ�λ��


	void DrawCard();//����
	//void DrawCard(vector<CCardinHand> &cardIH, vector<CCardinDeck> &cardID);
	//void CardAttack(CCard &creAttack, CCard &creBeattacked);	//��Ӽ�Ĺ���
//	void CardAttack(CCard &creAttack);							//��ӹ���Ӣ��
	void cardAttack(int srcNum, int srcCamp, int destNum, int destCamp);
	void CardAttack(int num);							//��ӹ���Ӣ�� ����+1

	void RoleAttack();											//Ӣ�۹���Ӣ��
	void RoleAttack(CCard &creBeattacked);						//Ӣ�۹������
	//void CreatureCommon(CCard card, vector<CCardinBattlefield> cardIB);//�����ù���
	void CardCummon(vector<CCard>&card1, vector<CCard>&card2, int num1, int num2,int battlePlace=0);//�ٻ�
	//void CardTranslate(vector<CCard>&card1, vector<CCard>&card2, int num1,int num2);//���ݿ��� 1Ϊԭ�� 2Ϊ����֮�� numΪ����
	//void CardTranslate(CCard &card, vector<CCard>&card2, int num2);
	void cardTransfer(int srcPool,int destPool, int srcNum, int destNum,int battlePlace=0);


	void CardDead(int num);
	//void CardDead(CCard &card);
	//void CardDeadE(CCard &card);

	void Check();//������з����¼�����
	void CheckDead();


	void SpellCheck();
	//���ܷ������ּ���ʱ�� �غϿ�ʼ00 �غϽ���01 �ٻ�02 ����03
	void SpellCheck(int sTime);
	void SpellCheck(CCard &card, int sTime);
	void SpellCheckPlayer(int sTime);
	void SpellCheckEnemy(int sTime);
	void Spelling(int spell_num);//�������� ����ID��
	bool Spelling(int spell_num, CCard &card1);


	int getCardPos(int cardPool,CCard &card);//��ȡcard�������е�λ��,û���򷵻�-1
	//void CreatureDead(CCardinBattlefield &creature);
	void CreatureDead(CCard &card);
	bool HeroIsDead();
	/*
	��Ա���� vector��
	�ƿ���� ���� ���� Ĺ��
	*/
//	vector<CCard>CinBattle, CinHand, CinDeck, CinCeme;
	/*�±����ΪPOOL_HAND,POOL_DECK,POOL_CEME,POOL_BATTLE*/
	vector<CCard> _cardPool[4];

	BoardRole *_hero;
	int ActionPoints,ActPtsMax;//�ж����������ֵ


	int *_battleID;				// ���ڴ��潻���õ�ID��ַ
	bool *_battleState;			// �û���Ϣ��Ӧ�ı�־
	GameState _gameState;  //�ж���Ϸ����״̬


	void update(float dt);

	GameBoard *_gameboard;
	int _camp;
	int *_cardIds;
	

};