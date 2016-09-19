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

	_isConnect=_socket->Connect("127.0.0.1", 9999);  //测试用
	//_isConnect = _socket->Connect(_ip, 9999);
	return _isConnect;
}

bool GameSocket::sendMsg(std::string &message)
{
	if (!_isConnect)
		return false;
	
	//发送信息
	//std::thread t1(&GameSocket::sendThread,message, this);//将收文件的监听置于此     
	//t1.detach();  //可用，将子线程从主线程中分离出来
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
	std::thread t2(&GameSocket::recvThread, this, message);//将收文件的监听置于此     
	t2.detach();  //可用，将子线程从主线程中分离出来
	
	return true;
}

void GameSocket::recvThread(std::string &message)
{
	char  recvBuf[20] = "\0";
	_socket->Recv(recvBuf, 20, 0);
	message = std::string(recvBuf);
	_isConnect = false;
}
//bool GameSocket::IsConnect()//判断是否链接到服务器
//{
//	return _isConnect;
//}
//
//
//bool GameSocket::GetLocalIP(char* ip)
//{
//	//1.初始化wsa  
//	WSADATA wsaData;
//	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (ret != 0)
//	{
//		return false;
//	}
//	//2.获取主机名  
//	char hostname[256];
//	ret = gethostname(hostname, sizeof(hostname));
//	if (ret == SOCKET_ERROR)
//	{
//		return false;
//	}
//	//3.获取主机ip  
//	int *p;
//	int *a = p;
//	HOSTENT* host;
//	host= gethostbyname(hostname);  //不理解为什么出错
//	if (host == NULL)
//	{
//		return false;
//	}
//	//4.转化为char*并拷贝返回  
//	strcpy(ip, inet_ntoa(*(in_addr*)*host->h_addr_list));
//	return true;
//}