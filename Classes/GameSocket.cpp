#include"GameSocket.h"

GameSocket::GameSocket()
{
	_isConnect = false;
	_socket = nullptr;

}



bool GameSocket::connect()
{
	_socket = new ODSocket();
	_socket->Init();
	_socket->Create(AF_INET, SOCK_STREAM, 0);

	_isConnect=_socket->Connect("127.0.0.1", 9999);  //������
	//_isConnect = _socket->Connect(_ip, 9999);
	return _isConnect;
}

bool GameSocket::sendMsg(std::string &message)
{
	if (!_isConnect)
		return false;
	
	//������Ϣ
	//std::thread t1(&GameSocket::sendThread,message, this);//�����ļ��ļ������ڴ�     
	//t1.detach();  //���ã������̴߳����߳��з������
	return true;
	
}

void GameSocket::sendThread(std::string &message)
{
	_socket->Send(message.c_str(), strlen(message.c_str()) + 1, 1);
	_isConnect = false;	
}

bool GameSocket::recvMsg(std::string &message)
{
	if (!_isConnect)
		return false;
	std::thread t2(&GameSocket::recvThread, this, message);//�����ļ��ļ������ڴ�     
	t2.detach();  //���ã������̴߳����߳��з������
	
	return true;
}

void GameSocket::recvThread(std::string &message)
{
	char  recvBuf[20] = "\0";
	_socket->Recv(recvBuf, 20, 0);
	message = std::string(recvBuf);
	_isConnect = false;
}
//bool GameSocket::IsConnect()//�ж��Ƿ����ӵ�������
//{
//	return _isConnect;
//}
//
//
//bool GameSocket::GetLocalIP(char* ip)
//{
//	//1.��ʼ��wsa  
//	WSADATA wsaData;
//	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (ret != 0)
//	{
//		return false;
//	}
//	//2.��ȡ������  
//	char hostname[256];
//	ret = gethostname(hostname, sizeof(hostname));
//	if (ret == SOCKET_ERROR)
//	{
//		return false;
//	}
//	//3.��ȡ����ip  
//	int *p;
//	int *a = p;
//	HOSTENT* host;
//	host= gethostbyname(hostname);  //�����Ϊʲô����
//	if (host == NULL)
//	{
//		return false;
//	}
//	//4.ת��Ϊchar*����������  
//	strcpy(ip, inet_ntoa(*(in_addr*)*host->h_addr_list));
//	return true;
//}