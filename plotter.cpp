#include "plotter.hpp"
#ifdef _DEBUG
#include <iostream>
#endif
#include <cstdio>
#include <cfloat>

using namespace std;

void Plotter::plot (const std::vector<share_t>& shares)
{
	// FIXME: output and calculations
	if (!shares.size())
	{
		printf("There are no shares to plot?!\n");
		return;
	}
	float* values = shares.size() < 30 ? new float[shares.size()] : new float[30];
	float biggest = FLT_MIN;
	float smallest = FLT_MAX;
	float difference = 0.0f;
	const int width = shares.size() < 30 ? (int)shares.size() : 30;
	const int height = 20;
	char drawArea[height * width];
	memset((void*)&drawArea[0], ' ', height * width * sizeof(char));
	
	for (register int i = 0; i < width; i++)
	{
		if (biggest < shares[i].close)
		{
			biggest = shares[i].close;
		}
		if (smallest > shares[i].close)
		{
			smallest = shares[i].close;
		}
		values[i] = shares[i].close;
	}
	difference = biggest - smallest;
	for (register int i = width - 1; i >= 0; i--)
	{
		float newVal = values[i] - smallest;
		int position = 20 - (int)((newVal / difference) * 20.0f);
		drawArea[position * width + (width - i - 1)] = '*';
	}
	printf("=========================================================================\n");
	printf("%s shares from %d/%d/%d to %d/%d/%d\n", shares[0].name.c_str(),
		shares[width-1].date.month, shares[width-1].date.day, shares[width-1].date.year,
		shares[0].date.month, shares[0].date.day, shares[0].date.year);
	printf("=========================================================================\n");
	for (register int i = 0; i < height; i++)
	{
		if (i == 0)
		{
			printf("%05.1f |", biggest);
		}
		else if (i == (height - 1))
		{
			printf("%05.1f |", smallest);
		}
		else
		{
			printf("      |");
		}
		for (register int j = 0; j < width; j++)
		{
			printf("%c", drawArea[i * width + j]);
		}
		printf("\n");
	}
	printf("      +------------------------------\n");
	printf("    %d/%d/%d                 %d/%d/%d\n",
		shares[width-1].date.month, shares[width-1].date.day, shares[width-1].date.year,
		shares[0].date.month, shares[0].date.day, shares[0].date.year);
	delete[] values;
}
