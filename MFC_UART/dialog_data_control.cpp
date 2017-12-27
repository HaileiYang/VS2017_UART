






#include "stdafx.h"
#include "dialog_data_control.h"
#include "resource.h"
#include "afxdialogex.h"
#include "MFC_UARTDlg.h"


BOOL	DIALOG_DATA::InitPort(CComboBox	*comBox)
{
	comBox->AddString(TEXT("COM1"));
	comBox->AddString(TEXT("COM2"));
	comBox->AddString(TEXT("COM3"));
	comBox->AddString(TEXT("COM4"));
	comBox->SetCurSel(2);
	return TRUE;
}


BOOL	DIALOG_DATA::InitBaud(CComboBox	*comBox)
{
	comBox->AddString(TEXT("9600"));
	comBox->AddString(TEXT("57600"));
	comBox->AddString(TEXT("115200"));
	comBox->SetCurSel(0);
	return TRUE;
}


