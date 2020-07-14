#include<iostream>
#include<vector>
#include<string>
#define width 1000
#define height 1000
using namespace std;
struct cell {
	int xPos, yPos, layerNum, bfsNum;
	bool visited, obstacle, via;
};

int main()
{
	int layer_count;
	cout << "Input number of layers:";
	cin >> layer_count;
	cell*** arr = new cell** [layer_count];

	for (int i = 0; i < layer_count; i++)
	{
		arr[i] = new cell* [width];

		for (int j = 0; j < width; j++)
			arr[i][j] = new cell[height];
	}

	//3D initailization
	for(int i = 0; i < layer_count; i++)
		for(int j = 0; j < width; j++)
			for (int k = 0; k < height; k++)
			{
				arr[i][j][k].layerNum = i;
				arr[i][j][k].xPos = j;
				arr[i][j][k].yPos = k;
				arr[i][j][k].bfsNum = 0;
				arr[i][j][k].visited = 0;
				arr[i][j][k].obstacle = 0;
				arr[i][j][k].via = 0;
			}

	// deallocate memory
	for (int i = 0; i < layer_count; i++)
	{
		for (int j = 0; j < width; j++)
			delete[] arr[i][j];

		delete[] arr[i];
	}

	delete[] arr;



	return 0;
}