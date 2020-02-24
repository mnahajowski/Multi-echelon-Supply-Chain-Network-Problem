#include "CRandom.h"

CRandom::CRandom()
{
	std::random_device random_seed;
	setSeed(random_seed());
}

CRandom::CRandom(int new_seed) {
	setSeed(new_seed);
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

void CRandom::setSeed(int new_seed) {
	gen.seed(new_seed);
}


