#include <iostream>
#include "container.h"
using namespace std;

class Analizator
 {
private: 
	static const string operatori;
	Container prefix; //sir citit tastatura
	Container postfix; //sirul final
	Container stack; //pt a face prelucrarea
	
public:
	Analizator();
	Analizator(int marimeMax);
	
	~Analizator();

	static int orderOf(char chr);
	void adauga(string str);
	void prelucreaza();
	
	Container getPostfix();

	Container getPreFix();
	Container getStack();

	void setStack(Container _stack);
	void setPreFix(Container _prefix);
	void setPostFix(Container _postfix);
};