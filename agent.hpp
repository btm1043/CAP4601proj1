#pragma once
#include <cstddef>
#pragma once
/* FILE: agent.hpp
 * AUTHOR: Bryant Matt
 * COURSE: CAPT
 * ASSIGNMENT: PROJECT 1 / ConnectM
 */
#ifndef AGENT_HPP
#define AGENT_HPP

#include "board.hpp"

class agent {
private:
	char sym;
	int bestmove;
	board* compboard;

public:
	agent(char s,board* b);

	int best_move(char sym);
	void get_tempboard(board* b);


};

#endif