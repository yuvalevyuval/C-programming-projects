#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "test_data.h"

// Q1
void mathStringCalc(const char mathString[]){
	//we feed a new array to a number then arithmetic action, numbers are positive, arithmetic actions are -1 -> -4.
	double current = 0.0;
	int i = 0, j = 0, x = 0;
	int CalcString[100] = { 0 };
	while ((i < 101)&&(mathString[i] != '\0')) {
		if (mathString[i] == ' ') {
			j++;
			i++;
		}
		else if (mathString[i] == '+') {
			CalcString[j] = -1;
			i++;
		}
		else if (mathString[i] == '-') {
			CalcString[j] = -2;
			i++;
		}
		else if (mathString[i] == '*') {
			CalcString[j] = -3;
			i++;
		}
		else if (mathString[i] == '/') {
			CalcString[j] = -4;
			i++;
		}
		// if wer'e not on a (+ - * /) or a (' ') we must have a number here.
		//so we feed the new array using string to int algorithm.
		else{
			int res = 0;
			while ((mathString[i] != ' ') && (mathString[i] != '\0')) {
				res = res * 10 + (mathString[i]- '0');
				++i;
			}
			CalcString[j] = res;
		}
	}
	//now we have an array, we calculate res by running on the array cell by cell.
	current = CalcString[0];
	while ((x < 101) && (CalcString[x] != '\0')) {
		if ((CalcString[x] != -1) && (CalcString[x] != -2) && (CalcString[x] != -3) && (CalcString[x] != -4)) {
			x++;
		}
		else if (CalcString[x] == -1) {
			current = current + CalcString[x + 1];
			x++;
		}
		else if (CalcString[x] == -2) {
			current = current - CalcString[x + 1];
			x++;
		}
		else if (CalcString[x] == -3) {
			current = current * CalcString[x + 1];
			x++;
		}
		else if (CalcString[x] == -4) {
			current = current / CalcString[x + 1];
			x++;
		}

	}
	printf("%s = %.3lf\n", mathString, current);
}

// Q2
void isPalindrome(char str[], int i, int n) {
	//base case.
	if (i == n / 2) {
		printf("\"%s\" -> True\n", str);
	}
	//reduction step.
	else if (str[i] == str[n - i - 1]) {
		isPalindrome(str, i + 1, n);
	}
	//stoping case.
	else {
		printf("\"%s\" -> False\n", str);
	}
}

// Q3

void printSudoku(int sudoku[][N]) {
	int row = 0, col = 0;
	printf("----------------------\n");
	for (row = 0; row < N; row++) {
		printf("|");
		for (col = 0; col < N; col++) {
			printf("%2d", sudoku[row][col]);
			if (col % 3 == 2) printf("|");
		}
		printf(" \n");
		if (row % 3 == 2) printf("----------------------\n");
	}
	return;
}
// Q3 - main

int Test_Puzzle_Fin(int sudoku[][N]) {
	//making shure we are not beyond the 9X9 puzzle.
	int row = 0, col = 0;
	for (row = 0; row < 9; row++) {
		for (col = 0; col < 9; col++) {
			if (sudoku[row][col] == 0)
				return 0;
		}
	}
	return 1;
}

int Square_Me(int num) {
	int k = num;
	k = k / 3;
	k = k * 3;
	return k;
}

int Test_Square_Validness(int sudoku[][N], int row, int col, int i) {
	//making shure we are putting a legit number in the corresponding square. 
	int C = Square_Me(col), R = Square_Me(row);
	row = R;
	col = C;
	while (row < R + 3) {
		while (col < C + 3) {
			if (sudoku[row][col] == i) {
				return 0;
			}
			col++;
		}
		col = col - 3;
		row++;
	}
	return 1;
}

int Test_Cell(int sudoku[][N], int row, int col, int i) {
	//making shure the cell is a valid input.
	int index = 0;
	if (Test_Square_Validness(sudoku, row, col, i) == 0)
		return 0;
	for (index = 0; index < 9; index++) {
		if (sudoku[row][index] == i)
			return 0;
	}
	for (index = 0; index < 9; index++) {
		if (sudoku[index][col] == i)
			return 0;
	}
	return 1;
}

int Test_Singularity(int sudoku[][N], int row, int col, int i) {
	//by definition, thw sudoku is a easy sudoku, so we must have 1 and only 1 solution
	//if the solution we got is a single solution, then it must be THE soulution.
	int n = 1;
	for (n = 1; n < 10; n++) {
		if (n == i)
			continue;
		if (Test_Cell(sudoku, row, col, n) == 1)
			return;
	}
	sudoku[row][col] = i; //now we set the i value to this place, cuz it is the only possible solution.
	return;
}

void solveSudoku(int sudoku[][N])
{
	int row = 0, col = 0, i = 0;
	//***int check = 0;
	while (Test_Puzzle_Fin(sudoku) == 0) {
		for (row = 0; row < 9; row++) {
			for (col = 0; col < 9; col++) {
				if (sudoku[row][col] != 0)
					continue;
				for (i = 1; i < 10; i++) {
					//***check = TestCell(sudoku, row, col, i);
					if (Test_Cell(sudoku, row, col, i)) {
						Test_Singularity(sudoku, row, col, i);
						break;
					}
				}
			}
		}
	}
	printSudoku(sudoku);
	return;
}



// exercise 3
int main()
{
	int opt = 0, i;

	printf("Hello. Please choose a question by entering 1-3:\n");
	scanf("%d", &opt);

	while (opt < 1 || opt > 3) {
		printf("Invalid number was entered. Please choose again 1-3:\n");
		scanf("%d", &opt);
	}

	switch (opt) {
	case 1:
		mathStringCalc(mathString1);
		mathStringCalc(mathString2);
		mathStringCalc(mathString3);
		mathStringCalc(mathString4);
		break;
	case 2:
		for (i = 0; i < 6; i++)
			isPalindrome(strings[i], 0, len[i]);
		break;
	case 3:
		printf("Sudoku 1 solution:\n");
		solveSudoku(sudoku1);
		printf("\nSudoku 2 solution:\n");
		solveSudoku(sudoku2);
		break;
	default:
		printf("We should not get here!\n");
	}

	return 0;
}
