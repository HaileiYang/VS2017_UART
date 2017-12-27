
#include "stdafx.h"
#include "uart_control.h"




BOOL	UART::OpenPort(LPCWSTR portname)
{
	UART::portname = portname;
	hComm = CreateFile(portname,
		GENERIC_READ | GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		0);
	if (hComm == INVALID_HANDLE_VALUE) {
		CloseHandle(hComm);
		return FALSE;
	}
	return TRUE;
}

BOOL	UART::SetPortDCB(int arg)
{
	DCB	dcb;
	int rate = arg;
	memset(&dcb, 0, sizeof(dcb));
	if (!GetCommState(hComm, &dcb)) {
		return FALSE;
	}

	dcb.BaudRate = rate;
	dcb.Parity = NOPARITY;
	dcb.fParity = 0;
	dcb.StopBits = ONESTOPBIT;
	dcb.ByteSize = 8;
	dcb.fOutxCtsFlow = 0;
	dcb.fOutxDsrFlow = 0;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fDsrSensitivity = 0;
	dcb.fRtsControl = RTS_CONTROL_ENABLE;
	dcb.fOutX = 0;
	dcb.fInX = 0;

	dcb.fErrorChar = 0;
	dcb.fBinary = 1;
	dcb.fNull = 0;
	dcb.fAbortOnError = 0;
	dcb.wReserved = 0;
	dcb.XonLim = 2;
	dcb.XoffLim = 4;
	dcb.XoffChar = 0x19;
	dcb.XonChar = 0x13;
	dcb.EvtChar = 0;

	if (!SetCommState(hComm, &dcb)) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

BOOL	UART::SetTimeOut(DWORD ReadInternal, DWORD ReadTotalMultiplier,
	DWORD ReadTotalconstant, DWORD WriteTotalMultipilier,
	DWORD WriteTotalconstant)
{
	COMMTIMEOUTS	timeout;
	timeout.ReadIntervalTimeout = ReadInternal;
	timeout.ReadTotalTimeoutConstant = ReadTotalconstant;
	timeout.ReadTotalTimeoutMultiplier = ReadTotalMultiplier;
	timeout.WriteTotalTimeoutConstant = WriteTotalconstant;
	timeout.WriteTotalTimeoutMultiplier = WriteTotalMultipilier;

	if (SetCommTimeouts(hComm, &timeout)) {
		return FALSE;
	}
	return TRUE;

}

BOOL	UART::InitComm(LPCWSTR port,int rate)
{
	if (OpenPort(port)) {
		if (SetPortDCB(rate)) {
			SetTimeOut(0, 0, 0, 0,0);
			SetCommMask(hComm, EV_RXCHAR);
			PurgeComm(hComm, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);
			return TRUE;
		}
	}
	return FALSE;

}

BOOL UART::ReceiveChar(char*RXBuff)
{
	BOOL bRead = TRUE;
	BOOL bResult = TRUE;
	DWORD dwError = 0;
	DWORD BytesRead = 0;

	for (;;) {
		bResult = ClearCommError(hComm, &dwError, &comstat);
		if (comstat.cbInQue == 0) {
			continue;
		}
		if (bRead) {
			bResult = ReadFile(hComm, RXBuff, 1, &BytesRead, &m_ov);
		}
		if (!bResult) {
			switch (dwError = GetLastError()) {
			case ERROR_IO_PENDING:
			{
				bRead = FALSE;
				break;
			}
			default:
				break;
			}
		}
		else {
			bRead = TRUE;

		}
		if (!bRead) {
			bRead = TRUE;
			bResult = GetOverlappedResult(hComm,
				&m_ov,
				&BytesRead,
				TRUE);
		}
	}


}

BOOL UART::WriteChar(BYTE*	m_szWriteBuffer, DWORD m_nToSend)
{
	BOOL bWrite = TRUE;
	BOOL bResult = TRUE;
	DWORD BytesSent = 0;
	HANDLE	m_hWriteEvent = 0;
	ResetEvent(m_hWriteEvent);
	if (bWrite) {
		m_ov.Offset = 0;
		m_ov.OffsetHigh = 0;
		bResult = WriteFile(hComm,
			m_szWriteBuffer,
			m_nToSend,
			&BytesSent,
			&m_ov);
		if (!bResult) {
			DWORD  dwError = GetLastError();
			switch (dwError) {
			case ERROR_IO_PENDING: {
				BytesSent = 0;
				bWrite = FALSE;
				break;
			}
			default:
				break;

			}
		}
	}
	if (!bWrite) {
		bWrite = TRUE;
		bResult = GetOverlappedResult(hComm,
			&m_ov,
			&BytesSent,
			TRUE);
		if (!bResult) {

		}
		if (BytesSent != m_nToSend) {

		}
	}
	return TRUE;
}



BOOL UART::GetPortName(LPCWSTR 	name, DWORD name_len)
{

	return TRUE;

}




