#ifndef HARD_H
#define HARD_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stack>
#include "operators.h"
#include "aesthetics.h"
using namespace std;

struct node{
	int i;
	int j;
	
	node()
	{
		i = 1;
		j = 1;
	}
	node(int a, int b)
	{
		i = a;
		j = b;
	}
	node(const node &x)
	{
		i = x.i;
		j = x.j;
	}
	bool operator==(const node &x)
	{
		if (i == x.i && j == x.j)
			return true;
		return false;
	}
};

vector <node> VISITED;

bool is_visited(node x)
{
	for (int i = 0; i < VISITED.size(); i++)
	{
		if (VISITED.at(i) == x)
		{
			return true;
		}
	}
	return false;
}

void gen_hard(VECTOR &MAZE, int arr_height, int arr_length)
{
	stack <node> PATH;
	vector <char> choices;
	bool COMPLETE = false;
	int i = 1; 
	int j = 1;
	node root(i, j);
	PATH.push(root);
	VISITED.push_back(root);
	while(!COMPLETE)
	{
		node curr(PATH.top());

		//i = curr.i;
		//j = curr.j;
		//cout << "I = " << i << "  J = " << j << endl;
		
		node n1(i - 2, j);
		node n2(i + 2, j);
		node n3(i, j - 2);
		node n4(i, j + 2);
		//print(MAZE, arr_height, arr_length);
		if (i - 2 > 0 && MAZE.at(i - 1).at(j) != ' ' && !is_visited(n1))
		{
			choices.push_back('u');
		}
		if (i + 2 < arr_height - 1 && MAZE.at(i + 1).at(j) != ' ' && !is_visited(n2))
		{
			choices.push_back('d');
		}
		if (j - 2 > 0 && MAZE.at(i).at(j - 1) != ' ' && !is_visited(n3))
		{	
			choices.push_back('l');
		}
		if (j + 2 < arr_length - 1 && MAZE.at(i).at(j + 1) != ' ' && !is_visited(n4))
		{	
			choices.push_back('r');
		}

		if (choices.size() > 0)
		{
			bool moved = false;
			//cout << "Size = " << choices.size() << endl;
			//for (int q = 0; q < choices.size(); q++)
			//{
			//	cout << q << choices.at(q);
			//}
			//cout << endl;
			while (!moved)
			{
				int x = rand() % choices.size();
				
				//cout << "X = " << x << endl;
				if (choices.at(x) == 'u')
				{
					go_up(MAZE, arr_height, i, j);
					PATH.push(n1);
					VISITED.push_back(n1);
					moved = true;
					//cout << "U" << endl;
				}
				else if (choices.at(x) == 'd')
				{
					go_down(MAZE, arr_height, i, j);
					PATH.push(n2);
					VISITED.push_back(n2);
					moved = true;
					//cout << "D" << endl;
				}
				else if (choices.at(x) == 'l')
				{
					go_left(MAZE, arr_length, i, j);
					PATH.push(n3);
					VISITED.push_back(n3);
					moved = true;
					//cout << "L" << endl;
				}
				else if (choices.at(x) == 'r')
				{
					go_right(MAZE, arr_length, i, j);
					PATH.push(n4);
					VISITED.push_back(n4);
					moved = true;
					//cout << "R" << endl;
				}
			}
		}
		else
		{
			PATH.pop();
			if(!PATH.empty())
			{
				i = PATH.top().i;
				j = PATH.top().j;
				//cout << "Going to " << i << ", " << j << endl;
			}
		}
		choices.clear();
		//print(MAZE, arr_height, arr_length);
		if(PATH.empty())
		{
			COMPLETE = true;
		}
	}
}

#endif
