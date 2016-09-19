#pragma once
#include<vector>
#include"cocos2d.h"
#include"string.h"
using namespace std;
USING_NS_CC;

/*get,set函数宏*/
#ifndef MEM_GET_SET
#define MEM_GET_SET(member,member_type) \
	member_type get##member(){return member;} \
	void set##member(member_type value){ this->member = value; }
#endif


/*
*@CCard
*@brief:存储卡牌数据.
*@形态
*5种牌的形态
*牌库 手牌 场地 墓地 以及装备 0-1-2-3-4 state——状态
*@阵营
camp:标记牌的归属 0-1-2 友方 敌方 中立
*@基本属性 
*health attack cost
*@类型
type:随从 法术 武器 道具 0-1-2-3
*@职业
*get_profession()
*@品质
*quality 0-1-2-3-4 白 蓝 紫 橙
*@ID 
*见CPP
*@牌的位置
Pos:0-4
*/
class CCard
{
	/****************************************************初始化********************************************/
public:
	CCard();
	CCard(int ID);
	~CCard();
	void cardCreate(int ID);
	/****************************************************get/set函数********************************************/
public:
	/*获取战斗时经过各种加成后的攻击*/
	int getFinalAttack();
	/*获取战斗时经过各种加成后的血量*/
	int getFinalHealth();
	/*获取战斗时经过各种加成后的费用*/
	int getFinalCost();
	//获得BUFF
	void getBuff(int health_change, int attack_change);
	//受伤
	void damaged(int x);
	//回复生命值
	int heal(int x);
	//死亡检测
	bool isDead();

	//获得spell 待完善
	void getSpell();
	void getBuff(CCard &card, int buffID);

	MEM_GET_SET(_cardID, int);
	MEM_GET_SET(_cost, int);
	MEM_GET_SET(_attack, int);
	MEM_GET_SET(_health, int);
	MEM_GET_SET(_cardName, std::string);
	MEM_GET_SET(_cardDescribe, std::string);
	MEM_GET_SET(_type,int);
	MEM_GET_SET(_profession, int);
	MEM_GET_SET(_quality, int);
	MEM_GET_SET(_cardPath, std::string);
	MEM_GET_SET(_armor, int);
	MEM_GET_SET(_buffID, vector<int>);
	MEM_GET_SET(_spellID, vector<int>);
	MEM_GET_SET(_descID, vector<int>);
	MEM_GET_SET(_state, int);
	MEM_GET_SET(_camp, int);
	MEM_GET_SET(_costBattle, int);
	MEM_GET_SET(_attackBattle, int);
	MEM_GET_SET(_healthBattle, int);
	MEM_GET_SET(_costBuff, int);
	MEM_GET_SET(_attackBuff, int);
	MEM_GET_SET(_healthBuff, int);
	MEM_GET_SET(_isAttack, bool);
	MEM_GET_SET(_canAttack, bool);
	MEM_GET_SET(_place, int);
	MEM_GET_SET(_healthMax, int);
	MEM_GET_SET(_pos, int);
	/****************************************************基本属性********************************************/
private:
	int _cardID;
	int  _cost, _attack, _health ; //初始费用/初始攻击/初始血量
	std::string _cardName, _cardDescribe;
	int _type, _profession, _quality;//初始类型/初始职业/初始品质
	std::string _cardPath;
	/****************************************************特殊属性********************************************/
private:
	int _armor; //护甲_armor
	vector<int>_spellID, _buffID, _descID;
private:
	int _pos; //在战场上的位置
	int _state, _camp;//状态/阵营
	int _costBattle,_attackBattle, _healthBattle;	//战斗时实际费用/攻击/生命
	int _costBuff, _attackBuff, _healthBuff;//实时buff攻击血量
	bool _isAttack;				//表示是否已经攻击过
	bool _canAttack;			//表示第一回合能不能行动
	int _place; //?????
	int _healthMax;//????

};
