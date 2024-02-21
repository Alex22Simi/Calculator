#define _CRT_SECURE_NO_WARNINGS
#include "calculator.h"
#include <cmath>

int Calculator::defaultSize = 100;

Calculator::Calculator():
	analizator(Analizator(defaultSize)),eroare(nullptr),expresie(""),rezultat(0),bufferSize(defaultSize)
{

}

Calculator::Calculator(int _bufferSize) :
	analizator(Analizator(_bufferSize)), eroare(nullptr), expresie(""), rezultat(0), bufferSize(_bufferSize)
{

}

Calculator::~Calculator()
{

	if (eroare != nullptr)
	{
		delete[]eroare;
		eroare = nullptr;
	}

}

Calculator::Calculator(const Calculator& calculator)//constructor copiere
{
	this->analizator = calculator.analizator;
	this->expresie = calculator.expresie;
	this->rezultat = calculator.rezultat;
	this->bufferSize = calculator.bufferSize;
	this->eroare=nullptr;
	if (calculator.eroare != nullptr)
	{
		this->eroare = new char[strlen(calculator.eroare) + 1];
		strcpy_s(this->eroare, strlen(calculator.eroare) + 1, calculator.eroare);
	}


}

Calculator& Calculator::operator=(const Calculator& calculator)
{
	if (this == &calculator)return *this;

	if (eroare != nullptr)
	{
		delete[]eroare;
		eroare = nullptr;
	}


	this->analizator = calculator.analizator;
	this->expresie = calculator.expresie;
	this->rezultat = calculator.rezultat;
	this->bufferSize = calculator.bufferSize;
	this->eroare = nullptr;
	if (calculator.eroare != nullptr)
	{
		this->eroare = new char[strlen(calculator.eroare) + 1];
		strcpy_s(this->eroare, strlen(calculator.eroare) + 1, calculator.eroare);
	}


	return *this;
}
string Calculator::getExpresie()
{
	return this->expresie;
}
void Calculator::setExpresie(string expresie)
{
	this->expresie = expresie;
}
void Calculator::prelucreaza()
{
	if (expresie != "")
	{
		analizator.adauga(expresie);
		analizator.prelucreaza();
		string* temp=analizator.getPostfix().getSir();
		int len = analizator.getPostfix().getMarimeStack();

		bool sign = 1;
		while (sign)
		{
			sign = 0;
			for (int i = 0; i < len; i++)
			{

				if (strchr("+-*/^#",temp[i][0]) && sign==0 && temp[i].length()==1)
				{
					sign = 1;
					bool minus =0;
					if (temp[i - 2][0] == '-')
					{
						minus = 1;
					}

					double a =string_to_double((char*)temp[i - 2].c_str()+minus, temp[i - 2].length()-minus);
					if (minus)a = -a;

		
					minus = 0;
					if (temp[i - 1][0] == '-')
					{
						minus = 1;
					}

					double b = string_to_double((char*)temp[i - 1].c_str()+minus, temp[i - 1].length()-minus);
					if (minus)b = -b;

					char op=temp[i][0];
					double resDouble = calculate(a, b, op);
					char* tempRes = double_to_string(abs(resDouble));
					string res="";
					if (resDouble < 0)
						res += '-';
					res += tempRes;
					replace(temp, res, i - 2, i,len);
					len-=2;
					
					delete[]tempRes;
				}
			}
		}
		bool minus = 0;
		if (temp[0][0] == '-')
		{
			minus = 1;
		}
		this->rezultat = string_to_double((char*)temp[0].c_str()+minus, temp[0].length()-minus);

		if (minus)
			this->rezultat = -this->rezultat;

	}
}
Analizator Calculator::getAnalizator()
{
	return this->analizator;
}
void Calculator::setAnalizator(Analizator analizator)
{
	this->analizator = analizator;
}
void Calculator::setEroare(char* eroare)
{
	if (this->eroare != nullptr)
	{
		delete[] this->eroare;
	}

	this->eroare = new char[strlen(eroare)+1];
	strcpy_s(this->eroare, strlen(eroare) + 1, eroare);
}

double Calculator::calculate(double a, double b, char op)
{
	if (op == '+')
		return a + b;

	if (op == '-')
		return a - b;

	if (op == '*')
		return a * b;

	if (op == '/')
		return a / b;

	if (op == '^')
		return putere(a,b);

	if (op == '#')
		return radical(a,b);

	return 0;

}

double Calculator::string_to_double(char* str, int len)
{
	double res = 0;
	bool dot = 0;
	int p = 10;
	for (int i = 0; i < len; i++)
	{

		if (str[i] == '.')dot = 1;
		else
		{
			double num = str[i] - '0';
			if (!dot)
				res = res * 10 + num;
			else
			{
				res += num / p;
				p *= 10;
			}
		};
	}
	return res;
};



void Calculator::replace(string* vec, string str, int start, int end, int len)
{
	int iteratii = end - start;
	for (int j = 0; j < iteratii; j++)
	{
		for (int i = start + 1; i < len - 1; i++)
		{
			vec[i] = vec[i + 1];
		}
	}
	vec[start] = str;

}

char* Calculator::double_to_string(double number)
{
	const double fix = 0.00000000001;
	number += fix;
	char* str;
	int len = 0;
	int int_part = int(number);
	double decimal_part = number - int(number);
	bool sign = 0;

	if (number < 0)
	{
		len++;
		sign = 1;
		number = abs(number);
	}

	if (number == 0)
	{
		char* str = new char[2];
		str[0] = '0';
		str[1] = 0;
		return str;
	}



	if (!int_part)len++;

	while (int_part > 0)
	{
		int_part /= 10;
		len++;
	}

	int rev = len;


	if (decimal_part)
	{
		len++;
		int rest = 0;
		int addUp = 0;
		for (int i = 0; i < 9; i++)
		{
			decimal_part *= 10;

			if ((int(decimal_part)) % 10 == 0)
			{
				rest++;
			}
			else {
				addUp++;
				addUp += rest;
				rest = 0;
			}
		}
		len += addUp;

	}

	str = new char[len + 1];
	int_part = int(number);
	decimal_part = number - int(number);

	int i = rev;
	while (i > 0)
	{
		str[i - 1] = int_part % 10 + '0';
		int_part /= 10;
		i--;
	}

	decimal_part *= 10;

	for (i = rev; i < len; i++)
	{
		if (i == rev)str[i] = '.';

		else {
			str[i] = int(decimal_part) % 10 + '0';
			decimal_part = decimal_part * 10;
		}
	}
	str[len] = 0;
	if (str[len - 1] == '.')str[len - 1] = 0;

	return str;



}

double Calculator::getResult()
{
	return this->rezultat;
}

int Calculator::getDefaultSize()
{
	return this->defaultSize;
}
int Calculator::getBufferSize()
{
	return this->bufferSize;
}
char* Calculator::getEroare()
{
	if (this->eroare == nullptr)
	{
		return nullptr;
	}
	char* copie = new char[strlen(this->eroare) + 1];
	strcpy_s(copie, strlen(this->eroare) + 1, this->eroare);

	return copie;
}

void  Calculator::setDefaultSize(int _defaultSize)
{
	if (_defaultSize > 0)
	{
		this->defaultSize = _defaultSize;
	}
}
void  Calculator::setBufferSize(int _bufferSize)
{
	if (_bufferSize > this->bufferSize)
	{
		this->bufferSize = _bufferSize;
	}
}
void Calculator::operator!()//stege mesajul de eroare
{
	if (this->eroare)
	{
		strcpy_s(this->eroare,1, "");
	}
}