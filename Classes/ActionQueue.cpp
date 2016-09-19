#include"ActionQueue.h"

ActionQueue::ActionQueue()
{
	_delayTime = 0.f;
	_curActionNum = -1;
}

void ActionQueue::push(Action* action,Node* target, float lastTime)
{
	auto act = Sequence::create(
		DelayTime::create(_delayTime),
		CallFunc::create(CC_CALLBACK_0(ActionQueue::addCurActionNum, this)),
		action,
		NULL);
	

	this->runAction(act);
	action->setTarget(target);
	_delayTime+= lastTime;
	_actions.pushBack(act);
	_delays.push_back(_delayTime);
	return;

}

void ActionQueue::reset(bool immediate)
{

	if (!immediate)
		this->runAction(Sequence::create(
		DelayTime::create(_delayTime),
		CallFunc::create(CC_CALLBACK_0(ActionQueue::resetCallBack, this)),
		NULL));
	else
		resetCallBack();
}

void ActionQueue::delay(float time)
{
	_delayTime += time;
}

void ActionQueue::advance(float time)
{
	_delayTime -= time;
}

void ActionQueue::dump(bool stopCurAction )
{
	
	auto len = _actions.size();
	if (len <= _curActionNum)
	{
		log("the curActionNum >=len!");
		return;
	}
	for (int i = len-1; i >_curActionNum; i--)
	{
		this->stopAction(_actions.at(i));
		_actions.erase(i);
		_delays.erase(_delays.begin() + i);//¿ÉÄÜ´í
	}
	_delayTime = _delays[_curActionNum];
}

void ActionQueue::insert(int place, Action* action, Node* target, float lastTime)
{

}

void ActionQueue::remove(int place, Action* action, Node* target, float lastTime)
{

}

void ActionQueue::pushCallBack()
{
}

void ActionQueue::resetCallBack()
{
	_curActionNum = -1;
	_delayTime = 0.f;
	_actions.clear();
	_delays.clear();
}

void ActionQueue::delayCallBack()
{

}

void ActionQueue::advanceCallBack()
{

}

void ActionQueue::dumpCallBack()
{

}

void ActionQueue::insertCallBack()
{

}

void ActionQueue::removeCallBack()
{

}

void ActionQueue::addCurActionNum()
{
	_curActionNum+=1;
}