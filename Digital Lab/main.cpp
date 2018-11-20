#include <iostream>
#include <fstream>
#include "DigitalLab.h"
using namespace std;
int main()
{
	ifstream file("input.txt");
	if (!file)
	{
		abort();
	}
	DigitalLab d(file);
	d.scan();
	d.print(cout);
}