#pragma once
#include<vector>
#include"Card.h"
#include"GameBoard.h"


using namespace std;

class CAIEnemy;

enum GameState{
	GAME_BEGIN,
	GAME_RUN,  //自己的回合
	GAME_WAIT, //对方的回合
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
	战斗流程
		游戏开始-准备牌库-抽初始牌
		游戏中
		游戏结束
	*/
	CBattle *_enemy;//传递对面战斗类的指针

	void GameStart();
	void GameOver();
	void Gaming();


	/*
	基础流程 ##
		回合开始（）-水晶增加-充满水晶-抽牌

		检测
		随从检测死亡-移除
		英雄检测死亡-移除 to be writen
		

		抽牌
		随从攻击
		召唤随从
		异能
		回合结束
	*/
	/*
	*/
	void TurnStart();
	void TurnOver();

	virtual void Turning();

	void ActionChange(int num);
	vector<CCard>& CheckPosition(CCard &card);//检测牌的位置


	void DrawCard();//抽牌
	//void DrawCard(vector<CCardinHand> &cardIH, vector<CCardinDeck> &cardID);
	//void CardAttack(CCard &creAttack, CCard &creBeattacked);	//随从间的攻击
//	void CardAttack(CCard &creAttack);							//随从攻击英雄
	void cardAttack(int srcNum, int srcCamp, int destNum, int destCamp);
	void CardAttack(int num);							//随从攻击英雄 重载+1

	void RoleAttack();											//英雄攻击英雄
	void RoleAttack(CCard &creBeattacked);						//英雄攻击随从
	//void CreatureCommon(CCard card, vector<CCardinBattlefield> cardIB);//由引用构造
	void CardCummon(vector<CCard>&card1, vector<CCard>&card2, int num1, int num2,int battlePlace=0);//召唤
	//void CardTranslate(vector<CCard>&card1, vector<CCard>&card2, int num1,int num2);//传递卡牌 1为原来 2为传递之后 num为序列
	//void CardTranslate(CCard &card, vector<CCard>&card2, int num2);
	void cardTransfer(int srcPool,int destPool, int srcNum, int destNum,int battlePlace=0);


	void CardDead(int num);
	//void CardDead(CCard &card);
	//void CardDeadE(CCard &card);

	void Check();//检测所有发生事件后续
	void CheckDead();


	void SpellCheck();
	//技能发动共分几个时段 回合开始00 回合结束01 召唤02 死亡03
	void SpellCheck(int sTime);
	void SpellCheck(CCard &card, int sTime);
	void SpellCheckPlayer(int sTime);
	void SpellCheckEnemy(int sTime);
	void Spelling(int spell_num);//发动技能 技能ID号
	bool Spelling(int spell_num, CCard &card1);


	int getCardPos(int cardPool,CCard &card);//获取card在数组中的位置,没有则返回-1
	//void CreatureDead(CCardinBattlefield &creature);
	void CreatureDead(CCard &card);
	bool HeroIsDead();
	/*
	成员变量 vector类
	牌库的牌 手牌 场地 墓地
	*/
//	vector<CCard>CinBattle, CinHand, CinDeck, CinCeme;
	/*下标可以为POOL_HAND,POOL_DECK,POOL_CEME,POOL_BATTLE*/
	vector<CCard> _cardPool[4];

	BoardRole *_hero;
	int ActionPoints,ActPtsMax;//行动点数及最大值


	int *_battleID;				// 用于储存交互用的ID地址
	bool *_battleState;			// 用户信息响应的标志
	GameState _gameState;  //判断游戏进行状态


	void update(float dt);

	GameBoard *_gameboard;
	int _camp;
	int *_cardIds;
	

};