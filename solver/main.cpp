#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct node {
	int i; 
	int j;
	int uc;
	double hc; 
	double tc;
	node *p;
	node *c1;
	node *c2;
	node *c3;
	node *c4;

	node()
	{
		i = 1;
		j = 1;
		uc = 0;
		hc = 0;
		tc = 0;
		p = NULL;
		c1 = NULL;
		c2 = NULL;
		c3 = NULL;
		c4 = NULL;
	}
	node(int a, int b)
	{
		node();
		i = a;
		j = b;
	}
	node(const node &x)
	{
		i = x.i;
		j = x.j;
		uc = x.uc;
		hc = x.hc;
		tc = x.tc;
		p = x.p;
		c1 = x.c1;
		c2 = x.c2;
		c3 = x.c3;
		c4 = x.c4;
	}
	void operator=(const node &x)
	{
		i = x.i;
		j = x.j;
		uc = x.uc;
		hc = x.hc;
		tc = x.tc;
		p = x.p;
		c1 = x.c1;
		c2 = x.c2;
		c3 = x.c3;
		c4 = x.c4;
	}
	void print()
	{
		cout << "(" << i << ", " << j << ")" << endl; 
	}
};

struct compare  {  
	bool operator()(const node& l,const node& r)  
	{  
		return l.tc > r.tc;  
	}  
};

vector <node> VISITED;
priority_queue <node, vector<node>, compare> SEARCH;

void find_start(vector <vector <char> > MAZE, node &start)
{
	for (int i = 0; i < MAZE.size(); i++)
	{
		if (MAZE.at(i).at(0) == ' ')
		{
			start.i = i;
			start.j = 0;
			return;
		}
	}
	for (int j = 0; j < MAZE.at(0).size(); j++)
	{
		if (MAZE.at(0).at(j) == ' ')
		{
			start.i = 0;
			start.j = j;
			return;
		}
	}
}

void find_end(vector < vector <char> > MAZE, node &end)
{
	for (int i = 0; i < MAZE.size(); i++)
	{
		if (MAZE.at(i).at(MAZE.at(i).size() - 1) == ' ')
		{
			end.i = i;
			end.j = MAZE.at(0).size() - 1;
			return;
		}
	}
	for (int j = 0; j < MAZE.at(0).size(); j++)
	{
		if (MAZE.at(MAZE.size() - 1).at(j) == ' ')
		{
			end.i = MAZE.size() - 1;
			end.j = j;
			return;
		}
	}
}

bool already_visited(node n)
{
	for (int i = 0; i < VISITED.size(); i++)
	{
		if (VISITED.at(i).i == n.i && VISITED.at(i).j == n.j)
		{
			return true;
		}
	}
	return false;
}

double heuristic(node n, node end)
{
	int x = n.i - end.i;
	if (x < 0)
		x *= -1;
	int y = n.j - end.j;
	if (y < 0)
		y *= -1;
	return x + y;
}

void print(vector < vector <char> > MAZE, node n)
{
	node curr = n;
	stack <node> TO_PRINT;
	TO_PRINT.push(curr);
	while (curr.p != NULL)
	{
		curr = *curr.p;
		TO_PRINT.push(curr);
	}
	while (!TO_PRINT.empty())
	{
		int a = TO_PRINT.top().i;
		int b = TO_PRINT.top().j;
		MAZE.at(a).at(b) = 'x';
		TO_PRINT.pop();
	}
	for (int i = 0; i < MAZE.size(); i++)
	{
		for (int j = 0; j < MAZE.at(i).size(); j++)
		{
			cout << MAZE.at(i).at(j);
		}
		cout << endl;
	}
}

void search(vector < vector <char> > &MAZE, node start, node end)
{
	SEARCH.push(start);
	
	while (!SEARCH.empty())
	{
		node *curr = new node(SEARCH.top());
		if (curr->i == end.i && curr->j == end.j)
		{
			print(MAZE, SEARCH.top());
			return;
		}
		SEARCH.pop();
		VISITED.push_back(*curr);

		node *n1 = new node(curr->i + 1, curr->j);		//up
		node *n2 = new node(curr->i - 1, curr->j);		//down
		node *n3 = new node(curr->i, curr->j + 1);		//right
		node *n4 = new node(curr->i, curr->j - 1);		//left

		n1->uc = curr->uc + 1;
		n2->uc = curr->uc + 1;
		n3->uc = curr->uc + 1;
		n4->uc = curr->uc + 1;
		n1->hc = heuristic(*n1, end);
		n2->hc = heuristic(*n2, end);
		n3->hc = heuristic(*n3, end);
		n4->hc = heuristic(*n4, end);
		n1->tc = n1->uc + n1->hc;
		n2->tc = n2->uc + n2->hc;
		n3->tc = n3->uc + n3->hc;
		n4->tc = n4->uc + n4->hc;

		if (n1->i < MAZE.size()) 
		{	
			if (MAZE.at(n1->i).at(n1->j) == ' ' && !already_visited(*n1))
			{
				curr->c1 = n1;
				n1->p = curr;
				SEARCH.push(*n1);
			}
		}
		if (n2->i > -1)
		{	
			if (MAZE.at(n2->i).at(n2->j) == ' ' && !already_visited(*n2))
			{
				curr->c2 = n2;
				n2->p = curr;
				SEARCH.push(*n2);
			}
		}
		if (n3->j < MAZE.at(0).size())
		{	
			if (MAZE.at(n3->i).at(n3->j) == ' ' && !already_visited(*n3))
			{
				curr->c3 = n3;
				n3->p = curr;
				SEARCH.push(*n3);
			}
		}
		if (n4->j > -1)
		{	
			if (MAZE.at(n4->i).at(n4->j) == ' ' && !already_visited(*n4))
			{
				curr->c4 = n4;
				n4->p = curr;
				SEARCH.push(*n4);
			}
		}
	}
	cout << "NO SOLUTION" << endl;
	for (int i = 0; i < VISITED.size(); i++)
	{
		int a = VISITED.at(i).i;
		int b = VISITED.at(i).j;
		MAZE.at(a).at(b) = 'x';
	}
	for (int i = 0; i < MAZE.size(); i++)
	{
		for (int j = 0; j < MAZE.at(i).size(); j++)
		{
			cout << MAZE.at(i).at(j);
		}
		cout << endl;
	}
}

int main(int argc, char *argv[])
{
	string filename;
	if (argc == 2)
	{
		filename = argv[1];
	}
	if (argc == 1)
	{
		cout << "Enter the file name: " << endl;
		cin >> filename;
	}

	string line;
	vector < vector <char> > MAZE;
	ifstream file(filename.c_str());
	if (file.is_open())
	{
		while (getline(file, line))
		{
			vector <char> lineData;
			stringstream lineStream(line);

			char value;
			while (lineStream >> noskipws >> value)
			{
				lineData.push_back(value);
			}
			MAZE.push_back(lineData);
		}
		file.close();
	}
	else
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	node start;
	node end;
	
	find_start(MAZE, start);
	find_end(MAZE, end);

	search(MAZE, start, end);

	return 0;
}
