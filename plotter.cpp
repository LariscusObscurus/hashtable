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
	
	for (register int i = 0; i < (int)shares.size(); i++)
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
	for (register int i = width - 1; i >= 0; i--)
	{
#ifdef _DEBUG
	cout << "before shares.size() = " << shares.size() << "; i = " << i << "\n";
#endif
		float newVal = values[i] - smallest;
		int position = 20 - (int)(newVal / difference * 20.0f);
		drawArea[position * width + i] = '*';
#ifdef _DEBUG
	cout << "after shares.size() = " << shares.size() << "; i = " << i << "\n";
#endif
	}
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
	delete[] values;
}
