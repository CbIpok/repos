#define N 8
#define M 8
#define COUNT 10000
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <stdio.h>

FILE* in;
FILE* out;

float x[N][M] = {
	{1,2,3,4,5,6,7,8},
	{1,2,3,4,5,6,7,8},
	{1,2,3,4,5,6,7,8},
	{1,2,3,4,5,6,7,8},
	{1,2,3,4,5,6,7,8},
	{1,2,3,4,5,6,7,8},
	{1,2,3,4,5,6,7,8},
	{1,2,3,4,5,6,7,8}
};

float f[N][M];

float** readInput()
{
	return 0;
}

float** readOutput()
{
	return 0;
}


int main()
{
	in = fopen("dct_II_inputs_8x8_float32.bin", "rb");
	in = fopen("dct_II_outputs_8x8_float32.bin", "rb");
	float c[N] = { 1.0 / sqrt(2.0) ,1,2,3,4,5,6,7 };
	clock_t begin = clock();
	for (size_t t = 0; t < COUNT; t++)
	{
		for (int n = 0; n < N; n++)
		{
			for (int m = 0; m < N; m++)
			{
				float sum_i = 0;
				for (int i = 0; i < N; i++)
				{
					float sum_j = 0;
					for (int j = 0; j < N; j++)
					{
						sum_j += cos(M_PI*n*(2 * i + 1) / 16)*cos(M_PI*m*(2 * j + 1) / 16)*x[i][j];
					}
					sum_i += sum_j;
				}
				f[n][m] = sum_i;
			}
		}
	}
	clock_t end = clock();
	printf("%Lf", (long double)(end - begin));
}