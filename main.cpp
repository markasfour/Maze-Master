#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

typedef vector < vector<char> > VECTOR;

unsigned int LENGTH = 1;
unsigned int HEIGHT = 1;

void print(VECTOR MAZE, int h, int l)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < l; j++)
		{
			cout << MAZE.at(i).at(j);
		}
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc > 1 && argc < 4)						//if length & height passed
	{
		if (argc == 2)								//missing one arg
		{
			cout << "Missing height arg" << endl;
			return 1;
		}
		else
		{
			char l = *argv[1];
			char h = *argv[2];
			if (l - '0' <= 0)						//must be >= 0
			{
				cout << "Invalid length" << endl;
				return 1;
			}
			LENGTH = l - '0';
			if (h - '0' <= 0)						//must be >= 0
			{
				cout << "Invalid height" << endl;
				return 1;
			}
			HEIGHT = h - '0';
		}
	}
	if (argc > 3)									//too many args passed
	{
		cout << "Too many arguments" << endl;
		return 1;
	}
	if (argc == 1)									//no args passed
	{
		cout << "Enter the length of the maze." << endl;
		int l = 0;
		while (l <= 0)								//get length
		{
			cin >> l;
		}
		cout << "Enter the height of the maze." << endl;
		int h = 0;
		while (h <= 0)								//get height
		{
			cin >> h;
		}
		LENGTH = l;
		HEIGHT = h;
	}

	srand(time(NULL));								//set rand sequence
	int arr_height = (2 * HEIGHT) + 1;
	int arr_length = (2 * LENGTH) + 2;
	VECTOR MAZE(arr_height, vector <char> (arr_length));		//set maze

	for (int i = 0; i < arr_height; i++)			//init maze with spaces
	{
		for (int j = 0; j < arr_length; j++)
		{
			MAZE.at(i).at(j) = ' ';
		}
	}

	for (int i = 0; i < arr_height; i++)			//init left & right
	{
		MAZE.at(i).at(0) = '|';
		MAZE.at(i).at(arr_length - 1) = '|';
	}
	for (int i = 0; i < arr_length; i++)			//init top & bottom
	{
		MAZE.at(0).at(i) = '_';
		MAZE.at(arr_height - 1).at(i) = '^';
	}
	
	//print(MAZE, arr_height, arr_length);

	return 0;
}
