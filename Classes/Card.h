#pragma once
#include<vector>
#include"cocos2d.h"
#include"string.h"
using namespace std;
USING_NS_CC;

/*get,set������*/
#ifndef MEM_GET_SET
#define MEM_GET_SET(member,member_type) \
	member_type get##member(){return member;} \
	void set##member(member_type value){ this->member = value; }
#endif


/*
*@CCard
*@brief:�洢��������.
*@��̬
*5���Ƶ���̬
*�ƿ� ���� ���� Ĺ�� �Լ�װ�� 0-1-2-3-4 state����״̬
*@��Ӫ
camp:����ƵĹ��� 0-1-2 �ѷ� �з� ����
*@�������� 
*health attack cost
*@����
type:��� ���� ���� ���� 0-1-2-3
*@ְҵ
*get_profession()
*@Ʒ��
*quality 0-1-2-3-4 �� �� �� ��
*@ID 
*��CPP
*@�Ƶ�λ��
Pos:0-4
*/
class CCard
{
	/****************************************************��ʼ��********************************************/
public:
	CCard();
	CCard(int ID);
	~CCard();
	void cardCreate(int ID);
	/****************************************************get/set����********************************************/
public:
	/*��ȡս��ʱ�������ּӳɺ�Ĺ���*/
	int getFinalAttack();
	/*��ȡս��ʱ�������ּӳɺ��Ѫ��*/
	int getFinalHealth();
	/*��ȡս��ʱ�������ּӳɺ�ķ���*/
	int getFinalCost();
	//���BUFF
	void getBuff(int health_change, int attack_change);
	//����
	void damaged(int x);
	//�ظ�����ֵ
	int heal(int x);
	//�������
	bool isDead();

	//���spell ������
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
	/****************************************************��������********************************************/
private:
	int _cardID;
	int  _cost, _attack, _health ; //��ʼ����/��ʼ����/��ʼѪ��
	std::string _cardName, _cardDescribe;
	int _type, _profession, _quality;//��ʼ����/��ʼְҵ/��ʼƷ��
	std::string _cardPath;
	/****************************************************��������********************************************/
private:
	int _armor; //����_armor
	vector<int>_spellID, _buffID, _descID;
private:
	int _pos; //��ս���ϵ�λ��
	int _state, _camp;//״̬/��Ӫ
	int _costBattle,_attackBattle, _healthBattle;	//ս��ʱʵ�ʷ���/����/����
	int _costBuff, _attackBuff, _healthBuff;//ʵʱbuff����Ѫ��
	bool _isAttack;				//��ʾ�Ƿ��Ѿ�������
	bool _canAttack;			//��ʾ��һ�غ��ܲ����ж�
	int _place; //?????
	int _healthMax;//????

};
