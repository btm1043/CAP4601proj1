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

board::board(int inn, int inm, char** b, int* v) {
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

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			boardarr[i][j] = b[i][j];
		}
	}

	for (int k = 0; k < n; k++) {
		valid[k] = v[k];
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

char** board::getBoardarr()
{
	return boardarr;
}

int* board::getValid()
{
	return valid;
}

int board::getM()
{
	return m;
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

int board::getBoardScore(int col,char sym) {
	int score = 0;
	int count = 0;
	int emptcount = 0;
	int best = 0;

	//Preference for center column
	if (col == n / 2) {
		score += 5;
	}


	//Score Rows

	//row to check
	int r = valid[col];
	r = r - 1;

	//from col to column 0
	for (int i = col; i > 0; i--) {
		if (boardarr[r][i] == sym) {
			count++;
		}
		else if(boardarr[r][i]==' ') {
			emptcount++;
		}
		else {
			i = 0;
		}
	}
	//from col to column n
	for (int i = col + 1; i < n; i++) {
		if (boardarr[r][i] == sym) {
			count++;
		}
		else if (boardarr[r][i] == ' ') {
			emptcount++;
		}
		else {
			i = n;
		}
	}
	if (count + emptcount >= m && (boardarr[r][col-1]==sym || boardarr[r][col+1]==sym)) {
		score += count;
	}
	else {
		score += (-100);
	}
	if (count == m) {
		score += 1000;
	}


	//Score Columns
	//for (int i = 0; i < n; i++) {
	//	//Loop through row elements
	//	for (int j = 0; j < n; j++) {
	//		if (boardarr[j][i] == sym) {
	//			count++;

	//		}
	//		else {
	//			if (count > best) {
	//				best = count;
	//			}
	//			count = 0;
	//		}
	//	}
	//	if (best < m - 1) {
	//		score += best * 10;
	//	}
	//	else {
	//		score += 1000;
	//	}
	//	best = 0;
	//	count = 0;
	//}
	return score;
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


void board::unplacePiece(int col, char sym) {
	valid[col]--;
	boardarr[valid[col]][col] = ' ';
	
}

void board::setBoardarr(char** b) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			boardarr[i][j] = b[i][j];
		}
	}

	
}
void board::setValid(int* v) {
	for (int k = 0; k < n; k++) {
		valid[k] = v[k];
	}
}
