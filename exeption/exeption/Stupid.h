#pragma once
#include <iostream>
class Stupid
{
public:
	Stupid();
	~Stupid();
};



Stupid::Stupid()
{
	throw std::out_of_range("123");
}


Stupid::~Stupid()
{
	std::cout << "Destructor after exeption";
}
