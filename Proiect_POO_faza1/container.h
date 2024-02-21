#pragma once
#include <iostream>
#include <string>
using namespace std;
class Container //am facut o stiva/coada pt salvarea si prelucrarea datelor de intrare
{
private:
	string* sir;
	int maxNr;
	int marimeStack;
	static int defaultSize;
public: 
	
	Container();
	Container(int maxSize);
	Container(const Container &stack);//copiem dintr-un stack in altul pt stackuri care exista deja
	~Container();
	
	Container& operator=(const Container& stack);//copiem dintr-un stack in altul, pt cele care nu exista inca
	string& operator[](int index);

	string pop(); //pt a scoate ultimul element din sir
	string pop_back(); //pt a scoate primul element din sir
	void push(string element); //pt a adauga un element la finalul sirului
	void push_back(string element); //pt a adauga un element la inceputul sirului
	
	int getDefaultSize();
	int getMaxNr();
	int getMarimeStack();
	string* getSir();

	void setDefaultSize(int defaultSize);
	void setMaxNr(int maxNr);
	void setSir(string* sir, int marimeStack);
};
