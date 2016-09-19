#pragma once

#include"cocos2d.h"
#include"ODSocket.h"
USING_NS_CC;
/*@GameSocket 
*brief 负责客户端与服务器的链接与信息交互
*每次交互信息需要链接一次
*根据信息名，客户端的ai和服务器判断做什么响应
*例如“msg="RE";sendMsg（msg）;”（round end：回合结束），服务器则通知对面 他的回合开始
*例如“recvMsg(msg);if(msg=="AT1")”（attack card num 1：攻击对面战场上第一张卡牌），战斗流程类则通知AI执行此条命令
*关于msg内容的规范，下次会议上确定
*/
class GameSocket
{
public:
	GameSocket();
	bool connect();  //链接到服务器,失败则返回false
	bool sendMsg(std::string &message);  //向服务器发送信息
	bool recvMsg(std::string &message); //接受信息
	bool IsConnect();//判断是否链接到服务器
	
private:
	//bool GameSocket::GetLocalIP(char* ip);
	//char *_ip;
	
	void sendThread(std::string &message);
	void recvThread(std::string &message);
	bool _isConnect;
	ODSocket *_socket;
};