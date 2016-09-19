#pragma once
#include"cocos2d.h"
USING_NS_CC;

class Tool
{
public:

	/*获取系统的时间*/
	static int getGameTime();

	/**创建中文标签
	  *请在texts/texts.xml中设置相应中文的键值*/
	static Label* createLabelByKey(const std::string key, const std::string fontType="Arial",float fontSize=24);

	/**更改中文标签内容
	*请在texts/texts.xml中设置相应中文的键值*/
	static void setLabelString(Label* label, const std::string key);


	/*本游戏中使用的标题型字体样式*/
	static Label*createTitleLabel(int fontSize=15);
	/*本游戏中使用的正文型字体样式*/
	static Label*createTextLabel();

	static Label*createEnglishLabel();


};