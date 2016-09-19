#pragma once
#include "cocos2d.h"
#include"GameBoard.h"
#include "Battle.h"
#include"Card.h"
using std::vector;

using namespace cocos2d::ui;
USING_NS_CC;

#define AIM 0		//判断是否是指向性
#define ATTACK 1	//判断随从是否能够攻击

/*@BeginID/EndID
*@brief:表示触摸开始与结束对应含义
*@位数:3位
*@百位
*表示判定区域
*0=无效区
*1=我方手牌
*2=敌方手牌
*3=我方随从
*4=敌方随从
*5=野怪
*6=我方英雄
*7=敌方英雄
*8=己方英雄技能
*9=敌方英雄技能
*10=己方装备区
*11==敌方
*12==回合结束
*13=我方牌库
*14=敌方牌库
*@十位
*表类型
*若是我方英雄，0，1表示能否攻击（现在基本只有能否攻击，在加入异能后另行增加）
*@个位
*表示序列号
*0-9表示在数组中的第几位（技能装备等返回第几个）
*/
/*@BattleID
*@brief:负责与battle的通信
*@位数:8位
*@格式:
类型      使用牌位置     目标位置  （非指向性目标位置为00 0）
××      ××   ×      ××   ×
*@类型：
*随从召唤                01
*法术装备等道具          02
*技能					03
*攻击					04

*@位置:
××（表示大区域）   ×（表示第几张牌（数组位置））
*@区域：
*01：手牌
*02：我方随从
*03：敌方随从
*04：野怪
*05：我方英雄
*06：敌方英雄
*07：我方技能
*/



/*@BattleTool2D
*@brief:负责处理用户的行为---与游戏面板交互以及送达用户指令.
*/
class BattleTool2D : public cocos2d::Node
{
	/***************************************************构造析构初始化********************************************/
public:
	BattleTool2D(GameBoard * gameboard, CBattle* battleMy, CBattle* battleIt, int *battleID, bool *battleState);
	virtual void onEnter() override;
	/*****************************************************触摸检测************************************************/
public:
	/**@onTouchBegan:当触摸开始
	*/
	bool onTouchBegan(Touch* touch, Event* event);
	/**@onTouchBegan:当触摸移动
	*/
	void onTouchMoved(Touch* touch, Event* event);
	/**@onTouchBegan:当触摸结束
	*/
	void onTouchEnded(Touch* touch, Event* event);
	/*****************************************************私有方法************************************************/
private:
	/**@collisionCheck:碰撞检测
	*@p:待检测点
	*@node:可能碰撞的容器
	*@return:true=碰撞,false=未碰撞
	*/
	bool collisionCheck(Point p, Node *node);
	int judgeTouchPoint(cocos2d::Point tp, int PartID);
	int judgeCard(CCard *_card, int JudgeType);//判断卡牌的一些特性

	//辅助函数
	/*用来判断是否单机一下，而不是长时间按住*/
	void resetOneTouch(float dt);	
	/*用来显示技能的描述*/
	void disSkilldiscribe(float dt);					


	bool judgePointIn(Vec2 p, Vec2 p0);
	int judgePointIn(Vec2 p, Vec2 p0, Vec2 p1, Vec2 p2);
	int judgePointIn(Vec2 p, Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3);

	/*****************************************************成员变量************************************************/
private:
	bool *_battleState;			// 用户信息响应的标志
	int *_battleID;				//负责与battle的通信的battleID的指针,当准备好通信时才使用
private:
	GameBoard * _gameboard;     //面板指针
	CBattle	*_battleMy,*_battleIt; //战斗流程对象指针
private:
	int _beginID, _endID;		//表示触摸开始与结束对应含义
	int _t_battleID;			//battleID的内部备份
	bool _mouseDown;			//判断是up还是down
	int _sight;					//判断是否把鼠标改成准星，或是手牌随鼠标移动，1为变准星，2为手牌随鼠标移动
	bool _isOneTouch;			//用来判断是否单机一下，而不是长时间按住
	int _roleWord;				//用来判断是否已经单机一次英雄，弹出表情选项,1表示我方英雄表情，2表示敌方英雄表情
	Sprite* _mouseSprite;		//使用指向性卡牌时鼠标的变化
	BoardCard* _cardSel;		//被选中的卡牌
};

