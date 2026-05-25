#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <bitset>
#include <cstdlib>
#include <cstring>

using namespace std;

void scalarUniformQuant()
{
	
}

void scalarNonUniformQuant()
{

}

void vectorNonUniformQuant()
{

}

bool readImage(const char* fileName, unsigned char* data, int size)
{
	FILE* file;
	fopen_s(&file, fileName, "rb");

	if (!file)
	{
		cout << "Failed to open file: " << fileName << endl;
		return false;
	}

	fread(data, sizeof(char), size, file);
	fclose(file);

	return true;
}

bool writeImage(const char* fileName, unsigned char* data, int size)
{
	FILE* file;
	fopen_s(&file, fileName, "wb");

	if (!file)
	{
		cout << "Failed to wrtie file: " << fileName << endl;
		return false;
	}

	fwrite(data, sizeof(char), size, file);
	fclose(file);

	return true;
}

int main(void)
{
	
}