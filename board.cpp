/* FILE: board.cpp
 * AUTHOR: Bryant Matt
 * COURSE: CAP4601
 * ASSIGNMENT: PROJECT 1 / ConnectM
 * Description: Holds constructor and drivers for game board
 */


#include "board.hpp"

/*
Game board deconstructor
*/
board::~board()
{
	for (int i = 0; i < n; i++) {
		delete[] boardarr[i];
		
	}
		

	delete[] boardarr;
	delete[] valid;

}

/*
Game board constructor
Dynamically allocated 2d char array and 1d int array with provided n paramater
Fills 2d char array with ' '
inn- the input for n parameter of the board
inm- the input for m parameter of the board
pp- Player piece symbol
cp- computer piece symbol

*/
board::board(int inn, int inm, char pp, char cp)
{
	n = inn;
	m = inm;
	p = pp;
	c = cp;

	valid = new int[n];

	boardarr = new char*[n];

	for (int i = 0; i < n; i++) {
		boardarr[i] = new char[n];
		valid[i] = 0;
	}

	for (int j = 0; j < n; j++) {
		for (int k = 0; k < n; k++) {
			boardarr[j][k] = ' ';
		}
	}

}


/*
printBoard
Prints board for the game using two helper functions
*/
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

/*
printHsplit
printBoard helper function
prints horizontal split between rows
*/
void board::printHsplit()
{
	for (int i = 0; i < n; i++) {
		std::cout << "+---";
	}
	std::cout << "+\n";
}

/*
printDrow
printBoard helper function
prints the horizontal data lines of the board
row- row from 2d char boardarr
*/
void board::printDrow(char* row)
{
	for (int i = 0; i < n; i++) {
		std::cout << "| " << row[i] << " ";
	}
	std::cout << "|\n";
}

/*
getN
Needed for agent's abSearch algorithm
@returns N parameter of board
*/
int board::getN()
{
	return n;
}

/*
isValid
Checks is a col has a valid move left
col- column to check
@return -2 is no more valid moves else return 0
*/
int board::isValid(int col) {
	if (col > n - 1 || col<0 || valid[col]>n - 1) {
		return -1;
	}
	return 0;
}

/*
isWon
Checks if the move causes a win
col- column move was placed in
row- row move was placed in
sym- symbol that was placed during move
@returns true if any win criteria are met, false if not
*/
bool board::isWon(int col, int row, char sym)
{
	int cons = 0;
	//Check horizontal win
	for (int i = 0; i < n; i++) {
		if (boardarr[row][i] == sym) {
			cons++;
			if (cons == m) {
				//std::cout << "HORZ";
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
				//std::cout << "VERT";
				return true;
			}
		}
		else {
			cons = 0;
		}
	}

	//check Diagonal wins
	
	//Find start of positive and negative diagonal
	int SNDcol = col;
	int SNDrow = row;
	int SPDcol = col;
	int SPDrow = row;

	while (SNDcol != 0 && SNDrow < n - 1) {
		SNDcol--;
		SNDrow++;
	}
	while (SPDcol != n - 1 && SPDrow < n - 1) {
		SPDcol++;
		SPDrow++;
	}

	cons = 0;
	
	//Check Positive sloped diagonal win
	while (SPDrow >= 0 && SPDcol>=0) {
		if (boardarr[SPDrow][SPDcol] == sym) {
			cons++;
			if (cons == m) {
				//std::cout << "SPD";
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
	while (SNDrow >= 0 && SNDcol<n) {
		if (boardarr[SNDrow][SNDcol] == sym) {
			cons++;
			if (cons == m) {
				//std::cout << "SND";
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

/*
placePiece
Check validility of placing move in a col, then places it
col- column entity wants to place a piece in
sym- symbol that should be placed
@return -1 if not valid move
		1 if move creats a win
		0 if valid move

*/
int board::placePiece(int col,char sym)
{
	if (col > n-1 || col<0 || valid[col]>n - 1) {
		return -1;
	}


	boardarr[valid[col]][col] = sym;
	valid[col]++;

	bool won = isWon(col, valid[col] - 1,sym);
	if (won) {
		return 1;
	}
	return 0;
}

/*
unplacePiece
Removes placed piece
Needed for Alpa beta pruning
col- column to remove from
sym- symbol to remove (more to tracking than function
*/
void board::unplacePiece(int col, char sym) {
	valid[col]--;
	boardarr[valid[col]][col] = ' ';
}

/*
getBoardScore
Utility function for abSearch
col- column recent move was made to
sym- symbol of recent move

@return score of board
*/
int board::getBoardScore(int col, char sym) {
	int score = 0;

	//Win/ Lose score
	if (isWon(col, valid[col] - 1, p)) {
		score -= 10000;
	}else if (isWon(col, valid[col] - 1, c)) {
		score += 10000;
	}

	if (boardarr[0][n / 2] == c) {
		score += 100;
	}


	int filled = 0;
	int count = 0;

	//Checks for potential win horizonatlly
	count = rowPotential(&filled, col, c);

		//If agent has space to win add score
		if (count >= m) {
			score+=100*filled;
		}
	count = rowPotential(&filled, col, p);

	//If player has space to win add score
	if (count >= m || filled==m-1) {
		score -= 100 * filled;
	}

	filled = 0;
	count = 0;

	//Checks for potential win vertically
	count = colPotential(&filled, col, c);

	if (count >= m) {
		score += 100 * filled;
	}
	count = colPotential(&filled, col, p);

	if (count >= m || filled == m - 1) {
		score -= 100 * filled;
	}

	return score;

}


/*
rowPotential
Checks to left and right of move for empty spaces and spaces with same piece
filled- pointer to hold return value of spaces filled with same pieces
col-column last piece was places
sym-callers symbol
*/
int board::rowPotential(int* filled, int col, char sym) {
	int count = 0;

	int r = valid[col];
	r = r - 1;

	//from col-1 to column 0
	for (int i = col-1; i >= 0; i--) {
		if (boardarr[r][i] == sym || boardarr[r][i] == ' ') {
			if (boardarr[r][i] == ' ') {
				if (valid[i] == r) {
					count++;
				}
			}
			if (boardarr[r][i] == sym) {
				count++;
				*filled = *filled + 1;
			}
		}
		else {
			i = -1;
		}
	}
	//from col+1 to column n
	for (int i = col + 1; i < n; i++) {
		if (boardarr[r][i] == sym || boardarr[r][i] == ' ') {
			if (boardarr[r][i] == ' ') {
				if (valid[i] == r) {
					count++;
				}
			}
			if (boardarr[r][i] == sym) {
				count++;
				*filled = *filled + 1;
			}
		}
		else {
			i = n;
		}
	}

	return count;
}

/*
colPotential
Checks to up and down of move for empty spaces and spaces with same piece
filled- pointer to hold return value of spaces filled with same pieces
col-column last piece was places
sym-callers symbol
*/
int board::colPotential(int* filled, int col, char sym) {
	int count = 0;

	int r = valid[col];
	//get row below last move
	r = r - 2;

	for (int i = r; i >= 0; i--) {
		if (boardarr[i][col] == sym || boardarr[i][col] == ' ') {
			count++;
			if (boardarr[i][col] == sym) {
				*filled = *filled + 1;
			}
		}
		else {
			i = 0;
		}
	}
	//from col to column n
	for (int i = r + 2; i < n; i++) {
		if (boardarr[i][col] == sym || boardarr[i][col] == ' ') {
			count++;
			if (boardarr[i][col] == sym) {
				*filled = *filled + 1;
			}
		}
		else {
			i = n;
		}
	}

	return count;
}









