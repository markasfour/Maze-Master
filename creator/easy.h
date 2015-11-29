#ifndef EASY_H
#define EASY_H

#include <iostream>
#include <vector>
#include "operators.h"

bool check_maze(VECTOR MAZE, int h, int l, int &x, int &y)
{
	if ((h - 1) / 2 == 1 && (l - 1) / 2 == 1)
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

void gen_easy(VECTOR &MAZE, int arr_height, int arr_length)
{
	VECTOR PATH(arr_height, vector <char> (arr_length));
	for (int i = 0; i < arr_height; i++)			
	{
		for (int j = 0; j < arr_length; j++)
		{
			PATH.at(i).at(j) = ' ';
		}
	}
	bool COMPLETE = false;
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
	remove_floaters(MAZE, arr_height, arr_length);
}

void set_start_end(VECTOR &MAZE, int arr_height, int arr_length)
{
	//Set start point
	bool LEFT = false;
	bool RIGHT = false;
	bool TOP = false;
	bool BOTTOM = false;
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
			LEFT = true;
		}
		else										//start at right wall
		{
			start = rand() % (arr_height - 2) + 1;
			if (start % 2 == 0)
			{
				start++;
			}
			MAZE.at(start).at(arr_length - 1) = ' ';
			RIGHT = true;
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
			TOP = true;
		}
		else										//start at bottom wall
		{
			start = rand() % (arr_length - 2) + 1;
			if (start % 2 == 0)
			{
				start++;
			}
			MAZE.at(arr_height - 1).at(start) = ' ';
			BOTTOM = true;
		}
	}
	
	//Set end point on opposite side of start
	int end;
	if (RIGHT)							//end at left wall
	{
		end = rand() % (arr_height - 2) + 1;
		if (end % 2 == 0)
		{
			end++;
		}
		MAZE.at(end).at(0) = ' ';
	}
	else if (LEFT)						//end at right wall
	{
		end = rand() % (arr_height - 2) + 1;
		if (end % 2 == 0)
		{
			end++;
		}
		MAZE.at(end).at(arr_length - 1) = ' ';
	}
	else if (BOTTOM)					//end at top wall
	{
		end = rand() % (arr_length - 2) + 1;
		if (end % 2 == 0)
		{
			end++;
		}
		MAZE.at(0).at(end) = ' ';
	}
	else if (TOP)						//end at bottom wall
	{
		end = rand() % (arr_length - 2) + 1;
		if (end % 2 == 0)
		{
			end++;
		}
		MAZE.at(arr_height - 1).at(end) = ' ';
	}
}

#endif
