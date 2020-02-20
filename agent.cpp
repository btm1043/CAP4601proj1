#include "agent.hpp"
#include "board.hpp"
#include <stdlib.h>
#include <iostream>

agent::agent(char s,board* b)
{
	sym = s;
	compboard = new board(b->getN(), b->getM(), b->getBoardarr(), b->getValid());
	//bestmove = best_move(compboard, sym);
}

int agent::best_move(char sym)
{
	
	int bestscore = -10000;
	int score = 0;
	int bestcol = rand() % compboard->getN();

	for (int i = 0; i < compboard->getN(); i++) {
		compboard->placePiece(i, sym);
		score = compboard->getBoardScore(i,sym);
		compboard->printBoard();
		std::cout << "Board Score for i=" << i << " is " << score << "\n";

		if (score > bestscore) {
			bestscore = score;
			bestcol = i;
		}
		compboard->unplacePiece(i, sym);
	}


	return bestcol;
}

void agent::get_tempboard(board* b)
{
	compboard->setBoardarr(b->getBoardarr());
	compboard->setValid(b->getValid());


}

