/* FILE: ConnectM.cpp
 * AUTHOR: Bryant Matt
 * COURSE: CAP4601
 * ASSIGNMENT: PROJECT 1 / ConnectM
 * Description: Holds game generator and driver
 */

#include <iostream>
// for <streamsize> 
#include<ios>      
// for numeric_limits 
#include<limits>  

#include "board.hpp"
#include "agent.hpp"


using namespace std;

//Generates and starts game
void generateGame(int n, int m);

//Places piece for user turn
int playerTurn(board* b,char sym);

//Places piece for computer turn
int computerTurn(board* b,int bmove,char sym);

int main(int argc, char** argv)
{
	/*
	n - store command line argument in N position
	*/
	int n;

	/*
	m - store command line argument in M position
	*/
	int m;

	//If Correct number of command line parameters are present
	if (argc == 3) {
		n=atoi(argv[1]);
		m=atoi(argv[2]);
		//Check validility of parameters
		if ((n > 2 && n <= 10) && (m > 1 && m < n)) {
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


/*
generateGame- Generates game board and loops through turns
n - is the size of the nxn board
m - is the needed connected pieces to win
No return
*/
void generateGame(int n, int m)
{
	//Ask user for what piece they want to uses and correct case
	char c;
	char p;

	std::cout << "What piece would you like X or O?";
	std::cin >> p;
	if (p == 'x' || p=='X') {
		p = 'X';
		c = 'O';
	}else if (p == 'o'||p=='O') {
		p = 'O';
		c = 'X';
	}
	else {
		std::cout << "INVALID INPUT: Your piece was defaulted to X\n";
		p = 'X';
		c = 'O';
	}

	//Creates board for the game
	board* b = new board(n, m,p,c);

	//Creates agent for opposing player
	agent* comp = new agent(c, p, b);
	
	//Won flag
	int won=0;

	//player turn flag
	bool pTurn;


	//Asks users if they want to go first and sets pTurn correctly
	char ans;
	std::cout << "Whould you like to go first [y][n]?";
	std::cin >> ans;
	if (ans == 'y' || ans == 'Y') {
		pTurn = true;
	}
	else if (ans == 'n' || ans == 'N') {
		pTurn = false;
	}
	else {
		std::cout << "INVALID INPUT: Default, user goes first.\n";
		pTurn = true;
	}

	
	//Game Loop
	int turns = n * n;

	while (won != 1 || turns==0) {
		if (pTurn) {
			b->printBoard();
			won = playerTurn(b, p);
			while (won == -1 && turns>1) {
				won = playerTurn(b, p);
			}
			turns--;
			if (won == 1) {
				std::cout << "User WINS. Guess my agent wasn't good enough.\n";
				b->printBoard();
			}
			pTurn = false;
		}
		else {
			//Uses agent abSearch call
			won = computerTurn(b, (comp->abSearch(b)), c);
			turns--;
			if (won == 1) {
				std::cout << "Computer WINS. Better luck next time!\n";
				b->printBoard();
			}
			pTurn = true;
		}
		if (turns == 0) {
			std::cout << "Looks like its a tie... Oh well\n";
		}

	}

	delete b;
	delete comp;
}

/*
playerTurn- factorized function to handle players move
b- pointer to game board
sym- player's piece symbol
*/
int playerTurn(board* b, char sym)
{
	int place;

	std::cout << "What column would you like to place your piece?";
	if(!(cin >> place)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		place = -1;
	}
	return b->placePiece(place, sym);
	
}

/*
computerTurn- factorized fuction to handle computer move
b- pointe to game board
bmove- move returned from agents abSearch function
sym- computer's piece symbol
*/
int computerTurn(board* b,int bmove,char sym)
{
	int place;
	
	place = bmove;
	return b->placePiece(place, sym);

}