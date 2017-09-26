#pragma once
#include <fstream>
#include <string>

extern int const GRIDSIZE = 9;
extern char const UNKNOWN = '0';
extern char const FLAGNUM = '4';  //student ID: 15061075

class Sudoku
{
public:
	Sudoku(int n);
	int SudokuGenerate(int pos, long& count, bool solve);  // solve = true <==> solve sudoku puzzle
	int SudokuSolve(char* path);
private:
	char grid[GRIDSIZE][GRIDSIZE];
	int n;
	std::ofstream output;
	char buff[163];
	bool IsValid(int pos, bool solve);
	void PrintSudoku();
};