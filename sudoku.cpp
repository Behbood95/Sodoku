#include "sudoku.h"
#include "stdafx.h"

using namespace std;
string const NOSUCHFILE = "No such file: ";
string const OUTFILE = "sudoku.txt";
int const SQRTSIZE = int(sqrt(GRIDSIZE));

Sudoku::Sudoku(int n)
{
	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
		{
			grid[i][j] = UNKNOWN;
		}
	}
	grid[0][0] = FLAGNUM;
	this->n = n;
	output.open(OUTFILE);
	for (int i = 0; i < GRIDSIZE * GRIDSIZE; i++)
	{
		if ((i + 1) % 9 == 0)
		{
			buff[2 * i + 1] = '\n';
			continue;
		}
		buff[2 * i + 1] = ' ';
	}
	buff[162] = '\n';
}

int Sudoku::SudokuGenerate(int pos, long& count, bool solve)
{
	if (pos == GRIDSIZE * GRIDSIZE)
	{
		PrintSudoku();
		count++;
		if (count == n)
		{
			return 1;
		}
	}
	else
	{
		int x = pos / GRIDSIZE;
		int y = pos % GRIDSIZE;
		if (grid[x][y] == UNKNOWN)
		{
			int base = x / 3 * 3;
			for (int i = 0; i < GRIDSIZE; i++)         // try to fill the pos from 1-9
			{
				grid[x][y] = (i + base) % GRIDSIZE + 1 + '0';
				if (IsValid(pos, solve))               // if the number is valid
				{
					if (SudokuGenerate(pos + 1, count, solve) == 1)       // try to fill next pos
					{
						return 1;
					}
				}
				grid[x][y] = UNKNOWN;
			}
		}
		else
		{
			if (SudokuGenerate(pos + 1, count, solve) == 1)
			{
				return 1;
			}
		}
	}
	return 0;
}

int Sudoku::SudokuSolve(char* path)
{
	ifstream input;
	input.open(path);
	if (input)
	{
		int total = 0;
		string temp[GRIDSIZE];
		string str;
		int line = 0;
		bool exc = false;     // wrong input such as 'a','.',etc. in the input file
		while (total < 1000000 && getline(input, str))
		{
			temp[line] = str;
			line++;
			if (line == GRIDSIZE)
			{
				for (int i = 0; i < GRIDSIZE; i++)
				{
					for (int j = 0; j < GRIDSIZE; j++)
					{
						grid[i][j] = temp[i][2 * j];
						if(grid[i][j] < '0' || grid[i][j] > '9')
						{ 
							exc = true;
							break;
						}
					}
				}
				getline(input, str);
				line = 0;
				if (exc)
				{
					exc = false;
					continue;
				}
				total++;
				// solve sudoku
				long count = 0;
				SudokuGenerate(0, count, true);
			}
		}
		//cout << total << endl;
	}
	else
	{
		cout << NOSUCHFILE << string(path) << endl;
		return 0;
	}
	return 1;
}

bool Sudoku::IsValid(int pos, bool solve)
{
	int x = pos / GRIDSIZE;
	int y = pos % GRIDSIZE;
	int z = x / SQRTSIZE * SQRTSIZE + y / SQRTSIZE;
	int leftTop = z / SQRTSIZE * GRIDSIZE * SQRTSIZE + (z % SQRTSIZE) * SQRTSIZE;
	int rightDown = leftTop + (2 * GRIDSIZE + SQRTSIZE - 1);
	int bound = solve ? GRIDSIZE : y;
	// check row
	for (int i = 0; i < bound; i++)
	{
		if (i == y)
		{
			continue;
		}
		if (grid[x][i] == grid[x][y])
		{
			return false;
		}
	}
	// check column
	bound = solve ? GRIDSIZE : x;
	for (int i = 0; i < bound; i++)
	{
		if (i == x)
		{
			continue;
		}
		if (grid[i][y] == grid[x][y])
		{
			return false;
		}
	}	
	// check box
	int bound_x = leftTop / GRIDSIZE;
	int bound_y = leftTop % GRIDSIZE;
	if (bound_x % 3 != 0 || bound_y % 3 != 0 || bound_x > GRIDSIZE -3 || bound_y > GRIDSIZE - 3)
	{
		cout << "error" << endl;
		exit(0);
	}
	for (int i = bound_x; i < (bound_x + 3); i++)
	{
		for (int j = bound_y; j < (bound_y + 3); j++)
		{
			if (i == x && j == y)
			{
				if (solve)
				{
					continue;
				}
				else
				{
					return true;
				}
			}
			if (grid[i][j] == grid[x][y])
			{
				return false;
			}
		}
	}
	return true;
}

void Sudoku::PrintSudoku()
{
	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
		{
			buff[18 * i + 2 * j] = grid[i][j];
		}
	}
	output << buff;
}