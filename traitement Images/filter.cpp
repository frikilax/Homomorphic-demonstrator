#include "filter.h"

Filter::Filter(string name, int height, int width, vector<int> values)
{
	filterName = name;
	filterHeight = height;
	filterWidth = width;
	filterValues = values;
}


void Filter::print()
{
	cout << "filter '" << filterName << "'" << endl;
	for(int i=0; i<filterHeight; i++)
	{
		for(int j=0; j<filterWidth; j++)
		{
			cout << filterValues[i*filterWidth+j] << " ";
		}
		cout << endl;
	}
}

int Filter::getValue(int x, int y)
{
	if(x > filterHeight - 1)
		throw invalid_argument("x over height of filter matrix");
	if(y > filterWidth - 1)
		throw invalid_argument("y over width of filter matrix");

	return filterValues[x*filterWidth+y];
}


int Filter::getNorm()
{
	int sum = 0;

	for(int i=0; i<filterValues.size(); i++)
	{
		sum += filterValues[i];
	}

	return sum;
}