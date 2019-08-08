#include "StdAfx.h"
#include "TXTcpSend.h"


SOCKET tcp_socket()
{
	return WSASocket(AF_INET, SOCK_STREAM,IPPROTO_TCP,NULL,0,WSA_FLAG_OVERLAPPED);
}

SOCKET tcp_create(const unsigned int h,const unsigned int p)
{
	//�����׽���   
	SOCKET sockClient = WSASocket(AF_INET, SOCK_STREAM,IPPROTO_TCP,NULL,0,WSA_FLAG_OVERLAPPED);  
	 if(INVALID_SOCKET == sockClient) 
	 {  
		WSACleanup();//�ͷ��׽�����Դ   
		return INVALID_SOCKET;
	 } 
	 //�������������ģʽ
	 //ULONG ul = 1;
	 //ioctlsocket(sockClient, FIONBIO, &ul);

	//set Recv   and  Send time   out 
	 //int   TimeOut = 3000;   //���÷��ͳ�ʱ6�� 
	 //if(setsockopt(sockClient,SOL_SOCKET,SO_SNDTIMEO,(char   *)&TimeOut,sizeof(TimeOut))==SOCKET_ERROR) 
	 //{ 
	 // return ERR_NETINIT;
	 //} 
 
	 //TimeOut = 3000;//���ý��ճ�ʱ6�� 
	 //if(setsockopt(sockClient,SOL_SOCKET,SO_RCVTIMEO,(char   *)&TimeOut,sizeof(TimeOut))==SOCKET_ERROR) 
	 //{ 
	 // return ERR_NETINIT;
	 //} 

	 SOCKADDR_IN    servAddr;    //��������ַ
	memset(&servAddr,0,sizeof(servAddr));
	servAddr.sin_family =AF_INET;  
	servAddr.sin_addr.s_addr = h;
	servAddr.sin_port = htons(p); 
	int nServAddlen = sizeof(servAddr);

	//���ȶ�UDP����connect��Ŀ�ĵ�ַ�Ͷ˿ڣ���֤����Ͷ�ݵ�WSARecvFrom�ܹ�������������
	int nRet=WSAConnect(sockClient,(const sockaddr *)&servAddr,nServAddlen,NULL,NULL,NULL,NULL);

	 if (nRet == SOCKET_ERROR &&
		WSAGetLastError() != WSAEWOULDBLOCK)
	{
		closesocket(sockClient);
		return INVALID_SOCKET;
	}

	 return sockClient;
}

unsigned int tcp_net_send(const SOCKET sockClient,const LPWSABUF lpBuffer,const DWORD dwBufferCount,const LPDWORD lpNumberOfBytesSent,const DWORD dwFlags,const LPWSAOVERLAPPED pOlap)
{
	return WSASend(sockClient,lpBuffer,dwBufferCount,lpNumberOfBytesSent,dwFlags,pOlap,NULL);
}
unsigned int tcp_net_recv(const SOCKET sockClient,LPWSABUF lpBuffer,const DWORD dwBufferCount,LPDWORD lpNumberOfBytesRecv,DWORD *dwFlags,LPWSAOVERLAPPED pOlap)
{
	unsigned int nRetVal=WSARecv(sockClient, 
	lpBuffer, 
	1, 
	lpNumberOfBytesRecv, 
	dwFlags,
	pOlap, 
	NULL); 
	return nRetVal;
}