#pragma once

#include"cocos2d.h"
#include"ODSocket.h"
USING_NS_CC;
/*@GameSocket 
*brief ����ͻ��������������������Ϣ����
*ÿ�ν�����Ϣ��Ҫ����һ��
*������Ϣ�����ͻ��˵�ai�ͷ������ж���ʲô��Ӧ
*���硰msg="RE";sendMsg��msg��;����round end���غϽ���������������֪ͨ���� ���ĻغϿ�ʼ
*���硰recvMsg(msg);if(msg=="AT1")����attack card num 1����������ս���ϵ�һ�ſ��ƣ���ս����������֪ͨAIִ�д�������
*����msg���ݵĹ淶���´λ�����ȷ��
*/
class GameSocket
{
public:
	GameSocket();
	bool connect();  //���ӵ�������,ʧ���򷵻�false
	bool sendMsg(std::string &message);  //�������������Ϣ
	bool recvMsg(std::string &message); //������Ϣ
	bool IsConnect();//�ж��Ƿ����ӵ�������
	
private:
	//bool GameSocket::GetLocalIP(char* ip);
	//char *_ip;
	
	void sendThread(std::string &message);
	void recvThread(std::string &message);
	bool _isConnect;
	ODSocket *_socket;
};