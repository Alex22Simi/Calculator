#pragma once

#include <iostream>
#include <string>
#include "analizator.h"
#include "functii.h"


using namespace std;

class Calculator
{
private:
	Analizator analizator;
	char* eroare;
	string expresie;
	double rezultat;
	int bufferSize; //cate caractere citeste max
	static int defaultSize;
public:
	Calculator();
	Calculator(const Calculator& calculator);

	~Calculator();

	Calculator(int _bufferSize);
	Calculator& operator=(const Calculator& calculator);
	double calculate(double a, double b, char op);
	
	double getResult();
	string getExpresie();
	void setExpresie(string expresie);
	void prelucreaza();
	Analizator getAnalizator();
	void setAnalizator(Analizator analizator);
	void setEroare(char* eroare);
	void replace(string* vec, string str, int start, int end, int len);
	double string_to_double(char* str, int len);
	char* double_to_string(double number);
	int getDefaultSize();
	int getBufferSize();
	char* getEroare();
	void setDefaultSize(int _defaultSize);
	void setBufferSize(int _bufferSize);

	void operator!();
};