// Ai1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "board.hpp"

#define PLAYER_SYMBOL 'X'
#define COM_SYMBOL 'O'


int generateGame(int n, int m);
int playerTurn(board* b);
int computerTurn(board* b);

int main(int argc, char** argv)
{
	int n;
	int m;


	if (argc == 3) {
		n=atoi(argv[1]);
		m=atoi(argv[2]);
		if ((n > 2 && n <= 10) && (m > 1 && m < n)) {
			std::cout << "Hello World!\n" << n << "\n" << m <<"\n";
			generateGame(n, m);
		}
		else {
			std::cout << "ERROR: PARAMETER ERRORS\n";
		}
	}
	else {
		std::cout << "ERROR: NOT CORRECT AMOUNT OF PARAMETERS\n";
	}

    
}

int generateGame(int n, int m)
{
	board* b = new board(n, m);
	int won=0;
	bool pTurn = true;

	b->printBoard();

	while (won!=1) {
		if (pTurn) {
			won=playerTurn(b);
			while (won == -1) {
				won = playerTurn(b);
			}
			pTurn = false;
		}
		else {
			won=computerTurn(b);
			while (won == -1) {
				won = computerTurn(b);
			}
			pTurn = true;
		}
		b->printBoard();
	}
	
	return 0;
}

int playerTurn(board* b)
{
	int place;

	std::cout << "What column would you like to place your piece?";
	std::cin >> place;
	return b->placePiece(place, PLAYER_SYMBOL);
	
}

int computerTurn(board* b)
{
	int place;
	
	place = (rand() % 10);
	return b->placePiece(place, COM_SYMBOL);

}