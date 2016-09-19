#pragma once
//#include"Battle.h"
#include<vector>
using namespace std;
class CBattle;
class CCard;

class CAIEnemy//:public Node
{
public:
	CAIEnemy(CBattle*);
	~CAIEnemy();
	CBattle* bat;
	float AiTurn();
	void AiCummom();
	void AiAttack();
	bool AiCummon(int);
	void AiAttackTo(int num1, int num2, int s1, int s2);

	float calcValue(int, int);
	void find(int, int, int);
	/*
	void Turning();//ai回合
	bool AICardUse(vector<CCard>&card);//ai使用卡牌
	void AICheckAttack();
	void AICardAttack(vector<CCard>&card,CCard &beAttCard);//ai攻击随从
	int Value_Mode[10], Mode;
	double Value(CCard &card);
	double Value_EXMin(CCard &card, vector<CCard>&cardT);
	double Value_Spell(CCard &card);
	vector<CCard> Value_Cost();
	bool KO();
	bool KO(CBattle *player);
	*/
	vector<int> dp(vector<int>&p, vector<int>&v, int m, vector<CCard> &card);
	bool place[5];
	vector<int> _atkCard;
	int _atkF[5];
	int setPlace();
	float delayTime;	
};

