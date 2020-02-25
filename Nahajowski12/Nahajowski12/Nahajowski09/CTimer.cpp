#include "CTimer.h"



CTimer::CTimer()
{
}


CTimer::~CTimer()
{
}

void CTimer::cStart() {
	QueryPerformanceFrequency(&li_freq);
	QueryPerformanceCounter(&li_start);
}

double CTimer::cResult() {
	double d_secs;
	QueryPerformanceCounter(&li_end);
	d_secs = li_end.QuadPart - li_start.QuadPart;
	d_secs = d_secs / li_freq.QuadPart;
	return d_secs;
}