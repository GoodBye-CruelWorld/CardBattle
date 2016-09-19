#include "Card.h"


CCard::CCard()
{
}

CCard::CCard(int num)
{
	cardCreate(num);
}

void CCard::cardCreate(int num)
{
	//编号说明 编号为7位 前3位表示职业 3位表示类型 后三位为编号
	/*职业 00战士 01弓箭手 100 为中立 200+为boss 
	类型同前
	*/

	_cardPath = "card/2.png";

	_armor = 0;
	_cardID = num;
	_profession = num / 10000;
	num = num % 1000;
	_type = num % 10;
	if (_profession == 00){
		if (num == 0){
			_health = 3;
			_cardPath = "card/0.png";
			_attack = 4;
			_cost = 2;
			_armor = 1;
			_quality = 0;
			_cardName = "Name00";
			_cardDescribe = "Desc00";
		}
		if (num == 1){
			_cost = 1;
			_attack = 2;
			_health = 3;
			_cardPath = "card/1.png";
			_quality = 0;
			_cardName = "Name01";
			_cardDescribe = "Desc01";
		}
		if (num == 2){
			_cost = 3;
	
			_attack = 3;
			_health = 3;
			_quality = 0;
			_cardName = "Name01";
			_cardDescribe = "Desc01";
			_spellID.push_back(2001102);
		}
		if (num == 3){
			_cost = 5;
			_attack = 4;
			_health = 3;
			_quality = 1;
			_cardName = "巨人战士";
			_cardDescribe = "降临：眩晕一个随从直到你的下个回合开始";
			_spellID.push_back(2102);
		}
		if (num == 4){
			_cost = 6;
			_attack = 7;
			_health = 5;
			_quality = 1;
			_cardName = "英灵";
			_cardDescribe = "返场：6";
			_spellID.push_back(6904001);
		}
		if (num ==5){
			_cost = 8;
			_attack = 7;
			_health = 7;
			_quality = 1;
			_cardName = "铁甲武士";
			_cardDescribe = "每个回合结束获得护甲+2";
			_spellID.push_back(2001101);
		}
		if (num == 6){
			_cost = 2;
			_attack = 3;
			_health = 3;
			_quality = 2;
			_cardName = "前线指挥官";
			_cardDescribe = "友方角色每有一点护甲值，获得+1攻击力";
			_spellID.push_back(20099);
		}
		if (num == 7){
			_cost = 4;
			_attack = 5;
			_health = 1;
			_quality = 2;
			_cardName = "铁骑";
			_armor = 5;
			_cardDescribe = "护甲5 攻击反制";
			_spellID.push_back(90004);
		}
		if (num == 8){
			_cost = 11;
			_attack = 10;
			_health = 10;
			_armor = 4;
			_quality = 3;
			_cardName = "战神";
			_cardDescribe = "护甲4 随从豁免 攻击反制";
			_spellID.push_back(90004);
			_spellID.push_back(90199);
		}
		if (num == 1000){
			_cost = 0;
			_quality = 0;
			_cardName = "重返战场";
			_cardDescribe = "回复一名随从所有生命值，并使其获得护甲+1";
		}
		if (num == 1001){
			_cost = 0;
			_quality = 1;
			_cardName = "冲锋";
			_cardDescribe = "抽一张牌，下个回合开始前，英雄获得攻击反制";
		}
		if (num == 1002){
			_cost = 2;
			_quality = 2;
			_cardName = "紧急包扎";
			_cardDescribe = "本回合死亡的随从，回合结束重新返回战场并有1点生命值";
		}
		if (num == 1003){
			_cost = 4;
			_quality = 2;
			_cardName = "战事准备";
			_cardDescribe = "每有一个友方角色有护甲，摸一张牌";
		}
		if (num == 2000){
			_cost = 1;
			_attack = 2;
			_health = 2;
			_quality = 0;
			_cardName = "新手之剑";
			_cardDescribe = "武器";
		}
		if (num == 2001){
			_cost = 3;
			_attack = 4;
			_health = 2;
			_quality = 0;
			_cardName = "精钢剑";
			_cardDescribe = "武器";
		}
		if (num == 2002){
			_cost = 4;
			_attack = 0;
			_health = 3;
			_quality = 1;
			_cardName = "反击装甲";
			_cardDescribe = "回合外英雄获得护甲+1，攻击+1并拥有攻击反制";
		}
		if (num == 2003){
			_cost = 2;
			_attack = 1;
			_health = 2;
			_quality = 2;
			_cardName = "鲜血祭品";
			_cardDescribe = "攻击受伤的随从时，直接消灭";
		}
	}

	
	_healthBuff = 0;
	_healthBattle = _health;
	_attackBuff = 0;
	_attackBattle = _attack;
	_costBattle = _cost;
	_costBuff = 0;
}

CCard::~CCard()
{
}

void CCard::damaged(int x){
	_healthBattle -= (x - 0);
}

int CCard::heal(int x){
	x = (_healthBattle + x > _healthMax) ? _healthMax - _healthBattle : x;
	_healthBattle += x;
	return x;

}

bool CCard::isDead(){
	if (getFinalHealth() <= 0) return true;
	return false;
}

void CCard::getBuff(int _health_change, int _attack_change){
	_healthBattle += _health_change;
	_attackBattle += _attack_change;
}

int CCard::getFinalAttack(){
	return _attackBattle + _attackBuff;
}
int CCard::getFinalHealth(){
	return _healthBattle + _healthBuff;
}
int CCard::getFinalCost(){
	return _costBattle + _costBuff;
}
