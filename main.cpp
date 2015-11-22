#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

typedef vector < vector<char> > VECTOR;

unsigned int LENGTH = 1;
unsigned int HEIGHT = 1;
int arr_height = 3;
int arr_length = 3;

void beautify(VECTOR &MAZE, int h, int l)
{
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < l; j++)
		{
			if (MAZE.at(i).at(j) == 'x')
			{
				if (j - 1 >= 0)
				{
					if (MAZE.at(i).at(j - 1) != ' ')
					{
						left = true;
					}
				}
				if (j + 1 < l)
				{
					if (MAZE.at(i).at(j + 1) != ' ')
					{
						right = true;
					}
				}
				if (i - 1 >= 0)
				{
					if (MAZE.at(i - 1).at(j) != ' ')
					{
						up = true; 
					}
				}
				if (i + 1 < h)
				{
					if (MAZE.at(i + 1).at(j) != ' ')
					{
						down = true;
					}
				}
			
				if (left && right && !(up && down))
				{
					MAZE.at(i).at(j) = '-';
				}
				else if (up && down && !(left && right))
				{
					MAZE.at(i).at(j) = '|';
				}
				else
				{
					MAZE.at(i).at(j) = '+';
				}
			}
			left = false;
			right = false;
			up = false;
			down = false;
		}
	}
}

void print(VECTOR MAZE, int h, int l)
{
	beautify(MAZE, h, l);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < l; j++)
		{
			cout << MAZE.at(i).at(j);
		}
		cout << endl;
	}
}

bool go_right(VECTOR &MAZE, int l, int &i, int &j)
{
	if (j + 2 >= l - 1)
	{
		return false;
	}
	else
	{
		MAZE.at(i).at(j + 1) = ' ';
		j += 2;
		return true;
	}
	cout << "R" << endl;
}

bool go_left(VECTOR &MAZE, int l, int &i, int &j)
{
	if (j - 2 <= 0)
	{
		return false;
	}
	else
	{
		MAZE.at(i).at(j - 1) = ' ';
		j -= 2;
		return true;
	}
	cout << "L" << endl;
}

bool go_down(VECTOR &MAZE, int h, int &i, int &j)
{
	if (i + 2 >= h - 1)
	{
		return false;
	}
	else
	{
		MAZE.at(i + 1).at(j) = ' ';
		i += 2;
		return true;
	}
	cout << "D" << endl;
}

bool go_up(VECTOR &MAZE, int h, int &i, int &j)
{
	if (i - 2 <= 0)
	{
		return false;
	}
	else
	{
		MAZE.at(i - 1).at(j) = ' ';
		i -= 2;
		return true;
	}
	cout << "U" << endl;
}

bool check_maze(VECTOR MAZE, int h, int l, int &x, int &y)
{
	if (HEIGHT == 1 && LENGTH == 1)
	{
		return true;
	}
	for (int i = 1; i < h; i += 2)
	{
		for (int j = 1; j < l; j += 2)
		{
			int space = 0;
			if (MAZE.at(i - 1).at(j) == ' ')
				space++;
			if (MAZE.at(i + 1).at(j) == ' ')
				space++;
			if (MAZE.at(i).at(j - 1) == ' ')
				space++;
			if	(MAZE.at(i).at(j + 1) == ' ')
				space++;
			if (space >= 3)
			{
				x = i;
				y = j;
				return false;
			}
		}
	}
	return true;
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
	arr_height = (2 * HEIGHT) + 1;
	arr_length = (2 * LENGTH) + 1;
	VECTOR MAZE(arr_height, vector <char> (arr_length));		//set maze

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
	
	bool COMPLETE = false;
	VECTOR PATH(arr_height, vector <char> (arr_length));
	for (int i = 0; i < arr_height; i++)			//init maze with x
	{
		for (int j = 0; j < arr_length; j++)
		{
			PATH.at(i).at(j) = ' ';
		}
	}
	int i = 1;
	int j = 1;
	PATH.at(1).at(1) = 'x';
	while (!COMPLETE)
	{
		int y = rand() % 4;
		if (y == 0)
		{
			if (go_up(MAZE, arr_height, i, j))
			{
				PATH.at(i).at(j) = 'x';
				PATH.at(i + 1).at(j) = 'x';
			}
		}
		else if (y == 1)
		{
			if (go_down(MAZE, arr_height, i, j))
			{
				PATH.at(i).at(j) = 'x';
				PATH.at(i - 1).at(j) = 'x';
			}
		}
		else if (y == 2)
		{
			if (go_left(MAZE, arr_length, i, j))
			{
				PATH.at(i).at(j) = 'x';
				PATH.at(i).at(j + 1) = 'x';
			}
		}
		else
		{
			if (go_right(MAZE, arr_length, i, j))
			{
				PATH.at(i).at(j) = 'x';
				PATH.at(i).at(j - 1) = 'x';
			}
		}

		if (check_maze(PATH, arr_height, arr_length, i, j))	//check paths are complete
		{
			COMPLETE = true;
		}
	}
	
	//Set start point
	int start = rand() % 4;
	if (start < 2)									//start at left or right
	{
		if (start == 0)								//start at left wall
		{
			start = rand() % (arr_height - 2) + 1;
			if (start % 2 == 0)
			{
				start++;
			}
			MAZE.at(start).at(0) = ' ';
		}
		else										//start at right wall
		{
			start = rand() % (arr_height - 2) + 1;
			if (start % 2 == 0)
			{
				start++;
			}
			MAZE.at(start).at(arr_length - 1) = ' ';
		}
	}
	else
	{
		if (start == 2)								//start at top wall
		{
			start = rand() % (arr_length - 2) + 1;
			if (start % 2 == 0)
			{
				start++;
			}
			MAZE.at(0).at(start) = ' ';
		}
		else										//start at bottom wall
		{
			start = rand() % (arr_length - 2) + 1;
			if (start % 2 == 0)
			{
				start++;
			}
			MAZE.at(arr_height - 1).at(start) = ' ';
		}
	}
	
	//Set end point
	int end;
	bool SAME = true;								//if start and end are same
	while (SAME)
	{
		end = rand() % 4;
		if (end < 2)								//end at left or right
		{
			if (end == 0)							//end at left wall
			{
				end = rand() % (arr_height - 2) + 1;
				if (end % 2 == 0)
				{
					end++;
				}
				if (MAZE.at(end).at(0) == ' ')
				{
					continue;	
				}
				else
				{
					MAZE.at(end).at(0) = ' ';
					SAME = false;
				}
			}
			else									//end at right wall
			{
				end = rand() % (arr_height - 2) + 1;
				if (end % 2 == 0)
				{
					end++;
				}
				if (MAZE.at(end).at(arr_length - 1) == ' ')
				{
					continue;	
				}
				else
				{
					MAZE.at(end).at(arr_length - 1) = ' ';
					SAME = false;
				}
			}
		}
		else
		{
			if (end == 2)							//end at top wall
			{
				end = rand() % (arr_length - 2) + 1;
				if (end % 2 == 0)
				{
					end++;
				}
				if (MAZE.at(0).at(end) == ' ')
				{
					continue;	
				}
				else
				{
					MAZE.at(0).at(end) = ' ';
					SAME = false;
				}
			}
			else									//end at bottom wall
			{
				end = rand() % (arr_length - 2) + 1;
				if (end % 2 == 0)
				{
					end++;
				}
				if (MAZE.at(arr_height - 1).at(end) == ' ')
				{
					continue;	
				}
				else
				{
					MAZE.at(arr_height - 1).at(end) = ' ';
					SAME = false;
				}
			}
		}
	}
	print(MAZE, arr_height, arr_length);

	cout << endl;
	//print(PATH, arr_height, arr_length);
	return 0;
}
