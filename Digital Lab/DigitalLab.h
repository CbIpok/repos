#pragma once
#include <istream>
#include <ostream>
#include <vector>
#include "Matrix.h"
class DigitalLab
{
public:
	DigitalLab(std::istream& istream);

	~DigitalLab()
	{
	}
	void scan();
	inline void print(std::ostream& ostream) { _matrix.print(ostream); };
private:
	Matrix _matrix;
	Matrix _pattern;
	bool _isEqual(int posX,int posY);
	void _refreshMatrixHash(size_t m);
	
	int _match(int posX, int posY);
	std::vector<int> _matrixHash;
	std::vector<int> _patternHash;
};
