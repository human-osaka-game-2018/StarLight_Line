﻿#include "Timer.h"

VOID Timer::Start()
{
	m_StartTime = std::chrono::system_clock::now();
}

VOID Timer::End()
{
	m_DiffTime = std::chrono::system_clock::now() - m_StartTime;
}

VOID Timer::Reset()
{
	m_DiffTime = (DebugDiffTime)0;
}

LONGLONG Timer::GetSecond()
{
	return std::chrono::duration_cast<std::chrono::seconds>(m_DiffTime).count();
}

LONGLONG Timer::GetMilliSecond()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(m_DiffTime).count();
}

LONGLONG Timer::GetMicroSecond()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(m_DiffTime).count();
}