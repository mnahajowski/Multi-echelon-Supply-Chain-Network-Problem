
#include <iostream>
#include "CRandom.h"

int main()
{
	CRandom c1;
	std::cout << c1.getDouble(5.0, 10.0);
	std::cout << "\n" << c1.getInt(5, 10);

}

