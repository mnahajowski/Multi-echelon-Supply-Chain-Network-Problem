#include "CRandom.h"

CRandom::CRandom()
{
}


CRandom::~CRandom()
{
}

int CRandom::getInt(int left, int right) {
	if (left > right) {
		int temp = left;
		left = right;
		right = temp;
	}

	std::uniform_int_distribution<> dis(left, right);
	return dis(gen);
}

double CRandom::getDouble(double left, double right) {
	if (left > right) {
		double temp = left;
		left = right;
		right = temp;
	}

	std::uniform_real_distribution<> dis(left, right);
	return dis(gen);
}