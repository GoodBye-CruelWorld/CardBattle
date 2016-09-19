#pragma once
#include"BoardChess.h"
#include "ui/CocosGUI.h"
#include"Card.h"
using namespace ui;


//角色头像
class RolePhote :public BoardChess
{
public:
	virtual void onEnter()override;
	static RolePhote*create(int RoleID/*,GameLibrary *_library*/);
	
	void explode();  //头像爆炸，代表i choose death
	float attack(float posX, float posY); //令英雄攻击（即头像移动）,注意头像的attack和武器的use的命令是分开的，大多数情况两条都要调用
	float attack(Vec2 Pos);
	

	void setWordChoicesVisible(bool visible);  //设置‘语句选择’的可见不可见
	void speakWord(int num); //说话，num代表第几条语句
private:
	void initwords();  //初始化语句选择和说话语句
	void speakWordCallBack();
private:

	Sprite *_phote;   //头像
	Sprite *_wordChoices[4];  //语句选择
	Sprite *_wordSpeak[4];    //说话语句
	int _wordSpeakOnScreen;
	//GameLibrary _library //数据库
};


//角色技能
class RoleSkill :public BoardChess
{
public:
	virtual void onEnter()override;
	static RoleSkill*create(int SkillID/*,GameLibrary *_library*/);
	
	void useSkill();   //使用技能
	bool IsUsed();	   //是否已使用
	void resetSkillUsable();  //使技能可使用，一般由流程类在下一回合开始时调用


	void changeSkill(int SkillID);   //改变技能，同时重置_isUsed为false


	void setCost(int cost);
	int	 getCost();

private:
	void changeSkillCallback();
private:

	int _cost;
	bool _isUsed;   //判断是否技能已使用

	//GameLibrary _library //数据库
};

//角色武器
class RoleWeapon :public BoardChess
{
public:
	virtual void onEnter()override;
	static RoleWeapon*create(CCard/*CBattleCard*/ &card);
	static RoleWeapon*create(int WeaponID/*,GameLibrary *_library*/);
	void broken(); //使武器损坏，即销毁

	void useWeapon();//使用武器
	bool IsUsed();	   //是否已使用
	void resetWeaponUsable();  //使武器可使用，一般由流程类在下一回合开始时调用


private:
	Sprite *_weaponFrame;//武器框

	int _attack;
	int _useTime;
	int _isUsed;
	//GameLibrary _library //数据库
};


//角色装备
class RoleEquip :public BoardChess
{
public:
	virtual void onEnter()override;
	static RoleEquip*create(CCard &card);
	static RoleEquip*create(int EquipID/*,GameLibrary *_library*/);
	void broken(); //使道具损坏，即销毁

	void useEquip();//使用装备
	bool IsUsed();	   //是否已使用
	void resetUsable();  //使装备可使用，一般由流程类在下一回合开始时调用


private:
	Sprite *_equipFrame;//装备框

	int _attack;
	int _useTime;  //耐久
	int _isUsed;  //是否已使用
	
	//GameLibrary _library //数据库
};


/*
*@BoardRole
*@brief 负责棋盘的人物模块
*1个人物头像，3个人物技能，1个武器框，3个装备框,攻击，血量，护甲（未写）等等
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
	
	bool addWeapon(int ID);  //如果本身有武器，则返回1，否则0
	bool addWeapon(CCard &card);
	bool removeWeapon();

	bool addEquip(int ID,int num);//
	bool addEquip(CCard &card,int num);
	bool removeEquip(int num);

	bool IsWeapon();
	int getCurEquipNum();  //武器不计其内
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

	int  _curEquipNum;  //装备总数
	bool _isWeapon;     //是否有武器
	//GameLibrary _library //数据库
};