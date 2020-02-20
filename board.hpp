#include <cstddef>
#pragma once
/* FILE: board.hpp
 * AUTHOR: Bryant Matt
 * COURSE: CAPT
 * ASSIGNMENT: PROJECT 1 / ConnectM
 */
#ifndef BOARD_HPP
#define BOARD_HPP

class board {
private:
	//Double char pointer to house dynamic board array
	char** boardarr;

	//Int pointer to house dynamic int array of valid moves
	int* valid;

	//grid size param
	int n;

	//win size
	int m;

	void printHsplit();
	void printDrow(char* row);
	bool isWon(int col, int row,char sym);

public:
	~board();


	board(int n, int m);
	board(int n, int m, char** b, int* v);

	void printBoard();

	char** getBoardarr();
	int* getValid();
	int getM();
	int getN();

	void setBoardarr(char** b);
	void setValid(int* v);
	
	int placePiece(int col,char sym);
	void unplacePiece(int col, char sym);
	int getBoardScore(int col,char sym);
	


};

#endif