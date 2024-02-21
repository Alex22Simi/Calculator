#include <cstring> //pt strlen

void stergereSpatii(char* str)
{
	int i = 0;
	while (i < strlen(str))
	{
		if (str[i] == ' ')
			strcpy_s(str + i, strlen(str + 1) + 1, str + i + 1);
		else
			i++;
	}
}

double putere(int a, int b)
{
	double p = 1;
	for (int i = 0; i < b; i++)
	{
		p = p * a;
	}
	return p;
}

double radical(int a, int b)
{
	int i = 0;
	double r = 1;
	while (r <= a)
	{
		r = 1;
		for (int j = 0; j < b; j++)
		{
			r = r * (i + 1);
		}
		i++;
	}
	return --i;
}



