#include "board.hpp"
#include <stdlib.h>
#include <iostream>
#include <string>

board::~board()
{
}

board::board(int inn, int inm)
{
	n = inn;
	m = inm;

	valid = (int*)malloc(n * sizeof(int));

	boardarr = (char**)malloc(n * sizeof(char*));

	for (int i = 0; i < n; i++) {
		boardarr[i] = (char*)malloc(n * sizeof(char));
		valid[i] = 0;
	}

	for (int j = 0; j < n; j++) {
		for (int k = 0; k < n; k++) {
			boardarr[j][k] = ' ';
		}
	}

}

void board::printBoard()
{
	for (int i = 0; i < n; i++) {
		std::cout << "  " << i << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < n; i++) {
		printHsplit();
		printDrow(boardarr[n - (i + 1)]);
	}
	printHsplit();
}

int board::placePiece(int col,char sym)
{
	if (col > n-1 || col<0 || valid[col]>n - 1) {
		return -1;
	}


	boardarr[valid[col]][col] = sym;
	valid[col]++;

	bool won = isWon(col, valid[col] - 1,sym);
	if (won) {
		std::cout << sym << " WON!!!\n";
		return 1;
	}
	return 0;
}

int board::getN()
{
	return n;
}

void board::printHsplit()
{
	for (int i = 0; i < n; i++) {
		std::cout << "+---";
	}
	std::cout << "+\n";
}

void board::printDrow(char* row)
{
	for (int i = 0; i < n; i++) {
		std::cout << "| " << row[i] << " ";
	}
	std::cout << "|\n";
}

bool board::isWon(int col, int row,char sym)
{
	int cons=0;
	//Check horizontal win
	for (int i = 0; i < n; i++) {
		if (boardarr[row][i] == sym) {
			cons++;
			if (cons == m) {
				std::cout << "HORZ";
				return true;
			}
		}
		else {
			cons = 0;
		}
	}

	cons = 0;
	//Check Vertical win
	for (int i = 0; i < n; i++) {
		if (boardarr[i][col] == sym) {
			cons++;
			if (cons == m) {
				std::cout << "VERT";
				return true;
			}
		}
		else {
			cons = 0;
		}
	}

	//check Diagonal wins

	//Find start of positive and negative diagonal
	int SNDcol=col;
	int SNDrow=row;
	int SPDcol=col;
	int SPDrow=row;

	while (SNDcol !=0 && SNDrow<9){
		SNDcol--;
		SNDrow++;
	}
	while (SPDcol != 9 && SPDrow<9) {
		SPDcol++;
		SPDrow++;
	}

std::cout << "Start of Negative diagonal:" << SNDcol << "," << SNDrow << "\n";
std::cout << "Start of Positive diagonal:" << SPDcol << "," << SPDrow << "\n";

cons = 0;

//Check Positive sloped diagonal win
while (SPDrow >= 0) {
	if (boardarr[SPDrow][SPDcol] == sym) {
		cons++;
			if (cons == m) {
				std::cout << "SPD";
				return true;
			}
		}
	else {
		cons = 0;
	}
	SPDrow--;
	SPDcol--;
}
cons = 0;
//Check negative sloped diagonal win
while (SNDrow >= 0) {
	if (boardarr[SNDrow][SNDcol] == sym) {
		cons++;
		if (cons == m) {
			std::cout << "SND";
			return true;
		}
	}
	else {
		cons = 0;
	}
	SNDrow--;
	SNDcol++;
}



	return false;
}
