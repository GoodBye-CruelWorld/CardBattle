#include"BoardCard.h"
#include"Tool.h"

//*类初始化
void BoardCard::onEnter()
{
	Node::onEnter();
	
	addChild(_normal); //默认显示正常图片
	addChild(_frame);
	addChild(_cardBack);
	_normal->setVisible(false);
	//_cardBack->setVisible(false);
}


//*静态创建卡牌显示类
BoardCard *BoardCard::create(CCard& card)
{

	auto boardcard = new (std::nothrow) BoardCard();
	if (boardcard   && boardcard->init())
	{
		boardcard->_frame= Sprite::create("card/frameMM.png");
		//boardcard->_frame->setScale(0.25f);
		boardcard->_frame->setRotation3D(Vec3(0, 180, 0));
		boardcard->_normal = Sprite::create(card.get_cardPath());
		boardcard->_normal->setScale(0.25f);
		boardcard->_normal->setRotation3D(Vec3(0, 180, 0));
		//boardcard->_battle = Sprite::create(card._path2);

		boardcard->_cardBack = Sprite::create("card/back.png");
		boardcard->_cardBack->setScale(0.25f);
		

		boardcard->_card = &card;
	/*	boardcard->_ID = card.get_cardID();
		boardcard->_attack = card.Attack;
		boardcard->_health = card.Health;1000000
		boardcard->_camp = card.Camp;
		boardcard->_camp = 0;
		boardcard->_cost = card.Cost;
		boardcard->_description = card.CardDescribe;*/


		//添加名称label
		boardcard->_laName = Tool::createTitleLabel();
		Tool::setLabelString(boardcard->_laName, boardcard->_card->get_cardName());
		boardcard->_laName->setPosition(boardcard->_frame->getContentSize().width / 2, boardcard->_frame->getContentSize().height *0.35);
		//添加描述label
		boardcard->_laDescription = Tool::createTextLabel();
		Tool::setLabelString(boardcard->_laDescription, boardcard->_card->get_cardDescribe());
		boardcard->_laDescription->setDimensions(75,45 );
		boardcard->_laDescription->setPosition(boardcard->_frame->getContentSize().width / 2, boardcard->_frame->getContentSize().height*0.185);
		//添加攻击label
		char s[3];
		sprintf(s, "%d", boardcard->_card->get_attack());//取实际
		boardcard->_laAttack = Tool::createEnglishLabel();
		boardcard->_laAttack->setString(s);
		boardcard->_laAttack->setPosition(20,9.5);

		//添加生命label
		char h[3];
		sprintf(h,"%d", boardcard->_card->get_health());//取实际
		boardcard->_laHealth = Tool::createEnglishLabel();
		boardcard->_laHealth->setString(h);
		boardcard->_laHealth->setPosition(80,9.5);  

		//添加费用label
		char c[3];
		sprintf(c, "%d", boardcard->_card->get_cost());
		boardcard->_laCost = Tool::createEnglishLabel();
		boardcard->_laCost->setString(c);
		boardcard->_laCost->setPosition(17, 105);

		boardcard->setContentSize(boardcard->_frame->getContentSize());

		boardcard->_frame->addChild(boardcard->_laName);
		boardcard->_frame->addChild(boardcard->_laCost);
		boardcard->_frame->addChild(boardcard->_laDescription);
		boardcard->_frame->addChild(boardcard->_laHealth);
		boardcard->_frame->addChild(boardcard->_laAttack);
		boardcard->_state = CARD_STATE_UNDEFINE;
		boardcard->autorelease();
		
	}
	else
	{
		CC_SAFE_DELETE(boardcard);
	}
	return boardcard;
}


//*卡牌爆炸,销毁对象,等同于die()
void BoardCard::exploside()
{
	die();
}
//*卡牌爆炸,销毁对象
void BoardCard::die()
{
	auto die_par = ParticleSystemQuad::create("particles/MISS.plist");
	die_par->setPosition(_frame->getContentSize().width / 2, _frame->getContentSize().height*0.05);
	die_par->setScale(0.5);
	addChild(die_par, 2);
	_state = 0;
	this->retain();
	this->runAction(TintTo::create(0.3f, Color3B::GRAY));
	this->runAction(Sequence::create(
		JumpBy::create(0.3f, Vec2(0, 0), 10, 50),
		ScaleTo::create(0.2f, 0, 0),
		CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, this)),
		NULL));

}


//*设置卡牌的状态:在牌库=0;在手上=1;在场上=2;在墓地=3;状态不明=4
void BoardCard::setCardState(int state)
{
	_state = state;
}


//*获取卡牌的状态:在牌库=0;在手上=1;在场上=2;在墓地=3;状态不明=4
int BoardCard::getCardState()
{
	return _state;
}


//*卡牌被沉默
void BoardCard::silent()
{
	_laDescription->removeFromParent();
	
	auto silent = Sprite::create("ChessBoard/chess/silent.png");
	silent->setPosition(150, 200);
	_normal->addChild(silent);
}


//*设置当前生命为CurHealth
//*每当当前生命发生改变需要调用，改变图像上的显示
void BoardCard::setCurrentHealth(int CurHealth)
{
	char s[3];
	sprintf(s, "%d", CurHealth);
	_laHealth->setString(s);
	if (CurHealth < _card->get_health())
		_laHealth->setColor(Color3B::RED);
	else
		_laHealth->setColor(Color3B::WHITE);
}


//*设置当前攻击为CurAttack
//*每当当前攻击发生改变需要调用，改变图像上的显示
void BoardCard::setCurrentAttack(int CurAttack)
{
	char s[3];
	sprintf(s, "%d", CurAttack);
	_laAttack->setString(s);
	if (CurAttack>_card->get_attack())
		_laAttack->setColor(Color3B::GREEN);
	else if (CurAttack < _card->get_attack())
		_laAttack->setColor(Color3B::GRAY);
	else
		_laAttack->setColor(Color3B::WHITE);
}


//*卡牌翻面,动画长度为1s
void BoardCard::turnSide()
{
	this->runAction(Sequence::create(RotateBy::create(0.5f, Vec3(0, 90, 0)), CallFunc::create(CC_CALLBACK_0(BoardCard::turnSideCallback, this)), RotateBy::create(0.5f, Vec3(0, 90, 0)), NULL));
}


//*卡牌翻面的内部回调
void BoardCard::turnSideCallback()
{
	if (this->_normal&&this->_cardBack)
	{
		this->_normal->setVisible(!this->_normal->isVisible());
		this->_cardBack->setVisible(!this->_cardBack->isVisible());
	}
}


//*卡牌攻击动画,时长为卡牌中心与目标位置（Position）的距离/400 s.
//*返回攻击到达的时间
//*另设有attackHero和attackCard供快捷使用
float BoardCard::attack(Vec2 Position)
{
	auto aa=this->getPositionX();
	int PosX = Position.x-this->getPositionX();
	int PosY = Position.y - this->getPositionY();
	float time = sqrt(PosX*PosX + PosY*PosY) / 400;
	auto action1 = MoveBy::create(time, Vec2(PosX,PosY));
	auto easeaction1 = EaseOut::create(action1, 0.2f);
	auto easeaction2 = EaseIn::create(action1->reverse(), 0.4);
	auto action2 = Sequence::create(easeaction1, easeaction2, NULL);
	this->runAction(action2);
	return time;
}


//*卡牌攻击英雄,参数为目标英雄的阵营
float BoardCard::attackHero(int Dest_Camp)
{
	return attack(Vec2(20, -190 + Dest_Camp * 280));
}


//*卡牌攻击卡牌,参数为目标卡牌的位置和目标卡牌的阵营
float BoardCard::attackCard(int Place, int Dest_Camp)
{
	return attack(Vec2(-155.2 + Place*82.5, -61 + 122 * Dest_Camp));
}

//*卡牌攻击卡牌,参数为目标卡牌
float BoardCard::attackCard(BoardCard* Dest_Card)
{
	return attack(Dest_Card->getPosition());
}


//*从牌库移到手牌里的动画
float BoardCard::transFromDeckToHand(int PosOrder,int TotalNum,int camp)
{

	if (PosOrder > TotalNum )
		return -1;
	float x, y;
	float angle;
	calculatePosAndAngle(PosOrder, TotalNum,angle, x, y,camp);
	if (camp == 0)
	{
		///this->runAction(MoveTo::create(1.f, Vec2(-200+80 * PosOrder, -330)));//移到相应位置
		this->runAction(MoveTo::create(1.f, Vec2(x, y)));//移到相应位置
		this->runAction(Sequence::create(RotateBy::create(0.5f, Vec3(0, 90, -60 + angle / 2)), CallFunc::create(CC_CALLBACK_0(BoardCard::turnSideCallback, this)), RotateBy::create(0.5f, Vec3(0, 90, -30 + angle / 2)), NULL));
		this->runAction(ScaleTo::create(1, 1.2));//缩放
	
		
	}
	else if (camp== 1)
	{
		//this->runAction(MoveTo::create(1.f, Vec2(-200+80*PosOrder, 330)));
		this->runAction(MoveTo::create(1.f, Vec2(x, y)));//移到相应位置
		this->runAction(Sequence::create(RotateBy::create(0.5f, Vec3(0, 0,60 - angle / 2)), RotateBy::create(0.5f, Vec3(0, 0, 30 - angle / 2)), NULL));
		this->runAction(ScaleTo::create(1, 1.2));
	}


	return 1.f;
}




//*从手牌中移入场上
float BoardCard::transFromHandToBattle(int PosOrder,int Camp)
{ 
	if (PosOrder > 5 || PosOrder < 0)
		return -1;
	
	this->runAction(MoveTo::create(1.f, Vec2(-155.2 + PosOrder*82.5, -61 + 122 * Camp)));
	this->runAction(ScaleTo::create(1, 1.2));
	if (Camp)
	{
		auto a=this->getRotation3D();
		this->runAction(Sequence::create(RotateBy::create(0.5f, Vec3(0, 90, 0)), CallFunc::create(CC_CALLBACK_0(BoardCard::turnSideCallback, this)), RotateTo::create(0.5f, Vec3(0, 180, 540)), NULL));
	}
	return 1.f;
}


void  BoardCard::calculatePosAndAngle(int place, int size,float &angle, float &x, float &y,int camp)
{
	if (size <= place)
		return;
	
	float a = 290.f;
	float b = 163.f;
	if (size == 1)
	{
		x = 0;
		y = 163 - 480;
		angle = 0;
	}
	else
	{
		angle = (-size * 10 + float(place)/ (size-1) * size*20) / 2;//为夹角的二分之一
		float theta = tan((90 - angle*2) / 180.0*3.1415926);
		x = sqrt(1.0 / (1.0 / (a*a) + theta*theta / (b*b)));
		if (angle < 0)
			x = -x;
		y = x*theta - 480;
	}
	if (camp == 1)
		y = -y;
}