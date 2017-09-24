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
		for (int j = 0; j <= GRIDSIZE; j++)
		{
			grid[i][j] = UNKNOWN;
		}
	}
	grid[0][0] = FLAGNUM;
	this->n = n;
	output.open(OUTFILE);
}

int Sudoku::SudokuGenerate(int pos, long& count)
{
	if (pos == GRIDSIZE * GRIDSIZE)
	{
		PrintSudoku();
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
			//int base = x / 3 * 3;
			for (int i = 0; i < GRIDSIZE; i++)
			{
				grid[x][y] = i + 1;
				if (IsValid(pos))
				{
					if (SudokuGenerate(pos + 1, count) == 1)
					{
						return 1;
					}
				}
				grid[x][y] = UNKNOWN;
			}
		}
		else
		{
			if (SudokuGenerate(pos + 1, count) == 1)
			{
				return 1;
			}
		}
	}
	return 0;
}

void Sudoku::SudokuSolve(char* path)
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
			if (total != 0)
			{
				output << endl;
			}
			total++;
			// solve sudoku
			long count = 0;
			SudokuGenerate(0, count);
		}
	}
	else
	{
		cout << NOSUCHFILE << string(path) << endl;
	}
}

bool Sudoku::IsValid(int pos)
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
				return true;
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
	char temp[163];
	for (int i = 0; i < GRIDSIZE * GRIDSIZE; i++)
	{
		temp[2 * i + 1] = ' ';
	}
	temp[162] = '\0';
	for (int i = 0; i < GRIDSIZE; i++)
	{
		//char temp[162];
		for (int j = 0; j < GRIDSIZE; j++)
		{
			temp[18 * i + 2 * j] = grid[i][j] + '0';
			//output << grid[i][j];
			if (j == GRIDSIZE - 1)
			{
				//output << endl;
				temp[18 * i + 2 * j + 1] = '\n';
			}
			/*else
			{
				temp[18 * i + 2 * j + 1] = ' ';
				//output << " ";
			}*/
		}
	}
	output << string(temp);
}