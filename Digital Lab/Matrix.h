#pragma once
#include <vector>
#include <ostream>
class Matrix
{
public:
	
	Matrix()
	{

	}

	~Matrix()
	{

	}

	void put(size_t i,size_t j, char value);
	void put(size_t pos, char value);
	void setSize(size_t m, size_t n);
	char get(size_t m, size_t n);
	inline size_t getM() { return _m; };
	inline size_t getN() { return _n; };
	void print(std::ostream& ostream);
private:
	size_t _m;
	size_t _n;
	size_t _at(size_t i, size_t j);
	std::vector <char> _matrix;
};
