#include "CRandomSearch.h"

const int CRandomSearch::MAXIMUM_TRIES = 300;
const double CRandomSearch::WANTED_VALUE = 100000;

CRandomSearch::CRandomSearch()
{

}


CRandomSearch::~CRandomSearch()
{
}

double *CRandomSearch::optimize(double seconds) {
	this->timer.cStart();
	//int size = c1->providers*c1->factories + c1->factories*c1->magazines + c1->magazines*c1->shops;
	int size = this->problem->getSizeOfSln();
	double *dbls = new double[size];
	double *bestDbls = new double[size];
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(50,600);
	int counter = 0;
	//std::cout << "daada";
	while (this->timer.cResult() < seconds) {
		for (int i = 0; i < size; i++) {
			dbls[i] = dis(gen);
		}
		
		if (counter == 0) {
			this->problem->dGetQuality(dbls, size);
			for (int i = 0; i < size; i++) {
				bestDbls[i] = dbls[i];
			}
		}
		else if (this->problem->dGetQuality(dbls, size) > this->problem->dGetQuality(bestDbls, size)) {
			for (int i = 0; i < size; i++) {
				bestDbls[i] = dbls[i];
			}
		}
		//std::cout << "\nAfter evaluate number " + counter;
		std::cout << "\nAfter evaluate number " << counter;
		std::cout << "\nNOWY MAX PROFIT1 " << this->problem->dGetQuality(dbls, size) << "\n";
		std::cout << "\nNOWY MAX PROFIT " << this->problem->dGetQuality(bestDbls, size) << "\n";
		counter++;
		//std::cout <<
	}
	

	delete dbls;
	return bestDbls;

}
