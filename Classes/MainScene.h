#ifndef MAINSCENE_H
#define MAINSCENE_H
#include"HelloWorldScene.h"

//3D part
/*
#include"Map.h"
#include"NPC.h"
#include"Head2D.h"
#include"GameUI.h"
#include"Trigger.h";
*///2D part
#include"TextCartoon.h"
#include"GameBoard.h"
#include"Tool2D.h"
#include"Battle.h"
#define CL(__className__) [](){ return __className__::create();}

class MyScene :public cocos2d::Scene
{

public:
	MyScene();
	~MyScene();
	virtual void run();
};
//
//class MyDemo:public Layer
//{
//public:
//	Size s;     //*winsize
//	Sprite3D* sprite;
//	bool mb_move[4];
//	int fieldofView;
//public:
//
//	virtual void onEnter() override;
//	virtual void onExit() override;
//
//	void helloworldCallback(Ref* sender);
//	
//	void restartCallback(Ref* sender);
//	void nextCallback(Ref* sender, TouchEventType type);
//	void backCallback(Ref* sender);
//
//	void createWorld3D();
//	void createUI();
//	/*let the camera for 3D feature zoom in to the target npc*/
//	bool zoomInCamera(Unit* npc);
//	/*let the camera for 3D feature zoom out the target npc*/
//	bool zoomOutCamera();
//
//	bool onTouchBegan(Touch* touch, Event*event);
//	void onTouchMoved(Touch* touch, Event* event);
//	void onTouchEnd(Touch*, Event*);
//	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
//	void onTouchesEnd(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
//
//	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)override; //键盘事件响应
//	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)override; //键盘事件响应
//
//	/**实时更新*/
//	void update(float dt);   
//
//	bool iscollision(Node* mySprite, Node* testSprite);//碰撞检测
//	bool iscollision(Vec2* point,Sprite3D* TarSprite);
//protected:
//
//	//在onEnter中初始化
//	std::vector<Camera *> _camera;
//
//	CGameUI *_ui;
//	Node _worldscene;
//	Map3D *_map;
//	Trigger *_trigger;
//	/*Player *_player;*/
//	//EffectSprite3D * _monster;
//	//NPC *_npc1,*_npc2;
//	Head2D _head2D;
//	bool m_key_Q, m_key_A, m_key_W, m_key_S, m_key_Z, m_key_X, m_key_R, m_key_F;
//
//	Effect3DOutline *_chosenEffect;
//
//	
//	
//};
//
//
//
//
//
//
//
//
//
//
//class MyLayer1 :public MyDemo
//{
//public:
//	virtual void onEnter() override;
//	virtual void onExit() override;
//	CREATE_FUNC(MyLayer1);
//};

class MyLayer2 :public Layer//改成Layer
{
public:
	virtual void onEnter() override;
	CREATE_FUNC(MyLayer2);
private:
	GameBoard *_gameBoard;
	BattleTool2D *_tool;
	CBattle *_battles[2];

	int _battleID[2];
	bool _battleState[2];
};
#endif