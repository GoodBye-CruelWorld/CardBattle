#include "Tool2D.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/************************************************************��ʼ��*******************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BattleTool2D::BattleTool2D(GameBoard * gameboard, CBattle* battleMy, CBattle* battleIt, int *battleID, bool * battleState)
{
	//��ʼ������
	_sight = 0;
	_isOneTouch = false;
	_roleWord = 0;

	_t_battleID = 0;


	// ��ʼ��ָ��
	_gameboard = gameboard;
	_battleID = battleID;
	_battleState = battleState;

	_battleIt = battleIt;
	_battleMy = battleMy;


	//�������׼��
	_mouseSprite = Sprite::create("b.png");
	_mouseSprite->setPosition(Vec2(0,0));
	this->addChild(_mouseSprite, 1);
	_mouseSprite->setVisible(false);

	_cardSel = NULL;

}

void BattleTool2D::onEnter()
{
	Node::onEnter();
	//������Ӧע��
	auto touchListener = EventListenerTouchOneByOne::create();//�������㴥���¼�������
	touchListener->onTouchBegan = CC_CALLBACK_2(BattleTool2D::onTouchBegan, this);//������ʼ
	touchListener->onTouchMoved = CC_CALLBACK_2(BattleTool2D::onTouchMoved, this);//�������ƶ�
	touchListener->onTouchEnded = CC_CALLBACK_2(BattleTool2D::onTouchEnded, this);//��������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);//ע��ַ���

	//���ü�ʱ����ʵʱ����
	//this->scheduleUpdate();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************�����������****************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BattleTool2D::onTouchBegan(Touch* touch, Event* event)
{
	_t_battleID = 0;

	_mouseDown = true;
	Point tp = touch->getLocation();
	_beginID =judgeTouchPoint(tp, 1);//����

	switch (_beginID / 100)
	{
	case 1:
		{	//ָ���������ָ��Card
			int Number = _beginID % 10;
			//�����ҷ��������еĵ�λ����,�ҵ�_beginID%10����Ӧ���кŵ�����
			if (true/*�жϵ�ǰ���ú�Cardָ������ķ���  _battleMy->_cardPool[POOL_HAND].at(Number).getCost()<=Battle.ActionPoints*/)
			{
				//���Card��ָ�������λ�����꣬�ı�Ϊtp
				//��_mouseSpriteͼƬ�ĳɶ�Ӧ�Ŀ��Ƶ�ͼƬ
				for (int i = 0; i < _battleMy->_cardPool[POOL_HAND].size(); i++)
				{
					auto card = _gameboard->getCard(POOL_HAND,i,0);
					if (collisionCheck(tp, card))
					{
						_cardSel= card;
						_gameboard->selectCard(POOL_HAND,i);
						_sight=1;//��ʾ����������ƶ�
					}
				}				
			}
			else
				_beginID = 0;
			break;
		}
	case 2:		
		break;
	case 3:																						//�ҷ����
		if (true/*(_beginID/10)%10!=0 �ж�����ܷ񹥻�*/)
		{			
			_mouseSprite->setPosition(tp);
			_mouseSprite->setVisible(true);			
		}
		else
			_beginID = 0;
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	
	case 8:																					/////////�ҷ�����
		{
			int Number = _beginID % 10;
			auto Skill = _gameboard->getRole(0)->getRoleSkill(Number);
			this->scheduleOnce(schedule_selector(BattleTool2D::disSkilldiscribe), 0.2f);
			break;
		}
	case 9:																					/////////�з�����
		{
			int Number =_beginID % 10;
			auto Skill=_gameboard->getRole(1)->getRoleSkill(Number);
			Skill->displayDescription();
			break; 
		}
	case 10:																				/////////�ҷ�װ��							
		if (_beginID%10==3)
		{ 
			auto Equip = _gameboard->getRole(0)->getWeapon();
			if (Equip == NULL)
				_beginID = 0;
			else
				Equip->displayDescription();
		}
		else
		{ 
			auto Equip=_gameboard->getRole(0)->getEquip(_beginID%10);
			if (Equip == NULL)
				_beginID = 0;
			else
				Equip->displayDescription();
		}
		break;
	case 11:																				/////////�з�װ��
		if (_beginID % 10 == 3)
		{
			auto Equip=_gameboard->getRole(1)->getWeapon();
			if (Equip == NULL)
				_beginID = 0;
			else
				Equip->displayDescription();
		}
		else
		{
			auto Equip=_gameboard->getRole(1)->getEquip(_beginID%10);
			if (Equip == NULL)
				_beginID = 0;
			else
				Equip->displayDescription();
		}
		break;
	
	default:
		break;
	}
	if (_beginID <= 0) 
		return false;

	
	return true;
}

void  BattleTool2D::onTouchEnded(Touch* touch, Event* event)
{
	Point BoardScreen = Point(1024,768);
	Point tp = touch->getLocation();
	bool judge = false;					//��ԭjudge

	_endID =judgeTouchPoint(tp, 2);
										
	_mouseDown = false;
	 

	////////////////////////////////////////////////////////////////////////////////////////Ӣ�۱������Ӧ
	//�ж��Ƿ񵥻�һ��,�������ñ���
	if (_isOneTouch)
	{
		if (_roleWord == 0)
		{
			if (_beginID / 100 == 6)			//�ҷ�����ѡ��
			{
				auto Role = _gameboard->getRole(0);
				Role->getRolePhote()->setWordChoicesVisible(true);
				_roleWord = 1;
				_beginID = 0;
			}
			if (_beginID / 100 == 7)		//�з�����ѡ��
			{
				auto Role = _gameboard->getRole(1);
				Role->getRolePhote()->setWordChoicesVisible(true);
				_roleWord = 2;
				_beginID = 0;
			}
		}
		else
		{
			if (_roleWord == 1)			//��ʾ����
			{
				auto Role = _gameboard->getRole(0);
				Role->getRolePhote()->setWordChoicesVisible(false);
				int number=judgePointIn(tp, Vec2(425, 262), Vec2(587, 262), Vec2(425, 119), Vec2(587, 116));
				if (number)
					Role->getRolePhote()->speakWord(number - 1);
					
				_roleWord = 0;
				_beginID = 0;
			}
			if (_roleWord == 2)			//��ʾ����
			{
				auto Role = _gameboard->getRole(1);
				Role->getRolePhote()->setWordChoicesVisible(false);
				_roleWord = 0;
				_beginID = 0;
			}			
		}
	}
	_isOneTouch = false;
	
	///////////////////////////////////////////////////////////////////////////////////////Ӣ�ۼ��ܵ�ʹ��
	//�жϷ�ָ���ܵ�ʹ��
	if ((_beginID / 100 == 8) && (_beginID % 100 / 10 == 0))
	{
		int Number = _beginID % 10;
		auto Skill=_gameboard->getRole(0)->getRoleSkill(Number);
		Skill->hideDescription();
		//ʹ�ü��ܵ�Ч��
		Skill->useSkill();	

		_t_battleID = 3 * 1000000 + 8 * 10000 + _beginID % 10 * 1000 ;
	}
	//ָ���Լ��ܵ�ʹ��
	if ((_beginID / 100 == 8) && (_beginID % 100 / 10 == 1))
	{
		int Number = _beginID % 10;
		auto Skill = _gameboard->getRole(0)->getRoleSkill(Number);
		Skill->hideDescription();

		//�жϼ����Ƿ���ȷָ��
		if ((_endID / 100 == 3) || (_endID / 100 == 4) || (_endID / 100 == 5) || (_endID / 100 == 6) || (_endID / 100 == 7))
		{
			//ʹ�ü��ܵ�Ч��
			Skill->useSkill();
		
			_t_battleID = 2 * 1000000 + 8 * 10000 + _beginID % 10 * 1000 + _endID/100 * 10 + _endID % 10;
		}		
	}



	////////////////////////////////////////////////////////////////////////////////////���ڵз� װ�� ���� ��Ϣ����ʾ��ȡ��
	//ȡ��װ�����ܵ���Ϣ��ʾ
	if ((_beginID / 100 == 9))
	{
		int Number = _beginID % 10;
		auto Skill = _gameboard->getRole(1)->getRoleSkill(Number);
		Skill->hideDescription();	
	}
	if (_beginID / 100 == 11)
	{
		
		int Number = _beginID % 10;
		if (Number==3)				//�ж��Ƿ���������3Ϊ����
		{ 
			auto Equip = _gameboard->getRole(1)->getWeapon();
			Equip->hideDescription();
		}
		else
		{
			auto Equip = _gameboard->getRole(1)->getEquip(_beginID % 10);
			Equip->hideDescription();
		}
	
	}




	///////////////////////////////////////////////////////////////////////////////////�ҷ����Ƶ�ʹ��	
	if (_beginID / 100 == 1)
	{
		//ʹ�÷�ָ������
		if ((_sight == 2)&&(tp.y>BoardScreen.y/4))															
		{
			//�ж�_beginID����ø���������
			auto _cradID = _battleMy->_cardPool[POOL_HAND].at(_beginID % 10).get_cardID();
			switch ((_cradID / 1000) % 10)
			{
			case 0:		//��ʾ�����
			{
				//�ж����̧�������Ƿ����ҷ������
				if ((_endID / 100 == 3) && (_endID / 10 % 10 == 0) && _battleMy->ActionPoints >= _battleMy->_cardPool[POOL_HAND].at(_beginID % 10).get_cost())		//�������,���Ҹ�λ�������
				{
					int Number = _battleMy->_cardPool[POOL_BATTLE].size();
					

					//����Cbattle�������ٻ�				
					_t_battleID = 1 * 1000000 + 01 * 10000 + _beginID % 10 * 1000 + 03 * 10 + Number % 10;
				}
				else
					_gameboard->setCardOraginState();//��ԭ����λ��	
				break;
			}
			case 1:		//��ʾΪ����
			{
				//����CBattle���ʹ�÷���
				_t_battleID = 2 * 1000000 + 01 * 10000 + _beginID % 10 * 1000 ;
				break;
			}
			default:
				break;
			}
			//��ԭĿǰ���Ƶ����ݻ�ų�����	
			_sight = 0;

		}
		else
			_gameboard->setCardOraginState();//��ԭ����λ��

		//TODO ������ָ�����ӵ�ʹ�ø���

		//ʹ��ָ���Ե�����
	
			
		if ((_sight == -1)&&((_endID / 100 == 3) || (_endID / 100 == 4) || (_endID / 100 == 5) || (_endID / 100 == 6) || (_endID / 100 == 7)))
		{
			auto _cradID = _battleMy->_cardPool[POOL_HAND].at(_beginID % 10).get_cardID();
			switch ((_cradID / 1000) % 10)
			{
			case 0:		//��ʾ�����
			{
				//�д���Ӧ��ֱ�Ӵ���ȥ,ս��ʹ��ʧ�ܵ��ж���Battle��				
				_t_battleID = 1 * 1000000 + 01 * 10000 + _beginID % 10 * 1000 + _endID / 100 * 10 + _endID % 10;				
				
				break;
			}
			case 1:		//��ʾΪ����
			{
				//����CBattle���ʹ�÷���
				_t_battleID = 2 * 1000000 + 01 * 10000 + _beginID % 10 * 1000 + _endID / 100 * 10 + _endID % 10;
				break;
			}
			default:
				break;
			}				
		}		
	}

	////////////////////////////////////////////////////////////////////////////////////////////////��ӹ���
	if (_beginID / 100 == 3)
	{
		if ((_endID / 100 == 4) || (_endID / 100 == 5) || (_endID / 100 == 7))
		{
			_t_battleID = 4 * 1000000 + 3 * 10000 + _beginID % 10 * 1000 + _endID / 100 * 10 + _endID % 10;					
		}		
	}

	///////////////////////////////////////////////////////////////////////////////////////////////Ӣ�۹���
	if (_beginID / 100 == 6)
	{
		if ((_endID / 100 == 4) || (_endID / 100 == 5) || (_endID / 100 == 6) || (_endID / 100 == 7))
		{
			_t_battleID = 4 * 1000000 + _beginID / 100 * 10000 + _beginID % 10 * 1000 + _endID / 100 * 10 + _endID % 10;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////�жϻغϽ���
	
	if ((_endID / 100 == 12) && (_beginID/100==12))
	{
		_t_battleID = 6 * 1000000;	
	}
	
	
	

	//���³�ʼ��_cardSel
	
	_cardSel = NULL;

	//�Ƴ�����׼��
	//_mouseSprite��ͼƬ��ԭ��׼��
	_mouseSprite->setVisible(false);
	_sight = 0;




	//��Ϣ����
	if (_t_battleID != 0)
	{
		*_battleID = _t_battleID;
		*_battleState = true;		
		_t_battleID= 0;
	}

}

void  BattleTool2D::onTouchMoved(Touch* touch, Event* event)
{
	Point tp = touch->getLocation();

	if ((_sight != -1) && (_sight != 2))//-1��ʾͼƬ���ƶ��У������������ж�
	{
		switch (_beginID / 100)
		{
		case 1:
			if (true/*(_beginID%100)/10==0�ж��Ƿ��� ��ָ����ߺͷ�������ӣ���ָ���Խ���Ч����*/)
			{ 
				
				_sight = 2;
			}
			else
			{
				_sight = 1;				
			}
			break;
		case 3:
			
			_sight = 1;
			//if ((_battleMy->_cardPool[POOL_BATTLE].at(_beginID % 10)._canAttack) && (!_battleMy->_cardPool[POOL_BATTLE].at(_beginID % 10)._isAttack))
			//	_sight = 1;	
			//else
			//{
			//	//��ʾ���ܹ���
			//	_gameboard->getRole(0)->getRolePhote()->speakWord(1);
			//	_beginID = 0;				
			//}
			break;
		case 6:
			if ((_beginID % 100) / 10)//Ӣ�ۿɹ���
			{
				_sight = 1;
			}
			else
			{
				//��������Ӣ�۲��ɹ���
				_gameboard->getRole(0)->getRolePhote()->speakWord(1);
				_beginID = 0;
			}

			break;
		case 8:
			if ((_beginID % 100) / 10)//����ָ����
			{
				_sight = 1;				
			}
			break;
		default:
			break;
		}
	}

	
	if (_sight == 1)					//�趨��������ƶ���ȡ����һ�ε��ж�
	{
		_sight = -1;

		_mouseSprite->setPosition(tp);
		_mouseSprite->setVisible(true);
	}
	if (_sight==-1)					//_sight==-1 ��ʾ�����׼���ƶ�
		_mouseSprite->setPosition(tp);
	if (_sight == 2)
		_cardSel->setPosition(tp-Vec2(1024/2,768/2));

}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************˽�з���*******************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BattleTool2D::judgeTouchPoint(cocos2d::Point tp, int PartID)
{	//1024*768
	Point BoardScreen=Point(1024,768);
	//BoradScreen=������̵Ĵ�С
	//����


	 
	///////////////////////////////////////////////////////////////////////////////////////////////////////////�жϱ����ʹ��
	if (_roleWord!=0)
	{
		_isOneTouch = true;
		this->scheduleOnce(schedule_selector(BattleTool2D::resetOneTouch), 0.5f);
		return   600 + 0 * 10 + 0;	
	}
	else
	///////////////////////////////////////////////////////////////////////////////////////////////////////////�ҷ��ƿ�
	if (false/**/ )
	{		
		
		
		
		
	}
	else
	///////////////////////////////////////////////////////////////////////////////////////////////////////////�з��ƿ�
	if (false/**/)
	{
	
	
	}
	else
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////�ҷ�Ӣ��
	if (judgePointIn(tp, Vec2(512, 160))/*tp�ж��Ƿ��Ǽ���Ӣ�۷�Χ*/)
	{
		
		_isOneTouch = true;
		this->scheduleOnce(schedule_selector(BattleTool2D::resetOneTouch), 0.5f);
		
				
		if (_gameboard->getRole(0)->getAttack()!=0)
		{
			return  600 + 1 * 10 + 0;	//1��ʾ���Թ���
		}
		else
			return  600 + 0 * 10 + 0;
	}
	else
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////�з�Ӣ��
	if (judgePointIn(tp, Vec2(512, 615))/*tp�ж��Ƿ��ǵз�Ӣ�۷�Χ*/)
	{
		
		_isOneTouch = true;
		this->scheduleOnce(schedule_selector(BattleTool2D::resetOneTouch), 0.5f);
		return   700 + 0 * 10 + 0;
				
	}
	else
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////�жϽ�����ť
	if (collisionCheck(tp, _gameboard->_endTurnButton) && _gameboard->_endTurnButton->isEnabled())
	{		
		return 1200 + 0*10 + 0;
	}
	else
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////Ұ����
	if (false/*tp�ж��Ƿ���Ұ������Χ*/)
	{
		return   500 + 0 * 10 + 0;
	}
	else
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////�ҷ�����
	if (judgePointIn(tp, Vec2(650, 191), Vec2(733, 214), Vec2(811, 207)))
	{
		int Number = 0;
		//�жϵڼ������ܣ�����Number
		Number =judgePointIn(tp, Vec2(650, 191), Vec2(733, 214), Vec2(811, 207)) - 1;
		//����Ӣ���࣬��ü�������
		int SkillID = 0;
		auto Skill=_gameboard->getRole(0)->getRoleSkill(Number);
		SkillID=Skill->getID();

		//�жϼ����Ƿ�ָ��
		bool  Direct = false;
		switch (SkillID)
		{
		default:
			break;
		}

		if (Direct)
		{
			return 800 + 1 * 10 + Number;//1��ʾָ����
		}
		else
			return 800 + 0 * 10 + Number;
	}
	else
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////�з�����
	if (judgePointIn(tp, Vec2(645, 589), Vec2(726, 567), Vec2(805, 574))/*�ж��Ƿ��ǵз������ܵķ�Χ*/)
	{
		int Number = 0;
		//�жϵڼ������ܣ�����Number
		Number =judgePointIn(tp, Vec2(645, 589), Vec2(726, 567), Vec2(805, 574));

		if (Number == -1)
			return 0;
		else
			return 900 + 0 * 10 + Number-1;
	}
	else
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////�ҷ�װ��
	if (judgePointIn(tp, Vec2(377,191), Vec2(294,213), Vec2(215,205))/*�ж��Ƿ����ҷ�װ���ķ�Χ*/)
	{
		int Number = 0;

		Number =judgePointIn(tp, Vec2(377, 191), Vec2(294, 213), Vec2(215, 205));
		
		//�жϵڼ���װ��������Number
		if (Number == -1)
			return 0;
		else
			return 1000 + 0 * 10 + Number;

	}
	else 
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////�з�װ��
	if (judgePointIn(tp, Vec2(374, 588), Vec2(295, 567), Vec2(215, 570))/*�ж��Ƿ��ǵз�װ���ķ�Χ*/)
	{
		int Number = 0;

		Number =judgePointIn(tp, Vec2(374, 588), Vec2(295, 567), Vec2(215, 570))-1;
		
		//�жϵڼ���װ��������Number
		if (Number == -1)
			return 0;
		else
			return 1100 + 0 * 10 + Number;

	}
	else
	////////////////////////////////////////////////////////////////////////////////////////////////////////////�ҷ��������ж���Χ
	if (tp.y < BoardScreen.y * 1 / 4)
	{
		

		
		int Number = -1;
		int Type = 0;
		//ָ���������ָ��Card
		for (int i = 0; i < _battleMy->_cardPool[POOL_HAND].size(); i++)
		{
			auto card = _gameboard->getCard(POOL_HAND,i,0);
			if (collisionCheck(tp, card/*->_frame*/))
			{
				Type = judgeCard(&_battleMy->_cardPool[POOL_HAND].at(i), AIM);
				_cardSel = card;
				return  100 + Type * 10 + i;
				
			}
		}

		return 0;
		//�����ҷ��������еĵ�λ������һ�ж�
		//������У����ص��е��Ƶ����кţ������еĵڼ��ţ�Number,δ����Number=-1


	}
	else
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////�ҷ����
	if (tp.y < BoardScreen.y * 2 / 4)
	{
		int Number = -1;//number�����жϵ�ǰ����ǵڼ������
		int Type = 0;
		

		//��갴��ʱ�ж�	
		if (PartID == 1)
		{
			//ָ���������ָ��Card
			for (int i = 0; i < _battleMy->_cardPool[POOL_BATTLE].size(); i++)
			{
				auto card = _gameboard->getCard(POOL_BATTLE,i,0);
				if (collisionCheck(tp, card))
				{
					Number = i;
				}
			}

			if ((Number == -1) && (PartID == 1))	//��ʾδ�������
				return 0;

			//�ж��ô��Ƿ��п���
			if (/*false!*/_battleMy->_cardPool[POOL_BATTLE].at(Number).get_health() != 0)
			{
				//�ж�����ܷ񹥻�
				
				return  300 +judgeCard(&_battleMy->_cardPool[POOL_BATTLE].at(Number), ATTACK) * 10 + Number;
			}
		}
		//���̧��ʱ�ж�
		else	
		{
			Number =judgePointIn(tp, Vec2(610, 326), Vec2(695, 326), Vec2(777, 326)) - 1 + 3;
			if (Number == 2)
				Number =judgePointIn(tp, Vec2(355, 326), Vec2(440, 326), Vec2(525, 326)) - 1;

			//�ж��ô��Ƿ��п���,�п��Ʒ���1
			if (false/*_battleMy->_cardPool[POOL_BATTLE].at(Number).Health != 0*/)
				return  300 + 1 * 10 + Number;			
			else
				return	300 + 0 * 10 + Number;
				
		
		}
	}
	else
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////�з����
	if (tp.y < BoardScreen.y * 3 / 4)
	{
		int Number = -1;
		
		//�ж������˵ڼ��������
		
		
		//Number =judgePointIn(tp, Vec2(610, 455), Vec2(695, 455), Vec2(777, 455)) - 1 + 3;
		//if (Number == 2)
		//	Number =judgePointIn(tp, Vec2(355, 455), Vec2(440, 455), Vec2(525, 455)) - 1;
		////�жϸ�λ���Ƿ��п���
		//if (true/*_battleIt->_cardPool[POOL_BATTLE].at(Number).Health == 0*/)
		//	Number = -1;									//��ʾ�ô�û�п���
		
		
		//ָ���������ָ��Card
		for (int i = 0; i < _battleIt->_cardPool[POOL_BATTLE].size(); i++)
		{
			auto card = _gameboard->getCard(POOL_BATTLE,i,1);
			if (collisionCheck(tp, card))
			{
				Number = i;
			}
		}		
		
		//������У����ص��е���ӵ����кţ������еĵڼ��ţ�Number,δ����Number=-1
		if (Number != -1)
		{
			//�ж�Retinue�����ͣ�����һ��ֵType
			return  400 + 0 * 10 + Number;
		}
	}
	else
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////�з�����
	if (tp.y > BoardScreen.y * 3 / 4)
	{
		//��ʱδ�뵽�к���
		return 0;
	}
					

	return 0;
}

void BattleTool2D::resetOneTouch(float dt)
{
	_isOneTouch = false;
}

void BattleTool2D::disSkilldiscribe(float dt)
{
	if (_beginID > 0)
	{
		int Number = _beginID % 10;
		auto Skill = _gameboard->getRole(0)->getRoleSkill(Number);
		Skill->displayDescription();		
	}
}

int BattleTool2D::judgeCard(CCard *_card, int judgeType)
{
	switch (judgeType)
	{
	case AIM:	//	�ж���ӻ����Ƿ���ָ����
	{
		

			
		return 0;
		break;
	}
	case ATTACK:
	{
		//�жϹ�����
		if (!_card->getFinalAttack())
			return 0;
		//�ж����ϵ�Debuff
		if (false)
			return 0;
		
		return 1;

		break;
	}

	default:
		break;
	}

	
}

bool BattleTool2D::judgePointIn(Vec2 p, Vec2 p0)
{
	if (((p.x<p0.x + 27) && (p.x>p0.x - 27)) && ((p.y<p0.y + 27) && (p.y>p0.y - 27)))
		return true;
	return false;
}

int BattleTool2D::judgePointIn(Vec2 p, Vec2 p0, Vec2 p1, Vec2 p2)
{
	if (((p.x<p0.x + 27) && (p.x>p0.x - 27)) && ((p.y<p0.y + 27) && (p.y>p0.y - 27)))
		return 1;
	if (((p.x<p1.x + 27) && (p.x>p1.x - 27)) && ((p.y<p1.y + 27) && (p.y>p1.y - 27)))
		return 2;
	if (((p.x<p2.x + 27) && (p.x>p2.x - 27)) && ((p.y<p2.y + 27) && (p.y>p2.y - 27)))
		return 3;

	return 0;
}

int BattleTool2D::judgePointIn(Vec2 p, Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3)
{
	if (((p.x<p0.x + 27) && (p.x>p0.x - 27)) && ((p.y<p0.y + 27) && (p.y>p0.y - 27)))
		return 1;
	if ((p.x<p1.x + 27) && (p.x>p1.x - 27) && (p.y<p1.y + 27) && (p.y>p1.y - 27))
		return 2;
	if ((p.x<p2.x + 27) && (p.x>p2.x - 27) && (p.y<p2.y + 27) && (p.y>p2.y - 27))
		return 3;
	if ((p.x<p3.x + 27) && (p.x>p3.x - 27) && (p.y<p3.y + 27) && (p.y>p3.y - 27))
		return 4;

	return 0;
}

bool BattleTool2D::collisionCheck(Point p, Node *node)
{
	auto s = Director::getInstance()->getWinSize();
	auto a = node->getPosition()+s/2;
	auto scale = node->getScale();
	Node*parent = node->getParent();
	while (parent != _gameboard)
	{
		a += parent->getPosition() - parent->getContentSize() / 2;
		parent = parent->getParent();
	}


	auto b = node->getContentSize() / 2 * node->getScale();

	if (p.x<(a.x + b.width) && p.x>(a.x - b.width) && p.y<(a.y + b.height) && p.y>(a.y - b.height))
		return true;
	else
		return false;
}