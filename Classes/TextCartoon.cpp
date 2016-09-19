#include"TextCartoon.h"


TextCartoon::TextCartoon()
{
	MaxLength = 25;	//����ÿ���������
	MaxRow = 2;		//����ÿҳ�������
	Flag = 0;		//��ʼ��ÿҳ��ָ�룬ָ��ǰ��ʾ���ַ�
	PageBegin = 0;		
	PageEnd = 0;
	
	TextLabel = Label::create("", "fonts/Marker Felt.ttf", 50);
	
	//����TextLabel��ê��
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
	//��str����TextStrAll��
	TextStrAll = str;
	
	//���str�ĳ���
	length=0;
	while (TextStrAll[length] != '\0')
	{
		length++;
	}	
	length++;
	
	//��str�м���'\n'���ڻ���
	ReLabel();

	//��ʼ��һҳ�����
	PageLabel();

	//������Ӧע��
	auto touchListener = EventListenerTouchOneByOne::create();//�������㴥���¼�������
	touchListener->onTouchBegan = CC_CALLBACK_2(TextCartoon::onTouchBegan, this);//������ʼ	
	touchListener->onTouchEnded = CC_CALLBACK_2(TextCartoon::onTouchEnded, this);//��������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);//ע��ַ���
	

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
	
	//�Զ�ֹͣ��ʱ��
	if (Flag >= PageEnd)
		this->unscheduleAllSelectors();
		
	
}


//��������
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
			if (i + j-number <= MaxLength) //���ǵ����һ���ַ��ǿո�
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

//������ҳ
void TextCartoon::PageLabel()
{
	//ÿ�λ�ҳ���³�ʼ��TextStr
	TextStr = new char[MaxRow*MaxLength+5];

	for (int k = 0; k <MaxRow*MaxLength+5; k++)
	 TextStr[k] = 0;

	PageBegin = Flag;
	PageEnd = Flag;

	//�ҵ���һҳ�ַ�����ĩβ
	int j = 0;
	while ((j < MaxRow) && (PageEnd <= length))
	{
		if (TextStrAll[PageEnd] == '\n') j++;
		PageEnd++;
	}
	PageEnd--;

	//���ü�ʱ��
	this->schedule(schedule_selector(TextCartoon::ChangeLabel), 1.f / 4, PageEnd - PageBegin, 0);





}

//����ֹͣ��ҳ�ļ�ʱ����ʹ�Ի����
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