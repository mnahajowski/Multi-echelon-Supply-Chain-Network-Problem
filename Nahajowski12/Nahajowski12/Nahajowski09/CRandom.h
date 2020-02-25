#pragma once
#include <random>
#include <iostream>

class CRandom
{
public:
	CRandom();
	CRandom(int seed);
	~CRandom();

	void setSeed(int seed);

	int getInt(int left, int right);
	double getDouble(double left, double right);

private:
	std::mt19937 gen;
};

