#include"TextCartoon.h"


TextCartoon::TextCartoon()
{
	MaxLength = 25;	//设置每行最大字数
	MaxRow = 2;		//设置每页最大行数
	Flag = 0;		//初始化每页的指针，指向当前显示的字符
	PageBegin = 0;		
	PageEnd = 0;
	
	TextLabel = Label::create("", "fonts/Marker Felt.ttf", 50);
	
	//设置TextLabel的锚点
	TextLabel->ignoreAnchorPointForPosition(true);
	TextLabel->setAnchorPoint(Point(0, 0));
	
	
	addChild(TextLabel);
}

void TextCartoon::onEnter()
{
	
	Node::onEnter();
}

void TextCartoon::SetLabelPosition(int x, int y)
{
	TextLabel->setPosition(x, y);
}

void TextCartoon::SetLabel(char* str)
{
	//将str存入TextStrAll中
	TextStrAll = str;
	
	//获得str的长度
	length=0;
	while (TextStrAll[length] != '\0')
	{
		length++;
	}	
	length++;
	
	//在str中加入'\n'用于换行
	ReLabel();

	//开始第一页的输出
	PageLabel();

	//触摸响应注册
	auto touchListener = EventListenerTouchOneByOne::create();//创建单点触摸事件监听器
	touchListener->onTouchBegan = CC_CALLBACK_2(TextCartoon::onTouchBegan, this);//触摸开始	
	touchListener->onTouchEnded = CC_CALLBACK_2(TextCartoon::onTouchEnded, this);//触摸结束
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);//注册分发器
	

}



void TextCartoon::ChangeLabel(float dt)
{
	
	if (!((TextStrAll[Flag] <= 'Z') && (TextStrAll[Flag] >= 'A') || (TextStrAll[Flag] >= 'a') && (TextStrAll[Flag] <= 'z')))
	{
		TextStr[Flag-PageBegin] = TextStrAll[Flag];
		Flag++;
	}
	else
		while ((TextStrAll[Flag] <= 'Z') && (TextStrAll[Flag] >= 'A') || (TextStrAll[Flag] >= 'a') && (TextStrAll[Flag] <= 'z'))
		{
			TextStr[Flag-PageBegin] = TextStrAll[Flag];
			Flag++;			
		}
	

	TextLabel->setString(TextStr);
	
	//自动停止计时器
	if (Flag >= PageEnd)
		this->unscheduleAllSelectors();
		
	
}


//用来换行
void TextCartoon::ReLabel()
{
	
	int n = 0;
	int number = 0;
	char * Textstr1;
	Textstr1 = new char[length / MaxLength * 2 + length];
	for (int il = 0; il <length / MaxLength * 2 + length; il++)	Textstr1[il] = 0;
	
	int i = 0;
	while ( i<=length)
	{
		if (((TextStrAll[i] <= 'Z') && (TextStrAll[i] >= 'A') || (TextStrAll[i] >= 'a') && (TextStrAll[i] <= 'z')))
		{ 
			int j = 1;
			while ((TextStrAll[j-1+i]  <= 'Z') && (TextStrAll[j-1+i] >= 'A') || (TextStrAll[j-1+i]  >= 'a') && (TextStrAll[j-1+i] <= 'z')) j++;
			j--;
			if (i + j-number <= MaxLength) //考虑到最后一个字符是空格
			{
				for (int k = 0; k < j; k++)  
					Textstr1[i + k + n] = TextStrAll[i + k];
					
				i = i + j;
			}
			else
			{				
				number = i;
				Textstr1[i + n] = '\n';
				n++;				
			}	
		}
		else
		{
			if (i + 1 - number <= MaxLength)
			{				
				Textstr1[i+ n] = TextStrAll[i];
				i++;		
			}
			else
			{				
				Textstr1[i + n] = '\n';				
				n++;
				Textstr1[i + n] = TextStrAll[i];
				i++;		
			}		
		}
	}

	length += n;
	TextStrAll = Textstr1;
}

//用来换页
void TextCartoon::PageLabel()
{
	//每次换页重新初始化TextStr
	TextStr = new char[MaxRow*MaxLength+5];

	for (int k = 0; k <MaxRow*MaxLength+5; k++)
	 TextStr[k] = 0;

	PageBegin = Flag;
	PageEnd = Flag;

	//找到这一页字符串的末尾
	int j = 0;
	while ((j < MaxRow) && (PageEnd <= length))
	{
		if (TextStrAll[PageEnd] == '\n') j++;
		PageEnd++;
	}
	PageEnd--;

	//调用计时器
	this->schedule(schedule_selector(TextCartoon::ChangeLabel), 1.f / 4, PageEnd - PageBegin, 0);





}

//用来停止本页的计时器，使对话完成
void TextCartoon::StopLabel()
{
	for (int i = Flag; i < PageEnd; i++)
	{
		TextStr[i-PageBegin] = TextStrAll[i];	
	}
	Flag = PageEnd+1;
	TextLabel->setString(TextStr);
	this->unschedule(schedule_selector(TextCartoon::ChangeLabel));
	

}


bool TextCartoon::onTouchBegan(Touch* touch, Event* event)
{


	return true;
}
void TextCartoon::onTouchEnded(Touch* touch, Event* event)
{
	

	if (Flag < PageEnd)
		StopLabel();
	else
		if (PageEnd<length-2) 
			PageLabel();


}