#pragma once
#include"cocos2d.h"
USING_NS_CC;
/*
*@ActionQueue
*@brief 负责游戏中动作顺序的管理.
*/
class ActionQueue:public Node
{
public:
	ActionQueue();
	/**@push:将一个动作放入动作序列中
	*@action:放入的动作
	*@lastTime:放入的动作的持续时间
	*/
	void push(Action* action, Node* target,float lastTime);
	/**@reset:重置动作序列时间为0,并清空动作序列
	*@immediate:true=立即重置,false=等动作序列结束后重置
	*/
	void reset(bool immediate);
	/**@delay:延迟下一个放入动作序列的动作的执行时间
	*@time:当前动作序列的最后一个动作执行完毕到即将放入的下一个动作开始执行的延迟时间
	*/
	void delay(float time);
	/**@advance:提前下一个放入动作序列的动作的执行时间
	*@time:当前动作序列的最后一个动作执行完毕到即将放入的下一个动作开始执行的提前时间
	*/
	void advance(float time);
	/**@dump:清空动作序列中还未执行的动作
	*@stopCurAction:是否停止当前动作
	*/
	void dump(bool stopCurAction=false);
	/**@insert:插入一个动作
	*#未开发*/
	void insert(int place, Action* action, Node* target, float lastTime);
	/**@remove:删除一个动作
	*#未开发*/
	void remove(int place, Action* action, Node* target, float lastTime);
	/**@getDelayTime:获取总延迟时间.
	*@return: float*/
	float getDelayTime(){ return _delayTime; }
private:
	void pushCallBack();
	void resetCallBack();
	void delayCallBack();
	void advanceCallBack();
	void dumpCallBack();
	void insertCallBack();
	void removeCallBack();
	void addCurActionNum();
private:
	float _delayTime;/*当前总延迟时间*/
	int _curActionNum;/*当前执行到动作序列的位置*/
	Vector<Action*> _actions;/*动作序列*/
	std::vector<float> _delays;/*动作延迟时间数组:为对应动作结束时间*/
};