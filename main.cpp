#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "aesthetics.h"
#include "operators.h"
#include "easy.h"
using namespace std;

typedef vector < vector<char> > VECTOR;

unsigned int LENGTH = 1;
unsigned int HEIGHT = 1;
int arr_height = 3;
int arr_length = 3;

bool get_input(int argc, char* argv[])
{
	if (argc > 1 && argc < 4)						//if length & height passed
	{
		if (argc == 2)								//missing one arg
		{
			cout << "Missing height arg" << endl;
			return false;
		}
		else
		{
			LENGTH = atoi(argv[1]);
			HEIGHT = atoi(argv[2]);
			if (LENGTH == 0)						//must be > 0
			{
				cout << "Invalid length" << endl;
				return false;
			}
			if (HEIGHT == 0)						//must be > 0
			{
				cout << "Invalid height" << endl;
				return false;
			}
		}
	}
	if (argc > 3)									//too many args passed
	{
		cout << "Too many arguments" << endl;
		return false;
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
	return true;
}

void maze_init(VECTOR &MAZE, int arr_height, int arr_length)
{
	for (int i = 0; i < arr_height; i++)			//init maze with x
	{
		for (int j = 0; j < arr_length; j++)
		{
			MAZE.at(i).at(j) = 'x';
		}
	}
	for (int i = 1; i < arr_height; i += 2)
	{
		for (int j = 1; j < arr_length; j += 2)
		{
			MAZE.at(i).at(j) = ' ';
		}
	}
}

int main(int argc, char* argv[])
{
	if (!get_input(argc, argv))
	{
		return 1;
	}

	srand(time(NULL));								//set rand sequence
	arr_height = (2 * HEIGHT) + 1;
	arr_length = (2 * LENGTH) + 1;
	VECTOR MAZE(arr_height, vector <char> (arr_length));		//set maze

	maze_init(MAZE, arr_height, arr_length);	
	
	gen_easy(MAZE, arr_height, arr_length);
	set_start_end(MAZE, arr_height, arr_length);

	print(MAZE, arr_height, arr_length);

	return 0;
}
