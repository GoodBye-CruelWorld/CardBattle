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
	void ReLabel();				//在str内加入'\n'让其自动换行
	void PageLabel();			//更新到新的一页时重载
	void StopLabel();			//鼠标点击，使文字全显示
	cocos2d::Layer* TextLayer;
	cocos2d::Label* TextLabel;
	char * TextStr, *TextStrPage, *TextStrAll;
	

	int Flag, length, MaxLength, MaxRow;
	int PageBegin, PageEnd;			//分别用来记录每一页的开始和结尾位置

};



