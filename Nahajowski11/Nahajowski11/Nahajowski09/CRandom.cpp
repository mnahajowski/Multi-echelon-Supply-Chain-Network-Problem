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

/*int *CRandom::getInts(int left, int right) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(left, right);
	std::cout << "\n";
	for (int i = 0; i < this->size; i++) {
		this->rand_ints[i] = dis(gen);
		std::cout << rand_ints[i] << " ";
	}
	std::cout << "\n";

	return this->rand_ints;
}

double *CRandom::getDoubles(double left, double right) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(left, right);

	std::cout << "\n";
	for (int i = 0; i < this->size; i++) {
		this->rand_dbls[i] = dis(gen);
		std::cout << rand_dbls[i] << " ";
	}
	std::cout << "\n";

	return this->rand_dbls;
}*/

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


