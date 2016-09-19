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
	//���˵�� ���Ϊ7λ ǰ3λ��ʾְҵ 3λ��ʾ���� ����λΪ���
	/*ְҵ 00սʿ 01������ 100 Ϊ���� 200+Ϊboss 
	����ͬǰ
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
			_cardName = "����սʿ";
			_cardDescribe = "���٣�ѣ��һ�����ֱ������¸��غϿ�ʼ";
			_spellID.push_back(2102);
		}
		if (num == 4){
			_cost = 6;
			_attack = 7;
			_health = 5;
			_quality = 1;
			_cardName = "Ӣ��";
			_cardDescribe = "������6";
			_spellID.push_back(6904001);
		}
		if (num ==5){
			_cost = 8;
			_attack = 7;
			_health = 7;
			_quality = 1;
			_cardName = "������ʿ";
			_cardDescribe = "ÿ���غϽ�����û���+2";
			_spellID.push_back(2001101);
		}
		if (num == 6){
			_cost = 2;
			_attack = 3;
			_health = 3;
			_quality = 2;
			_cardName = "ǰ��ָ�ӹ�";
			_cardDescribe = "�ѷ���ɫÿ��һ�㻤��ֵ�����+1������";
			_spellID.push_back(20099);
		}
		if (num == 7){
			_cost = 4;
			_attack = 5;
			_health = 1;
			_quality = 2;
			_cardName = "����";
			_armor = 5;
			_cardDescribe = "����5 ��������";
			_spellID.push_back(90004);
		}
		if (num == 8){
			_cost = 11;
			_attack = 10;
			_health = 10;
			_armor = 4;
			_quality = 3;
			_cardName = "ս��";
			_cardDescribe = "����4 ��ӻ��� ��������";
			_spellID.push_back(90004);
			_spellID.push_back(90199);
		}
		if (num == 1000){
			_cost = 0;
			_quality = 0;
			_cardName = "�ط�ս��";
			_cardDescribe = "�ظ�һ�������������ֵ����ʹ���û���+1";
		}
		if (num == 1001){
			_cost = 0;
			_quality = 1;
			_cardName = "���";
			_cardDescribe = "��һ���ƣ��¸��غϿ�ʼǰ��Ӣ�ۻ�ù�������";
		}
		if (num == 1002){
			_cost = 2;
			_quality = 2;
			_cardName = "��������";
			_cardDescribe = "���غ���������ӣ��غϽ������·���ս������1������ֵ";
		}
		if (num == 1003){
			_cost = 4;
			_quality = 2;
			_cardName = "ս��׼��";
			_cardDescribe = "ÿ��һ���ѷ���ɫ�л��ף���һ����";
		}
		if (num == 2000){
			_cost = 1;
			_attack = 2;
			_health = 2;
			_quality = 0;
			_cardName = "����֮��";
			_cardDescribe = "����";
		}
		if (num == 2001){
			_cost = 3;
			_attack = 4;
			_health = 2;
			_quality = 0;
			_cardName = "���ֽ�";
			_cardDescribe = "����";
		}
		if (num == 2002){
			_cost = 4;
			_attack = 0;
			_health = 3;
			_quality = 1;
			_cardName = "����װ��";
			_cardDescribe = "�غ���Ӣ�ۻ�û���+1������+1��ӵ�й�������";
		}
		if (num == 2003){
			_cost = 2;
			_attack = 1;
			_health = 2;
			_quality = 2;
			_cardName = "��Ѫ��Ʒ";
			_cardDescribe = "�������˵����ʱ��ֱ������";
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
