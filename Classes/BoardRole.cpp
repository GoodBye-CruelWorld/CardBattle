#include"BoardRole.h"
#include"Tool.h"
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//RolePhote
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void RolePhote::onEnter()
{
	Node::onEnter();
}

RolePhote * RolePhote::create(int RoleID)
{
	auto rolePhote = new (std::nothrow)RolePhote();
	rolePhote->_chessID = RoleID;
	if (rolePhote&&rolePhote->init())
	{
		switch (RoleID)
		{
		case 0:
		{
			rolePhote->_phote = Sprite::create("ChessBoard/chess/hero/1.png");
		
			rolePhote->addChild(rolePhote->_phote);
			rolePhote->initwords();
		}
			break;

		default:
			break;
		}

	}
	else
	{
		CC_SAFE_DELETE(rolePhote);
	}
	return rolePhote;
}


void RolePhote::initwords()
{

	Label *label[8];
	std::string word[4];
	word[0] = "Hello!";
	word[1] = "Well Play.";
	word[2] = "My honor.";
	word[3] = "I'm sorry.";

	for (int i = 0; i < 4; i++)
	{
		_wordChoices[i] = Sprite::create("ChessBoard/chess/dialog.png");
		addChild(_wordChoices[i]);
		_wordChoices[i]->setVisible(false);
		label[i] = Label::create(word[i], "Arial", 24);
		label[i]->setColor(Color3B::BLACK);
		label[i]->setPosition(75, 50);
		_wordChoices[i]->addChild(label[i]);

	}
	_wordChoices[0]->setPosition(-80, 90);
	_wordChoices[1]->setPosition(80, 90);
	_wordChoices[2]->setPosition(-80, -50);
	_wordChoices[3]->setPosition(80, -50);



	
	for (int i = 0; i < 4; i++)
	{
		_wordSpeak[i] = Sprite::create("ChessBoard/chess/dialog.png");
		_wordSpeak[i]->setPosition(Vec2(-20, 120));
		_wordSpeak[i]->setVisible(false);
		addChild(_wordSpeak[i]);

		label[i+4] = Label::create(word[i], "Arial", 24);
		label[i+4]->setColor(Color3B::BLACK);
		label[i+4]->setPosition(75, 50);
		_wordSpeak[i]->addChild(label[i+4]);

	}

	_wordSpeakOnScreen = 0;
}



void RolePhote::explode()
{
	this->removeFromParent();
	this->release();
}

float RolePhote::attack(Vec2 Pos)
{
	 return attack(Pos.x, Pos.y);
}
float RolePhote::attack(float PosX, float PosY)
{
	auto time = sqrt(PosX*PosX + PosY*PosY) / 400;
	auto action1 = MoveBy::create(sqrt(PosX*PosX+PosY*PosY)/400, Vec2(0, 400));
	auto easeaction1=EaseOut::create(action1, 0.2);
	auto easeaction2 = EaseIn::create(action1->reverse(), 0.4);
	auto action2 = Sequence::create(easeaction1, easeaction2, NULL);
	this->runAction(action2);
	return time;
}






void RolePhote::setWordChoicesVisible(bool visible) //设置‘语句选择’的可见不可见
{
	for (int i = 0; i < 4; i++)
		_wordChoices[i]->setVisible(visible);
}
void RolePhote::speakWord(int num) //说话，num代表第几条语句
{
	if (num < 0 || num>3)
		return ;

	if (_wordSpeakOnScreen)
	{
		_wordSpeak[_wordSpeakOnScreen]->stopAllActions();
		_wordSpeak[_wordSpeakOnScreen]->setVisible(false);
	//	_wordSpeakOnScreen->runAction(Sequence::create(FadeOut::create(0.05f), CallFunc::create(CC_CALLBACK_0(Sprite::setVisible, _wordSpeak[num], false)), NULL));
	}
	_wordSpeakOnScreen = num;

	//a->setCascadeOpacityEnabled(true);
	_wordSpeak[num]->setVisible(true);
	_wordSpeak[num]->setOpacity(0);
	//进行（1s淡入，2秒延时，1秒淡出，回调设为不可见）的动作
	_wordSpeak[num]->runAction(Sequence::create(FadeIn::create(1), DelayTime::create(1.5f), FadeOut::create(0.2f), CallFunc::create(CC_CALLBACK_0(RolePhote::speakWordCallBack, this)), NULL));

}

void RolePhote::speakWordCallBack()
{
	if (_wordSpeakOnScreen)
	{
		_wordSpeak[_wordSpeakOnScreen]->setVisible(false);
		_wordSpeakOnScreen = 0;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//RoleSkill
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void RoleSkill::onEnter()
{
	BoardChess::onEnter();
	addChild(_face);
	addChild(_back);
	addChild(_description);
}


RoleSkill *RoleSkill::create(int SkillID/*,GameLibrary _library */)
{
	auto roleSkill = new (std::nothrow)RoleSkill();
	roleSkill->_chessID = SkillID;
	if (roleSkill&&roleSkill->init())
	{
	    //改为roleSkill->_face = Sprite::create(_library->getPath1(SKILL_TABLE,SkillID));
		roleSkill->_face = Sprite::create("ChessBoard/chess/skill.png");
    	//改为roleSkill->setCost(_library->getCost(SKILL_TABLE,SkillID))); 
		roleSkill->setCost(2); //测试用

		//描述
		roleSkill->_description = Sprite::create("ChessBoard/chess/b.png");
		auto label = Label::create("_library->getDescription(SKILL_TABLE,SkillID)", "Arial", 20);
		roleSkill->_description->addChild(label);
		roleSkill->_description->setVisible(false);

		roleSkill->_isUsed = false;
		

		roleSkill->_back = Sprite::create("ChessBoard/chess/skill2.png");
		roleSkill->_back->setVisible(false);

	}
	else
	{
		CC_SAFE_DELETE(roleSkill);
	}
	return roleSkill;
}

void RoleSkill::useSkill()
{
	_isUsed = true;
	turnSide();
	//_skill这张图片做出更改
	
}

void RoleSkill::changeSkill(int SkillID)
{
	_chessID = SkillID;
	this->runAction(Sequence::create(DelayTime::create(2), CallFunc::create(CC_CALLBACK_0(RoleSkill::changeSkillCallback, this)), NULL));

}

void RoleSkill::changeSkillCallback()
{
	_face->removeFromParent();
	
	_face = Sprite::create("ChessBoard/chess/skill2.png");
	this->addChild(_face);

	_isUsed = false;  //可删，如果不必要的话
}

void RoleSkill::setCost(int cost)
{
	_cost = cost;
}

int RoleSkill::getCost()
{
	return _cost;
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//RoleWeapon
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void RoleWeapon::onEnter()
{
	Node::onEnter();
	addChild(_weaponFrame, 1);
	addChild(_face, 1);
	addChild(_back, 1);
}

RoleWeapon *RoleWeapon::create(int WeaponID/*,GameLibrary _library */)
{
	auto roleWeapon = new (std::nothrow)RoleWeapon();
	roleWeapon->_chessID = WeaponID;
	if (roleWeapon&&roleWeapon->init())
	{
	
		//roleWeapon->_face = Sprite::create(_library->getPath1(CARD_TABLE,WeaponID));s
		roleWeapon->_face = Sprite::create("ChessBoard/chess/a.png");
		roleWeapon->_weaponFrame = Sprite::create("ChessBoard/chess/a.png");  //装饰用
		roleWeapon->_back = Sprite::create("ChessBoard/chess/a.png");
		roleWeapon->_back->setVisible(false);
		//roleWeapon->_attack = _library->getAttack(CARD_TABLE,WeaponID);
		//roleWeapon->_useTime = _library->getUseTime(CARD_TABLE,WeaponID);
		roleWeapon->_isUsed = false;
	
		//描述
		roleWeapon->_description = Sprite::create("ChessBoard/chess/b.png");
		auto label = Label::create("_library->getDescription(CARD_TABLE,WeaponID)", "Arial", 20);
		roleWeapon->_description->addChild(label);
		roleWeapon->_description->setVisible(false);
	}
	else
	{
		CC_SAFE_DELETE(roleWeapon);
	}
	return roleWeapon;
}

RoleWeapon *RoleWeapon::create(CCard &card)
{
	auto roleWeapon = new (std::nothrow)RoleWeapon();
	roleWeapon->_chessID = card.get_cardID();
	if (roleWeapon&&roleWeapon->init())
	{
		
			roleWeapon->_face = Sprite::create(card.get_cardPath());
			roleWeapon->_weaponFrame = Sprite::create("ChessBoard/chess/a.png");//装饰用
			roleWeapon->_back = Sprite::create("ChessBoard/chess/a.png"); 

		
			roleWeapon->_back->setVisible(false);
			//roleWeapon->_attack = card.Attack;
			//roleWeapon->_useTime = card.UseTime;
			roleWeapon->_isUsed = false;

			//描述
			roleWeapon->_description = Sprite::create("ChessBoard/chess/b.png");
			auto label = Label::create("_library->getDescription(CARD_TABLE,WeaponID)", "Arial", 20);
			roleWeapon->_description->addChild(label);
			roleWeapon->_description->setVisible(false);
	}
	else
	{
		CC_SAFE_DELETE(roleWeapon);
	}
	return roleWeapon;
}

void RoleWeapon::broken() //使武器损坏，即销毁
{
	//一个borken的动画
	this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(RoleWeapon::removeFromParent, this)), NULL));

	this->autorelease();
}

void RoleWeapon::useWeapon()
{
	_isUsed = true;
	this->_useTime--;
	if (!_useTime)
		broken();
}

bool RoleWeapon::IsUsed()	   //是否已使用
{
	return _isUsed;
}

void RoleWeapon::resetWeaponUsable()
{
	_isUsed = false;
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//RoleEquip
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void RoleEquip::onEnter()
{
	Node::onEnter();
}

RoleEquip *RoleEquip::create(int EquipID)
{
	auto roleEquip = new (std::nothrow)RoleEquip();
	roleEquip->_chessID = EquipID;
	if (roleEquip&&roleEquip->init())
	{
		switch (roleEquip->_chessID)
		{
		case 0:
			roleEquip->_face = Sprite::create("ChessBoard/chess/a.png");
			roleEquip->_equipFrame = Sprite::create("ChessBoard/chess/a.png");  //装饰用
			roleEquip->addChild(roleEquip->_equipFrame, 1);
			roleEquip->addChild(roleEquip->_face, 1);

			//roleEquip->_attack = skilldata->getAttack(EquipID);
			//roleEquip->_useTime = skilldata->getUseTime(EquipID);
			roleEquip->_isUsed = false;
			break;
		default:
			break;
		}

	}
	else
	{
		CC_SAFE_DELETE(roleEquip);
	}
	return roleEquip;
}

RoleEquip *RoleEquip::create(CCard &card)
{
	auto roleEquip = new (std::nothrow)RoleEquip();
	roleEquip->_chessID = card.get_cardID();
	if (roleEquip&&roleEquip->init())
	{

		roleEquip->_face = Sprite::create(card.get_cardPath());
		roleEquip->_equipFrame = Sprite::create("ChessBoard/chess/a.png");//装饰用
		roleEquip->_back = Sprite::create("ChessBoard/chess/a.png");

		roleEquip->addChild(roleEquip->_equipFrame, 1);
		roleEquip->addChild(roleEquip->_face, 1);
		roleEquip->addChild(roleEquip->_back, 1);
		roleEquip->_back->setVisible(false);
		//roleEquip->_attack = skilldata->getAttack(EquipID);
		//roleEquip->_useTime = skilldata->getUseTime(EquipID);
		roleEquip->_isUsed = false;



	}
	else
	{
		CC_SAFE_DELETE(roleEquip);
	}
	return roleEquip;
}

void RoleEquip::broken() //使武器损坏，即销毁
{
	//一个borken的动画
	this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(RoleEquip::removeFromParent, this)), NULL));

	this->autorelease();
}

void RoleEquip::useEquip()
{
	_isUsed = true;
	this->_useTime--;
	if (_useTime == 0)
		broken();
}

bool RoleEquip::IsUsed()	   //是否已使用
{
	return _isUsed;
}

void RoleEquip::resetUsable()
{
	_isUsed = false;
}



//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//RoleRole
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void BoardRole::onEnter()
{
	BoardChess::onEnter();
	_rolePhote->setPosition(0, 0);
	addChild(_rolePhote);
	for (int i = 0; i < 3; i++)
	{
		addChild(_roleSkill[i]);
	}
}

BoardRole *BoardRole::create(int RoleID/*,GameLibrary *_library*/)
{
	auto role = new (std::nothrow)BoardRole();
	role->_chessID= RoleID;
	if (role&&role->init())
	{ 
		//role->_rolePhote = RolePhote::create(_library->getPath(ROLE_TABLE,RoleID));  数据库搭建之后
		role->_rolePhote = RolePhote::create(RoleID);  //测试用
		for (int i = 0; i < 3; i++)
		{
			role->_roleSkill[i] = RoleSkill::create(RoleID + i * 100);
			//role->_roleSkill[i] = RoleSkill::create(_library->getSkillID(ROLE_TABLE,RoleID,i),_library);
			role->_roleEquip[i] = NULL;
		}
			

		role->_roleWeapon = NULL;

		role->_attackLb = Tool::createTitleLabel(45);
		role->_attackLb->setPosition(10, 10);
		role->_rolePhote->addChild(role->_attackLb);

		role->_healthLb = Tool::createTitleLabel(60);
		role->_healthLb->setPosition(50, 10);
		//role->_healthLb->setScale(3);
		role->_rolePhote->addChild(role->_healthLb);

		role->_maxHealth = 20;
		role->setAttack(0);
		role->setHealth(role->_maxHealth);
		
	}
	else
	{
		CC_SAFE_DELETE(role);
	}
	return role;
}

RoleSkill* BoardRole::getRoleSkill(int num)
{
	return  _roleSkill[num];
}
RolePhote* BoardRole::getRolePhote()
{
	return _rolePhote;
}
RoleEquip* BoardRole::getEquip(int num)
{
	return _roleEquip[num];
}
RoleWeapon* BoardRole::getWeapon()
{
	return _roleWeapon;
}
int BoardRole::getAttack()
{
	return _attack;
}

void BoardRole::setAttack(int attack)
{
	_attackLb->setVisible(true);
	_attack = attack;
	char c[10];
	sprintf(c, "%d", _attack);
	_attackLb->setString(c);
	if (_attack == 0)
		_attackLb->setVisible(false);
}



int BoardRole::getHealth()
{
	return _health;
}

void BoardRole::setHealth(int health,float delay)
{
	if (delay != 0)
	{
		this->runAction(Sequence::create(
			DelayTime::create(delay),
			CallFunc::create(CC_CALLBACK_0(BoardRole::setHealth, this, health, 0)),
			NULL));
		return;
	}

	_healthLb->setVisible(true);
	_health = health;
	char c[10];
	sprintf(c, "%d", _health);
	_healthLb->setString(c);
	if (_health == _maxHealth)
		_healthLb->setColor(Color3B::WHITE);
	else
		_healthLb->setColor(Color3B::RED);
}

bool BoardRole::addWeapon(int ID)
{
	if (_roleWeapon)
	{
		_roleWeapon->broken();
		_roleWeapon = RoleWeapon::create(ID);
		_roleWeapon->setPosition(-200, 0);
		addChild(_roleWeapon);
		return true;
	}
	else
	{
		_roleWeapon = RoleWeapon::create(ID);
		_roleWeapon->setPosition(-200, 0);
		addChild(_roleWeapon);
		return false;
	}
}

bool BoardRole::addWeapon(CCard &card)
{
	if (_roleWeapon)
	{
		_roleWeapon->broken();
		_roleWeapon = RoleWeapon::create(card);
		_roleWeapon->setPosition(-200, 0);
		addChild(_roleWeapon);
		return true;
	}
	else
	{
		_roleWeapon = RoleWeapon::create(card);
		_roleWeapon->setPosition(-200, 0);
		addChild(_roleWeapon);
		return false;
	}
}

bool BoardRole::removeWeapon()
{
	if (!IsWeapon())
		return false;

	this->getWeapon()->broken();
	return true;
}


bool BoardRole::addEquip(int ID,int num)
{
	if (num > 2 || num < 0)
		return false;
	if (_roleEquip[num])
	{
		_roleEquip[num]->broken();
		_roleEquip[num] = RoleEquip::create(ID);
		_roleEquip[num]->setPosition(-200, 0);
		addChild(_roleEquip[num]);
		return true;
	}
	else
	{
		_roleEquip[num] = RoleEquip::create(ID);
		_roleEquip[num]->setPosition(-200, 0);
		addChild(_roleEquip[num]);
		return false;
	}
}

bool BoardRole::addEquip(CCard &card,int num)
{

	if (num > 2 || num < 0)
		return false;

	if (_roleEquip[num])
	{
		_roleEquip[num]->broken();
		_roleEquip[num] = RoleEquip::create(card);
		_roleEquip[num]->setPosition(-200, 0);
		addChild(_roleEquip[num]);
		return true;
	}


	_roleEquip[num] = RoleEquip::create(card);
	_roleEquip[num]->setPosition(-200, 0);
	addChild(_roleEquip[num]);
	return false;

}

bool BoardRole::removeEquip(int num)
{
	if (!this->getEquip(num))
		return false;
	this->getEquip(num)->broken();
	return true;
}

int BoardRole::getCurEquipNum()
{
	int curNum=0;
	for (int i = 0; i < 3; i++)
		if (getEquip(i))
			curNum++;

	return curNum;
}

bool BoardRole::IsWeapon()
{
	if (getWeapon())
		return true;
	else
		return false;
}
