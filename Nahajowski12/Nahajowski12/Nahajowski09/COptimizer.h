#pragma once
#include "CMscnProblem.h"
#include "CProblem.h"
#include "CTimer.h"
class COptimizer
{
public:
	COptimizer();
	COptimizer(CProblem *problem) { this->problem = problem; };
	~COptimizer();

	virtual double *optimize(double seconds) = 0;
	void setProblem(CProblem *newProblem) { problem = newProblem; };

protected:
	CProblem *problem;
	CTimer timer;
};

