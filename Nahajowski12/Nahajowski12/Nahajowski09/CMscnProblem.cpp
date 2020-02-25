#include "CMscnProblem.h"
#include "CRandomSearch.h"
//jak sprawdziæ czy sie utworzyl
const int CMscnProblem::DEFAULT_SIZE = 3;
const double CMscnProblem::NULL_POINTER_ERROR = -1;
const double CMscnProblem::INVALID_SIZE_ERROR = -2;
const double CMscnProblem::NEGATIVE_VALUES_ERROR = -3;
const double CMscnProblem::INVALID_INDEX = -4;
const double CMscnProblem::INVALID_VALUE = -5;
const double CMscnProblem::PROVIDER_POWER_EXTENDED_ERROR = -6;
const double CMscnProblem::FACTORY_POWER_EXTENDED_ERROR = -7;
const double CMscnProblem::MAGAZINE_POWER_EXTENDED_ERROR = -8;
const double CMscnProblem::SHOP_POWER_EXTENDED_ERROR = -9;
const double CMscnProblem::FACTORY_SUM_EXTENDED_ERROR = -10;
const double CMscnProblem::MAGAZINE_SUM_EXTENDED_ERROR = -11;
const double CMscnProblem::WRONG_SEPARATOR_ERROR = -12;
const double CMscnProblem::INVALID_PROVIDER_NUMBER = -13;
const double CMscnProblem::INVALID_FACTORY_NUMBER = -14;
const double CMscnProblem::INVALID_MAGAZINE_NUMBER = -15;
const double CMscnProblem::INVALID_SHOP_NUMBER = -16;

const double CMscnProblem::MINIMUM_COST_CD = 1;
const double CMscnProblem::MINIMUM_COST_CF = 1;
const double CMscnProblem::MINIMUM_COST_CM = 1;
const double CMscnProblem::MAXIMUM_COST_CD = 10;
const double CMscnProblem::MAXIMUM_COST_CF = 10;
const double CMscnProblem::MAXIMUM_COST_CM = 10;

const double CMscnProblem::MINIMUM_COST_UD = 1;
const double CMscnProblem::MAXIMUM_COST_UD = 500;
const double CMscnProblem::MINIMUM_COST_UF = 1;
const double CMscnProblem::MAXIMUM_COST_UF = 500;
const double CMscnProblem::MINIMUM_COST_UM = 1;
const double CMscnProblem::MAXIMUM_COST_UM = 500;

const double CMscnProblem::MINIMUM_COST_SD = 1;
const double CMscnProblem::MAXIMUM_COST_SD = 100;
const double CMscnProblem::MINIMUM_COST_SF = 1;
const double CMscnProblem::MAXIMUM_COST_SF = 100;
const double CMscnProblem::MINIMUM_COST_SM = 1;
const double CMscnProblem::MAXIMUM_COST_SM = 100;
const double CMscnProblem::MINIMUM_COST_SS = 1;
const double CMscnProblem::MAXIMUM_COST_SS = 100;

//const double CMscnProblem::PRINT_MANY_ERROR = 4;

CMscnProblem::CMscnProblem()
{	
	this->providers = DEFAULT_SIZE;
	this->factories = DEFAULT_SIZE;
	this->magazines = DEFAULT_SIZE;
	this->shops = DEFAULT_SIZE;

	this->sd = new double[this->providers];
	this->sf = new double[this->factories];
	this->sm = new double[this->magazines];
	this->ss = new double[this->shops];
	this->p = new double[this->shops];
	this->ud = new double[this->providers];
	this->uf = new double[this->factories];
	this->um = new double[this->magazines];

	this->cd = new double*[this->providers];
	this->xd = new double*[this->providers];
	this->minmaxxd = new double*[(this->providers)];

	for (int i = 0; i < this->providers; i++) {
		this->cd[i] = new double[this->factories];
		this->xd[i] = new double[this->factories];
		this->minmaxxd[i] = new double[2*(this->factories)];
	}

	this->cf = new double*[this->factories];
	this->xf = new double*[this->factories];
	this->minmaxxf = new double*[(this->factories)];

	for (int i = 0; i < this->factories; i++) {
		this->cf[i] = new double[this->magazines];
		this->xf[i] = new double[this->magazines];
		this->minmaxxf[i] = new double[2*(this->magazines)];
	}

	this->cm = new double*[this->magazines];
	this->xm = new double*[this->magazines];
	this->minmaxxm = new double*[(this->magazines)];
	for (int i = 0; i < this->magazines; i++) {
		this->cm[i] = new double[this->shops];
		this->xm[i] = new double[this->shops];
		this->minmaxxm[i] = new double[2*(this->shops)];
	}

}

CMscnProblem::~CMscnProblem()
{
	
	delete this->sd;
	delete this->sf;
	delete this->sm;
	delete this->ss;
	delete this->p;
	delete this->ud;
	delete this->uf;
	delete this->um;
	
	
	for (int i = 0; i < this->providers; i++) {
		delete this->cd[i];
		delete this->xd[i];
		delete this->minmaxxd[i];
	}
	delete this->cd;
	delete this->xd;
	delete this->minmaxxd;
	
	for (int i = 0; i < this->factories; i++) {
		delete this->cf[i];
		delete this->xf[i];
		delete this->minmaxxf[i];
	}
	delete this->cf;
	delete this->xf;
	delete this->minmaxxf;
	
	for (int i = 0; i < this->magazines; i++) {
		
		delete this->cm[i];
		delete this->xm[i];
		delete this->minmaxxm[i];
	}
	
	delete this->cm;
	delete this->xm;
	delete this->minmaxxm;

}

void CMscnProblem::setProviderNumber(int new_number_of_providers) {

	double *new_sd = new double[new_number_of_providers];
	v_copy_array(new_sd, this->providers, new_number_of_providers, &(this->sd));

	double *new_ud = new double[new_number_of_providers];
	v_copy_array(new_ud, this->providers, new_number_of_providers, &(this->ud));

	double **new_cd = new double*[new_number_of_providers];

	v_copy_matrix(new_cd, this->providers, new_number_of_providers, this->factories, &this->cd);
	
	double **new_xd = new double*[new_number_of_providers];
	
	v_copy_matrix(new_xd, this->providers, new_number_of_providers, this->factories, &this->xd);
	
	this->providers = new_number_of_providers;
}

void CMscnProblem::setFactoriesNumber(int new_number_of_factories) {

	
	double *new_sf = new double[new_number_of_factories];
	v_copy_array(new_sf, this->factories, new_number_of_factories, &(this->sf));
	
	double *new_uf = new double[new_number_of_factories];
	v_copy_array(new_uf, this->factories, new_number_of_factories, &(this->uf));

	double **new_cf = new double*[new_number_of_factories];
	
	v_copy_matrix(new_cf, this->factories, new_number_of_factories, this->magazines, &(this->cf));
	
	
	double **new_cd = new double*[this->providers];
	v_copy_matrix_another(new_cd, this->factories, new_number_of_factories, this->providers, &(this->cd));
	
	double **new_xf = new double*[new_number_of_factories];
	
	v_copy_matrix(new_xf, this->factories, new_number_of_factories, this->magazines, &(this->xf));

	double **new_xd = new double*[this->providers];
	v_copy_matrix_another(new_xd, this->factories, new_number_of_factories, this->providers, &(this->xd));

	this->factories = new_number_of_factories;
	
}

void CMscnProblem::setMagazinesNumber(int new_number_of_magazines) {
	
	double *new_sm = new double[new_number_of_magazines];
	v_copy_array(new_sm, this->magazines, new_number_of_magazines, &(this->sm));

	double *new_um = new double[new_number_of_magazines];
	v_copy_array(new_um, this->magazines, new_number_of_magazines, &(this->um));

	double **new_cm = new double*[new_number_of_magazines];
	
	v_copy_matrix(new_cm, this->shops, new_number_of_magazines, this->shops, &(this->cm));
	double **new_cf = new double*[this->factories];
	v_copy_matrix_another(new_cf, this->magazines, new_number_of_magazines, this->factories, &(this->cf));

	double **new_xm = new double*[new_number_of_magazines];
	v_copy_matrix(new_xm, this->magazines, new_number_of_magazines, this->factories, &(this->xm));
	double **new_xf = new double*[this->factories];

	v_copy_matrix_another(new_xf, this->magazines, new_number_of_magazines, this->factories, &(this->xf));

	this->magazines = new_number_of_magazines;
}


void CMscnProblem::setShopsNumber(int new_number_of_shops) {

	double *new_ss = new double[new_number_of_shops];
	v_copy_array(new_ss, this->shops, new_number_of_shops, &(this->ss));

	double *new_p = new double[new_number_of_shops];
	v_copy_array(new_p, this->providers, new_number_of_shops, &(this->p));
	
	double **new_cm = new double*[this->magazines];
	
	v_copy_matrix_another(new_cm, this->shops, new_number_of_shops,this->magazines, &(this->cm));
	
	double **new_xm = new double*[this->magazines];
	v_copy_matrix_another(new_xm, this->shops, new_number_of_shops, this->magazines, &(this->xm));
	this->shops = new_number_of_shops;
}

void CMscnProblem::v_copy_sd(double *cOther, int old_number, int new_number) {
	int new_length_temp = new_number;
	if (new_number > old_number) {
		new_length_temp = old_number;
	}

	for (int i = 0; i < new_length_temp; i++) {
		cOther[i] = this->sd[i];
	}
	delete[] this->sd;
	this->sd = cOther;
}

void CMscnProblem::v_copy_matrix(double **cOther, int old_number, int new_number, int second_size, double ***old) {

	int new_length_temp = new_number;

	if (new_number > old_number) {
		new_length_temp = old_number;
	}

	for (int i = 0; i < new_length_temp; i++) {
		cOther[i] = new double[second_size];

		for (int j = 0; j < second_size; j++) {
			cOther[i][j] = (*old)[i][j];
		}
	}
	for (int i = new_length_temp; i < new_number; i++) {
		cOther[i] = new double[second_size];
	}

	for (int i = 0; i < old_number; i++) {
		delete (*old)[i];
	}
	
	delete *old;
	//cOther[1][1] = 6.7;
	(*old) = cOther;
}

void CMscnProblem::v_copy_matrix_another(double **cOther, int old_number, int new_number, int second_size, double ***old) {

	int new_length_temp = new_number;
	if (new_number > old_number) {
		new_length_temp = old_number;
	}

	for (int i = 0; i < second_size; i++) {
		cOther[i] = new double[new_number];

		for (int j = 0; j < new_length_temp; j++) {
			cOther[i][j] = (*old)[i][j];
		}
	}

	for (int i = 0; i < second_size; i++) {
		delete (*old)[i];
	}

	delete *old;

	(*old) = cOther;
}


void CMscnProblem::v_copy_array(double *cOther, int old_number, int new_number, double **old) {

	int new_length_temp = new_number;
	if (new_number > old_number) {
		new_length_temp = old_number;
	}

	for (int i = 0; i < new_length_temp; i++) {
		cOther[i] = (*old)[i];
	}

	delete[] *old;
	*old = cOther;
}

double CMscnProblem::income() {

	double current_income = 0;
	//std::cout << "\nincome ";
	for (int i = 0; i < this->magazines; i++) {
		for (int j = 0; j < this->shops; j++) {
			current_income += this->xm[i][j] * p[j];
		}
		//std::cout << current_income << " ";
	}

	//std::cout << "dada " << xm[0][0] << " " << p[0] << "\n";
	return current_income;
}

double CMscnProblem::transport_cost() {
	double current_transport_cost = 0;

	for (int i = 0; i < this->providers; i++) {
		for (int j = 0; j < this->factories; j++) {
			current_transport_cost += cd[i][j] * xd[i][j];
		}
	}

	for (int i = 0; i < this->factories; i++) {
		for (int j = 0; j < this->magazines; j++) {
			current_transport_cost += cf[i][j] * xf[i][j];
		}
	}

	for (int i = 0; i < this->magazines; i++) {
		for (int j = 0; j < this->shops; j++) {
			current_transport_cost += cm[i][j] * xm[i][j];
		}
	}

	return current_transport_cost;
}

double CMscnProblem::universal_cost() {
	double current_universal_cost = 0;
	double current_in_place = 0;

	for (int i = 0; i < this->providers; i++) {
		for (int j = 0; j < this->factories; j++) {
			current_in_place += xd[i][j];
		}
		if (current_in_place > 0) {
			current_universal_cost += ud[i];
		}
	}
	current_in_place = 0;
	//std::cout << "\ncost " << current_universal_cost << "\n";
	for (int i = 0; i < this->factories; i++) {
		for (int j = 0; j < this->magazines; j++) {
			current_in_place += xf[i][j];
		}
		if (current_in_place > 0)
			current_universal_cost += uf[i];
	}
	
	current_in_place = 0;

	for (int i = 0; i < this->magazines; i++) {
		for (int j = 0; j < this->shops; j++) {
			current_in_place += xm[i][j];
		}
		if (current_in_place > 0)
			current_universal_cost += um[i];
	}
	//std::cout << "\ncost " << current_universal_cost << "\n";
	return current_universal_cost;

}

double CMscnProblem::overall() {
	//std::cout << "\nPrzychody : " << income() << " Wydatki " << transport_cost() << " " << universal_cost()<<"\n";
	return (income() - transport_cost() - universal_cost());
}

void CMscnProblem::setAllProvidersPower() {
	for (int i = 0; i < this->providers; i++) {
		sd[i] = 1000;
	}
}

void CMscnProblem::setAllFactoriesPower() {
	for (int i = 0; i < this->factories; i++) {
		sf[i] = 1000;
	}
}

void CMscnProblem::setAllMagazinesPower() {
	for (int i = 0; i < this->magazines; i++) {
		sm[i] = 1000;
	}
}

void CMscnProblem::setAllShopsPower() {
	for (int i = 0; i < this->shops; i++) {
		ss[i] = 1000;
	}
}


void CMscnProblem::setOneProviderPower(int index, double value, double *error) {
	if (value < 0)
		*error = INVALID_VALUE;
	else if (index < 0 || index >= this->providers)
		*error = INVALID_INDEX;
	else
		sd[index] = value;
}

void CMscnProblem::setOneFactoryPower(int index, double value, double *error) {
	if (value < 0)
		*error = INVALID_VALUE;
	else if (index < 0 || index >= this->factories)
		*error = INVALID_INDEX;
	else
		sf[index] = value;
}

void CMscnProblem::setOneMagazinePower(int index, double value, double *error) {
	if (value < 0)
		*error = INVALID_VALUE;
	else if (index < 0 || index >= this->magazines)
		*error = INVALID_INDEX;
	else
		sm[index] = value;
}

void CMscnProblem::setOneShopPower(int index, double value, double *error) {
	if (value < 0)
		*error = INVALID_VALUE;
	else if (index < 0 || index >= this->shops)
		*error = INVALID_INDEX;
	else
		ss[index] = value;
}

void CMscnProblem::setAllCD() {
	for (int i = 0; i < this->providers; i++) {
		for (int j = 0; j < this->factories; j++) {
			cd[i][j] = 2;
		}
	}
}

void CMscnProblem::setAllCF() {
	for (int i = 0; i < this->factories; i++) {
		for (int j = 0; j < this->magazines; j++) {
			cf[i][j] = 2;
		}
	}
}

void CMscnProblem::setAllCM() {
	for (int i = 0; i < this->magazines; i++) {
		for (int j = 0; j < this->shops; j++) {
			cm[i][j] = 2;
		}
	}
}

void CMscnProblem::setOneCD(int provider_index, int factory_index, double value, double *error) {
	if (value < 0)
		*error = INVALID_VALUE;
	else if (provider_index < 0 || provider_index >= this->providers || factory_index < 0 || factory_index >= this->factories)
		*error = INVALID_INDEX;
	else
		cd[provider_index][factory_index] = value;
}

void CMscnProblem::setOneCF(int factory_index, int magazine_index, double value, double *error) {
	if (value < 0)
		*error = INVALID_VALUE;
	else if (factory_index < 0 || factory_index >= this->factories || magazine_index < 0 || magazine_index >= this->magazines)
		*error = INVALID_INDEX;
	else
		cf[factory_index][magazine_index] = value;
}

void CMscnProblem::setOneCM(int magazine_index, int shop_index, double value, double *error) {
	if (value < 0)
		*error = INVALID_VALUE;
	else if (magazine_index < 0 || magazine_index >= this->magazines || shop_index < 0 || shop_index >= this->shops)
		*error = INVALID_INDEX;
	else
		cm[magazine_index][shop_index] = value;
}



bool CMscnProblem::providerPower() {
	double current_sum = 0;
	for (int k = 0; k < this->providers; k++) {

		current_sum = 0;
		//std::cout << "da";

		for (int i = 0; i < this->factories; i++) {
			current_sum += xd[k][i];
		}
		if (current_sum > sd[k])
			return false;
	}
	return true;
}

bool CMscnProblem::factoryPower() {

	double current_sum = 0;
	for (int k = 0; k < this->factories; k++) {
		current_sum = 0;

		for (int i = 0; i < this->magazines; i++) {
			current_sum += xf[k][i];
		}
		if (current_sum > sf[k])
			return false;
	}
	return true;

}

bool CMscnProblem::magazinePower() {

	double current_sum = 0;

	for (int k = 0; k < this->magazines; k++) {
		current_sum = 0;
		for (int i = 0; i < this->shops; i++) {
			current_sum += xm[k][i];
		}

		if (current_sum > sm[k])
			return false;
	}
	return true;
}

bool CMscnProblem::shopPower() {

	double current_sum = 0;

	for (int k = 0; k < this->shops; k++) {
		current_sum = 0;

		for (int i = 0; i < this->magazines; i++) {
			current_sum += xm[i][k];
		}

		if (current_sum > ss[k])
			return false;
	}

	return true;
}

bool CMscnProblem::factorySum() {

	double current_sum_in = 0;
	double current_sum_out = 0;

	for (int k = 0; k < this->factories; k++) {
		current_sum_in = 0;
		current_sum_out = 0;

		for (int i = 0; i < this->providers; i++) {
			current_sum_in += xd[i][k];
		}
		for (int j = 0; j < this->magazines; j++) {
			current_sum_out += xf[k][j];
		}
		//std::cout << "\n" << current_sum_in << " " << current_sum_out << "\n";
		if (current_sum_out > current_sum_in)
			return false;
	}
	return true;
}

bool CMscnProblem::magazineSum() {

	double current_sum_in = 0;
	double current_sum_out = 0;

	for (int k = 0; k < this->magazines; k++) {
		current_sum_in = 0;
		current_sum_out = 0;

		for (int i = 0; i < this->factories; i++) {
			current_sum_in += xf[i][k];
		}

		for (int j = 0; j < this->shops; j++) {
			current_sum_out += xm[k][j];
		}

		//std::cout << "\n" << current_sum_in << " " << current_sum_out << "\n";

		if (current_sum_out > current_sum_in)
			return false;
	}
	//std::cout << "dadA";
	
	return true;

}

void CMscnProblem::setOneUD(int index, double value, double *error) {
	if (value < 0)
		*error = INVALID_VALUE;
	else if (index < 0 || index >= this->providers)
		*error = INVALID_INDEX;
	else
		ud[index] = value;
}

void CMscnProblem::setOneUF(int index, double value, double *error) {
	if (value < 0)
		*error = INVALID_VALUE;
	else if (index < 0 || index >= this->factories)
		*error = INVALID_INDEX;
	else
		uf[index] = value;
}

void CMscnProblem::setOneUM(int index, double value, double *error) {
	if (value < 0)
		*error = INVALID_VALUE;
	else if (index < 0 || index >= this->magazines)
		*error = INVALID_INDEX;
	else
		um[index] = value;
}

void CMscnProblem::setAllUD() {

	for (int i = 0; i < this->providers; i++) {
		ud[i] = 1;
	}
}

void CMscnProblem::setAllUF() {

	for (int i = 0; i < this->factories; i++) {
		uf[i] = 1;
	}
}

void CMscnProblem::setAllUM() {

	for (int i = 0; i < this->factories; i++) {
		um[i] = 1;
	}
}

void CMscnProblem::setOneInc(int index, double value, double *error) {
	if (value < 0)
		*error = INVALID_VALUE;
	else if (index < 0 || index >= this->shops)
		*error = INVALID_INDEX;
	else
		p[index] = value;
}

void CMscnProblem::setAllInc() {
	for (int i = 0; i < this->shops; i++) {
		p[i] = 150;
	}
}

void CMscnProblem::setOneMaxMinXD( int x, int y, double value, double *error) {
	if (value < 0)
		*error = INVALID_VALUE;
	else if (x < 0 || y < 0 || x >= this->providers || y >= this->factories)
		*error = INVALID_INDEX;
	else
		minmaxxd[x][y] =value;
}

void CMscnProblem::setOneMaxMinXF(int x, int y, double value, double *error) {
	if (value < 0)
		*error = INVALID_VALUE;
	else if (x < 0 || y < 0 || x >= this->factories || y >= this->magazines)
		*error = INVALID_INDEX;
	else
		minmaxxd[x][y] = value;
}

void CMscnProblem::setOneMaxMinXM(int x, int y, double value, double *error) {
	if (value < 0)
		*error = INVALID_VALUE;
	else if (x < 0 || y < 0 || x >= this->magazines || y >= this->shops)
		*error = INVALID_INDEX;
	else
		minmaxxd[x][y] = value;
}

void CMscnProblem::setAllmaxMin() {
	for (int i = 0; i < (this->providers); i++) {
		for (int j = 0; j < (this->factories)*2; j+=2) {
			this->minmaxxd[i][j] = 0;
			this->minmaxxd[i][j + 1] = sd[i];
			std::cout << minmaxxd[i][j] << " " << minmaxxd[i][j + 1] << " ";
		}
		std::cout << "\n";
	}

	for (int i = 0; i < (this->factories); i++) {
		for (int j = 0; j < (this->magazines)*2; j+=2) {
			this->minmaxxf[i][j] = 0;
			this->minmaxxf[i][j+1] = sf[i];
		}
	}

	for (int i = 0; i < (this->magazines); i ++) {
		for (int j = 0; j < (this->shops)*2; j+=2) {
			this->minmaxxm[i][j] = 0;
			this->minmaxxm[i][j+1] = sm[i];
		}
	}
}


double CMscnProblem::getMaxMin(int index, double *pdSolution, double *error, int length) {
	double minim = 0;
	double maxim = 0;
	//std::cout << "INDEX " << index << "\n";
	if (index < 0 || index > this->providers*this->factories + this->factories*this->magazines + this->magazines*this->shops)
		*error = INVALID_VALUE;
	else if (index < this->providers*this->factories) {
		//std::cout << "tak1\n";
		//std::cout << "INDEX " << index << "\n";
		//std::cout << "wartosc " << minmaxxd[index%this->providers][(index%this->factories)] << "\n";
		if (minmaxxd[index%this->providers][((index*2)%((this->factories)*2)) + 1] > maxim) {
			maxim = minmaxxd[index%this->providers][((index*2)%((this->factories)*2)) + 1];
			//std::cout << "MAXIM " << maxim << "\n";
		}
	}
	else if (index < this->providers*this->factories + this->factories*this->magazines) {
		index = index - this->providers*this->factories;
		//std::cout << "tak2\n";
		if (minmaxxf[index%this->factories][((index*2)%((this->magazines)*2)) + 1] > maxim) {
			//maxim = minmaxxf[index%this->factories][(index%((this->magazines)*2)) + 1];
			maxim = minmaxxf[index%this->factories][((index*2) % ((this->magazines) * 2)) + 1];
			//std::cout << "MAXIM2 " << maxim << "\n";
		}
	}
	else if (index < this->providers*this->factories + this->factories*this->magazines + this->magazines*this->shops) {
		index = index - (this->providers*this->factories + this->factories*this->magazines);
		//std::cout << "tak3\n";
		if (minmaxxm[index%this->magazines][((index*2)%((this->shops)*2)) + 1] > maxim) {
			maxim = minmaxxm[index%this->magazines][((index*2)%((this->shops)*2)) + 1];
			//std::cout << "MAXIM3 " << maxim << "\n";
		}
	}
	return maxim;

}

double CMscnProblem::dGetQuality(double *pdSolution, int length) {
	if (pdSolution == NULL) {
		return NULL_POINTER_ERROR;
	}
	else if (length != providers * factories + factories * magazines + magazines * shops) {
		return INVALID_SIZE_ERROR;
	}
	double test = 0;
	this->bConstraintSatisfied(pdSolution, &test, length);
	int counter = 0;
	for (int i = 0; i < this->providers; i++) {
		for (int j = 0; j < this->factories; j++) {
			if (pdSolution[counter] < 0)
				return NEGATIVE_VALUES_ERROR;
			else {
				this->xd[i][j] = pdSolution[counter];
				counter++;
			}	
		}
	}

	for (int i = 0; i < this->factories; i++) {
		for (int j = 0; j < this->magazines; j++) {
			if (pdSolution[counter] < 0)
				return NEGATIVE_VALUES_ERROR;
			else {
				this->xf[i][j] = pdSolution[counter];
				counter++;
			}
		}
	}

	for (int i = 0; i < this->magazines; i++) {
		for (int j = 0; j < this->shops; j++) {
			if (pdSolution[counter] < 0)
				return NEGATIVE_VALUES_ERROR;
			else {
				this->xm[i][j] = pdSolution[counter];
				counter++;
			}
		}
	}
	
	repair(pdSolution, &test, length);
	//std::cout << "\n"<<pdSolution[1] << "\n";
	//std::cout << "tu";
	
	return overall();
}


void CMscnProblem::repair(double *pdSolution, double *error, int length) {
	double test = 0;
	
	while (!providerPower()) {
		for (int i = 0; i < this->providers; i++) {
			for (int j = 0; j < this->factories; j++) {
				this->xd[i][j] = this->xd[i][j] - 0.1*this->xd[i][j];
				
				//counter++;
			}
		}
	}
	while (!factoryPower()) {
		for (int i = 0; i < this->factories; i++) {
			for (int j = 0; j < this->magazines; j++) {
				this->xf[i][j] = this->xf[i][j] - 0.1*this->xf[i][j];
				
				//std::cout << "tu1";
				//counter++;
			}
		}
	}
	
	while (!magazinePower()) {
		for (int i = 0; i < this->magazines; i++) {
			for (int j = 0; j < this->shops; j++) {
				this->xm[i][j] = this->xm[i][j] - 0.1*this->xm[i][j];
				
				//std::cout << "tu2";
				//counter++;
			}
		}
	}
	//std::cout << "tu2";
	while (!factorySum()) {
		for (int i = 0; i < this->factories; i++) {
			for (int j = 0; j < this->magazines; j++) {
				this->xf[i][j] = this->xf[i][j] - 0.7*this->xf[i][j];
				//std::cout << "tu3";
				//counter++;
			}
		}
		//std::cout << "jestem";
		double current_sum_in = 0;
		double current_sum_out = 0;

		/*for (int k = 0; k < this->factories; k++) {
			current_sum_in = 0;
			current_sum_out = 0;

			for (int i = 0; i < this->providers; i++) {
				current_sum_in += xd[i][k];
			}
			for (int j = 0; j < this->magazines; j++) {
				current_sum_out += xf[k][j];
			}
			std::cout << "\n" << current_sum_in << " " << current_sum_out << "\n";
		}*/
	}
	
	
	while (!magazineSum()) {
		for (int i = 0; i < this->magazines; i++) {
			for (int j = 0; j < this->shops; j++) {
				this->xm[i][j] = this->xm[i][j] - 0.7*this->xm[i][j];
				//std::cout << "tu4";
				//counter++;
			}
		}
	}
	//std::cout << "jestem2";

	int counter = 0;
	for (int i = 0; i < this->providers; i++) {
		for (int j = 0; j < this->factories; j++) {
			pdSolution[counter] = this->xd[i][j];
			counter++;
			//counter++;
		}
	}
	for (int i = 0; i < this->factories; i++) {
		for (int j = 0; j < this->magazines; j++) {
			pdSolution[counter] = this->xf[i][j];
			counter++;
		}
	}
	for (int i = 0; i < this->magazines; i++) {
		for (int j = 0; j < this->shops; j++) {
			pdSolution[counter] = this->xm[i][j];
			counter++;
		}
	}
	
	//std::cout << "\nCzy spelnia warunki " << this->bConstraintSatisfied(pdSolution, &test, 12);

	//pdSolution[1] = 312;
	//if (!providerPower() || !factoryPower() || !magazinePower() || !shopPower() || !factorySum() || !magazineSum()) {
		//int counter2 = 0;
		/*for (int i = 0; i < this->providers; i++) {
			for (int j = 0; j < this->factories; j++) {
				this->xd[i][j] = sd[i]/this->factories;
				//counter++;
			}
		}

		for (int i = 0; i < this->factories; i++) {
			for (int j = 0; j < this->magazines; j++) {
				this->xf[i][j] = sf[i] / this->magazines;
				//counter++;
			}
		}*/
		/*if (!factorySum()) {
			double suma1 = 0;
			double suma2 = 0;
			for (int i = 0; i < this->providers; i++) {
				for (int j = 0; j < this->factories; j++) {
					suma1 += xd[i][j];
				}
			}
			for (int i = 0; i < this->factories; i++) {
				for (int j = 0; j < this->magazines; j++) {
					suma2 += xf[i][j];
				}
			}
			double x = suma2 - suma1;
			for (int i = 0; i < this->factories; i++) {
				for (int j = 0; j < this->magazines; j++) {
					this->xf[i][j] = this->xf[i][j] - x / (this->factories * this->magazines);
				}
			}
		}
		if (!magazineSum()) {
			double suma1 = 0;
			double suma2 = 0;
			for (int i = 0; i < this->factories; i++) {
				for (int j = 0; j < this->magazines; j++) {
					suma1 += xf[i][j];
				}
			}
			for (int i = 0; i < this->magazines; i++) {
				for (int j = 0; j < this->shops; j++) {
					suma2 += xm[i][j];
				}
			}
			double x = suma2 - suma1;
			for (int i = 0; i < this->magazines; i++) {
				for (int j = 0; j < this->shops; j++) {
					this->xm[i][j] = this->xm[i][j] - x / (this->magazines * this->shops);
				}
			}
		}*/


		/*for (int i = 0; i < this->magazines; i++) {
			for (int j = 0; j < this->shops; j++) {
				this->xm[i][j] = sm[i] / this->shops;
				if (this->xm[i][j] > ss[j] / this->magazines) {
					this->xm[i][j] = ss[j] / this->magazines;
				}
				//counter++;
			}
		}*/











		/*for (int i = 0; i < this->providers; i++) {
			for (int j = 0; j < this->factories; j++) {
				std::cout << xd[i][j] << " ";
			}
		}
		std::cout << "\n";
		for (int i = 0; i < this->factories; i++) {
			for (int j = 0; j < this->magazines; j++) {
				std::cout << xf[i][j] << " ";
			}
		}
		std::cout << "\n";
		for (int i = 0; i < this->magazines; i++) {
			for (int j = 0; j < this->shops; j++) {
				std::cout << xm[i][j] << " ";
			}
		}*/
		/*CRandom randomizer;
		for (int i = 0; i < length; i++) {
			pdSolution[i] = randomizer.getDouble(0, this->getMaxMin(i, &pdSolution[i], &test, length));
		}

		for (int i = 0; i < this->providers*this->factories; i++) {
			pdSolution[i] = sd[i] / this->factories;
		}
		for (int i = this->providers*this->factories; i < this->providers*this->factories + this->factories*this->magazines;i++) {
			if()
		}*/
	//}
}

double CMscnProblem::bConstraintSatisfied(double *pdSolution, double *error, int length) {

	
	if (pdSolution == NULL) {
		*error =  NULL_POINTER_ERROR;
	}
	else if (length != providers * factories + factories * magazines + magazines * shops) {
		*error =  INVALID_SIZE_ERROR;
	}
	
	int counter = 0;
	for (int i = 0; i < this->providers; i++) {
		for (int j = 0; j < this->factories; j++) {
			if (pdSolution[counter] < 0)
				*error =  NEGATIVE_VALUES_ERROR;
			else {
				this->xd[i][j] = pdSolution[counter];
				counter++;
			}
		}
	}
	
	for (int i = 0; i < this->factories; i++) {
		for (int j = 0; j < this->magazines; j++) {
			if (pdSolution[counter] < 0)
				*error = NEGATIVE_VALUES_ERROR;
			else {
				this->xf[i][j] = pdSolution[counter];
				counter++;
			}
		}
	}

	for (int i = 0; i < this->magazines; i++) {
		for (int j = 0; j < this->shops; j++) {
			if (pdSolution[counter] < 0)
				*error = NEGATIVE_VALUES_ERROR;
			else {
				this->xm[i][j] = pdSolution[counter];
				counter++;
			}
		}
	}
	

	if (!providerPower())
		return PROVIDER_POWER_EXTENDED_ERROR;
	else if (!factoryPower())
		return FACTORY_POWER_EXTENDED_ERROR;
	else if (!magazinePower()) {
		return MAGAZINE_POWER_EXTENDED_ERROR;
	}
	else if (!shopPower())
		return SHOP_POWER_EXTENDED_ERROR;
	else if (!factorySum())
		return FACTORY_SUM_EXTENDED_ERROR;
	else if (!magazineSum())
		return MAGAZINE_SUM_EXTENDED_ERROR;

	return true;

}

void CMscnProblem::solutionToFile() {
	FILE *pFile;
	pFile = NULL;
	pFile = fopen("solution.txt", "w+");

	std::string result;
	const char *cstr;

	if (pFile != NULL) {

		result = this->allNumberstoString(&(this->providers));
		cstr = result.c_str();
		fputs("D ", pFile);
		fputs(cstr, pFile);

		result = this->allNumberstoString(&(this->factories));
		cstr = result.c_str();
		fputs("\nF ", pFile);
		fputs(cstr, pFile);

		result = this->allNumberstoString(&(this->magazines));
		cstr = result.c_str();
		fputs("\nM ", pFile);
		fputs(cstr, pFile);

		result = this->allNumberstoString(&(this->shops));
		cstr = result.c_str();
		fputs("\nS ", pFile);
		fputs(cstr, pFile);

		fputs("\nxd\n", pFile);
		result = this->allMatrixTostring(&(this->xd), this->providers, this->factories);
		cstr = result.c_str();
		fputs(cstr, pFile);

		fputs("xf\n", pFile);
		result = this->allMatrixTostring(&(this->xf), this->factories, this->magazines);
		cstr = result.c_str();
		fputs(cstr, pFile);

		fputs("xm\n", pFile);
		result = this->allMatrixTostring(&(this->xm), this->magazines, this->shops);
		cstr = result.c_str();
		fputs(cstr, pFile);
	}
}

void CMscnProblem::problemToFile() {

	FILE *pFile;
	pFile = NULL;
	pFile = fopen("problem.txt", "w+");

	std::string result;
	const char *cstr;

	
	if (pFile != NULL) {

		result = this -> allNumberstoString(&(this->providers));
		cstr = result.c_str();
		fputs("D;", pFile);
		fputs(cstr, pFile);

		result = this->allNumberstoString(&(this->factories));
		cstr = result.c_str();
		fputs("\nF;", pFile);
		fputs(cstr, pFile);

		result = this->allNumberstoString(&(this->magazines));
		cstr = result.c_str();
		fputs("\nM;", pFile);
		fputs(cstr, pFile);

		result = this->allNumberstoString(&(this->shops));
		cstr = result.c_str();
		fputs("\nS;", pFile);
		fputs(cstr, pFile);

		result = this->allArraytoString(&(this->sd), this->providers);
		cstr = result.c_str();
		fputs("\nsd\n", pFile);
		fputs(cstr, pFile);
		fputs("\nsf\n", pFile);	
		result = this->allArraytoString(&(this->sf), this->factories);
		cstr = result.c_str();
		fputs(cstr, pFile);
		fputs("\nsm\n", pFile);
		result = this->allArraytoString(&(this->sm), this->magazines);
		cstr = result.c_str();
		fputs(cstr, pFile);
		fputs("\nss\n", pFile);
		result = this->allArraytoString(&(this->ss), this->shops);
		cstr = result.c_str();
		fputs(cstr, pFile);
		fputs("\ncd\n", pFile);
		result = this->allMatrixTostring(&(this->cd), this->providers, this->factories);
		cstr = result.c_str();
		fputs(cstr, pFile);

		fputs("cf\n", pFile);
		result = this->allMatrixTostring(&(this->cf), this->factories, this->magazines);
		cstr = result.c_str();
		fputs(cstr, pFile);

		fputs("cm\n", pFile);
		result = this->allMatrixTostring(&(this->cm), this->magazines, this->shops);
		cstr = result.c_str();
		fputs(cstr, pFile);

		fputs("ud\n", pFile);
		result = this->allArraytoString(&(this->ud), this->providers);
		cstr = result.c_str();
		fputs(cstr, pFile);

		fputs("\nuf\n", pFile);
		result = this->allArraytoString(&(this->uf), this->factories);
		cstr = result.c_str();
		fputs(cstr, pFile);

		fputs("\num\n", pFile);
		result = this->allArraytoString(&(this->um), this->magazines);
		cstr = result.c_str();
		fputs(cstr, pFile);

		fputs("\np\n", pFile);
		result = this->allArraytoString(&(this->p), this->shops);
		cstr = result.c_str();
		fputs(cstr, pFile);
		
		fputs("\nxdminmax\n", pFile);
		result = this->allMatrixTostring(&(this->minmaxxd), (this->providers), (this->factories)*2);
		cstr = result.c_str();
		fputs(cstr, pFile);
		
		fputs("xfminmax\n", pFile);
		result = this->allMatrixTostring(&(this->minmaxxf), (this->factories), (this->magazines)*2);
		cstr = result.c_str();
		fputs(cstr, pFile);
		
		fputs("xmminmax\n", pFile);
		result = this->allMatrixTostring(&(this->minmaxxm), (this->magazines), (this->shops)*2);
		cstr = result.c_str();
		fputs(cstr, pFile);
		
		fclose(pFile);
	}

}

std::string CMscnProblem::allArraytoString(double **from, int length) {
	std::string my_sd;
	std::string my_string;

	for (int i = 0; i < length; i++) {
		my_string = std::to_string((*from)[i]);
		my_sd.append(my_string);
		my_sd.append(";");
	}
	return my_sd;
}

std::string CMscnProblem::allMatrixTostring(double ***from, int x, int y) {
	std::string my_sd;
	std::string my_string;

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			my_string = std::to_string((*from)[i][j]);
			my_sd.append(my_string);
			my_sd.append(";");
		}
		my_sd.append("\n");		
	}

	return my_sd;
}

std::string CMscnProblem::allNumberstoString(int *from) {
	std::string my_string;
	my_string = std::to_string(*from);
	return my_string;
}

std::string convertToString(char* a, int size)
{
	int i;
	std::string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}

void CMscnProblem::solutionFromFile(double *error) {
	FILE *pFile;
	pFile = NULL;
	pFile = fopen("kon2_2.txt", "r");

	char bufor[1000];

	fseek(pFile, 0, SEEK_END);
	long lSize = ftell(pFile);
	rewind(pFile);
	fread(bufor, sizeof(char), lSize, pFile);

	int a_size = lSize;
	std::string s_a = convertToString(bufor, a_size);
	//setAllFromFile(s_a, lSize);

	setSlnFromFile(s_a, lSize, error);
}

void CMscnProblem::setSlnFromFile(std::string stream, int length, double *error) {
	std::string my_string = "";
	double dbls[1000];
	int index = 0;
	double dbl;

	for (int i = 0; i < length; i++) {
		while (stream[i] >= '0' && stream[i] <= '9') {
			my_string += stream[i];
			i++;
		}

		if (i > 0) {
			if (stream[i - 1] >= '0' && stream[i - 1] <= '9') {
				dbl = atof(my_string.c_str());
				dbls[index] = dbl;
				index++;
				my_string = "";

			}

		}
	}

	int current_index = 0;

	if (dbls[current_index] != this->providers) {
		*error = INVALID_PROVIDER_NUMBER;
		std::cout << "tut " << dbls[current_index] << " " << this->providers << "\n";
	}

	current_index++;

	if (dbls[current_index] != this->factories) {
		*error = INVALID_FACTORY_NUMBER;
	}

	current_index++;

	if (dbls[current_index] != this->magazines) {
		*error = INVALID_MAGAZINE_NUMBER;
	}

	current_index++;

	if (dbls[current_index] != this->shops) {
		*error = INVALID_SHOP_NUMBER;
	}

	current_index++;
	std::cout << "\n";
	if (*error == 0) {
		for (int i = current_index; i < index; i++) {
			std::cout << dbls[i] << " ";
		}
	}
	else {
		std::cout << "\n error = " << *error << "\n";
	}
	std::cout << "\n";


	if (*error == 0) {
		int counter = current_index;
		for (int i = 0; i < this->providers; i++) {
			for (int j = 0; j < this->factories; j++) {
				if (dbls[counter] < 0)
					*error =  NEGATIVE_VALUES_ERROR;
				else {
					this->xd[i][j] = dbls[counter];
					counter++;
				}
			}
		}

		for (int i = 0; i < this->factories; i++) {
			for (int j = 0; j < this->magazines; j++) {
				if (dbls[counter] < 0)
					*error = NEGATIVE_VALUES_ERROR;
				else {
					this->xf[i][j] = dbls[counter];
					counter++;
				}
			}
		}

		for (int i = 0; i < this->magazines; i++) {
			for (int j = 0; j < this->shops; j++) {
				if (dbls[counter] < 0)
					*error = NEGATIVE_VALUES_ERROR;
				else {
					this->xm[i][j] = dbls[counter];
					counter++;
				}
			}
		}
	}


}


void CMscnProblem::problemFromFile() {
	FILE *pFile;
	pFile = NULL;
	pFile = fopen("kon2.txt", "r");

	char bufor[1000];

	fseek(pFile, 0, SEEK_END);
	long lSize = ftell(pFile);
	rewind(pFile);
	fread(bufor, sizeof(char), lSize, pFile);

	int a_size = lSize;
	std::string s_a = convertToString(bufor, a_size);
	setAllFromFile(s_a, lSize);

}
/*
void CMscnProblem::setAllFromFile(std::string stream, int length, double *error) {
	//std::cout << stream;
	std::string my_string="";
	double dbls[1000];
	int index = 0;
	double dbl;

	for (int i = 0; i < length && *error == 0; i++) {
		while (stream[i] >= '0' && stream[i] <= '9') {
			my_string += stream[i];
			i++;
		}

		if (i > 0) {
			if (stream[i - 1] >= '0' && stream[i - 1] <= '9') {
				dbl = atof(my_string.c_str());
				dbls[index] = dbl;
				index++;
				my_string = "";

				if (stream[i] != ';' && stream[i] != '\n') {
					*error = WRONG_SEPARATOR_ERROR;
					std::cout << " Zly separator\n";
					std::cout << "Separator" <<stream[i] << "jest bledny";
				}
			}
			
		}
	}
	if (*error == 0) {
		//std::cout << "wykonuje";
		int current_index = 0;
		double test;
		this->setProviderNumber(dbls[current_index]);

		current_index++;
		this->setFactoriesNumber(dbls[current_index]);
		current_index++;
		this->setMagazinesNumber(dbls[current_index]);
		current_index++;
		this->setShopsNumber(dbls[current_index]);
		current_index++;

		for (int i = 0; i < this->providers; i++) {
			this->setOneProviderPower(i, dbls[current_index], &test);
			current_index++;
		}

		for (int i = 0; i < this->factories; i++) {
			this->setOneFactoryPower(i, dbls[current_index], &test);
			current_index++;
		}

		for (int i = 0; i < this->magazines; i++) {
			this->setOneMagazinePower(i, dbls[current_index], &test);
			current_index++;
		}

		for (int i = 0; i < this->shops; i++) {
			this->setOneShopPower(i, dbls[current_index], &test);
			current_index++;
		}

		for (int i = 0; i < this->providers; i++) {
			for (int j = 0; j < this->factories; j++) {
				this->setOneCD(i, j, dbls[current_index], &test);
				current_index++;
			}
		}
		for (int i = 0; i < this->factories; i++) {
			for (int j = 0; j < this->magazines; j++) {
				this->setOneCF(i, j, dbls[current_index], &test);
				current_index++;
			}
		}

		for (int i = 0; i < this->magazines; i++) {
			for (int j = 0; j < this->shops; j++) {
				this->setOneCM(i, j, dbls[current_index], &test);
				current_index++;
			}
		}

		for (int i = 0; i < this->providers; i++) {
			this->setOneUD(i, dbls[current_index], &test);
			current_index++;
		}

		for (int i = 0; i < this->factories; i++) {
			this->setOneUF(i, dbls[current_index], &test);
			current_index++;
		}

		for (int i = 0; i < this->magazines; i++) {
			this->setOneUM(i, dbls[current_index], &test);
			current_index++;
		}

		for (int i = 0; i < this->shops; i++) {
			this->setOneInc(i, dbls[current_index], &test);
			current_index++;
		}

		for (int i = 0; i < this->providers; i++) {
			for (int j = 0; j < this->factories; j++) {
				this->setOneMaxMinXD(i, j, dbls[current_index], &test);
				current_index++;
			}
		}

		for (int i = 0; i < this->factories; i++) {
			for (int j = 0; j < this->magazines; j++) {
				this->setOneMaxMinXF(i, j, dbls[current_index], &test);
				current_index++;
			}
		}

		for (int i = 0; i < this->magazines; i++) {
			for (int j = 0; j < this->shops; j++) {
				this->setOneMaxMinXM(i, j, dbls[current_index], &test);
				current_index++;
			}
		}
	}
	
}
*/
void CMscnProblem::setAllFromFile(std::string stream, int length) {
	//std::cout << stream;
	std::string my_string = "";
	double dbls[1000];
	int index = 0;
	double dbl;
	std::cout << "\n";
	for (int i = 0; i < length; i++) {
		while (stream[i] >= '0' && stream[i] <= '9') {
			my_string += stream[i];
			i++;
		}

		if (i > 0) {
			if (stream[i - 1] >= '0' && stream[i - 1] <= '9') {
				dbl = atof(my_string.c_str());
				dbls[index] = dbl;
				index++;
				my_string = "";
				std::cout << dbls[index - 1] << " ";
			}
			

		}
	}
	std::cout << "\n";
		//std::cout << "wykonuje";
		int current_index = 0;
		double test;
		this->setProviderNumber(dbls[current_index]);

		current_index++;
		this->setFactoriesNumber(dbls[current_index]);
		current_index++;
		this->setMagazinesNumber(dbls[current_index]);
		current_index++;
		this->setShopsNumber(dbls[current_index]);
		current_index++;

		for (int i = 0; i < this->providers; i++) {
			this->setOneProviderPower(i, dbls[current_index], &test);
			current_index++;
		}

		for (int i = 0; i < this->factories; i++) {
			this->setOneFactoryPower(i, dbls[current_index], &test);
			
			current_index++;
			
		}

		for (int i = 0; i < this->magazines; i++) {
			this->setOneMagazinePower(i, dbls[current_index], &test);
			current_index++;
		}

		for (int i = 0; i < this->shops; i++) {
			this->setOneShopPower(i, dbls[current_index], &test);
			
			current_index++;
		}

		for (int i = 0; i < this->providers; i++) {
			for (int j = 0; j < this->factories; j++) {
				this->setOneCD(i, j, dbls[current_index], &test);
				
				current_index++;
			}
		}
		for (int i = 0; i < this->factories; i++) {
			for (int j = 0; j < this->magazines; j++) {
				this->setOneCF(i, j, dbls[current_index], &test);
				current_index++;
			}
		}

		for (int i = 0; i < this->magazines; i++) {
			for (int j = 0; j < this->shops; j++) {
				this->setOneCM(i, j, dbls[current_index], &test);
				
				current_index++;
			}
		}

		for (int i = 0; i < this->providers; i++) {
			this->setOneUD(i, dbls[current_index], &test);
			std::cout << "\n" << dbls[current_index] << " ";
			current_index++;
		}

		for (int i = 0; i < this->factories; i++) {
			this->setOneUF(i, dbls[current_index], &test);
			
			current_index++;
		}

		for (int i = 0; i < this->magazines; i++) {
			this->setOneUM(i, dbls[current_index], &test);
			current_index++;
		}

		for (int i = 0; i < this->shops; i++) {
			this->setOneInc(i, dbls[current_index], &test);
			std::cout << "\n\n\n" << dbls[current_index-1] << "\n\n\n";
			current_index++;
		}

		for (int i = 0; i < this->providers; i++) {
			for (int j = 0; j < this->factories; j++) {
				this->setOneMaxMinXD(i, j, dbls[current_index], &test);
				current_index++;
			}
		}

		for (int i = 0; i < this->factories; i++) {
			for (int j = 0; j < this->magazines; j++) {
				this->setOneMaxMinXF(i, j, dbls[current_index], &test);
				current_index++;
			}
		}

		for (int i = 0; i < this->magazines; i++) {
			for (int j = 0; j < this->shops; j++) {
				this->setOneMaxMinXM(i, j, dbls[current_index], &test);
				current_index++;
			}
		}

}

/*void CMscnProblem::vGenerateInstance(int iInstanceSeed) {
	double test;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(MINIMUM_COST_SD, MAXIMUM_COST_SD);

	for (int i = 0; i < this->providers; i++) {
		this->setOneProviderPower(i, dis(gen), &test);
	}
	dis = std::uniform_real_distribution<>(MINIMUM_COST_SF, MAXIMUM_COST_SF);
	for (int i = 0; i < this->factories; i++) {
		this->setOneFactoryPower(i, dis(gen), &test);
	}

	dis = std::uniform_real_distribution<>(MINIMUM_COST_SM, MAXIMUM_COST_SM);
	for (int i = 0; i < this->magazines; i++) {
		this->setOneMagazinePower(i, dis(gen), &test);
	}
	dis = std::uniform_real_distribution<>(MINIMUM_COST_SS, MAXIMUM_COST_SS);
	for (int i = 0; i < this->shops; i++) {
		this->setOneShopPower(i, dis(gen), &test);

	}

	dis = std::uniform_real_distribution<>(MINIMUM_COST_CD, MAXIMUM_COST_CD);
	for (int i = 0; i < this->providers; i++) {
		for (int j = 0; j < this->factories; j++) {
			this->setOneCD(i, j, dis(gen), &test);

		}
	}

	dis = std::uniform_real_distribution<>(MINIMUM_COST_CF, MAXIMUM_COST_CF);
	for (int i = 0; i < this->factories; i++) {
		for (int j = 0; j < this->magazines; j++) {
			this->setOneCF(i, j, dis(gen), &test);
		}
	}

	dis = std::uniform_real_distribution<>(MINIMUM_COST_CM, MAXIMUM_COST_CM);
	for (int i = 0; i < this->magazines; i++) {
		for (int j = 0; j < this->shops; j++) {
			this->setOneCM(i, j, dis(gen), &test);

		}
	}

	dis = std::uniform_real_distribution<>(MINIMUM_COST_UD, MAXIMUM_COST_UD);
	for (int i = 0; i < this->providers; i++) {
		this->setOneUD(i, dis(gen), &test);
	}

	dis = std::uniform_real_distribution<>(MINIMUM_COST_UF, MAXIMUM_COST_UF);

	for (int i = 0; i < this->factories; i++) {
		this->setOneUF(i, dis(gen), &test);
	}
	dis = std::uniform_real_distribution<>(MINIMUM_COST_UM, MAXIMUM_COST_UM);

	for (int i = 0; i < this->magazines; i++) {
		this->setOneUM(i, dis(gen), &test);
	}
}*/

void CMscnProblem::vGenerateInstance(int iInstanceSeed) {
	CRandom randomizer(iInstanceSeed);
	double test;

	for (int i = 0; i < this->providers; i++) {
		this->setOneProviderPower(i, randomizer.getDouble(MINIMUM_COST_SD, MAXIMUM_COST_SD), &test);
		this->setOneUD(i, randomizer.getDouble(MINIMUM_COST_UD, MAXIMUM_COST_UD), &test);
	}

	for (int i = 0; i < this->factories; i++) {
		this->setOneFactoryPower(i, randomizer.getDouble(MINIMUM_COST_SF, MAXIMUM_COST_SF), &test);
		this->setOneUF(i, randomizer.getDouble(MINIMUM_COST_UF, MAXIMUM_COST_UF), &test);
	}

	for (int i = 0; i < this->magazines; i++) {
		this->setOneMagazinePower(i, randomizer.getDouble(MINIMUM_COST_SM, MAXIMUM_COST_SM), &test);
		this->setOneUM(i, randomizer.getDouble(MINIMUM_COST_UM, MAXIMUM_COST_UM), &test);
	}

	for (int i = 0; i < this->shops; i++) {
		this->setOneShopPower(i, randomizer.getDouble(MINIMUM_COST_SS, MAXIMUM_COST_SS), &test);
	}

	for (int i = 0; i < this->providers; i++) {
		for (int j = 0; j < this->factories; j++) {
			this->setOneCD(i, j, randomizer.getDouble(MINIMUM_COST_CD, MAXIMUM_COST_CD), &test);
		}
	}

	for (int i = 0; i < this->factories; i++) {
		for (int j = 0; j < this->magazines; j++) {
			this->setOneCF(i, j, randomizer.getDouble(MINIMUM_COST_CF, MAXIMUM_COST_CF), &test);
		}
	}

	for (int i = 0; i < this->magazines; i++) {
		for (int j = 0; j < this->shops; j++) {
			this->setOneCM(i, j, randomizer.getDouble(MINIMUM_COST_CM, MAXIMUM_COST_CM), &test);
		}
	}
}
