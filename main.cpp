// Sudoku.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

string const USAGE = "USAGE: sudoku.exe -c N(1 <= N <= 100,0000)\n       sudoku.exe -s absolute_path_of_puzzlefile";

void PrintUsage()
{
	cout << USAGE << endl;
}

int main(int argc, char* argv[])
{
	//clock_t start, finish;
	//start = clock();
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
				Sudoku su(n);
				long count = 0;
				su.SudokuGenerate(1, count, false);
			}
		}
		// -s
		else if (argv[1][0] == '-' && argv[1][1] == 's')
		{
			Sudoku su(1);
			su.SudokuSolve(argv[2]);
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
	//finish = clock();
	//cout << finish - start << "/" << CLOCKS_PER_SEC << " (s) " << endl;
    return 0;
}

