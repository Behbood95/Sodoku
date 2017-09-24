// SudokuProject.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

string const OUTFILE = "sudoku.txt";
string const USAGE = "USAGE: sudoku.exe -c N(1 <= N <= 100,0000)\n       sudoku.exe -s absolute_path_of_puzzlefile";
string const NOSUCHFILE = "No such file: ";
int const FLAGNUM = 4;  //student ID: 15061075
int const GRIDSIZE = 9;
int const UNKNOWN = 0;
int const SQRTSIZE = int(sqrt(GRIDSIZE));
int grid[GRIDSIZE][GRIDSIZE];
//string const space = " ";

void PrintUsage() 
{
	cout << USAGE << endl;
}

void PrintSudoku(ofstream &output)
{
	for (int i = 0; i < GRIDSIZE; i++)
	{
		//string line = "";
		//char temp[1];
		for (int j = 0; j < GRIDSIZE; j++)
		{
			output << grid[i][j];
			//temp[0] = '0' + grid[i][j];
			//line = line + string(temp);
			if (j == GRIDSIZE - 1)
			{
				output << endl;
			}
			else
			{
				output << " ";
			}
			//line = line + space;
		}
	}
}

bool IsValid(int pos)
{
	int x = pos / GRIDSIZE;
	int y = pos % GRIDSIZE;
	int z = x / SQRTSIZE * SQRTSIZE + y / SQRTSIZE;
	int leftTop = z / SQRTSIZE * GRIDSIZE * SQRTSIZE + (z % SQRTSIZE) * SQRTSIZE;
	int rightDown = leftTop + (2 * GRIDSIZE + SQRTSIZE - 1);
	// check row
	for (int i = 0; i < y; i++)
	{
		if (grid[x][i] == grid[x][y])
		{
			return false;
		}
	}
	// check column
	for (int i = 0; i < x; i++)
	{
		if (grid[i][y] == grid[x][y])
		{
			return false;
		}
	}
	// check box
	for (int i = leftTop / GRIDSIZE; i < (leftTop / GRIDSIZE + 3); i++)
	{
		for (int j = leftTop % GRIDSIZE; j < (leftTop % GRIDSIZE + 3); j++)
		{
			if (i == x && j == y)
			{
				continue;
			}
			if (grid[i][j] == grid[x][y])
			{
				return false;
			}
		}
	}
	return true;
}

int SudokuGenerate(ofstream& output, long n, int pos, long& count) 
{
	if (pos == GRIDSIZE * GRIDSIZE)
	{
		PrintSudoku(output);
		count++;
		if (count == n)
		{
			return 1;
		}
		output << endl;
	}
	else
	{
		int x = pos / GRIDSIZE;
		int y = pos % GRIDSIZE;
		if (grid[x][y] == UNKNOWN)
		{
			for (int i = 0; i < GRIDSIZE; i++)
			{
				grid[x][y] = i + 1;
				if (IsValid(pos))
				{
					if (SudokuGenerate(output, n, pos + 1, count) == 1)
					{
						return 1;
					}
				}
				grid[x][y] = UNKNOWN;
			}
		}
		else
		{
			if (SudokuGenerate(output, n, pos + 1, count) == 1)
			{
				return 1;
			}
		}
	}
	return 0;
}

void SudokuSolve(char* path, ofstream& output)
{
	ifstream input;
	input.open(path);
	if (input)
	{
		int total = 0;
		while (total < 1000000)
		{
			// init grid
			for (int i = 0; i < GRIDSIZE; i++)
			{
				for (int j = 0; j < GRIDSIZE; j++)
				{
					if (!(input >> grid[i][j]))
					{
						return;
					}
				}
			}
			total++;
			// solve sudoku
			long count = 0;
			SudokuGenerate(output, 1, 0, count);
		}
	}
	else
	{
		cout << NOSUCHFILE << string(path) << endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		// -c
		if (argv[1][0] == '-' && argv[1][1] == 'c') 
		{
			long n = 0;
			for (unsigned i = 0; i < string(argv[2]).length(); i++)
			{
				if (argv[2][i] < '0' || argv[2][i] > '9')
				{
					PrintUsage();
					return 0;
				}
				n = n * 10 + argv[2][i] - '0';
			}
			// wrong patameter
			if (n < 1 || n > 1000000) {
				PrintUsage();
				return 0;
			}
			else
			{
				ofstream output;
				output.open(OUTFILE);
				long count = 0;
				grid[0][0] = FLAGNUM;  // init FLAGNUM
				SudokuGenerate(output, n, 1, count);  // backtracking algorithm
			}
		}
		// -s
		else if (argv[1][0] == '-' && argv[1][1] == 's') 
		{
			ofstream output;
			output.open(OUTFILE);
			SudokuSolve(argv[2], output);
		}
		// wrong parameter
		else 
		{
			PrintUsage();
		}
	}
	// wrong patameter
	else
	{
		PrintUsage();
	}
    return 0;
}

