#include <iostream>
using namespace std;

unsigned int LENGTH = 1;
unsigned int HEIGHT = 1;

int main(int argc, char* argv[])
{
	if (argc > 1 && argc < 4)
	{
		if (argc == 2)
		{
			cout << "Missing height arg" << endl;
			return 1;
		}
		else
		{
			char l = *argv[1];
			char h = *argv[2];
			if (l - '0' <= 0)
			{
				cout << "Invalid length" << endl;
				return 1;
			}
			LENGTH = l - '0';
			if (h - '0' <= 0)
			{
				cout << "Invalid height" << endl;
				return 1;
			}
			HEIGHT = h - '0';
		}
	}
	if (argc > 3)
	{
		cout << "Too many arguments" << endl;
		return 1;
	}
	if (argc == 1)
	{
		cout << "Enter the length of the maze." << endl;
		int l = 0;
		while (l <= 0)
		{
			cin >> l;
		}
		cout << "Enter the height of the maze." << endl;
		int h = 0;
		while (h <= 0)
		{
			cin >> h;
		}
		LENGTH = l;
		HEIGHT = h;
	}
	return 0;
}
