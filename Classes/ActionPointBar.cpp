#include"ActionPointBar.h"

/////////////////////////////////////////
//ActionPoint
////////////////////////////////////////
void ActionPoint::onEnter()
{
	Node::onEnter();
	_available = false;
	_avail= Sprite::create("ChessBoard/chess/actionPoint/pointAvail.png");
	_unavail = Sprite::create("ChessBoard/chess/actionPoint/pointUnavail.png");
	addChild(_unavail,0);
	addChild(_avail, 1);
	_avail->setVisible(false);
	//_avail->retain();
}

void ActionPoint::explode()
{
	//this->runAction(....)  //ִ�б�ը����
	Node::onExit();          //ɾ��
}

void ActionPoint::setAvailable()
{
	if (!_available)
	{
		_available = true;
		_avail->setVisible(true);
	}

}

void ActionPoint::setUnavailable()
{
	if(_available)
	{
		_available= false;
		_avail->setVisible(false);
	}
}

bool ActionPoint::IsAvailable()
{
	return _available;
}


/////////////////////////////////////////
//ActionPointBar
////////////////////////////////////////
void ActionPointBar::onEnter()
{
	Node::onEnter();
	_curTotalActionPoint = 0;
	_curAvailActionPoint = 0;
	_curTempActionPoint = 0;
	_bar = Sprite::create("ChessBoard/chess/actionPoint/actionPointBar1.png");
	addChild(_bar,2);
}

int ActionPointBar::getNumofTotalActionPoint()  //��ȡ��ǰ�ж�����
{
	return _curTotalActionPoint;
}

int ActionPointBar::getNumofAvailActionPiint()
{
	return _curAvailActionPoint;
}

int ActionPointBar::addTotalActionPoint(int delta)
{
	int correctDelta;  //У���������
	if ((_curTotalActionPoint + delta) > MAX_ACTIONPOINT)  //���Ŀǰ�ж���������������������ж�����
		correctDelta = MAX_ACTIONPOINT - _curTotalActionPoint;   //����������С�������С
	else
		correctDelta = delta;

	for (int i = 0; i < correctDelta; i++)
	{
		_actionPoint[_curTotalActionPoint] = new ActionPoint();
		_actionPoint[_curTotalActionPoint]->setPosition(Vec2(0, 93.5 - 161.5 + 12 * (i + _curTotalActionPoint)));//0,0��������λ��
		addChild(_actionPoint[_curTotalActionPoint++]);
	}

	return delta - correctDelta;    //�������������
}

void ActionPointBar::addAvailActionPoint(int delta)
{
	if (_curAvailActionPoint + delta > _curTotalActionPoint)
	{
		_curTempActionPoint = _curAvailActionPoint + delta - _curTotalActionPoint;  //��ʱ���ж�����

		int overflow = addTotalActionPoint(_curTempActionPoint);  //�����ж���������
		if (!overflow)   //��������
		{
			delta -= overflow;
			_curTempActionPoint -= overflow;
		}//���ȥ
	}

	for (int i = 0; i < delta; i++)
	{
		_actionPoint[_curAvailActionPoint];
		_actionPoint[_curAvailActionPoint]->runAction(Sequence::create(
			DelayTime::create((1+i)*0.3f),
			CallFunc::create(CC_CALLBACK_0(ActionPoint::setAvailable, _actionPoint[_curAvailActionPoint])),
			NULL));
		_curAvailActionPoint++;
	}
}

void ActionPointBar::fullAvailActionPoint()
{
	addAvailActionPoint(_curTotalActionPoint - _curAvailActionPoint);
}

int ActionPointBar::reduceAvailActionPoint(int delta)
{
	int correctDelta;
	if (_curAvailActionPoint < delta)
		correctDelta = _curAvailActionPoint;
	else
		correctDelta = delta;

	for (int i = correctDelta; i > 0; i--)
	{
		_actionPoint[--_curAvailActionPoint]->setUnavailable();
	}
	return delta - correctDelta;  //����δ��ȥ���ж�����
}

int ActionPointBar::reduceTotalActionPoint(int delta)
{
	int correctDelta;
	if (_curTotalActionPoint < delta)
		correctDelta = _curTotalActionPoint;
	else
		correctDelta = delta;

	for (int i = correctDelta; i > 0; i--)
	{
		_actionPoint[_curTotalActionPoint--]->explode(); 
	}
	return delta - correctDelta;  //����δ��ȥ���ж�����
}

void ActionPointBar::removeTempActionPoint()
{
	if (!_curTempActionPoint)
	{
		reduceTotalActionPoint(_curTempActionPoint);
		_curTempActionPoint = 0;
	}
}