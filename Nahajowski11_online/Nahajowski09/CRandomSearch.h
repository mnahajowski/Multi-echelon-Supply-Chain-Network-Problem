#pragma once
#include "CMscnProblem.h"
class CRandomSearch
{
public:
	CRandomSearch();
	double *CBestRandomize(CMscnProblem *c1);
	~CRandomSearch();

	const static int MAXIMUM_TRIES;
	const static double WANTED_VALUE;
};

