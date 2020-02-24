#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <atlstr.h>
#include <sstream>
#include <random>
#include "CRandom.h"
#define _CRT_SECURE_NO_DEPRECATE
class CMscnProblem
{
public:
	CMscnProblem();
	~CMscnProblem();
	const static int DEFAULT_SIZE;

	void setProviderNumber(int number_of_providers);
	void setFactoriesNumber(int number_of_factories);
	void setMagazinesNumber(int number_of_magazines);
	void setShopsNumber(int number_of_shops);

	void v_copy_array(double *cOther, int old_number, int new_number, double **old);
	void v_copy_sd(double *cOther, int old_number, int new_number);
	void v_copy_matrix(double **cOther, int old_number, int new_number, int second_size,double ***old);
	void v_copy_matrix_another(double **cOther, int old_number, int new_number, int second_size, double ***old);

	double income();
	double transport_cost();
	double universal_cost();
	double overall();

	bool providerPower();
	bool factoryPower();
	bool magazinePower();
	bool shopPower();

	void setAllProvidersPower();
	void setAllFactoriesPower();
	void setAllMagazinesPower();
	void setAllShopsPower();

	void setOneProviderPower(int index, double value, double *error);
	void setOneFactoryPower(int index, double value, double *error);
	void setOneMagazinePower(int index, double value, double *error);
	void setOneShopPower(int index, double value, double *error);

	void setAllCD();
	void setAllCF();
	void setAllCM();

	void setOneCD(int provider_index, int factory_index, double value, double *error);
	void setOneCF(int factory_index, int magazine_index, double value, double *error);
	void setOneCM(int magazine_index, int shop_index, double value, double *error);

	void setOneUD(int index, double value, double *error);
	void setOneUF(int index, double value, double *error);
	void setOneUM(int index, double value, double *error);

	void setOneInc(int index, double value, double *error);
	void setAllInc();

	void setAllmaxMin();
	void setOneMaxMinXD(int x, int y, double value, double *error);
	void setOneMaxMinXF(int x, int y, double value, double *error);
	void setOneMaxMinXM(int x, int y, double value, double *error);
	void getMaxMin(int index, double *pdSolution, double *error, int length);

	void setAllUD();
	void setAllUF();
	void setAllUM();
		

	bool factorySum();
	bool magazineSum();

	void problemToFile();
	void solutionToFile();

	void problemFromFile();
	void setAllFromFile(std::string stream, int length);

	int getSizeOfSln() { return providers * factories + factories * magazines + magazines * shops; }

	void solutionFromFile(double *error);
	void setSlnFromFile(std::string stream, int length, double *error);

	std::string allArraytoString(double **from, int length);
	std::string allMatrixTostring(double ***from, int x, int y);
	std::string allNumberstoString(int *from);

	double dGetQuality(double *pdSolution, int length);
	bool bConstraintSatisfied(double *pdSolution, double *error, int length);

	void vGenerateInstance(int iInstanceSeed);

	const static double NULL_POINTER_ERROR;
	const static double INVALID_SIZE_ERROR;
	const static double NEGATIVE_VALUES_ERROR;
	const static double PRINT_MANY_ERROR;
	const static double INVALID_INDEX;
	const static double INVALID_VALUE;
	const static double PROVIDER_POWER_EXTENDED_ERROR;
	const static double FACTORY_POWER_EXTENDED_ERROR;
	const static double MAGAZINE_POWER_EXTENDED_ERROR;
	const static double SHOP_POWER_EXTENDED_ERROR;
	const static double FACTORY_SUM_EXTENDED_ERROR;
	const static double MAGAZINE_SUM_EXTENDED_ERROR;
	const static double WRONG_SEPARATOR_ERROR;
	const static double INVALID_PROVIDER_NUMBER;
	const static double INVALID_FACTORY_NUMBER;
	const static double INVALID_MAGAZINE_NUMBER;
	const static double INVALID_SHOP_NUMBER;

	const static double MINIMUM_COST_CD;
	const static double MINIMUM_COST_CF;
	const static double MINIMUM_COST_CM;
	const static double MAXIMUM_COST_CD;
	const static double MAXIMUM_COST_CF;
	const static double MAXIMUM_COST_CM;

	const static double MINIMUM_COST_UD;
	const static double MAXIMUM_COST_UD;
	const static double MINIMUM_COST_UF;
	const static double MAXIMUM_COST_UF;
	const static double MINIMUM_COST_UM;
	const static double MAXIMUM_COST_UM;

	const static double MINIMUM_COST_SD;
	const static double MAXIMUM_COST_SD;
	const static double MINIMUM_COST_SF;
	const static double MAXIMUM_COST_SF;
	const static double MINIMUM_COST_SM;
	const static double MAXIMUM_COST_SM;
	const static double MINIMUM_COST_SS;
	const static double MAXIMUM_COST_SS;


	
private: 
	double **cd;
	double **cf;
	double **cm;

	double *sd;
	double *sf;
	double *sm;
	double *ss;
	double *p;	//przychody w danych sklepach
	double *ud;	// jednorazowe koszty
	double *uf;
	double *um;

	double **xd;
	double **xf;
	double **xm;

	double **minmaxxd;
	double **minmaxxf;
	double **minmaxxm;

	int providers;
	int factories;
	int magazines;
	int shops;

	friend class CRandomSearch;
};

