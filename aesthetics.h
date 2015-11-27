#ifndef AESTHETICS_H
#define AESTHETICS_H

#include <iostream>
#include <vector>
using namespace std;

typedef vector < vector<char> > VECTOR;

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
	for (int i = 0; i < h; i++)
	{
		for (int j = l - 2; j > -1; j -= 2)
		{
			if (MAZE.at(i).at(j) == ' ')
			{
				MAZE.at(i).insert(MAZE.at(i).begin() + j + 1, ' ');
			}
			else
			{
				MAZE.at(i).insert(MAZE.at(i).begin() + j + 1, '-');
			}
		}
	}
}

void print(VECTOR MAZE, int h, int l)
{
	beautify(MAZE, h, l);
	for (int i = 0; i < MAZE.size(); i++)
	{
		for (int j = 0; j < MAZE.at(i).size(); j++)
		{
			cout << MAZE.at(i).at(j);
		}
		cout << endl;
	}
}

#endif
