#include <cstddef>
#pragma once
/* FILE: board.hpp
 * AUTHOR: Bryant Matt
 * COURSE: CAPT
 * ASSIGNMENT: PROJECT 1 / ConnectM
 */
#ifndef BOARD_HPP
#define BOARD_HPP

#include <stdlib.h>
#include <iostream>
#include <string>

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

	//Player piece
	char p;

	//Agent piece
	char c;

	/*
		printHsplit
		printBoard helper function
		prints horizontal split between rows
	*/
	void printHsplit();

	/*
		printDrow
		printBoard helper function
		prints the horizontal data lines of the board
		row- row from 2d char boardarr
	*/
	void printDrow(char* row);

	/*
		isWon
		Checks if the move causes a win
		col- column move was placed in
		row- row move was placed in
		sym- symbol that was placed during move
		@returns true if any win criteria are met, false if not
	*/
	bool isWon(int col, int row, char sym);


public:
	~board();

	/*
		Game board constructor
		Dynamically allocated 2d char array and 1d int array with provided n paramater
		Fills 2d char array with ' '
		inn- the input for n parameter of the board
		inm- the input for m parameter of the board
		pp- Player piece symbol
		cp- computer piece symbol
	*/
	board(int n, int m, char pp, char cp);

	/*
		printBoard
		Prints board for the game using two helper functions
	*/
	void printBoard();

	/*
		getN
		Needed for agent's abSearch algorithm
		@returns N parameter of board
	*/
	int getN();

	/*
		isValid
		Checks is a col has a valid move left
		col- column to check
		@return -2 is no more valid moves else return 0
	*/
	int isValid(int col);

	/*
		placePiece
		Check validility of placing move in a col, then places it
		col- column entity wants to place a piece in
		sym- symbol that should be placed
		@return -1 if not valid move
		1 if move creats a win
		0 if valid move
	*/
	int placePiece(int col, char sym);

	/*
		unplacePiece
		Removes placed piece
		Needed for Alpa beta pruning
		col- column to remove from
		sym- symbol to remove (more to tracking than function
	*/
	void unplacePiece(int col, char sym);

	/*
		getBoardScore
		Utility function for abSearch
		col- column recent move was made to
		sym- symbol of recent move
		@return score of board
	*/
	int getBoardScore(int col, char sym);

	/*
		rowPotential
		Checks to left and right of move for empty spaces and spaces with same piece
		filled- pointer to hold return value of spaces filled with same pieces
		col-column last piece was places
		sym-callers symbol
	*/
	int rowPotential(int* filled, int col, char sym);

	/*
		colPotential
		Checks to up and down of move for empty spaces and spaces with same piece
		filled- pointer to hold return value of spaces filled with same pieces
		col-column last piece was places
		sym-callers symbol
	*/
	int colPotential(int* filled, int col, char sym);
};

#endif