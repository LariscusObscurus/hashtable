#include "plotter.hpp"
#include <cstdio>

using namespace std;

void Plotter::plot (const std::vector<Share_t>& shares)
{
	float values[30];
	float biggest = 0.0f;
	float smallest = 9999999.0f;
	float difference = 0.0f;
	const int width = 30;
	const int height = 20;
	char drawArea[height * width];
	memset((void*)&drawArea[0], ' ', height * width * sizeof(char));
	
	for (register int i = shares.size(); i >= 0; i--)
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
	for (register int i = 0; i < height; i++)
	{
		float newVal = values[i] - smallest;
		int position = (int)(newVal / difference);
		drawArea[i * width + position] = '*';
	}
	draw(shares[i].name, &values[0], biggest, smallest, difference);
}

void Plotter::draw (const std::string& name, const char* drawArea)
{
	printf("%s - shares\n", name.c_str());
	for (register int i = 0; i < height; i++)
	{
		printf("%f.1 |");
		printf("%30s\n", values[i], drawArea[i * width]);
	}
	printf("+------------------------------\n");
}
