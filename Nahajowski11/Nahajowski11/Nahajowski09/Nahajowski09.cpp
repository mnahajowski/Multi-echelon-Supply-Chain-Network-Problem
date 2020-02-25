#include "CMscnProblem.h"
#include "CRandom.h"
#include "CRandomSearch.h"
#include "CDiffEvol.h"
#include <iostream>


int main()
{

	CMscnProblem c1;
	double test = 0;

	
	c1.setProviderNumber(2);
	c1.setFactoriesNumber(2);	
	c1.setMagazinesNumber(2);	
	c1.setShopsNumber(2);
	
	c1.setAllProvidersPower();
	c1.setAllFactoriesPower();
	c1.setAllMagazinesPower();
	c1.setAllShopsPower();
	std::cout << "PO USTAWIENIACH MOCY \n";

	c1.setAllCD();
	c1.setAllCF();
	c1.setAllCM();
	
	//c1.setOneCD(1, 1, 5, &test);
	std::cout << "PO USTAWIENIACH KOSZTOW \n";
	c1.setAllUD();
	c1.setAllUF();
	c1.setAllUM();
	
	std::cout << "PO USTAWIENIACH CEN";
	c1.setAllInc();
	
	double *answer = new double[12];
	answer[0] = 100;
	answer[1] = 100;
	answer[2] = 100;
	answer[3] = 100;
	answer[4] = 100;
	answer[5] = 100;
	answer[6] = 100;
	answer[7] = 100;
	answer[8] = 100;
	answer[9] = 100;
	answer[10] = 100;
	answer[11] = 100;
	
	c1.setAllmaxMin();
	//c1.getMaxMin(0, answer, &test, 12);
	std::cout << "\nCzy spelnia warunki " << c1.bConstraintSatisfied(answer, &test, 12);
	std::cout << "\nProfit " << c1.dGetQuality(answer, 12)<<"\n";
	c1.problemToFile();
	c1.solutionToFile();
	std::cout << "\nZ PLIKU";
	
	/*double test2 = 0;
	CMscnProblem c2;
	c2.problemFromFile(&test2);
	std::cout << "\n" << test2 << "\n";*/
	double test3 = 0;
	CMscnProblem c2;
	c2.problemFromFile();
	double *answer2 = new double[3];
	double ***mySlns2;
	answer2[0] = 10;
	answer2[1] = 10;
	answer2[2] = 10;
	c2.solutionFromFile(&test3);
	/*std::cout << "\nCzy spelnia warunki " << c2.bConstraintSatisfied(answer2, &test, 3);
	std::cout << "\nProfit " << c2.dGetQuality(answer2, 3) << "\n";*/
	//std::cout <<"\nProfit " << c2.dGetQuality(answer, 12) << "\n";
	/*std::cout<<"\nCzy spelnia warunki "<< c2.bConstraintSatisfied(answer, &test, 12);
	std::cout << "\nProfit " << c2.dGetQuality(answer, 12)<<"\n";*/
	std::cout << "\n"<<c2.overall() << "\n";

	std::cout << "\n";

	/*CRandom *c10 = new CRandom(10);
	double *myDbls = new double[10];
	int *myInts = new int[10];
	myDbls = c10->getDoubles(0, 5);
	std::cout << "\n\n\n";
	myInts = c10->getInts(25, 50);*/

	CMscnProblem c5;
	c5.setProviderNumber(2);
	c5.setFactoriesNumber(2);
	c5.setMagazinesNumber(2);
	c5.setShopsNumber(2);
	c5.setAllInc();
	c5.vGenerateInstance(3);
	
	//c5.setAllmaxMin();
	std::cout << "\nCzy spelnia warunki " << c5.bConstraintSatisfied(answer, &test, 12);
	std::cout << "\nProfit " << c5.dGetQuality(answer, 12) << "\n";
	c5.setAllmaxMin();
	std::cout << "\n";

	
	CRandomSearch my_c;
	double *randSln = my_c.CBestRandomize(&c5);
	int sizeOfSln = c5.getSizeOfSln();
	//my_c.CBestRandomize(&c5);
	for (int i = 0; i < sizeOfSln; i++) {
		std::cout << randSln[i] << " ";
	}
	std::cout << c5.dGetQuality(randSln, sizeOfSln)<<"\n\n\n";

	std::cout << "\n";
	std::cout << "\nProfit " << c5.dGetQuality(answer, 12) << "\n";
	delete answer;
	delete answer2;
	//delete c10;
	delete randSln;
	/***************************************************/
	std::cout << "\n";
	CDiffEvol evol1(100);
	/*double **mySlns = new double*[3];
	for (int i = 0; i < 3; i++) {
		mySlns[i] = new double[sizeOfSln];
	}*/

	mySlns2 = evol1.evaluate(&c5);

}
