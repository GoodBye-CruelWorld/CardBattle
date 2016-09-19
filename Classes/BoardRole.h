#pragma once
#include"BoardChess.h"
#include "ui/CocosGUI.h"
#include"Card.h"
using namespace ui;


//��ɫͷ��
class RolePhote :public BoardChess
{
public:
	virtual void onEnter()override;
	static RolePhote*create(int RoleID/*,GameLibrary *_library*/);
	
	void explode();  //ͷ��ը������i choose death
	float attack(float posX, float posY); //��Ӣ�۹�������ͷ���ƶ���,ע��ͷ���attack��������use�������Ƿֿ��ģ���������������Ҫ����
	float attack(Vec2 Pos);
	

	void setWordChoicesVisible(bool visible);  //���á����ѡ�񡯵Ŀɼ����ɼ�
	void speakWord(int num); //˵����num����ڼ������
private:
	void initwords();  //��ʼ�����ѡ���˵�����
	void speakWordCallBack();
private:

	Sprite *_phote;   //ͷ��
	Sprite *_wordChoices[4];  //���ѡ��
	Sprite *_wordSpeak[4];    //˵�����
	int _wordSpeakOnScreen;
	//GameLibrary _library //���ݿ�
};


//��ɫ����
class RoleSkill :public BoardChess
{
public:
	virtual void onEnter()override;
	static RoleSkill*create(int SkillID/*,GameLibrary *_library*/);
	
	void useSkill();   //ʹ�ü���
	bool IsUsed();	   //�Ƿ���ʹ��
	void resetSkillUsable();  //ʹ���ܿ�ʹ�ã�һ��������������һ�غϿ�ʼʱ����


	void changeSkill(int SkillID);   //�ı似�ܣ�ͬʱ����_isUsedΪfalse


	void setCost(int cost);
	int	 getCost();

private:
	void changeSkillCallback();
private:

	int _cost;
	bool _isUsed;   //�ж��Ƿ�����ʹ��

	//GameLibrary _library //���ݿ�
};

//��ɫ����
class RoleWeapon :public BoardChess
{
public:
	virtual void onEnter()override;
	static RoleWeapon*create(CCard/*CBattleCard*/ &card);
	static RoleWeapon*create(int WeaponID/*,GameLibrary *_library*/);
	void broken(); //ʹ�����𻵣�������

	void useWeapon();//ʹ������
	bool IsUsed();	   //�Ƿ���ʹ��
	void resetWeaponUsable();  //ʹ������ʹ�ã�һ��������������һ�غϿ�ʼʱ����


private:
	Sprite *_weaponFrame;//������

	int _attack;
	int _useTime;
	int _isUsed;
	//GameLibrary _library //���ݿ�
};


//��ɫװ��
class RoleEquip :public BoardChess
{
public:
	virtual void onEnter()override;
	static RoleEquip*create(CCard &card);
	static RoleEquip*create(int EquipID/*,GameLibrary *_library*/);
	void broken(); //ʹ�����𻵣�������

	void useEquip();//ʹ��װ��
	bool IsUsed();	   //�Ƿ���ʹ��
	void resetUsable();  //ʹװ����ʹ�ã�һ��������������һ�غϿ�ʼʱ����


private:
	Sprite *_equipFrame;//װ����

	int _attack;
	int _useTime;  //�;�
	int _isUsed;  //�Ƿ���ʹ��
	
	//GameLibrary _library //���ݿ�
};


/*
*@BoardRole
*@brief �������̵�����ģ��
*1������ͷ��3�����＼�ܣ�1��������3��װ����,������Ѫ�������ף�δд���ȵ�
*/
class BoardRole :public BoardChess
{
public:
	virtual void onEnter()override;
	static BoardRole*create(int RoleID/*,GameLibrary *_library*/);
	RoleSkill* getRoleSkill(int num);
	RolePhote* getRolePhote();
	RoleEquip* getEquip(int num);
	RoleWeapon* getWeapon();

	int getAttack();
	int getHealth();

	void setAttack(int attack);
	void setHealth(int Health,float Delay=0.f);
	
	bool addWeapon(int ID);  //����������������򷵻�1������0
	bool addWeapon(CCard &card);
	bool removeWeapon();

	bool addEquip(int ID,int num);//
	bool addEquip(CCard &card,int num);
	bool removeEquip(int num);

	bool IsWeapon();
	int getCurEquipNum();  //������������
private:
	int _attack;
	int _health;
	int _maxHealth;

	Label*_attackLb;
	Label*_healthLb;

	RolePhote  *_rolePhote;
	RoleSkill  *_roleSkill[3];
	RoleEquip *_roleEquip[3];
	RoleWeapon *_roleWeapon;

	int  _curEquipNum;  //װ������
	bool _isWeapon;     //�Ƿ�������
	//GameLibrary _library //���ݿ�
};