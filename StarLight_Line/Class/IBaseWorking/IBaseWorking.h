﻿#ifndef I_BASE_WORKING_H
#define I_BASE_WORKING_H

#include <windows.h>

class IBaseWorking
{
public:
	IBaseWorking() {};
	~IBaseWorking() {};

	virtual VOID Update() = 0;

	virtual VOID Render() = 0;
};

#endif // !I_BASE_WORKING_H
