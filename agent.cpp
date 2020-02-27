/* FILE: agent.cpp
 * AUTHOR: Bryant Matt
 * COURSE: CAP4601
 * ASSIGNMENT: PROJECT 1 / ConnectM
 * Description: Holds agent constructor and functions
 */

#include "agent.hpp"

agent::~agent() {

}

/*
agent constuct
s- computer's piece symbol
pp- playesr's piece symbol
b- pointer to game board

*/
agent::agent(char s,char pp,board* b)
{
	sym = s;
	p = pp;
	compboard = b;
}

/*
abSearch- Initial call for all alpha beta searches
b- pointer to game board
@return the best column to place piece for computer
*/
int agent::abSearch(board* b) {

	int alpha = -INT_MAX;
	int beta = INT_MAX;
	int a;

	int alphaPrime;

	for (int i = 0; i < compboard->getN(); i++) {
		//check if initial move is valid
		if (compboard->isValid(i) == 0) {
			alphaPrime = minValue(compboard->placePiece(i, sym),i, 0, alpha, beta);
			compboard->unplacePiece(i, sym);
			if (alphaPrime > alpha) {
				alpha = alphaPrime;
				a = i;
			}
		}	
	}
	return a;
}

/*
minValue- min value function for alpha beta pruning
action- result of action
        1= game won
		0= regular state
mov- Move that cause the current state
cut- cutoff depth tracker
alpha- best possible for maximizing player
beta- best possible for minimizing player
*/
int agent::minValue(int action,int mov,int cut, int alpha, int beta) {
	if (cut == CUTOFF || action==1) {

		//get Board score for minimizing player
		int score = compboard->getBoardScore(mov, p);
		return score;
	}
	//Loops throug possible moves at the current cut depth
	for (int i = 0; i < compboard->getN(); i++) {
		//check if move is valid
		if (compboard->isValid(i) == 0) {
			beta = min(beta, maxValue(compboard->placePiece(i, p),i, cut + 1, alpha, beta));
			//unplace piece that create state for maxValue function
			compboard->unplacePiece(i, p);
			if (alpha >= beta)
			{
				return -INT_MAX;
			}
		}
	}
	return beta;
}

/*
maxValue- max value function for alpha beta pruning
action- result of action
		1= game won
		0= regular state
mov- Move that cause the current state
cut- cutoff depth tracker
alpha- best possible for maximizing player
beta- best possible for minimizing player
*/
int agent::maxValue(int action,int mov, int cut, int alpha, int beta) {
	if (cut == CUTOFF || action==1) {
		//get Board score for maximizing player
		int score = compboard->getBoardScore(mov, sym);
		return score;
	}
	//Loops throug possible moves at the current cut depth
	for (int i = 0; i < compboard->getN(); i++) {
		//check if move is valid
		if (compboard->isValid(i) == 0) {
			alpha = max(alpha, minValue(compboard->placePiece(i, sym),i, cut + 1, alpha, beta));
			//unplace piece that create state for maxValue function
			compboard->unplacePiece(i, sym);
			if (alpha >= beta)
			{
				return INT_MAX;
			}
		}
	}
	return alpha;
}

/*
Custom max function
a- integer
b- integer
@returns larger integer
*/
int agent::max(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

/*
Custom min function
a- integer
b- integer
@returns smaller integer
*/
int agent::min(int a, int b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}

