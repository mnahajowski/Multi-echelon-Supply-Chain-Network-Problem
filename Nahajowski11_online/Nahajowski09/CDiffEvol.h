#pragma once
#include "CMscnProblem.h"
class CDiffEvol
{
public:
	CDiffEvol();
	CDiffEvol(int new_length);
	~CDiffEvol();

	const static int MAXIMUM_TRIES;
	const static int DEFAULT_SIZE;
	const static double MINIMUM;
	const static double DIFF_WEIGHT;
	const static double CROSS_PROB;

	double ***evaluate(CMscnProblem *c1);
	bool individualsAreDifferent(double **sln1, double **sln2, double **sln3, double **sln4, int size);
	void bestOfSolutions(double **slns, int size);

private:
	double **solutions;
	int length;
};

