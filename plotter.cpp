#include "plotter.hpp"
#include <cstdio>

using namespace std;

void Plotter::plot (const std::vector<share_t>& shares)
{
	if (!shares.size())
	{
		return;
	}
	float* values = shares.size() <= 30 ? new float[shares.size()] : new float[30];
	float biggest = 0.0f;
	float smallest = 9999999.0f;
	float difference = 0.0f;
	const int width = shares.size() <= 30 ? (int)shares.size() : 30;
	const int height = 20;
	char drawArea[height * width];
	memset((void*)&drawArea[0], ' ', height * width * sizeof(char));
	
	for (register int i = (int)shares.size(); i >= 0; i--)
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
	for (register int i = 0; i < width; i++)
	{
		float newVal = values[i] - smallest;
		int position = (int)(newVal / difference);
		drawArea[position * width + i] = '*';
	}
	printf("%s - shares\n", shares[0].name.c_str());
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
