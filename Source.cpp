#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<queue>
#include<sstream>

#define width 1000
#define height 1000
#define viaCost 10
#define oppositePath 10

using namespace std;

struct cell {
	int xPos, yPos, layerNum, bfsNum;
	bool visited, obstacle, via, source, destination;
};

void bfs(cell*** arr, queue<cell> queue)
{

}

vector<int> parser(string str, cell***arr)
{
	int tempX, tempY, tempZ;
	std::vector<int> vect;
	std::stringstream ss(str);

	for (int i; ss >> i;) {
		vect.push_back(i);
		if (ss.peek() == ',')
			ss.ignore();
	}
	tempZ = vect[0];
	tempX = vect[1];
	tempY = vect[2];
	cout << tempZ << " " << tempX << " " << tempY << endl;
	return vect;
}


int main()
{
	int counter = 0;
	string subString;
	ifstream infile;
	infile.open("file.txt");
	int layer_count;
	string s;
	queue<cell> bfsQueue;
	cout << "Input number of layers:";
	cin >> layer_count;
	cell*** arr = new cell**[layer_count];

	for (int i = 0; i < layer_count; i++)
	{
		arr[i] = new cell*[width];
		for (int j = 0; j < width; j++)
			arr[i][j] = new cell[height];
	}

	//3D initailization
	for (int i = 0; i < layer_count; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < height; k++)
			{
				arr[i][j][k].layerNum = i;
				arr[i][j][k].xPos = j;
				arr[i][j][k].yPos = k;
				arr[i][j][k].bfsNum = 0;
				arr[i][j][k].visited = 0;
				arr[i][j][k].obstacle = 0;
				arr[i][j][k].via = 0;
				arr[i][j][k].source = 0;
				arr[i][j][k].destination = 0;
			}
	int temp, temp2;
	int tempX, tempY, tempZ;
	vector<int>tempVect;
	while (!infile.eof())
	{
		getline(infile, s);
		counter = 0;
		//net1 (1, 10, 20) (2, 30, 50) (1, 5, 100)
		for (int x = 0; x < s.length(); x++)
		{
			if (s[x] == '(' && counter == 0) //source start
			{
				temp = x + 1;
			}
			else if (s[x] == ')' && counter == 0) //source end
			{
				temp2 = x;
				subString = s.substr(temp, temp2);
				tempVect = parser(subString, arr);
				tempZ = tempVect[0];
				tempX = tempVect[1];
				tempY = tempVect[2];
				arr[tempZ][tempX][tempY].layerNum = tempZ;
				arr[tempZ][tempX][tempY].xPos = tempX;
				arr[tempZ][tempX][tempY].yPos = tempY;
				arr[tempZ][tempX][tempY].source = 1;

				counter++;
			}
			else if (s[x] == '(' && counter != 0) //destination start
			{
				temp = x + 1;
			}
			else if (s[x] == ')' && counter != 0) //destination end
			{
				temp2 = x;
				subString = s.substr(temp, temp2);
				tempVect = parser(subString, arr);
				tempZ = tempVect[0];
				tempX = tempVect[1];
				tempY = tempVect[2];
				arr[tempZ][tempX][tempY].layerNum = tempZ;
				arr[tempZ][tempX][tempY].xPos = tempX;
				arr[tempZ][tempX][tempY].yPos = tempY;
				arr[tempZ][tempX][tempY].destination = 1;

				counter++;
			}
			else
				continue;
		}

	}

	//test
	//net1(1, 10, 20) (2, 30, 50) (1, 5, 100)
	//net2(2, 100, 200) (1, 300, 50)
	//net3(1, 100, 50) (2, 300, 150) (2, 50, 50) (1, 2, 2)
	cout << arr[1][10][20].source << " " << arr[2][30][50].destination << " " << arr[1][5][100].destination << endl;
	cout << arr[2][100][200].source << " " << arr[1][300][50].destination << " " << endl;
	cout << arr[1][100][50].source << " " << arr[2][300][150].destination
		<< " " << arr[2][50][50].destination << " " << arr[1][2][2].destination << endl;

	// deallocate memory
	for (int i = 0; i < layer_count; i++)
	{
		for (int j = 0; j < width; j++)
			delete[] arr[i][j];

		delete[] arr[i];
	}

	delete[] arr;


	system("pause");
	return 0;
}