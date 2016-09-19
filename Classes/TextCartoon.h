#pragma once
#include "cocos2d.h"
using namespace cocos2d::ui;
USING_NS_CC;
#include "ui/CocosGUI.h"


class TextCartoon : public cocos2d::Node
{
public:
	TextCartoon();
	void SetLabel(char* str);
	
	void SetLabelPosition(int x,int y);
	virtual void onEnter() override;

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);


	
private:
	void ChangeLabel(float dt);
	void ReLabel();				//��str�ڼ���'\n'�����Զ�����
	void PageLabel();			//���µ��µ�һҳʱ����
	void StopLabel();			//�������ʹ����ȫ��ʾ
	cocos2d::Layer* TextLayer;
	cocos2d::Label* TextLabel;
	char * TextStr, *TextStrPage, *TextStrAll;
	

	int Flag, length, MaxLength, MaxRow;
	int PageBegin, PageEnd;			//�ֱ�������¼ÿһҳ�Ŀ�ʼ�ͽ�βλ��

};



