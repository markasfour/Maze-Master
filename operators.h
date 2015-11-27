#ifndef OPERATORS_H
#define OPERATORS_H

#include <iostream>
#include <vector>
using namespace std;

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

void remove_floaters(VECTOR &MAZE, int h, int l)
{
	for (int i = 1; i < h - 1; i ++)
	{
		for (int j = 1; j < l - 1; j ++)
		{
			int space = 0;
			if (MAZE.at(i).at(j) == 'x')
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
				if (space == 4)
				{
					int y = rand() % 4;
					if (y == 0)
					{
						MAZE.at(i - 1).at(j) = 'x';
					}
					else if (y == 1)
					{
						MAZE.at(i + 1).at(j) = 'x';
					}
					else if (y == 2)
					{
						MAZE.at(i).at(j - 1) = 'x';
					}
					else
					{
						MAZE.at(i).at(j + 1) = 'x';
					}
				}
			}
		}
	}
}

#endif
