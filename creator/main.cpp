#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "aesthetics.h"
#include "operators.h"
#include "easy.h"
#include "hard.h"
using namespace std;

typedef vector < vector<char> > VECTOR;

unsigned int LENGTH = 1;
unsigned int HEIGHT = 1;
int arr_height = 3;
int arr_length = 3;

bool get_input(int argc, char* argv[], string & mode)
{
	if (argc > 1 && argc < 5)						//if length & height passed
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
		if (argc > 4)
		{
			cout << "Too many arguments" << endl;
			return false;
		}
		else if (argv[3] == "e" || argv[3] == "E" || 
				 argv[3] == "easy" || argv[3] == "Easy")
		{
			mode = "e";
		}
		else
			mode = "h";
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
		cout << "Enter the difficulty of the maze. ";
		cout << "1 for easy, 2 for hard." << endl;
		int d = 0;
		while (d <= 0 || d > 2)
		{
			cin >> d;
		}
		if (d == 1)
			mode = "e";
		else
			mode = "h";
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
	string mode;
	if (!get_input(argc, argv, mode))
	{
		return 1;
	}

	srand(time(NULL));								//set rand sequence
	arr_height = (2 * HEIGHT) + 1;
	arr_length = (2 * LENGTH) + 1;
	VECTOR MAZE(arr_height, vector <char> (arr_length));		//set maze

	maze_init(MAZE, arr_height, arr_length);	
	
	if (mode == "e")
		gen_easy(MAZE, arr_height, arr_length);
	else
		gen_hard(MAZE, arr_height, arr_length);
	set_start_end(MAZE, arr_height, arr_length);

	print(MAZE, arr_height, arr_length);

	return 0;
}
