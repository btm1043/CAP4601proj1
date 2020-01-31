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

	void printBoard();
	
	int placePiece(int col,char sym);
	int getN();


};

#endif