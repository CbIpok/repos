#include "DigitalLab.h"
#include <iostream>
namespace
{
	void readMatrix(Matrix& matrix,std::istream& istream)
	{
		size_t mMatrix;
		istream >> mMatrix;
		size_t nMatrix;
		istream >> nMatrix;
		matrix.setSize(mMatrix, nMatrix);
		for (size_t i = 0; i < mMatrix*nMatrix; i++)
		{
			char buf;
			istream >> buf;
			matrix.put(i, buf);
		}
	}
}

DigitalLab::DigitalLab(std::istream& istream)
{
	readMatrix(_pattern, istream);
	readMatrix(_matrix, istream);
	for (size_t i = 0; i < _pattern.getN(); i++)
	{
		int hash = 0;
		for (size_t j = 0; j < _pattern.getM(); j++)
		{
			hash += _pattern.get(j, i) - '0';
		}
		_patternHash.push_back(hash);
	}
	for (size_t i = 0; i < _matrix.getN(); i++)
	{
		int hash = 0;
		for (size_t j = 0; j < _pattern.getM(); j++)
		{
			hash += _matrix.get(j, i) - '0';
		}
		_matrixHash.push_back(hash);
	}
}

bool DigitalLab::_isEqual(int posX, int posY)
{
	for (size_t i = 0; i < _pattern.getM(); i++)
	{
		for (size_t j = 0; j < _pattern.getN(); j++)
		{
			if (_pattern.get(i,j) != _matrix.get(i+posY,j + posX))
			{
				return false;
			}
		}
	}
	return true;
}

void DigitalLab::_refreshMatrixHash(size_t m)
{
	if (m + _pattern.getM()  > _matrix.getM())
	{
		return;
	}
	for (size_t i = 0; i < _matrix.getN(); i++)
	{
		_matrixHash[i] -= _matrix.get(m - 1, i) - '0';
		_matrixHash[i] += _matrix.get(m + _pattern.getM() - 1, i) - '0';
	}
}


void DigitalLab::scan()
{
	int posX = 0;
	int posY = 0;
	int i = _matrix.getM() - _pattern.getM();
	while (posY <= _matrix.getM() - _pattern.getM())
	{
		while (posX <= _matrix.getN() - _pattern.getN())
		{
			posX+=_match(posX, posY);
		}
		posY++;
		posX = 0;
		_refreshMatrixHash(posY);
	}
	
}

int DigitalLab::_match(int posX, int posY)
{
	int nextJump = _pattern.getN();
	bool isEqual = true;
	for (size_t i = 0; i < _pattern.getN(); i++)
	{
		if (_matrixHash.at(posX + i) == _patternHash.at(0) && nextJump > i)
		{
			nextJump = i + 1;
		}
		if (_matrixHash.at(posX + i) != (_patternHash.at(i)))
		{
			isEqual = false;
			if (nextJump == _pattern.getN())
			{
				nextJump = i + 1;
			}
			break;
		}
	}
	if (isEqual && _isEqual(posX,posY))
	{
		for (size_t i = 0; i < _pattern.getM(); i++)
		{
			for (size_t j = 0; j < _pattern.getN(); j++)
			{
				char cur = _matrix.get(i + posY, j + posX);
				char toWrite = (cur == '0') ? '*' : '2';
				_matrix.put(i + posY, j + posX, toWrite);
			}
		}
	}
	return nextJump;
}
