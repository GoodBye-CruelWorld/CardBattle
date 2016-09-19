
#include"MainScene.h"

#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCGroupCommand.h"


//
////
////将层按顺序设置，并定义返回，重载，前进的回调函数
////测试用
////
static std::function<Layer*()> createFunctions[] =
{
	//CL(MyLayer1),
	CL(MyLayer2)
};
//
static int sceneIdx = 0;//order of scene
#define MAX_LAYER (sizeof(createFunctions)/sizeof(createFunctions[0]));
//
static Layer*next()
{
	sceneIdx++;
	sceneIdx = sceneIdx%MAX_LAYER;

	auto layer = (createFunctions[sceneIdx])();
	return layer;
}

static Layer*restart()
{
	auto layer = (createFunctions[sceneIdx])();
	return layer;
}

static Layer*back()
{
	sceneIdx--;
	int total = MAX_LAYER;
	sceneIdx = (sceneIdx + total) % MAX_LAYER;

	auto layer = (createFunctions[sceneIdx])();
	return layer;
}
////*************************************************************************
////
////
////MyScene
////
////
////**************************************************************************
//enum GAME_SCENE{
//	SCENE_UI=0,
//	SCENE_WORLD,
//	SCENE_DIALOG,
//	SCENE_OSD,
//	SCENE_COUNT,
//};
//
//enum SCENE_LAYER{
//	LAYER_BACKGROUND = 0,
//	LAYER_DEFAULT,
//	LAYER_MIDDLE,
//	LAYER_TOP,
//	LAYER_COUNT,
//};
//
//enum GAME_CAMERAS_ORDER{
//	CAMERA_WORLD_3D_SKYBOX = 0,
//	CAMERA_WORLD_3D_SCENE,
//	CAMERA_WORLD_3D_FEATURE,//3D世界特写镜头
//	CAMERA_UI_2D,
//	CAMERA_DIALOG_2D_BASE,
//	CAMERA_DIALOG_3D_MODEL,
//	CAMERA_DIALOG_2D_ABOVE,
//	CAMERA_OSD_2D_BASE,
//	CAMERA_OSD_3D_MODEL,
//	CAMERA_OSD_2D_ABOVE,
//	CAMERA_COUNT,
//};
//static const char * s_CameraNames[CAMERA_COUNT] =
//{
//	"World 3D Skybox",
//	"World 3D Scene",
//	"World 3D Feature"
//	"UI 2D",
//	"Dialog 2D Base",
//	"Dialog 3D Model",
//	"Dialog 2D Above",
//	"OSD 2D Base",
//	"OSD 3D Model",
//	"OSD 2D Above"
//};
///** The scenes, located in different position, won't see each other. */
//static Vec3 s_scenePositons[SCENE_COUNT] = {
//	Vec3(0, 0, 0),          //  center  :   UI scene
//	Vec3(0, 10000, 0),      //  top     :   World sub scene
//	Vec3(10000, 0, 0),      //  right   :   Dialog sub scene
//	Vec3(0, -10000, 0),     //  bottom  :   OSD sub scene
//};
//
//static CameraFlag s_CF[LAYER_COUNT] =
//{
//	CameraFlag::USER1,
//	CameraFlag::DEFAULT,
//	CameraFlag::USER3,
//	CameraFlag::USER4,
//};
//static unsigned short s_CM[LAYER_COUNT] =
//{
//	(unsigned short)s_CF[0],
//	(unsigned short)s_CF[1],
//	(unsigned short)s_CF[2],
//	(unsigned short)s_CF[3],
//};
//*************************************************************************
//
//
//MyScene
//
//
//**************************************************************************
MyScene::MyScene()
{
	
}

MyScene::~MyScene()
{

}

void MyScene::run()
{
	sceneIdx = 0;
	addChild(restart());
	Director::getInstance()->replaceScene(this);
}
//*************************************************************************
////
////
////MyDemo
////
////
////**************************************************************************
//void MyDemo::restartCallback(Ref* sender)
//{
//	auto s = new (std::nothrow)MyScene();
//	s->addChild(restart());
//	Director::getInstance()->replaceScene(CCTransitionFade::create(2, s));
//
//}
//
//void MyDemo::backCallback(Ref* sender)
//{
//	auto s = new(std::nothrow)MyScene();
//	s->addChild(back());
//	Director::getInstance()->replaceScene(CCTransitionFade::create(1, s));
//
//}
//
//void MyDemo::nextCallback(Ref* sender, TouchEventType type)
//{
//
//	////预先移除本场景的定时器，以免敌人数量增加后碰撞检测出现bug
//	//unscheduleUpdate();
//	//unscheduleAllSelectors();
//
//	auto s = new(std::nothrow)MyScene();
//	s->addChild(next());
//	Director::getInstance()->replaceScene(CCTransitionFade::create(2, s));
//
//}
//
//
//void MyDemo::helloworldCallback(Ref* sender)
//{
//	sceneIdx = 0;
//	
//	auto l = new HelloWorld();
//	auto scene = l->createScene();
//
//	Director::getInstance()->replaceScene(CCTransitionFade::create(2, scene));
//}
//
//
//void MyDemo::onEnter()
//{
//	Layer::onEnter();
//	
//	m_key_Q = false;
//	m_key_W = false;
//	m_key_A = false;
//	m_key_S = false;
//	m_key_Z = false;
//	m_key_X = false;
//
//
//	fieldofView = 45;
//	_camera.resize(CAMERA_COUNT);
//
//	s= Director::getInstance()->getVisibleSize();
//	Camera *ca = nullptr;
//
//	//创建3D场景，该场景有3个相机
//	
//	auto _worldscene = Node::create();
//
//	//3D天空盒镜头
//	ca = _camera[CAMERA_WORLD_3D_SKYBOX] =
//		Camera::createPerspective(60,
//		s.width / s.height,
//		10,
//		1000);
//	ca->setDepth(CAMERA_WORLD_3D_SKYBOX);
//	ca->setName(s_CameraNames[CAMERA_WORLD_3D_SKYBOX]);
//	ca->setCameraFlag(s_CF[LAYER_BACKGROUND]);
//	ca->setPosition3D(Vec3(0.f, 0.f, 50.f));
//	_worldscene->addChild(ca);
//	// 3D场景镜头
//	ca = _camera[CAMERA_WORLD_3D_SCENE] =
//		Camera::createPerspective(fieldofView,
//		s.width / s.height,
//		0.1,
//		200);
//	ca->setDepth(CAMERA_WORLD_3D_SCENE);
//	ca->setName(s_CameraNames[CAMERA_WORLD_3D_SCENE]);
//
//	_worldscene->addChild(ca);
//
//	//3D特写镜头
//	ca = _camera[CAMERA_WORLD_3D_FEATURE] =
//		Camera::createPerspective(fieldofView,
//		s.width / s.height,
//		0.1,
//		800);
//	ca->setDepth(CAMERA_WORLD_3D_FEATURE);
//	ca->setName(s_CameraNames[CAMERA_WORLD_3D_FEATURE]);
//	ca->setPosition3D(Vec3(0, 650, 0));
//	ca->setRotation3D(Vec3(-90, 0, 0));
//	ca->setVisible(false);
//	//ca->setVisible(false);//设为不可见
//	_worldscene->addChild(ca);//添加3D特写镜头
//
//	//建立3D世界
//	_map = Map3D::create(0, _camera[CAMERA_WORLD_3D_SKYBOX], _camera[CAMERA_WORLD_3D_SCENE], _camera[CAMERA_WORLD_3D_FEATURE]);
//	_worldscene->addChild(_map);
//	_worldscene->setPosition3D(s_scenePositons[SCENE_WORLD]);
//	addChild(_worldscene);
//	
//	////////////////////////////////////////////////////////////////////////
//	//建立UI界面
//	// use the default camera to look 2D base UI layer
//	ca = _camera[CAMERA_UI_2D] = Camera::getDefaultCamera();
//	ca->setDepth(CAMERA_UI_2D);
//	ca->setName(s_CameraNames[CAMERA_UI_2D]);
//	// create UI element and add to ui scene
//
//	createUI();
//
//	_ui->setPosition3D(s_scenePositons[SCENE_UI]);
//	this->addChild(_ui);
//
//	 _trigger = new Trigger(_map,_ui);
//	addChild(_trigger);
//
//	//键盘响应
//	auto kb_listener = EventListenerKeyboard::create();
//	kb_listener->onKeyPressed = CC_CALLBACK_2(MyDemo::onKeyPressed, this);
//	kb_listener->onKeyReleased = CC_CALLBACK_2(MyDemo::onKeyReleased, this);
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(kb_listener, this);
//
//	//单点触摸响应
//	auto listener1 = EventListenerTouchOneByOne::create();
//	listener1->onTouchBegan = CC_CALLBACK_2(MyDemo::onTouchBegan, this);
//	listener1->onTouchMoved = CC_CALLBACK_2(MyDemo::onTouchMoved, this);
//	listener1->onTouchEnded = CC_CALLBACK_2(MyDemo::onTouchEnd, this);
//
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
//	//多点触摸响应
//	auto listener2 = EventListenerTouchAllAtOnce::create();
//	listener2->onTouchesBegan = CC_CALLBACK_2(MyDemo::onTouchesBegan, this);
//	listener2->onTouchesEnded = CC_CALLBACK_2(MyDemo::onTouchesEnd, this);
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
//
//
//	scheduleUpdate();
//}
//
//void MyDemo::onExit()
//{
//	Layer::onExit();
//}
//
//
////*************************************************************************
////
////
////创建UI界面
////
////
////**************************************************************************
//void MyDemo::createUI()
//{
//	_ui = CGameUI::create();
//}
//
//
///*when key is pressed*/
//void MyDemo::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
//{
//	switch (keycode)
//	{
//
//	case cocos2d::EventKeyboard::KeyCode::KEY_Q:
//		m_key_Q = true;	
//		break;
//	case cocos2d::EventKeyboard::KeyCode::KEY_W:
//		m_key_W = true;
//		break;
//	case cocos2d::EventKeyboard::KeyCode::KEY_A:
//		m_key_A = true;
//		break;
//	case cocos2d::EventKeyboard::KeyCode::KEY_S:
//		m_key_S = true;
//		break;
//	case cocos2d::EventKeyboard::KeyCode::KEY_Z:
//		m_key_Z = true;
//		break;
//	case cocos2d::EventKeyboard::KeyCode::KEY_X:
//		m_key_X = true;
//		break;
//	case cocos2d::EventKeyboard::KeyCode::KEY_R:
//		//让镜头特写到npc
//		//zoomInCamera(_map_npc1);
//		break;
//	case cocos2d::EventKeyboard::KeyCode::KEY_F:
//		_camera[CAMERA_WORLD_3D_FEATURE]->setVisible(!_camera[CAMERA_WORLD_3D_FEATURE]->isVisible());
//		break;
//	default:
//		break;
//	}
//}
//
//bool MyDemo::zoomInCamera(Unit *npc)
//{
//	if (npc)
//	{
//		_camera[CAMERA_WORLD_3D_FEATURE]->setVisible(true);
//		_camera[CAMERA_WORLD_3D_FEATURE]->setPosition3D(_camera[CAMERA_WORLD_3D_SCENE]->getPosition3D());
//		_camera[CAMERA_WORLD_3D_FEATURE]->setRotation3D(_camera[CAMERA_WORLD_3D_SCENE]->getRotation3D());
//		_camera[CAMERA_WORLD_3D_FEATURE]->runAction(MoveTo::create(1, npc->getPosition3D() + Vec3(0, 20, 20)));//可用
//		_camera[CAMERA_WORLD_3D_FEATURE]->runAction(RotateTo::create(1, Vec3(-45, 0, 0)));//可用
//	/*	auto sprite1 = Sprite::create(_head2D.head(npc->getKeyNum()));
//		sprite1->setPosition(s.width + sprite1->getContentSize().width / 2, sprite1->getContentSize().height / 2);
//		sprite1->runAction(MoveBy::create(1, Vec2(-s.width / 3, 0)));
//		sprite1->runAction(FadeIn::create(2));
//		_ui->addChild(sprite1,0,10);*/
//		return true;
//	}
//	return false;
//}
//
//bool MyDemo::zoomOutCamera()
//{
//	_camera[CAMERA_WORLD_3D_FEATURE]->setVisible(false);
//	_ui->removeChildByTag(10);
//	return true;
//}
//
////键盘事件响应
//
//void MyDemo::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
//{
//	switch (keycode)
//	{
//	case cocos2d::EventKeyboard::KeyCode::KEY_Q:
//		m_key_Q = false;
//		break;
//	case cocos2d::EventKeyboard::KeyCode::KEY_W:
//		m_key_W = false;
//		break;
//	case cocos2d::EventKeyboard::KeyCode::KEY_A:
//		m_key_A = false;
//		break;
//	case cocos2d::EventKeyboard::KeyCode::KEY_S:
//		m_key_S = false;
//		break;
//	case cocos2d::EventKeyboard::KeyCode::KEY_Z:
//		m_key_Z = false;
//		break;
//	case cocos2d::EventKeyboard::KeyCode::KEY_X:
//		m_key_X = false;
//		break;
//	default:
//		break;
//	}
//}//键盘事件响应
//
//void MyDemo::update(float dt)
//{
//	if (_trigger->_nextScene)
//	{
//		Scene* s = new MyScene();
//		auto l = new MyLayer2();
//		s->addChild(l);
//		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, s));
//	}
//	if (m_key_Q)
//	{
//		//代替的代码应该为
//		//#define KEY_Q   1
// 		//trriger->case(KEY_Q);
//		_map->getPlayer()->PosY+=0.9;
//		_map->getPlayer()->PosZ += 1.2;
//	}
//	if (m_key_W)
//	{
//		//代替的代码应该为
//		//#define KEY_W   2
//		//trriger->case(KEY_Q);
//		_map->getPlayer()->PosY -= 0.9;
//		_map->getPlayer()->PosZ -= 1.2;
//	}
//	if (m_key_A)
//	{
//		_map->getPlayer()->RotAngleV -= 1.0 / 360 * PI * 2;
//	}
//	if (m_key_S)
//	{
//		_map->getPlayer()->RotAngleV += 1.0 / 360 * PI * 2;
//	}
//	if (m_key_Z)
//	{
//		_map->getPlayer()->RotAngleH -= 1.0 / 360 * PI * 2;
//	}
//	if (m_key_X)
//	{
//		_map->getPlayer()->RotAngleH += 1.0 / 360 * PI * 2;
//	}
//
//}//实时更新
//
//bool MyDemo::iscollision(Node* mySprite, Node* testSprite)
//{
//	return true;
//}
//
//bool MyDemo::iscollision(Vec2* point, Sprite3D* TarSprite)
//{
//	auto h = TarSprite->getContentSize().height;
//	Vec3 nearP(point->x, point->y-h, 0.0f), farP(point->x, point->y-h, 1.0f);
//	auto camera = _camera[CAMERA_WORLD_3D_SCENE];
//	if (camera != Camera::getVisitingCamera())
//	{
//		return false;
//	}
//	auto size = Director::getInstance()->getWinSize();
//	camera->unprojectGL(size, &nearP, &nearP);
//	camera->unprojectGL(size, &farP, &farP);
//	Vec3 dir = farP - nearP;
//	dir.normalize();
//	Vec3 collisionPoint;
//	_map->getTerrain()->getIntersectionPoint(Ray(nearP, dir), collisionPoint);
//	//下面代码进行3D碰撞检测//TO DO
//	//test
//	auto aabb = TarSprite->getAABB();
//	
//	//auto obb = OBB(aabb); oob算法啊检测精准但消耗资源大
//	collisionPoint.y=collisionPoint.y+10000;
//	if (aabb.containPoint(collisionPoint))
//		return true;
//	else
//		return false;
//}
//
////碰撞检测
//
//
//
//
//
//bool MyDemo::onTouchBegan(Touch* touch,Event* event)
//{
//	auto location = touch->getLocation();
//	
//
//	return true;
//}
//
//void MyDemo::onTouchMoved(Touch* touch, Event* event)
//{
//	auto location = touch->getLocation();
//	/*if (iscollision(&location, _npc1))
//		_npc1->addEffect(_chosenEffect, -1);*/
//}
//void MyDemo::onTouchEnd(Touch* touch, Event* event)
//{
//	/*if (_camera[CAMERA_WORLD_3D_FEATURE]->isVisible())
//	{
//		zoomOutCamera();
//		return;
//	}*/
//	//特写镜头检测
//	auto location = touch->getLocation();
//	//for (int i = 0; i < _map->getCurUnits();i++)
//	//if (iscollision(&location, _map->getUnit(i)))
//	//{
//	//	zoomInCamera(_map->getUnit(i));
//	//	return;
//	//}
//
//	
//	auto camera = _camera[CAMERA_WORLD_3D_SCENE];
//	if (camera != Camera::getVisitingCamera())
//	{
//		return;
//	}
//	auto _player = _map->getPlayer();
//	if (_player)
//	{
//		Vec3 nearP(location.x, location.y, 0.0f), farP(location.x, location.y, 1.0f);
//		// convert screen touch location to the world location on near and far plane
//		auto size = Director::getInstance()->getWinSize();
//		camera->unprojectGL(size, &nearP, &nearP);
//		camera->unprojectGL(size, &farP, &farP);
//		Vec3 dir = farP - nearP;
//		dir.normalize();
//		Vec3 collisionPoint;
//		bool isInTerrain = _map->getTerrain()->getIntersectionPoint(Ray(nearP, dir), collisionPoint);
//		if (!isInTerrain)
//		{
//			_player->idle();
//		}
//		else
//		{
//			dir = collisionPoint - _player->getPosition3D();
//			dir.y = 0;
//			dir.normalize();
//			_player->_headingAngle = -1 * acos(dir.dot(Vec3(0, 0, -1)));
//			dir.cross(dir, Vec3(0, 0, -1), &_player->_headingAxis);
//			_player->_targetPos = collisionPoint;
//			_player->forward();
//
//		}
//	}
//	event->stopPropagation();
//}
////多点触摸相应：用于缩放和旋转视角
//void MyDemo::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
//{
//}
//void MyDemo::onTouchesEnd(const std::vector<Touch*>& touches, cocos2d::Event* event)
//{
//	
//}
//
//
////*************************************************************************
////
////
////MyLayer1
////
////
////**************************************************************************
//
//void MyLayer1::onEnter()
//{
//	MyDemo::onEnter();
//}
//
//void MyLayer1::onExit()
//{
//	MyDemo::onExit();
//}

void MyLayer2::onEnter()
{
	Layer::onEnter();
	auto s = Director::getInstance()->getWinSize();
	//auto label = Label::create("here is next scene~", "Arial", 50);
	//label->setPosition(480, 320);
	//addChild(label);


	_gameBoard = new GameBoard();
	_gameBoard->setPosition(Vec2(s.width / 2, s.height / 2));
	addChild(_gameBoard);




	int id[30];
	for (int i = 0; i < 30; i++)
		id[i] = i%3;

	for (int i = 0; i < 2; i++)
	{
		_battleID[i] = 0;
		_battleState[i] = false;
		_battles[i] = new CBattle(_gameBoard, &_battleID[i], &_battleState[i], id, i);

		this->addChild(_battles[i]);	
	}


	_battles[0]->setEnemy(_battles[1]);
	_battles[1]->setEnemy(_battles[0]);
	_battles[0]->GameStart();
	_battles[1]->GameStart();
	_tool = new BattleTool2D(_gameBoard, _battles[0], _battles[1], & _battleID[0], &_battleState[0]);
	addChild(_tool);




}