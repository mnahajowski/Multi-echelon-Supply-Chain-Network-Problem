#pragma once
class CProblem
{
public:
	CProblem();
	~CProblem();
	virtual int getSizeOfSln() = 0;
	virtual double getMaxMin(int index, double *pdSolution, double *error, int length) = 0;
	virtual double dGetQuality(double *pdSolution, int length) = 0;
	virtual double bConstraintSatisfied(double *pdSolution, double *error, int length) = 0;
	//virtual void giveProblem();

};

