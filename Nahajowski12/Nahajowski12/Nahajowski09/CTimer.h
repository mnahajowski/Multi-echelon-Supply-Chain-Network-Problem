#pragma once
#include <Windows.h>
class CTimer
{
public:
	CTimer();
	~CTimer();
	void cStart();
	double cResult();

private:
	LARGE_INTEGER li_start, li_end, li_freq;
};

