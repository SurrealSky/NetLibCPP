// NetLib.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include"NetLib.h"
#include <stdlib.h>
#include <process.h>
#include"MyIOCP.h"


MyIOCP *pIocp = NULL;



BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpReserved)  // reserved
{
	// Perform actions based on the reason for calling.
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.
		pIocp = MyIOCP::Instantialize();
		break;

	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
		break;

	case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.
		break;

	case DLL_PROCESS_DETACH:
		// Perform any necessary cleanup.
		MyIOCP::UnInstantialize();
		break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}



bool __stdcall	StartTheSystem(
	const int		m_iPortNr,
	const int		m_iMaxNumberOfConnections,
	const int		m_iNrOfIOWorkers,
	const int		m_iNrOfLogicalWorkers,
	const int		m_iMaxNrOfFreeBuff,
	const int		m_iMaxNrOfFreeContext,
	const bool	m_iSendInOrder,
	const bool	m_bReadInOrder,
	const int		m_iNrOfPendlingReads)
{
	if(pIocp->IsStarted())
		EndTheSystem();
	pIocp->m_StatusLock.Lock();
	pIocp->mMainCallBack=0;
	pIocp->m_StatusLock.Unlock();
	if(!pIocp->Start(m_iPortNr,
		m_iMaxNumberOfConnections,
		m_iNrOfIOWorkers,
		m_iNrOfLogicalWorkers,
		m_iMaxNrOfFreeBuff,
		m_iMaxNrOfFreeContext,
		m_iSendInOrder,
		m_bReadInOrder,
		m_iNrOfPendlingReads))
	{
		return false;
	}
	return true;
}

void __stdcall ChangeNotifyWnd(const HWND mHnd, const unsigned int mMsg)
{
	//pIocp->m_hWnd=mHnd;
	//pIocp->m_Msg=mMsg;
}

bool __stdcall	EndTheSystem()
{
	if (pIocp->IsStarted())
		pIocp->ShutDown();
	return true;
}

bool __stdcall OnConnectA(const MainCallBack _render, const unsigned char* mIp, const unsigned int mPort, const unsigned int _type)
{
	if (!pIocp->IsStarted())
	{
		return false;
	}
	pIocp->mMainCallBack = _render;
	if(pIocp==NULL||!pIocp->Connect(mIp,mPort,_type))
	{
		return false;
	}
	return true;
}

void __stdcall OnDisconnect(const unsigned int ClientID)
{
	pIocp->DisconnectClient(ClientID);
}

void __stdcall SendPacket(const unsigned int ClientID, const unsigned char *buffer,const unsigned int size)
{
	ByteBuffer message;
	message.append(buffer, size);
	pIocp->BuildPackageAndSend(ClientID, &message);
}