#include "CRandomSearch.h"

const int CRandomSearch::MAXIMUM_TRIES = 10;
const double CRandomSearch::WANTED_VALUE = 100000;

CRandomSearch::CRandomSearch()
{

}


CRandomSearch::~CRandomSearch()
{
}

double *CRandomSearch::CBestRandomize(CMscnProblem *c1) {
	int size = c1->providers*c1->factories + c1->factories*c1->magazines + c1->magazines*c1->shops;
	double *dbls = new double[size];
	double *bestDbls = new double[size];
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(50,100);
	int counter = 0;

	while (counter < MAXIMUM_TRIES && c1->dGetQuality(bestDbls, size) < WANTED_VALUE) {
		for (int i = 0; i < size; i++) {
			dbls[i] = dis(gen);
		}
		if (counter == 0) {
			for (int i = 0; i < size; i++) {
				bestDbls[i] = dbls[i];
			}
		}
		else if (c1->dGetQuality(dbls, size) > c1->dGetQuality(bestDbls, size)) {
			for (int i = 0; i < size; i++) {
				bestDbls[i] = dbls[i];
			}
		}
		std::cout << "\nNOWY PROFIT " << c1->dGetQuality(dbls, size) << "\n";
		counter++;
	}
	

	delete dbls;
	return bestDbls;

}
