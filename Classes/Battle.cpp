#include "Battle.h"
#include "AIEnemy.h"

CBattle::CBattle(GameBoard * gameboard, int *battleID, bool * battleState, int *cardId, int camp) 
{

	// �������ߵ�ָ��
	_battleID = battleID;
	_battleState = battleState;
	_gameState = GAME_BEGIN;
	_gameboard = gameboard;
	_camp = camp;
	_hero = _gameboard->getRole(camp);
	_cardIds = cardId;
	ActionPoints = ActPtsMax = 1;
	//vector<CCard>*/*CinBattle*/_cardPool[POOL_BATTLE], *_cardPool[POOL_HAND], *_cardPool[POOL_DECK], *_cardPool[POOL_CEME];
	
};
void CBattle::setEnemy(CBattle *e)
{
	_enemy = e;
}

void CBattle::TurnStart(){
	//�غϿ�ʼ �ж�����+1 �ж����� ������޵��� ���� ������
	ActionPoints = ActPtsMax++;

	//
	if (!_camp)
		_gameboard->startPlayerTurn();

	_gameboard->getActionPointBar(_camp)->addTotalActionPoint();
	_gameboard->getActionPointBar(_camp)->fullAvailActionPoint();
	//?����ж�
	DrawCard();
	_gameboard->getActionQueue()->reset(false);
	//ai->AiTurn();
	//���ܷ������
	SpellCheck(00);
	Check();


	//���ϻغϵ���ӱ�ɿ��Թ���
	for (int i = 0; i < _cardPool[POOL_BATTLE].size(); i++)
	{
		_cardPool[POOL_BATTLE].at(i).set_canAttack ( true);
		_cardPool[POOL_BATTLE].at(i).set_isAttack(false);
	}

	//����ǵз�,ת��Ai��
	if (_camp)
	{
		//ai->AiTurn()
		Turning();	
		/*this->runAction(Sequence::create(
		DelayTime::create(2.f),
			CallFunc::create(CC_CALLBACK_0(CBattle::Turning, this)),
			NULL));*/
	}
}


void CBattle::TurnOver()
{
	
	if (!_camp)
	{
		_gameboard->startAiTurn();


	}
	else
		_gameboard->startPlayerTurn();
	//���ͻغϿ�ʼ������
	*_enemy->_battleState = true;
	*_enemy->_battleID = 5000000;
}
void CBattle::ActionChange(int num){
	ActionPoints += num;
}


vector<CCard>& CBattle::CheckPosition(CCard &card){
	return _cardPool[card.get_state()];
	//7.21ע�ͣ����������ɴ���
	//switch (card.State)
	//{
	//case 0:
	//	return _cardPool[POOL_DECK];
	//	break;
	//case 1:
	//	return _cardPool[POOL_HAND];
	//	break;
	//case 2:
	//	return /*CinBattle*/_cardPool[POOL_BATTLE];
	//	break;
	//case 3:
	//	break;
	//default:
	//	return _cardPool[POOL_CEME];
	//	break ;
	//}	
}
void CBattle::SpellCheck(int sTime){
	//�����������Լ�����ս����� �Ƿ���Ϸ�������sTime
	SpellCheckPlayer(sTime);
	SpellCheckEnemy(sTime);
}

void CBattle::SpellCheck(CCard&card,int sTime){
	
	int jS = card.get_spellID().size();
	for (int j = 0; j < jS; j++)
		if (card.get_spellID()[j] % 100 == sTime){
			Spelling(card.get_spellID()[j], card);
		}
}



void CBattle::SpellCheckPlayer(int sTime){
	//int iP = CinBattle.size();
	int iP = _cardPool[POOL_BATTLE].size();
	for (int i = 0; i < iP; i++){
		SpellCheck(/*CinBattle[]*/_cardPool[POOL_BATTLE][i], sTime);
	}
}
void CBattle::SpellCheckEnemy(int sTime){
	int iE =_enemy->/*CinBattle*/_cardPool[POOL_BATTLE].size();
	for (int i = 0; i < iE; i++){
		SpellCheck(_enemy->/*CinBattle*/_cardPool[POOL_BATTLE][i], sTime);
	}

}



void CBattle::Spelling(int spell_num)
{

}




//void CBattle::CardAttack(CCard &creAttack, CCard &creBeattacked){//�໥�˺�
	//creAttack.Damaged(creBeattacked.GetAttack());
	//creBeattacked.Damaged(creAttack.GetAttack());

	////ȡ�����غ���ӵĹ�������
	//creAttack._isAttack = true;

	//auto srcCard = _gameboard->getCard(POOL_BATTLE, srcNum, srcCamp);
	//srcCard->setCurrentHealth(creAttack.GetHealth());
	//if (creAttack.IsDead()){
	//	card->exploside();
	//	CardDead(creAttack);
	//}

	//auto card1 = _gameboard->getCard(creBeattacked.flagNum);
	//card1->setCurrentHealth(creBeattacked.GetHealth());
	//if (creBeattacked.IsDead()){
	//	card1->exploside();
	//	CardDeadE(creBeattacked);
	//}

//}

void CBattle::cardAttack(int srcNum, int srcCamp, int destNum, int destCamp)
{

	//srcCard��������,destCard����������
	CCard *srcCard, *destCard;
	if (srcCamp == _camp)
		srcCard = &_cardPool[POOL_BATTLE].at(srcNum);
	else
		srcCard = &_enemy->_cardPool[POOL_BATTLE].at(srcNum);

	if (destCamp == _camp)
		destCard = &_cardPool[POOL_BATTLE].at(destNum);
	else
		destCard = &_enemy->_cardPool[POOL_BATTLE].at(destNum);


	srcCard->damaged(destCard->get_attack());
	destCard->damaged(srcCard->get_attack());

	//ȡ�����غ���ӵĹ�������
	srcCard->set_isAttack(true);


	_gameboard->cardAttack(srcNum, srcCamp, srcCard->getFinalHealth(), destNum, destCamp, destCard->getFinalHealth());

	if (srcCard->isDead()){
		if (srcCamp == _camp)
			CardDead(srcNum);
		else
			_enemy->CardDead(srcNum);
	}

	if (destCard->isDead()){
		if (destCamp == _camp)
			CardDead(destNum);
		else
			_enemy->CardDead(destNum);
	}
}


void CBattle::CardAttack(int num)						//��ӹ���Ӣ�� ����+1
{
	//auto card = _gameboard->getCard(POOL_BATTLE, num,_camp);
	auto creAttack = _cardPool[POOL_BATTLE][num];
	//double time = card->attackHero(!_camp);
	//_enemy->_hero->setHealth(_enemy->_hero->getHealth() - creAttack.GetAttack(), time);

	//if (creAttack.IsDead())
	//	card->exploside();
	_gameboard->cardAttack(num, _camp, creAttack.getFinalHealth(), -1, !_camp, _enemy->_hero->getHealth() - creAttack.getFinalAttack());
	if (_enemy->_hero->getHealth() <= 0)
	{
		_gameState = GAME_WIN;
		_enemy->_gameState = GAME_LOSE;
		GameOver();
	}
}


//void CBattle::CardAttack(CCard &creAttack)
//{
	////creAttack.Damaged(10);
	//auto card =_gameboard->getCard(creAttack.flagNum);
	////auto card = _gameboard->getCard(POOL_BATTLE,creAttack)
	////card->attack(Vec2(20,90-_camp*280)-card->getPosition());

	//double time=card->attackHero(!_camp);
	//_enemy->_hero->setHealth(_enemy->_hero->getHealth() - creAttack.GetAttack(),time);
	//if (creAttack.IsDead())
	//	card->exploside();
	//if (_enemy->_hero->getHealth() <= 0)
	//{
	//	_gameState = GAME_WIN;
	//	_enemy->_gameState = GAME_LOSE;
	//	GameOver();

	//}

//}

void CBattle::DrawCard(){
	
	int num1 = _cardPool[POOL_DECK].size()-1, num2 = _cardPool[POOL_HAND].size();

	//��ʾ����
	//_gameboard->getCard(_cardPool[POOL_DECK][num1].flagNum)->transFromDeckToHand(num2, num2,_camp);

	//���ݲ���
	//CardTranslate(_cardPool[POOL_DECK], _cardPool[POOL_HAND], num1, num2);
	cardTransfer(POOL_DECK, POOL_HAND, num1, num2);
	SpellCheck(5);
	Check();


}

void CBattle::CardCummon(vector<CCard>&card1, vector<CCard>&card2, int num1, int num2,int battlePlace){
	//����Ƿ���ٻ� �ٻ���� ���ƴ��� ���ܼ�� 
	SpellCheck(12);
	ActionChange(-card1[num1].get_cost());
	_gameboard->getActionPointBar(_camp)->reduceAvailActionPoint(card1[num1].get_cost());
	//CardTranslate(card1, card2, num1, num2);
	cardTransfer(POOL_HAND, POOL_BATTLE, num1, num2,battlePlace);
	SpellCheck(card2[num2],2);
	//card2[num2].Pos = num2;
	Check();

}



//void CBattle::CardTranslate(vector<CCard>&card1, vector<CCard>&card2, int num1, int num2){//���ݿ���
//	//���������� ���Ƶ������Ƿ�����
//	if (card2.size() == 0 || num2>card2.size()){
//		card2.push_back(card1[num1]);
//	}
//	else{
//		card2.insert(card2.begin() + num2, card1[num1]);
//	}
//
//	_gameboard->cardTransfer(POOL_DECK, POOL_HAND, num1, num2, _camp, card2[num2]);
//
//	card1.erase(card1.begin() + num1);
//}

void CBattle::cardTransfer(int srcPool, int destPool, int srcNum, int destNum,int battlePlace)
{
	if (_cardPool[destPool].size() == 0 || destNum>_cardPool[destPool].size())
	{
		_cardPool[destPool].push_back(_cardPool[srcPool][srcNum]);
	}
	else
	{
		_cardPool[destPool].insert(_cardPool[destPool].begin() + destNum, _cardPool[srcPool][srcNum]);
	}

	_gameboard->cardTransfer(srcPool, destPool, srcNum, destNum, _camp, _cardPool[destPool][destNum],battlePlace);
	
	_cardPool[srcPool].erase(_cardPool[srcPool].begin() + srcNum);
}



//void CBattle::CardTranslate(CCard &card, vector<CCard>&card2, int num2){
//	CardTranslate(CheckPosition(card), card2, card.Pos, num2);
//}
CBattle::~CBattle()
{
}


//void CBattle::CardDead(CCard &card){
//	//CardTranslate(card, _cardPool[POOL_CEME], 0);
//	if (card.Place < 0 || card.Place>4) card.Place = 0;
//	ai->place[card.Place] = true;
//	//����state,posδ��ʼ��
//	cardTransfer(card.State, POOL_CEME, card.Pos, 0);
//	//SpellCheck(13);
//	//SpellCheck(card, 03);
//}
void CBattle::CardDead(int num){
	//CardTranslate(card, _cardPool[POOL_CEME], 0);
	auto card = _cardPool[POOL_BATTLE].at(num);
	if (card.get_place() < 0 || card.get_place()>4) card.set_place(0);
	ai->place[card.get_place()] = true;
	cardTransfer(POOL_BATTLE, POOL_CEME, num, 0);
	//SpellCheck(13);
	//SpellCheck(card, 03);
}
void CBattle::CheckDead(){
	int k =_cardPool[POOL_BATTLE].size();
	vector<int>t;
	for (int i = 0; i < k; i++){
		if (_cardPool[POOL_BATTLE][i].isDead()){
			CardDead(i);
//			t.push_back(i); ����ͳһ��������
		}
	}
	
}

//void CBattle::CreatureDead(CCard &card){
void CBattle::update(float dt)
{
	int BattleID = *_battleID;
	bool BattleState = *_battleState;
	while (*_battleState)
	{
		switch (BattleID / 1000000)
		{
		case 01:					//��ʾ����ٻ�
		{
			CardCummon(_cardPool[POOL_HAND], /*CinBattle*/_cardPool[POOL_BATTLE], BattleID / 1000 % 10, BattleID % 10,-1);
			_gameboard->getActionQueue()->reset(false);
			break;
		}
		case 02:					//���߷���װ����ʹ��
		{
			auto CardID = _cardPool[POOL_HAND].at(BattleID / 1000 % 10).get_cardID();
			if (CardID / 1000 == 2)
				Spelling(CardID, _cardPool[POOL_HAND].at(BattleID / 1000 % 10));
			break;
		}
		case 03:					//	���ܵ�ʹ��
		{
			Spelling(BattleID / 1000 % 10);
			break;
		}
		case 04:					//����
		{
			if (BattleID / 10 % 10 != 7)
				//CardAttack(/*CinBattle*/_cardPool[POOL_BATTLE].at(BattleID / 1000 % 10), /*CinBattle*/_cardPool[POOL_BATTLE].at(BattleID / 1000 % 10));
			{
				cardAttack(BattleID / 1000 % 10, 0, BattleID % 10, 1);
				_gameboard->getActionQueue()->reset(false);
			}
			else
				//CardAttack(/*CinBattle*/_cardPool[POOL_BATTLE].at(BattleID / 1000 % 10));
			{
				CardAttack(BattleID / 1000 % 10);
				_gameboard->getActionQueue()->reset(false);
			}
			break;
			
		}
		case 5:  //�غϿ�ʼ
		{
			TurnStart();
			break;
		}
		case 6: //�غϽ���
		{
			TurnOver();
			break;
		}
		default:
			break;
		}
		*_battleState = false;
	}

}
void CBattle::Check()
{}

void CBattle::Turning()
{
	//this->scheduleOnce(schedule_selector(CBattle::TurnOver), 3.f);
	auto t=ai->AiTurn();
	_gameboard->getActionQueue()->reset(false);
	this->runAction(Sequence::create(
		DelayTime::create(t),
		CallFunc::create(CC_CALLBACK_0(CBattle::TurnOver, this)),
		NULL));
}



//��Ϸ��ʼ - ׼���ƿ� - ���ʼ��
void CBattle::GameStart()
{
	//׼���ƿ�
	for (int i = 0; i < 30; i++)
	{
		CCard card = CCard(_cardIds[i]);
		_gameboard->addCard(card,POOL_DECK,i,_camp,0.1f*i);
		_cardPool[POOL_DECK].push_back(card);
	}
	
	//֪ͨ������Ϸ��ʼ,������Ӧ����
	_gameboard->gameBegin();

	//���ʼ��
	/*	this->runAction(Sequence::create(
		DelayTime::create(1.f),
		CallFunc::create(CC_CALLBACK_0(CBattle::DrawCard,this)),
		NULL));*/
	this->DrawCard();
	_gameboard->getActionQueue()->reset(false);
	//ai���趨 ���ʹ�����Ҳ�ٿ���Ϊ�˲���
	auto p = new CAIEnemy(this);
	ai = p;
	
	//ת��gaming״̬
	if (_camp){
		_gameState = GAME_WAIT;
	}
	else
		_gameState = GAME_RUN;
	Gaming();
}

void CBattle::Gaming()
{
	this->scheduleUpdate();
}

void CBattle::GameOver()
{
	//�Ƴ���ʱ��
	this->unscheduleAllSelectors();

	//
	if (_gameState == GAME_WIN)
		_gameboard->gameWin();
	else if (_gameState == GAME_LOSE)
		_gameboard->gameLose();
}


bool CBattle::Spelling(int spell_num, CCard &card1){
	int numX = spell_num / 1000000, numID = spell_num % 1000000 / 1000, numChoose = spell_num / 100 % 10;
	CCard &SpellCard = card1;
	if (numChoose == 1) {
		CCard card2;
		//����µĿ���
		//&SpellCard = card2
	}
	switch (numID)
	{
	case 001:
		SpellCard.set_armor(SpellCard.get_armor() + numX);
		break;
	case 002:
		SpellCard.get_buffID().push_back(0000);
		break;
	case 003:
		SpellCard.damaged(numX);
		break;
	case 004:
		if (numX == 0){
			numX = 9999;
		}
		SpellCard.heal(numX);
		break;
	case 005:
		if (numX == 0)numX++;
		for (int i = 0; i < numX; i++){
			DrawCard();
		}
		break;
	case 200:
	{
		//������
		SpellCard.set_attackBuff(0);
		int s = /*CinBattle*/_cardPool[POOL_BATTLE].size();
		for (int i = 0; i < s; i++){
			SpellCard.set_attackBuff(SpellCard.get_attackBuff()+ _cardPool[POOL_BATTLE][i].get_armor());
		}
	}
	case 500:
		// �����ID
		Spelling(1001100, SpellCard);
		Spelling(4100, SpellCard);
		break;
	case 501:
		DrawCard();
		//hero �໥��
		break;
	case 502:
		//to be 
		break;
	case 503:
	{
		int s = /*CinBattle*/_cardPool[POOL_BATTLE].size();
		for (int i = 0; i < s; i++){
			if (/*CinBattle*/_cardPool[POOL_BATTLE][i].get_armor() > 0) DrawCard();
		}
		break;
	}
	case 900:
		//��ȡָ�� �������� ������
		break;
	case 901:
		//��ӻ���
		break;
	case 904:
		if (ActionPoints < numX) break;
		ActionChange(-numX);
		//CardTranslate(SpellCard, /*CinBattle*/_cardPool[POOL_BATTLE], SpellCard.Pos);//���������� ��ͷ�ٿ���
		cardTransfer(SpellCard.get_state(), /*CinBattle*/POOL_BATTLE, SpellCard.get_pos(),SpellCard.get_pos());//���������� ��ͷ�ٿ���
		break;
	default:
		break;
	}
	return true;

}


int CBattle::getCardPos(int cardPool, CCard &card)//��ȡcard�������е�λ��,û���򷵻�-1
{
	auto pool = &_cardPool[cardPool];
	int i = 0;
	int size = pool->size();
	for (i = 0; i < size; i++)
	{
		if (&pool->at(i)==&card)
			return i;
	}
	return -1;
}