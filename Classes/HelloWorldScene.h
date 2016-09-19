#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d::ui;

#include "ui/CocosGUI.h"

#include"cocostudio/CocoStudio.h"
using namespace cocostudio;

#include"audio\include\SimpleAudioEngine.h" //“Ù∆µ
using namespace CocosDenshion;

#include "../extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;

#include"Outline.h";
#include"GameResource.h"
#include"TextCartoon.h"
class HelloWorld : public cocos2d::Layer, public cocos2d::extension::EditBoxDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	//start game
	void startEvent(Ref*pSender, TouchEventType type);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	//“‘œ¬≤‚ ‘socket”√
public:
	cocos2d::extension::EditBox *_send;
	cocos2d::extension::EditBox *_recv;

	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
};

#endif // __HELLOWORLD_SCENE_H__
