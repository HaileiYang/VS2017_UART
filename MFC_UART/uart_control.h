#pragma once

#include "stdafx.h"
#include "windows.h"
#include "stdafx.h"
#include "stdio.h"

class UART {
	HANDLE	hComm;
	OVERLAPPED m_ov;
	COMSTAT comstat;
	DWORD m_dwCommEvent;
	LPCWSTR	portname;
public:
	BOOL	OpenPort(LPCWSTR portname);
	BOOL	SetPortDCB(int arg);
	BOOL	SetTimeOut(DWORD ReadInternal, DWORD ReadTotalMultiplier,
		DWORD ReadTotalconstant, DWORD WriteTotalMultipilier,
		DWORD WriteTotalconstant);
	BOOL	InitComm(void);
	BOOL ReceiveChar(char*RXBuff);
	BOOL WriteChar(BYTE*	m_szWriteBuffer, DWORD m_nToSend);
	BOOL GetPortName(LPCWSTR name, DWORD name_len);

};






