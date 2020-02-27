#pragma once
/* FILE: agent.hpp
 * AUTHOR: Bryant Matt
 * COURSE: CAP4601
 * ASSIGNMENT: PROJECT 1 / ConnectM
 * Description: Header for agent class
 */
#ifndef AGENT_HPP
#define AGENT_HPP

#include <cstddef>
#include <stdlib.h>
#include <iostream>
#include <climits>
#include "board.hpp"

//Cutoff depth
#define CUTOFF 6


class agent {
private:
	//Computer's symbol
	char sym;

	//Player's symbol
	char p;

	//pointer to game board
	board* compboard;

	/*
		minValue - min value function for alpha beta pruning
		action - result of action
			1 = game won
			0 = regular state
		mov - Move that cause the current state
		cut - cutoff depth tracker
		alpha - best possible for maximizing player
		beta - best possible for minimizing player
	*/
	int minValue(int action,int mov,int cut, int alpha, int beta);

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
	int maxValue(int action,int mov,int cut, int alpha, int beta);

	/*
		Custom max function
		a- integer
		b- integer
		@returns larger integer
	*/
	int max(int a, int b);

	/*
		Custom min function
		a- integer
		b- integer
		@returns smaller integer
	*/
	int min(int a, int b);

public:
	~agent();
	/*
		agent constuct
		s- computer's piece symbol
		pp- playesr's piece symbol
		b- pointer to game board
	*/
	agent(char s,char p,board* b);

	/*
		abSearch- Initial call for all alpha beta searches
		b- pointer to game board
		@return the best column to place piece for computer
	*/
	int abSearch(board* b);
};

#endif