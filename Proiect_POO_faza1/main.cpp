#include <iostream>
#include "calculator.h"

using namespace std;
int main()
{
	int bufferSize=500;
	Calculator calculator(bufferSize);
	char* buffer = new char[bufferSize + 1];
	cin.getline(buffer, bufferSize);
	stergereSpatii(buffer);
	calculator.setExpresie(string(buffer));
	calculator.prelucreaza();
	
	std::cout << calculator.getResult();


	return 0;
}