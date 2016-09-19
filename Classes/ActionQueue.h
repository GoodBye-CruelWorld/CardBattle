#pragma once
#include"cocos2d.h"
USING_NS_CC;
/*
*@ActionQueue
*@brief ������Ϸ�ж���˳��Ĺ���.
*/
class ActionQueue:public Node
{
public:
	ActionQueue();
	/**@push:��һ���������붯��������
	*@action:����Ķ���
	*@lastTime:����Ķ����ĳ���ʱ��
	*/
	void push(Action* action, Node* target,float lastTime);
	/**@reset:���ö�������ʱ��Ϊ0,����ն�������
	*@immediate:true=��������,false=�ȶ������н���������
	*/
	void reset(bool immediate);
	/**@delay:�ӳ���һ�����붯�����еĶ�����ִ��ʱ��
	*@time:��ǰ�������е����һ������ִ����ϵ������������һ��������ʼִ�е��ӳ�ʱ��
	*/
	void delay(float time);
	/**@advance:��ǰ��һ�����붯�����еĶ�����ִ��ʱ��
	*@time:��ǰ�������е����һ������ִ����ϵ������������һ��������ʼִ�е���ǰʱ��
	*/
	void advance(float time);
	/**@dump:��ն��������л�δִ�еĶ���
	*@stopCurAction:�Ƿ�ֹͣ��ǰ����
	*/
	void dump(bool stopCurAction=false);
	/**@insert:����һ������
	*#δ����*/
	void insert(int place, Action* action, Node* target, float lastTime);
	/**@remove:ɾ��һ������
	*#δ����*/
	void remove(int place, Action* action, Node* target, float lastTime);
	/**@getDelayTime:��ȡ���ӳ�ʱ��.
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
	float _delayTime;/*��ǰ���ӳ�ʱ��*/
	int _curActionNum;/*��ǰִ�е��������е�λ��*/
	Vector<Action*> _actions;/*��������*/
	std::vector<float> _delays;/*�����ӳ�ʱ������:Ϊ��Ӧ��������ʱ��*/
};