#include"GameBoard.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/************************************************************初始化*******************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameBoard::GameBoard()
{
}

void GameBoard::onEnter()
{
	Node::onEnter();

	//面板大小
	_size = Size(1024, 768);

	//背景，包含主背景和装饰物
	_bg = new BoardBG();
	addChild(_bg, 0);

	//行动点数条
	_actionPointBar[CAMP_FRIEND] = new ActionPointBar();
	_actionPointBar[CAMP_FRIEND]->setCamp(CAMP_FRIEND);
	_actionPointBar[CAMP_FRIEND]->setPosition(930 - 512, 384 - 425.5);
	addChild(_actionPointBar[CAMP_FRIEND]);

	_actionPointBar[CAMP_ENEMY] = new ActionPointBar();
	_actionPointBar[CAMP_ENEMY]->setCamp(CAMP_ENEMY);
	_actionPointBar[CAMP_ENEMY]->setPosition(104.5 - 512, 384 - 330.5);
	_actionPointBar[CAMP_ENEMY]->setRotation(180);
	addChild(_actionPointBar[CAMP_ENEMY]);


	//创建英雄
	initRole(0, 0);
	initRole(0, 1);

	//创建效果管理器
	_effect = new BoardEffect();
	_effect->addEffect(0,_bg->getDecoration(0),10); //测试用
	_effect->addEffect(4,_bg->getDecoration(3),5);   //测试用
	_effect->addEffect(1, _bg->getDecoration(1), 8);   
	_effect->addEffect(1, _bg->getDecoration(2), 15);
	addChild(_effect);




	//winbg
	_winbg = Sprite::create("bg/win.png");
	_winbg->setVisible(false);
	addChild(_winbg, 10);

	//losebg
	_losebg = Sprite::create("bg/lost.png");
	_losebg->setVisible(false);
	addChild(_losebg, 10);

	//结束按钮
	_endTurnButton = Button::create("ChessBoard/start01.png", "", "ChessBoard/start02.png");
	_endTurnButton->setPosition(Vec2(990-512, -8));
	addChild(_endTurnButton,10);

	_actionQueue = new ActionQueue();
	addChild(_actionQueue);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/************************************************************get接口******************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


BoardCard *GameBoard::getCard(int cardPool, int num, int camp)
{
	return _cardPools[cardPool + 4 * camp].at(num);
}

BoardRole *GameBoard::getRole(int camp)
{
	return _role[camp];
}

ActionPointBar *GameBoard::getActionPointBar(int num)
{
	return _actionPointBar[num];
}

BoardBG *GameBoard::getBG()
{
	return _bg;
}

BoardEffect *GameBoard::getEffect()
{
	return _effect;
}

Size GameBoard::getSize()
{
	return _size;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/***********************************************************战斗流程接口**************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameBoard::gameBegin()
{
	//播放一个VS的动画
	auto vs = Sprite::create("vs.png");
	addChild(vs);
	vs->setOpacity(0);
	vs->setScale(3);
	vs->runAction(Sequence::create(
		Spawn::create(FadeIn::create(0.4f), ScaleTo::create(0.4, 1.f), NULL),
		DelayTime::create(1.f),
		Spawn::create(FadeOut::create(0.4f), ScaleTo::create(0.4, 0.f), NULL),
		CallFunc::create(CC_CALLBACK_0(Sprite::setVisible, vs, false)),
		NULL));
}

void GameBoard::gameWin()
{
	this->stopAllActions();

	//播放战斗胜利音乐
	//SimpleAudioEngine::getInstance()->playEffect("bgm/battlewin.wav");

	//显示战斗胜利面板
	_winbg->setVisible(true);
	_winbg->setScale(0.0f);
	_winbg->runAction(Sequence::create(
		ScaleTo::create(0.1f, 0.8),
		NULL));

	//黑底
	auto dark = Sprite::create("bg/dark.png");
	dark->setScaleY(1.5);
	dark->setOpacity(0);
	dark->runAction(FadeTo::create(0.3f, 255 * 0.75));
	addChild(dark);
}

void GameBoard::gameLose()
{
	this->stopAllActions();

	//播放音乐
	//SimpleAudioEngine::getInstance()->playEffect("bgm/LOST.wav");

	//显示失败面板
	_losebg->setVisible(true);
	_losebg->setOpacity(0);
	_losebg->runAction(Sequence::create(
		DelayTime::create(0.5f),
		FadeIn::create(1.5f),
		NULL));

	
	//画面变黑
	auto dark = Sprite::create("bg/dark.png");
	dark->setOpacity(0);
	dark->setPosition(_size / 2);
	dark->runAction(FadeTo::create(2.f, 255 * 0.75));
	addChild(dark);

}

void GameBoard::startPlayerTurn()
{
	_endTurnButton->loadTextureNormal("ChessBoard/start01.png");
	_endTurnButton->setTouchEnabled(true);
	_endTurnButton->setEnabled(true);
}

void GameBoard::startAiTurn()
{
	_endTurnButton->setTouchEnabled(false);
	_endTurnButton->setEnabled(false);
	_endTurnButton->loadTextureNormal("ChessBoard/start02.png");

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/***********************************************************boardCard接口*************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameBoard::addCard(CCard &card, int cardPool, int num, int camp,float delay)
{
	/*延时处理*/
	/*有Bug,并不会执行callfunc语句*/
	//this->runAction(Sequence::create(DelayTime::create(delay),
	//	CallFunc::create(CC_CALLBACK_0(GameBoard::addCardCallBack, this, card, cardPool, num, camp)),
	//	NULL));
	addCardCallBack(card, cardPool, num, camp);
	//delay = 0.2f;
	//auto act = CallFunc::create(CC_CALLBACK_0(GameBoard::addCardCallBack, this, card, cardPool, num, camp));
	//	//	_actionQueue->delay(delay);
	//_actionQueue->push(act, this, delay);
	//return;
	//

	
}

void GameBoard::removeCard(int DestPool, int num, int camp, float delay)
{
	DestPool += camp * 4;
	_cardPools[DestPool].at(num)->die();
	_cardPools[DestPool].erase(num);
}

void GameBoard::cardTransfer(int SrcPool, int DestPool, int SrcNum, int DestNum,int camp, CCard &newCard,int battlePlace)
{
	auto act = CallFunc::create(CC_CALLBACK_0(GameBoard::cardTransferCallBack, this,SrcPool, DestPool, SrcNum,DestNum, camp,newCard,battlePlace));
	_actionQueue->push(act, this, 2.f);
	
}
void GameBoard::cardAttack(int srcOrder, int srcCamp, int srcHealth, int destOrder, int destCamp, int destHealth)
{
	auto act = CallFunc::create(CC_CALLBACK_0(GameBoard::cardAttackCallBack, this, srcOrder, srcCamp, srcHealth,destOrder,destCamp,destHealth));
	_actionQueue->push(act, this, 2.f);
}
void GameBoard::cardAttackCallBack(int srcOrder, int srcCamp, int srcHealth, int destOrder, int destCamp, int destHealth)
{
	if (srcOrder != -1 && destOrder != -1)
	{
		auto srcCard = _cardPools[POOL_BATTLE + 4 * srcCamp].at(srcOrder);
		auto destCard = _cardPools[POOL_BATTLE + 4 * destCamp].at(destOrder);
		auto delay = srcCard->attackCard(destCard);
		_effect->addEffect(4, destCard, delay);
		this->runAction(Sequence::create(
			DelayTime::create(delay),
			CallFunc::create(CC_CALLBACK_0(BoardCard::setCurrentHealth, srcCard, srcHealth)),
			CallFunc::create(CC_CALLBACK_0(BoardCard::setCurrentHealth, destCard, destHealth)),
			NULL));

	}
	if (srcOrder == -1 && destOrder != -1)
	{
		auto srcHero = _role[srcCamp]->getRolePhote();
		auto destCard = _cardPools[POOL_BATTLE + 4 * destCamp].at(destOrder);
		auto delay = srcHero->attack(destCard->getPosition());
		_effect->addEffect(4, destCard, delay);
		this->runAction(Sequence::create(
			DelayTime::create(delay),
			CallFunc::create(CC_CALLBACK_0(BoardRole::setHealth, _role[srcCamp], srcHealth, 0)),
			CallFunc::create(CC_CALLBACK_0(BoardCard::setCurrentHealth, destCard, destHealth)),
			NULL));
	}
	if (srcOrder != -1 && destOrder == -1)
	{
		auto srcCard = _cardPools[POOL_BATTLE + 4 * srcCamp].at(srcOrder);
		auto destHero = _role[destCamp]->getRolePhote();
		auto delay = srcCard->attackHero(destCamp);
		_effect->addEffect(4, destHero, delay);
		this->runAction(Sequence::create(
			DelayTime::create(delay),
			CallFunc::create(CC_CALLBACK_0(BoardCard::setCurrentHealth, srcCard, srcHealth)),
			CallFunc::create(CC_CALLBACK_0(BoardRole::setHealth, _role[destCamp], destHealth, 0)),
			NULL));
	}
	if (srcOrder == -1 && destOrder == -1)
	{
		auto srcHero = _role[srcCamp]->getRolePhote();
		auto destHero = _role[destCamp]->getRolePhote();
		auto delay = srcHero->attack(destHero->getPosition());
		_effect->addEffect(4, destHero, delay);
		this->runAction(Sequence::create(
			DelayTime::create(delay),
			CallFunc::create(CC_CALLBACK_0(BoardRole::setHealth, _role[srcCamp], srcHealth, 0)),
			CallFunc::create(CC_CALLBACK_0(BoardRole::setHealth, _role[destCamp], destHealth, 0)),
			NULL));
	}

}

void GameBoard::selectCard(int cardPool,int num)
{
	_oNum = num;
	auto card = _cardPools[cardPool].at(num);
	_oPos = card->getPosition();
	_oRotation = card->getRotation();
	_oScale = card->getScale();

	card->setScale(1.8f);
	card->setRotation(0);
	card->setPositionZ(20);

	auto outLine = Sprite::create("card/frameLine.png");
	card->addChild(outLine,1,10);
}

void GameBoard::setCardOraginState()
{
	
	auto card = _cardPools[POOL_HAND].at(_oNum);
	card->removeChildByTag(10);
	card->setPosition(_oPos);
	card->setPositionZ(0);
	card->setRotation(_oRotation);
	card->setScale(_oScale);
}

void GameBoard::showCardDescribe(int cardPool,int num)
{

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/***********************************************************boardCard接口*************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void GameBoard::adjustPool(int CardPool,int camp,int delay)
{
	switch (CardPool)
	{
	case POOL_DECK:
	{
	}
		break;
	case POOL_HAND:
	{
		auto size = _cardPools[CardPool + camp * 4].size();
		for (int i = 0; i < size; i++)
		{
			float angle, x, y;
			auto card = _cardPools[CardPool + camp * 4].at(i);
			card->calculatePosAndAngle(i, size, angle, x, y, camp);
			auto a = card->getRotation3D();
			card->runAction(Sequence::create(
				DelayTime::create(delay),
				Spawn::create(MoveTo::create(0.2f, Vec3(x, y, 0)), RotateTo::create(0.2f, Vec3(0, 180 - 180 * camp, 180 * camp + angle*(1 - 2 * camp))), NULL),
				NULL));
		}
	}
		break;
	case POOL_BATTLE:
	{
		auto size = _cardPools[CardPool + camp * 4].size();
		for (int i = 0; i < size; i++)
		{
			auto card = _cardPools[CardPool + camp * 4].at(i);
			int place = (card->getPositionX() + 155.2) / 82.5+0.5;
			card->runAction(MoveTo::create(0.1f, Vec2(-155.2 + place*82.5, -61 + 122 * camp)));
			card->runAction(ScaleTo::create(0.1, 1.2));
		}
	}
		break;
	case POOL_CEME:
	{}
		break;
	default:
		break;
	}	
}

void GameBoard::initRole(int RoleID, int camp/*,Library library*/)
{
	_role[camp] = BoardRole::create(RoleID);
	addChild(_role[camp]);
	if (!camp)
	{
		_role[camp]->setPosition(1, 384 - 610);
		_role[camp]->getRoleSkill(0)->setPosition(655 - 512, 220 + 384 - 580);
		_role[camp]->getRoleSkill(1)->setPosition(734.6 - 512, 220 + 384 - 556);
		_role[camp]->getRoleSkill(2)->setPosition(814 - 512, 220 + 384 - 564);
		_role[camp]->getRoleSkill(2)->setScale(1.2f);
	
	}
	else
	{
		_role[1]->setPosition(1, 226);
		_role[1]->getRoleSkill(0)->setPosition(655 - 512, -(220 + 384 - 580));
		_role[1]->getRoleSkill(1)->setPosition(734.6 - 512, -(220 + 384 - 556));
		_role[1]->getRoleSkill(2)->setPosition(814 - 512, -(220 + 384 - 564));
		_role[1]->getRoleSkill(2)->setScale(1.2f);
	}
}


ActionQueue *GameBoard::getActionQueue()
{
	return _actionQueue;
}


void GameBoard::addCardCallBack(CCard &card, int cardPool, int num, int camp)
{
	/*结构处理*/
	//创建一张新的面板卡牌
	auto BCard = BoardCard::create(card);
	addChild(BCard);
	//创建目标卡牌池指针
	auto pool = &_cardPools[cardPool + camp * 4];

	if (pool->size() == 0 || num >pool->size())
		pool->pushBack(BCard);
	else
		pool->insert(num, BCard);

	/*动画处理*/
	switch (cardPool)
	{
	case POOL_DECK:
		BCard->setRotation(90);
		BCard->setPosition3D(Vec3(285, -45 + 95 * camp, pool->size() % 30 * 1.5));
		break;
	case POOL_HAND:
		break;
	case POOL_BATTLE:
		break;
	case POOL_CEME:
		break;
	default:
		break;
	}
}


void GameBoard::cardTransferCallBack(int SrcPool, int DestPool, int SrcNum, int DestNum, int camp, CCard &newCard, int battlePlace)
{
	auto SrcCPool = &_cardPools[SrcPool + camp * 4];
	auto DestCPool = &_cardPools[DestPool + camp * 4];
	if (DestCPool->size() == 0 || DestNum>DestCPool->size()){
		DestCPool->pushBack(SrcCPool->at(SrcNum));
	}
	else{
		DestCPool->insert(DestNum, SrcCPool->at(SrcNum));
	}
	//auto bb = SrcCPool->at(SrcNum)->_card->flagNum;
	//auto aa = DestCPool->at(DestNum)->_card->flagNum;

	////newCard->flagNum = aa;
	DestCPool->at(DestNum)->_card = &newCard;
	SrcCPool->erase(SrcNum);

	/*必要动画*/
	if (SrcPool == 0 && DestPool == 1)
	{
		auto delay = DestCPool->at(DestNum)->transFromDeckToHand(DestNum, DestCPool->size(), camp);
		adjustPool(SrcPool, camp, delay);
		adjustPool(DestPool, camp, delay);
	}
	if (SrcPool == 1 && DestPool == 2)
	{
		float delay = 0;
		//ai操作时
		if (battlePlace != -1)
		{

			delay = DestCPool->at(DestNum)->transFromHandToBattle(battlePlace, camp);
			adjustPool(SrcPool, camp, delay);
		}
		else
		{
			DestCPool->at(DestNum)->removeChildByTag(10);
			adjustPool(SrcPool, camp, delay);
			adjustPool(DestPool, camp, delay);
		}
	}
	if (DestPool == POOL_CEME)
	{
		this->runAction(Sequence::create(
			DelayTime::create(0.8f),
			CallFunc::create(CC_CALLBACK_0(BoardCard::die, DestCPool->at(DestNum))),
			NULL));
	}
}