#include "CDiffEvol.h"

const int CDiffEvol::MAXIMUM_TRIES = 50;
const int CDiffEvol::DEFAULT_SIZE = 3;
const double CDiffEvol::MINIMUM = 0;
const double CDiffEvol::DIFF_WEIGHT = 0.1;
const double CDiffEvol::CROSS_PROB = 0.3;

CDiffEvol::CDiffEvol()
{
	this->solutions = new double*[DEFAULT_SIZE];
	this->length = DEFAULT_SIZE;
}

CDiffEvol::CDiffEvol(int new_length) {
	this->solutions = new double*[new_length];
	this->length = new_length;
}


CDiffEvol::~CDiffEvol()
{
	for (int i = 0; i < this->length; i++) {
		delete this->solutions[i];
	}
	delete this->solutions;
}
//void getMaxMin(int index, double *pdSolution, double *error, int length);
double ***CDiffEvol::evaluate(CMscnProblem *c1) {
	std::cout << "DE\n";
	double maxim = 0;
	double first_maxim = 0;
	double test2 = 0;
	int size = c1->providers*c1->factories + c1->factories*c1->magazines + c1->magazines*c1->shops;
	//std::cout << " " << size << "\n";
	double test;
	/*std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(50, 100);*/
	CRandom randomizer1;
	CRandom randomizer2;
	CRandom randomizer3;
	CRandom randomizer4;
	int counter = 0;
	double *dbls1 = new double[size];
	double *dbls2 = new double[size];
	double *dbls3 = new double[size];
	for (int i = 0; i < this->length; i++) {
		this->solutions[i] = new double[size];
		for (int j = 0; j < size; j++) {
			solutions[i][j] = randomizer1.getDouble(MINIMUM, c1->getMaxMin(j, solutions[i], &test, size));
			//std::cout << solutions[i][j] << " ";
			//std::cout << " Max " << c1->getMaxMin(j, solutions[i], &test, size) << " ";
		}
		//std::cout << "\n";
	}
	double **first_solutions = new double*[this->length];
	for (int i = 0; i < this->length; i++) {
		first_solutions[i] = new double[size];
		for (int j = 0; j < size; j++) {
			first_solutions[i][j] = solutions[i][j];
		}
	}
	//std::cout << "\n";
	for (int i = 0; i < this->length; i++) {
		/*for (int j = 0; j < size; j++) {
			std::cout << solutions[i][j] << " ";
		}*/
		//std::cout << "PROFIT DLA " << i << " = " << c1->dGetQuality(solutions[i], size) << "\n";
		if (c1->dGetQuality(solutions[i], size) > maxim) {
			maxim = c1->dGetQuality(solutions[i], size);
			first_maxim = c1->dGetQuality(solutions[i], size);
		}
		//std::cout << maxim << "\n";
		//std::cout << "\n";
	}
	std::cout << "MAXIM = " << maxim << "\n";
	//std::cout << "\n\n\n\n";
	double *indNew = new double[size];
	int counter2 = 1;
	bool flag = true;
	while (counter < MAXIMUM_TRIES) {

		for (int k = 0; k < this->length; k++) {
			for (int i = 0; i < size; i++) {
				dbls1[i] = randomizer2.getDouble(MINIMUM, c1->getMaxMin(i, dbls1, &test, size));
				dbls2[i] = randomizer3.getDouble(MINIMUM, c1->getMaxMin(i, dbls2, &test, size));
				dbls3[i] = randomizer4.getDouble(MINIMUM, c1->getMaxMin(i, dbls3, &test, size));
			}

			if (individualsAreDifferent(&solutions[k], &dbls1, &dbls2, &dbls3, size)) {
				for (int i = 0; i < size; i++) {
					std::random_device rd;
					std::mt19937 gen(rd());
					std::uniform_real_distribution<> dis(0, 1);
					if (dis(gen) < CROSS_PROB) {
						indNew[i] = dbls1[i] + DIFF_WEIGHT * (dbls2[i] - dbls3[i]);
						if (indNew[i] < 0) {
							indNew[i] = 0;
						}
						else if(indNew[i] > c1->getMaxMin(i, indNew, &test, size))
							indNew[i] = c1->getMaxMin(i, indNew, &test, size);
					}
					else {
						indNew[i] = solutions[k][i];
					}
				}
				if (c1->dGetQuality(indNew, size) > c1->dGetQuality(solutions[k], size)) {
					for (int i = 0; i < size; i++) {
						solutions[k][i] = indNew[i];
					}
					if (c1->dGetQuality(indNew, size) > maxim) {
						maxim = c1->dGetQuality(indNew, size);
					}
				}
				/*for (int m = 0; m< size; m++) {
					std::cout << "PROFIT DLA " << m << " = " << c1->dGetQuality(solutions[m], size) << "\n";
				}*/
			}

			
			//std::cout << "PROFIT DLA " << k << " = " << c1->dGetQuality(solutions[k], size) << "\n";
			//std::cout << "\n k = " << k << "\n";
		}
		
		counter++;
		std::cout << "After evaluate number " << counter << "\n";
		std::cout << "MAXIM = " << maxim << "\n";
		
		if (counter2 % 10 == 0 && flag == true) {
			length /= 2;
			flag = false;
		}
		else if (counter2 % 10 == 0 && flag == false) {
			length *= 2;
			flag = true;

			for (int i = 0; i < this->length; i++) {

				for (int j = 0; j < size; j++) {
					solutions[i][j] = randomizer1.getDouble(MINIMUM, c1->getMaxMin(j, solutions[i], &test, size));
				}
			}
		}
		counter2++;
		

		std::cout << "\n\n\nProfits for whole population\n";
		for (int i = 0; i < this->length; i++) {

			std::cout << "PROFIT DLA " << i << " = " << c1->dGetQuality(solutions[i], size);
			std::cout << "\n";
		}
		std::cout << "MAXIM = " << maxim << "\n";
	}
	std::cout << "\n\n\nProfits for whole population\n";
	for (int i = 0; i < this->length; i++) {
		/*for (int j = 0; j < size; j++) {
			std::cout << solutions[i][j] << " ";
		}*/
		std::cout << "PROFIT DLA " << i << " = " << c1->dGetQuality(solutions[i], size);
		//std::cout << "sat " << c1->bConstraintSatisfied(solutions[i], &test2, size) << "\n";
		std::cout << "\n";
	}
	std::cout << "MAXIM = " << maxim << "\n";

	std::cout << "\nBEFORE\n\n";
	for (int i = 0; i < this->length; i++) {
		/*for (int j = 0; j < size; j++) {
			std::cout << solutions[i][j] << " ";
		}*/
		std::cout << "PROFIT DLA " << i << " = " << c1->dGetQuality(first_solutions[i], size);
		std::cout << "\n";
	}
	std::cout << "FIRST_MAXIM = " << first_maxim << "\n";
	std::cout << "\n\n\n";
	delete dbls1;
	delete dbls2;
	delete dbls3;
	delete indNew;

	return &solutions;

}


bool CDiffEvol::individualsAreDifferent(double **sln1, double **sln2, double **sln3, double **sln4, int size) {
	bool test1_2 = true;
	bool test1_3 = true;
	bool test1_4 = true;
	bool test2_3 = true;
	bool test2_4 = true;
	bool test3_4 = true;
	for (int i = 0; i < size; i++) {
		if ((*sln1)[i] != (*sln2)[i])
			test1_2 = false;

		if ((*sln1)[i] != (*sln3)[i])
			test1_3 = false;

		if ((*sln1)[i] != (*sln4)[i])
			test1_4 = false;

		if ((*sln2)[i] != (*sln3)[i])
			test2_3 = false;

		if ((*sln2)[i] != (*sln4)[i])
			test2_4 = false;

		if ((*sln3)[i] != (*sln4)[i])
			test3_4 = false;

		if (test1_2 == false && test1_3 == false && test1_4 == false && test2_3 == false && test2_4 == false && test3_4 == false) {
			return true;
		}
	}
	return false;
}


