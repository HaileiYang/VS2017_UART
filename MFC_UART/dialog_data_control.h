#pragma once

#include "stdafx.h"
#include "windows.h"
#include "stdafx.h"
#include "stdio.h"

class DIALOG_DATA
{
	LPWSTR	portname[20];//�洢���п��ö˿�
	LPWSTR	selectport;
public:
	BOOL InitPort(CComboBox	*comBox);
	BOOL InitBaud(CComboBox	*comBox);


};











