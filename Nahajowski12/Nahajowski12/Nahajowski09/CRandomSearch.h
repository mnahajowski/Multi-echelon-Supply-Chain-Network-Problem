#pragma once
#include "CMscnProblem.h"
#include "COptimizer.h"
class CRandomSearch : public COptimizer
{
public:
	CRandomSearch();
	double *optimize(double seconds);
	~CRandomSearch();

	const static int MAXIMUM_TRIES;
	const static double WANTED_VALUE;
};

