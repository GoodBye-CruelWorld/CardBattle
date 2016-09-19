//finished at 16/7/26
//by Yan Yifan at SEU

#pragma once
#include"cocos2d.h"
#include"BoardBG.h"
#include"BoardEffect.h"
#include"BoardChess.h"
#include"ActionPointBar.h"
#include"BoardCard.h"
#include"BoardRole.h"
#include"ActionQueue.h"
USING_NS_CC;


#define POOL_DECK 0 //牌库池
#define POOL_HAND 1 //手牌池
#define POOL_BATTLE 2 //战斗池
#define POOL_CEME 3 //墓地池
/*
*@GameBoard
*@brief 游戏面板类主要负责有关游戏的显示.
*composed by six part:BG,Effect,Role,ActionPointBar,Card,AnimationManager.
*/
class GameBoard:public Node
{
	/****************************************************初始化********************************************/
public:
	GameBoard();
	virtual void onEnter()override;

	/****************************************************get接口********************************************/
public:
	/**@getCard:获取面板卡牌对象.
	*@cardPool:目标卡牌池.
	*@num:目标位置.
	*@camp 目标阵营.
	*/
	BoardCard *getCard(int cardPool, int num, int camp);

	/**@getBG:获取游戏背景,装饰物加在背景之上.
	*用于玩家与背景\装饰物的交互.
	*/
	BoardBG *getBG();

	/*@getEffect:获取游戏特效.
	*使用addEffect可以为棋盘中任意元素添加视觉特效.
	*/
	BoardEffect *getEffect();

	/**@getRole():获取角色.
	*可访问角色类的接口.
	*@camp:0=己方角色,1=对方角色.
	*/
	BoardRole *getRole(int camp);

	/**@getActionPointBar():获取行动点数条
	*可访问行动点数条类的接口
	*@camp:0=己方角色,1=对方角色.
	*/
	ActionPointBar *getActionPointBar(int camp);

	/**@getActionQueue():获取动作序列管理类
	*可访问动作序列管理类的接口
	*/
	ActionQueue *getActionQueue();
	/**@getSize():获取游戏面板大小
	*@return:Size--一个二位向量
	*/
	Size getSize();

	/************************************************与战斗流程有关的方法集****************************************/
public:
	/*当游戏开始时,面板的特效与动画*/
	void gameBegin();
	/*当游戏胜利时,面板的特效与动画*/
	void gameWin();
	/*当游戏失败时,面板的特效与动画*/
	void gameLose();
	/*当玩家回合开始时,面板的特效与动画*/
	void startPlayerTurn();
	/*当对方回合开始时,面板的特效与动画*/
	void startAiTurn();

	/************************************************与BoardCard有关的方法集****************************************/
public:
	/**@cardTransfer
	*将原卡牌向量中的第SrcOrder张牌转移到另一个卡牌向量的第DestOrder这个位置
	*@srcPool:原卡牌所在牌池
	*@destPool:目标卡牌池
	*@srcOrder:原卡牌在原牌池的位置
	*@destOrder:目标卡牌池的目标位置
	*@srcCamp:原卡牌池的阵营
	*@card:新建的CCard对象
	*@battlePlace:当目标卡牌池为战斗池时,需要一个战斗位置(0~4),其余情况无用
	*/
	void cardTransfer(int srcPool, int destPool, int srcOrder, int destOrder, int srcCamp,CCard &card,int battlePlace=0);//UNFINISHED:增加destCamp

	/**@addCard:在目标卡牌池的第num这个位置上新增一张牌.
	*@card:新建的CCard对象
	*@destPool:目标卡牌池
	*@num:目标位置
	*@camp:目标阵营
	*@delay:延迟执行时间
	*#addCard是凭空产生卡牌,与cardTransfer不同.
	*/
	void addCard(CCard &card, int destPool,int num,int camp,float delay=0.f);//UNFINISHED:只制作了在牌库池新增卡牌的动画：差手牌,战斗,墓地.

	/**@addCard:在目标卡牌池的第DestOrder这个位置上删除一张牌.
	*@destPool:目标卡牌池
	*@num:目标位置
	*@camp:目标阵营
	*@delay:延迟执行时间
	*/
	void removeCard(int destPool, int num, int camp = 0, float delay =0.f);


	/**@selectCard：某张牌被选中产生的显示上的变化.
	*@cardPool:目标卡牌池.
	*@num:目标位置.
	*/
	void selectCard(int cardPool,int num);

	/**@setCardOraginState:使选中的牌恢复原状态.
	*/
	void setCardOraginState();

	/**@showCardDescribe:显示卡牌信息.
	*@cardPool:目标卡牌池.
	*@num:目标位置.
	*/
	void showCardDescribe(int cardPool ,int num);//

	/**@cardAttack:集成的攻击函数.
	*@srcOrder 攻击方在战斗池的位置.
	*@srcCamp 攻击方的阵营.
	*@srcHealth 攻击方攻击完后的生命值
	*@destOrder 被攻击方在战斗池的位置.
	*@destCamp 被攻击方的阵营.
	*@srcHealth 被攻击方攻击完后的生命值
	*#hero Order=-1时代表hero.
	*/
	void cardAttack(int srcOrder, int srcCamp,int srcHealth ,int destOrder, int destCamp,int destHealth);




	/************************************************私有方法****************************************/
private:
	/*调整指定牌池的所有牌的位置*/
	void adjustPool(int CardPool,int camp,int delay);
	/*初始化角色*/
	void initRole(int RoleID, int camp/*,Library library*/);    //UNFINISHED:使用数据库

	void addCardCallBack(CCard &card, int destPool, int num, int camp);
	void cardTransferCallBack(int srcPool, int destPool, int srcOrder, int destOrder, int srcCamp, CCard &card, int battlePlace);//UNFINISHED:增加destCamp
	void cardAttackCallBack(int srcOrder, int srcCamp, int srcHealth, int destOrder, int destCamp, int destHealth);
	/************************************************成员变量****************************************/
	/*成员对象*/
private:
	Size _size;            //棋盘大小
	BoardBG *_bg;		   //棋盘的背景，包括主背景和装饰物
	BoardEffect *_effect;  //负责为棋盘添加各种特效，可同时添加多个特效
	ActionPointBar *_actionPointBar[2]; //0表示己方，1表示敌方
	BoardRole *_role[2]; //0表示己方，1表示敌方
	Sprite*_winbg, *_losebg;//胜利与失败的背景
	ActionQueue*_actionQueue;
	Vector<BoardCard*>_cardPools[8];/*8个卡牌显示类的数组*/
public:
	/*回合结束按钮*/
	Button *_endTurnButton;
	/*上一次操作属性*/
private:
	int _oNum; //原先牌在数组的位置
	float _oRotation, _oScale;//原先牌的角度与缩放
	Vec2 _oPos;//原先牌的位置

};