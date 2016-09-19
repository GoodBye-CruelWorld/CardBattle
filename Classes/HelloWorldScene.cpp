#include "HelloWorldScene.h"

USING_NS_CC;

#include"MainScene.h";

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

	auto textcar = new TextCartoon();
	textcar->SetLabel("Hello World 111111111111111111111111111111111111 /nAre \nyou ready?");
	textcar->SetLabelPosition(visibleSize.width / 4-100, visibleSize.height / 4-100);
	addChild(textcar);



	auto orc = EffectSprite3D::create(s_pathOrc_mod);
	orc->setScale(5);
	orc->setNormalizedPosition(Vec2(.5f, .3f));
	orc->setPositionZ(40);
	orc->setRotation3D(Vec3(0, 180, 0));
	orc->setGlobalZOrder(-1);
	addChild(orc);
	Effect3DOutline* effect = Effect3DOutline::create();
	effect->setOutlineColor(Vec3(1, 0, 0));
	effect->setOutlineWidth(0.01f);
	orc->addEffect(effect, -1);
	//
	/*auto sprite = Sprite3D::create("boss1.obj");
	sprite->setScale(13.f);
	sprite->setTexture("boss.png");
	sprite->setPosition(200, 200);
	sprite->runAction(RotateBy::create(10, Vec3(720, 0, 0)));
	addChild(sprite);*/
	auto s = Director::getInstance()->getWinSize();
	
	//create a start button
	auto startButton = Button::create("button/start1.png", "button/start2.png");
	startButton->setTouchEnabled(true);
	startButton->setPosition(Vec2(0, visibleSize.height / 2));
	startButton->runAction(MoveTo::create(0.2f, Vec2(visibleSize.width / 2, visibleSize.height / 2)));
	startButton->addTouchEventListener(this, toucheventselector(HelloWorld::startEvent));
	addChild(startButton);

	//´´½¨ÊäÈë¿ò
	auto editBoxSize = Size(visibleSize.width - 100, 60);
	_send = cocos2d::extension::EditBox::create(editBoxSize, cocos2d::extension::Scale9Sprite::create("green_edit.png"));
	_send->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 3 / 4));
	_send->setFontName("Paint Boy");
	_send->setFontSize(25);
	_send->setFontColor(Color3B::RED);
	_send->setPlaceHolder("send");
	_send->setPlaceholderFontColor(Color3B::WHITE);
	_send->setMaxLength(8);
	_send->setReturnType(cocos2d::extension::EditBox::KeyboardReturnType::DONE);
	//_send->setDelegate(this);
	addChild(_send);

	
	
	
    return true;
}

void HelloWorld::startEvent(Ref*pSender, TouchEventType type)
{
	{
		Scene* s = new MyScene();
		auto l = new MyLayer2();

		s->addChild(l);
		switch (type)
		{
		case TOUCH_EVENT_BEGAN:
			break;
		case TOUCH_EVENT_MOVED:
			break;
		case TOUCH_EVENT_ENDED:

		//	Director::getInstance()->replaceScene(TransitionFade::create(2, s));
			Director::getInstance()->replaceScene(s);
			break;
		case TOUCH_EVENT_CANCELED:
			break;
		default:
			break;
		}
		s->release();
		l->release();
	}
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
	log("editBox %p DidBegin.", editBox);
}

void HelloWorld::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
	log("editBox %p DidEnd.", editBox);
}

void HelloWorld::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text)
{
	log("editBox %p TextChanged, text: %s", editBox, text.c_str());
}

void HelloWorld::editBoxReturn(cocos2d::extension::EditBox *editBox)
{
	log("editBox %p was returned.", editBox);

	/*if (_send== editBox)
	{
		_TTFShowEditReturn->setString("send return.");
	}
	else if (_editEmail == editBox)
	{
		_TTFShowEditReturn->setString("Email EditBox return.");
	}*/
}