#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<queue>
#include<sstream>

#define width 31
#define height 31
#define viaCost 10
#define oppositePath 10

using namespace std;

struct cell {
	int xPos, yPos, layerNum, bfsNum, netlist;
	bool visited, obstacle, via, source, destination;
};

bool calculate(cell***& arr, vector<cell>& bfsQueue, int num, int destZ, int destX, int destY)
{
	int x = bfsQueue[num].xPos, y = bfsQueue[num].yPos, z = bfsQueue[num].layerNum;
	if (z % 2 == 0) //check all 4 conditions of even layers
	{
		if (destY > y) // if y is less than destination
		{
			if (((y + 1) >= 0 && (y + 1) <= 999) && arr[z][x][y + 1].visited == 0 && arr[z][x][y + 1].obstacle == 0 && arr[destZ][x][y + 1].obstacle == 0)
			{
				arr[z][x][y + 1].visited = 1;
				arr[z][x][y + 1].obstacle = 1;
				arr[z][x][y + 1].bfsNum = bfsQueue[num].bfsNum + 1;
				bfsQueue.push_back(arr[z][x][y + 1]);
			}
			else //via
			{
				if (abs(z - destZ) % 2 == 1) // example 2 & 3
				{
					if (arr[z][x][y].via == 1 && arr[destZ][x][y].via == 1)
					{
						cout << "Cannot find a path for this net." << endl;
						system("pause");
						exit(0);
					}
					arr[z][x][y].via = 1;
					arr[destZ][x][y].via = 1;
					arr[destZ][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
					bfsQueue.push_back(arr[destZ][x][y]);
				}
				else if (destZ == z) // example 2 & 2
				{
					arr[z][x][y].via = 1;
					if (z - 1 > 1 && arr[z - 1][x][y].obstacle == 0)
					{
						if (arr[z][x][y].via == 1 && arr[z - 1][x][y].via == 1)
						{
							cout << "Cannot find a path for this net." << endl;
							system("pause");
							exit(0);
						}
						arr[z - 1][x][y].via = 1;
						arr[z - 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[z - 1][x][y]);
					}
					else
					{
						if (arr[z][x][y].via == 1 && arr[z + 1][x][y].via == 1)
						{
							cout << "Cannot find a path for this net." << endl;
							system("pause");
							exit(0);
						}
						arr[z + 1][x][y].via = 1;
						arr[z + 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[z + 1][x][y]);
					}
				}
				else if(abs(z - destZ) % 2 == 0) // example 2 & 4
				{
					// destz w el z el na5d el max w n minus 1 and hn check for obstacle w n7tlo via w n push it  
					arr[z][x][y].via = 1;
					int m = min(destZ, z);
					if (arr[z][x][y].via == 1 && arr[m + 1][x][y].via == 1)
					{
						cout << "Cannot find a path for this net." << endl;
						system("pause");
						exit(0);
					}
					if (arr[m + 1][x][y].obstacle == 0)
					{
						arr[m + 1][x][y].via = 1;
						arr[m + 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[m + 1][x][y]);
					}
				}
			}
		}
		else if (destY < y)
		{
			if (((y - 1) >= 0 && (y - 1) <= 999) && arr[z][x][y - 1].visited == 0 && arr[z][x][y - 1].obstacle == 0 && arr[destZ][x][y - 1].obstacle == 0)
			{
				arr[z][x][y - 1].visited = 1;
				arr[z][x][y - 1].obstacle = 1;
				arr[z][x][y - 1].bfsNum = bfsQueue[num].bfsNum + 1;
				bfsQueue.push_back(arr[z][x][y - 1]);
			}
			else //via
			{
				
				if (abs(z - destZ) % 2 == 1) // example 2 & 3
				{
					if (arr[z][x][y].via == 1 && arr[destZ][x][y].via == 1)
					{
						cout << "Cannot find a path for this net." << endl;
						system("pause");
						exit(0);
					}
					arr[z][x][y].via = 1;
					arr[destZ][x][y].via = 1;
					arr[destZ][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
					bfsQueue.push_back(arr[destZ][x][y]);
				}
				else if (destZ == z) // example 2 & 2
				{
					
					arr[z][x][y].via = 1;
					if (z - 1 > 1 && arr[z - 1][x][y].obstacle == 0)
					{
						if (arr[z][x][y].via == 1 && arr[z - 1][x][y].via == 1)
						{
							cout << "Cannot find a path for this net." << endl;
							system("pause");
							exit(0);
						}
						arr[z - 1][x][y].via = 1;
						arr[z - 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[z - 1][x][y]);
					}
					else
					{
						if (arr[z][x][y].via == 1 && arr[z + 1][x][y].via == 1)
						{
							cout << "Cannot find a path for this net." << endl;
							system("pause");
							exit(0);
						}
						arr[z + 1][x][y].via = 1;
						arr[z + 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[z + 1][x][y]);
					}
				}
				else if (abs(z - destZ) % 2 == 0)// example 2 & 4
				{
					// destz w el z el na5d el max w n minus 1 and hn check for obstacle w n7tlo via w n push it  
					arr[z][x][y].via = 1;
					int m = min(destZ, z);
					if (arr[z][x][y].via == 1 && arr[m + 1][x][y].via == 1)
					{
						cout << "Cannot find a path for this net." << endl;
						system("pause");
						exit(0);
					}
					if (arr[m + 1][x][y].obstacle == 0)
					{
						arr[m + 1][x][y].via = 1;
						arr[m + 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[m + 1][x][y]);
					}
					else
					{
						cout << "Error!!!!" << endl;
					}
				}
			}
		}
		else //destY == y
		{
			if (destX == x && destZ == z)
				return true;
			else
			{
				if (abs(z - destZ) % 2 == 1) // example 2 & 3
				{
					if (arr[z][x][y].via == 1 && arr[destZ][x][y].via == 1)
					{
						cout << "Cannot find a path for this net." << endl;
						system("pause");
						exit(0);
					}
					arr[z][x][y].via = 1;
					arr[destZ][x][y].via = 1;
					arr[destZ][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
					bfsQueue.push_back(arr[destZ][x][y]);
				}
				else if (destZ == z) // example 2 & 2
				{
					if (arr[z][x][y].via == 1 && arr[z - 1][x][y].via == 1)
					{
						cout << "Cannot find a path for this net." << endl;
						system("pause");
						exit(0);
					}
					arr[z][x][y].via = 1;
					if (z - 1 > 1 && arr[z - 1][x][y].obstacle == 0)
					{
						arr[z - 1][x][y].via = 1;
						arr[z - 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[z - 1][x][y]);
					}
					else
					{
						if (arr[z][x][y].via == 1 && arr[z + 1][x][y].via == 1)
						{
							cout << "Cannot find a path for this net." << endl;
							system("pause");
							exit(0);
						}
						arr[z + 1][x][y].via = 1;
						arr[z + 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[z + 1][x][y]);
					}
				}
				else if (abs(z - destZ) % 2 == 0)// example 2 & 4
				{
					// destz w el z el na5d el max w n minus 1 and hn check for obstacle w n7tlo via w n push it  
					arr[z][x][y].via = 1;
					int m = min(destZ, z);
					if (arr[z][x][y].via == 1 && arr[m + 1][x][y].via == 1)
					{
						cout << "Cannot find a path for this net." << endl;
						system("pause");
						exit(0);
					}
					if (arr[m + 1][x][y].obstacle == 0)
					{
						arr[m + 1][x][y].via = 1;
						arr[m + 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[m + 1][x][y]);
					}
				}
			}
		}
	}




	else //z % 2 != 0
	{
		if (destX > x) // if X is less than destination
		{
			if (((x + 1) >= 0 && (x + 1) <= 999) && arr[z][x + 1][y].visited == 0 && arr[z][x + 1][y].obstacle == 0 && arr[destZ][x + 1][y].obstacle == 0)
			{
				arr[z][x + 1][y].visited = 1;
				arr[z][x + 1][y].obstacle = 1;
				arr[z][x + 1][y].bfsNum = bfsQueue[num].bfsNum + 1;
				bfsQueue.push_back(arr[z][x + 1][y]);
			}
			else //via
			{
				if (abs(z - destZ) % 2 == 1) // example 2 & 3
				{
					if (arr[z][x][y].via == 1 && arr[destZ][x][y].via == 1)
					{
						cout << "Cannot find a path for this net." << endl;
						system("pause");
						exit(0);
					}
					arr[z][x][y].via = 1;
					arr[destZ][x][y].via = 1;
					arr[destZ][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
					bfsQueue.push_back(arr[destZ][x][y]);
				}
				else if (destZ == z) // example 2 & 2
				{
					arr[z][x][y].via = 1;
					if (z - 1 > 1 && arr[z - 1][x][y].obstacle == 0)
					{
						if (arr[z][x][y].via == 1 && arr[z - 1][x][y].via == 1)
						{
							cout << "Cannot find a path for this net." << endl;
							system("pause");
							exit(0);
						}
						arr[z - 1][x][y].via = 1;
						arr[z - 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[z - 1][x][y]);
					}
					else
					{
						if (arr[z][x][y].via == 1 && arr[z + 1][x][y].via == 1)
						{
							cout << "Cannot find a path for this net." << endl;
							system("pause");
							exit(0);
						}
						arr[z + 1][x][y].via = 1;
						arr[z + 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[z + 1][x][y]);
					}
				}
				else if (abs(z - destZ) % 2 == 0)// example 2 & 4
				{
					// destz w el z el na5d el max w n minus 1 and hn check for obstacle w n7tlo via w n push it  
					arr[z][x][y].via = 1;
					int m = min(destZ, z);
					if (arr[z][x][y].via == 1 && arr[m + 1][x][y].via == 1)
					{
						cout << "Cannot find a path for this net." << endl;
						system("pause");
						exit(0);
					}
					if (arr[m + 1][x][y].obstacle == 0)
					{
						arr[m + 1][x][y].via = 1;
						arr[m + 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[m + 1][x][y]);
					}
				}
			}

		}
		else if (destX < x) // if X is greater than destination
		{
			if (((x - 1) >= 0 && (x - 1) <= 999) && arr[z][x - 1][y].visited == 0 && arr[z][x - 1][y].obstacle == 0 && arr[destZ][x - 1][y].obstacle == 0)
			{
				arr[z][x - 1][y].visited = 1;
				arr[z][x - 1][y].obstacle = 1;
				arr[z][x - 1][y].bfsNum = bfsQueue[num].bfsNum + 1;
				bfsQueue.push_back(arr[z][x - 1][y]);
			}
			else //via
			{
				if (abs(z - destZ) % 2 == 1) // example 2 & 3
				{
					if (arr[z][x][y].via == 1 && arr[destZ][x][y].via == 1)
					{
						cout << "Cannot find a path for this net." << endl;
						system("pause");
						exit(0);
					}
					arr[z][x][y].via = 1;
					arr[destZ][x][y].via = 1;
					arr[destZ][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
					bfsQueue.push_back(arr[destZ][x][y]);
				}
				else if (destZ == z) // example 2 & 2
				{
					arr[z][x][y].via = 1;
					if (z - 1 > 1 && arr[z - 1][x][y].obstacle == 0)
					{
						arr[z - 1][x][y].via = 1;
						arr[z - 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[z - 1][x][y]);
					}
					else
					{
						if (arr[z][x][y].via == 1 && arr[z + 1][x][y].via == 1)
						{
							cout << "Cannot find a path for this net." << endl;
							system("pause");
							exit(0);
						}
						arr[z + 1][x][y].via = 1;
						arr[z + 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[z + 1][x][y]);
					}
				}
				else if (abs(z - destZ) % 2 == 0)// example 2 & 4
				{
					// destz w el z el na5d el max w n minus 1 and hn check for obstacle w n7tlo via w n push it  
					arr[z][x][y].via = 1;
					int m = min(destZ, z);
					if (arr[z][x][y].via == 1 && arr[m + 1][x][y].via == 1)
					{
						cout << "Cannot find a path for this net." << endl;
						system("pause");
						exit(0);
					}
					if (arr[m + 1][x][y].obstacle == 0)
					{
						arr[m + 1][x][y].via = 1;
						arr[m + 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[m + 1][x][y]);
					}
				}
			}
		}
		else //destX == x
		{
			if (destY == y && destZ == z)
				return true;
			else
			{
				if (abs(z - destZ) % 2 == 1) // example 2 & 3
				{
					if (arr[z][x][y].via == 1 && arr[destZ][x][y].via == 1)
					{
						cout << "Cannot find a path for this net." << endl;
						system("pause");
						exit(0);
					}
					arr[z][x][y].via = 1;
					arr[destZ][x][y].via = 1;
					arr[destZ][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
					bfsQueue.push_back(arr[destZ][x][y]);
				}
					else if (destZ == z) // example 2 & 2
				{
					arr[z][x][y].via = 1;
					if (z - 1 > 1 && arr[z - 1][x][y].obstacle == 0)
					{
						if (arr[z][x][y].via == 1 && arr[z - 1][x][y].via == 1)
						{
							cout << "Cannot find a path for this net." << endl;
							system("pause");
							exit(0);
						}
						arr[z - 1][x][y].via = 1;
						arr[z - 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[z - 1][x][y]);
					}
					else
					{
						if (arr[z][x][y].via == 1 && arr[z + 1][x][y].via == 1)
						{
							cout << "Cannot find a path for this net." << endl;
							system("pause");
							exit (0);
						}
						arr[z + 1][x][y].via = 1;
						arr[z + 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[z + 1][x][y]);
					}
				}
				else if (abs(z - destZ) % 2 == 0)// example 2 & 4
				{
					// destz w el z el na5d el max w n minus 1 and hn check for obstacle w n7tlo via w n push it  
					arr[z][x][y].via = 1;
					int m = min(destZ, z);
					if (arr[z][x][y].via == 1 && arr[m + 1][x][y].via == 1)
					{
						cout << "Cannot find a path for this net." << endl;
						system("pause");
						exit(0);
					}
					if (arr[m + 1][x][y].obstacle == 0)
					{
						arr[m + 1][x][y].via = 1;
						arr[m + 1][x][y].bfsNum = arr[z][x][y].bfsNum + viaCost;
						bfsQueue.push_back(arr[m + 1][x][y]);
					}
				}
			}
		}

	}


	return false;
}

void bfs(cell***& arr, vector<cell>& bfsQueue, int destZ, int destX, int destY)
{
	int count = 1;
	bool flag = calculate(arr, bfsQueue, 0, destZ, destX, destY);
	if (flag == false)
	{
		while (calculate(arr, bfsQueue, count, destZ, destX, destY) != true)
		{
			count++;
		}
	}
	cell destDelay = bfsQueue.back();
	cout << "Delay = " << destDelay.bfsNum << endl;
	cout << "Size of Queue " << bfsQueue.size() << endl;
	//for (int i = 0; i < bfsQueue.size(); i++)
	//{
	//	cout << bfsQueue[i].layerNum << " " << bfsQueue[i].xPos << " " << bfsQueue[i].yPos << " " << bfsQueue[i].bfsNum << endl;
	//}

}

vector<int> parser(string str, cell*** arr)
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
	int counter = 0, netCount = 1 , counterloop = 1;
	string subString;
	ifstream infile;
	infile.open("file.txt");
	ofstream outfile;
	outfile.open("out.txt");
	int layer_count;
	string s;
	vector<cell> bfsQueue, destVec, outCopy;
	cout << "Input number of layers:";
	cin >> layer_count;
	layer_count+=2;
	cell*** arr = new cell * *[layer_count];

	for (int i = 0; i < layer_count; i++)
	{
		arr[i] = new cell * [width];
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
		bfsQueue.clear();
		destVec.clear();
		outCopy.clear();
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
				arr[tempZ][tempX][tempY].bfsNum = 1;
				arr[tempZ][tempX][tempY].visited = 1;
				arr[tempZ][tempX][tempY].obstacle = 1;
				arr[tempZ][tempX][tempY].via = 0;
				bfsQueue.push_back(arr[tempZ][tempX][tempY]);
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
				destVec.push_back(arr[tempZ][tempX][tempY]);
				counter++;
			}
			else
				continue;
		}
		for (int i = 0; i < destVec.size(); i++) {
			bfs(arr, bfsQueue, destVec[i].layerNum, destVec[i].xPos, destVec[i].yPos);
			for (int j = 0; j < bfsQueue.size(); j++)
			{
				arr[bfsQueue[j].layerNum][bfsQueue[j].xPos][bfsQueue[j].yPos].bfsNum = 1;
				arr[bfsQueue[j].layerNum][bfsQueue[j].xPos][bfsQueue[j].yPos].source = 1;
				arr[bfsQueue[j].layerNum][bfsQueue[j].xPos][bfsQueue[j].yPos].destination = 0;
				arr[bfsQueue[j].layerNum][bfsQueue[j].xPos][bfsQueue[j].yPos].obstacle = 1;
				outCopy.push_back(bfsQueue[j]);
			}
			bfsQueue.clear();
			bfsQueue.push_back(outCopy.back());
			bfsQueue[0].bfsNum = 1;
		}
		//print outCopy into output file 
		outfile << "net" << netCount;
		for (int i = 0; i < outCopy.size(); i++) {
			outfile << " (" << outCopy[i].layerNum << ", " << outCopy[i].xPos << ", " << outCopy[i].yPos << ")";
			arr[outCopy[i].layerNum][outCopy[i].xPos][outCopy[i].yPos].netlist = netCount;
		}
		outfile << endl;
		for (int z = 1; z < layer_count - 1; z++)
		{
			cout << "Layer " << counterloop << ":" << endl;
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < width; j++)
				{
					if (arr[z][i][j].obstacle == 1)
						cout << arr[z][i][j].netlist << " ";
					else
						cout << 0 << " ";
				}
				cout << endl;
			}
			counterloop++;
		}
		netCount++;
	}
	cout << endl;
	infile.close();
	outfile.close();

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
