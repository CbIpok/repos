#include "Matrix.h"

void Matrix::put(size_t i, size_t j, char value)
{
	_matrix.at(i*_m + j) = value;
}

void Matrix::put(size_t pos, char value)
{
	_matrix.at(pos) = value;
}

void Matrix::setSize(size_t m, size_t n)
{
	_matrix.resize(m*n, '\0');
	_m = m;
	_n = n;
}

char Matrix::get(size_t i, size_t j)
{
	return (_matrix.at(_at(i,j)) == '1' || _matrix.at(_at(i,j)) == '2')?'1':'0';
}

void Matrix::print(std::ostream & ostream)
{
	for (size_t i = 0; i < _m; i++)
	{
		for (size_t j = 0; j < _n; j++)
		{
			ostream << _matrix.at(_at(i, j))<<" ";
		}
		if (i < _n - 1)
			ostream << std::endl;
	}
}

size_t Matrix::_at(size_t i, size_t j)
{
	return i * _n + j;
}
