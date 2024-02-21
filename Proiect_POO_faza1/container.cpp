#include "container.h"

int Container::defaultSize = 100;//maxim 50 operatii

Container::Container()
{
	this->maxNr = defaultSize;
	this->sir = new string[this->maxNr];
	this->marimeStack = 0;
}
Container::Container(int maxSize)
{
	this->maxNr = maxSize;
	this->sir = new string[this->maxNr];
	this->marimeStack = 0;
}

Container::Container(const Container& stack)//constructor copiere
{
	this->maxNr = stack.maxNr;
	this->sir = new string[stack.maxNr];
	this->marimeStack = stack.marimeStack;
	for (int i = 0; i < marimeStack; i++)
	{
		this->sir[i] = stack.sir[i];
	}
}

Container& Container::operator=(const Container& stack)
{
	if (this == &stack)return *this;

	if (sir != nullptr)
	{
		delete[]sir;
		sir = nullptr;
	}

	this->maxNr = stack.maxNr;
	this->sir = new string[stack.maxNr];
	this->marimeStack = stack.marimeStack;
	for (int i = 0; i < marimeStack; i++)
	{
		this->sir[i] = stack.sir[i];
	}
}

Container::~Container()
{

	if (sir != nullptr)
	{
		delete[]sir;
		sir = nullptr;
	}
}

string Container::pop()
{
	if (marimeStack == 0) return "";

	string element = this->sir[marimeStack - 1];
	this->sir[marimeStack - 1] = "";
	marimeStack--;

	return element;
}
string Container::pop_back()
{
	if (this->marimeStack == 0)
		return "";
	string element = this->sir[0];
	for (int i = 0; i < marimeStack - 1; i++)
	{
		sir[i] = sir[i + 1];
	}
	this->sir[marimeStack - 1] = "";
	marimeStack--;
	return element;

}
void Container::push(string element)
{
	if (this->marimeStack == this->maxNr)
		return; //opreste subprogramul
	this->marimeStack++;
	sir[this->marimeStack - 1] = element;
}
void Container::push_back(string element)
{
	if (this->marimeStack == this->maxNr)
		return;
	this->marimeStack++;
	for (int i = 1; i < marimeStack; i++)
	{
		sir[i + 1] = sir[i];
	}
	sir[0] = element;
}

int Container::getDefaultSize()
{
	return this->defaultSize;
}
int Container::getMaxNr()
{
	return this->maxNr; 
}
int Container::getMarimeStack()
{
	return this->marimeStack;
}
string* Container::getSir()
{
	if (marimeStack == 0)
		return nullptr;
	string* copie = new string[marimeStack];
	for (int i = 0; i < marimeStack; i++)
	{
		copie[i] = sir[i];
	}
	return copie;
}

void Container::setDefaultSize(int defaultSize)
{
	this->defaultSize = defaultSize;
}
void Container::setMaxNr(int maxNr)
{
	this->maxNr = maxNr;
	if (marimeStack > maxNr)
		  marimeStack = maxNr;

	string* copie = new string[marimeStack];
	for (int i = 0; i < marimeStack; i++)
	{
		copie[i] = sir[i];
	}

	if (sir != nullptr) {
		delete[] sir;
		sir = nullptr;
	}

	this->sir = new string[maxNr];
	for (int i = 0; i < marimeStack; i++)
	{
		sir[i] = copie[i];
	}
	if (copie != nullptr) {
		delete[] copie;
		copie = nullptr;
	}
}

void Container::setSir(string* sir, int marimeStack)
{
	if (marimeStack > this->maxNr)
		return;

	if (this->sir!=nullptr)
	{
		delete[] this->sir;
		this->sir = nullptr;
	}

	this->marimeStack = marimeStack;
	this->sir = new string[maxNr];
	for (int i = 0; i < marimeStack; i++)
	{
		this->sir[i] = sir[i];
	}
}

string& Container::operator[](int index)
{
	if (index >= marimeStack)
		throw "Index out of bounds";
	else
		return sir[index];
}



