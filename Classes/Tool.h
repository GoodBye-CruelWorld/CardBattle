#pragma once
#include"cocos2d.h"
USING_NS_CC;

class Tool
{
public:

	/*��ȡϵͳ��ʱ��*/
	static int getGameTime();

	/**�������ı�ǩ
	  *����texts/texts.xml��������Ӧ���ĵļ�ֵ*/
	static Label* createLabelByKey(const std::string key, const std::string fontType="Arial",float fontSize=24);

	/**�������ı�ǩ����
	*����texts/texts.xml��������Ӧ���ĵļ�ֵ*/
	static void setLabelString(Label* label, const std::string key);


	/*����Ϸ��ʹ�õı�����������ʽ*/
	static Label*createTitleLabel(int fontSize=15);
	/*����Ϸ��ʹ�õ�������������ʽ*/
	static Label*createTextLabel();

	static Label*createEnglishLabel();


};