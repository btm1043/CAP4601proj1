/* FILE: README.txt
 * AUTHOR: Bryant Matt
 * COURSE: CAP4601
 * ASSIGNMENT: PROJECT 1 / ConnectM
 */
 
Description
 ConnectM is a command line ran game that allows users to play a connect 4 style game, in different dimesions
 and winning condition. ConnectM's computer player is using a alpha beta pruning- minimax algorithm to find
 the winning moves.

Setup and Compilation
 
 1. Download and unzip the submission from eLearning on Linux server
 2. Submission includes
	-ConnectM.cpp
	-board.cpp
	-board.hpp
	-agent.cpp
	-agent.hpp
	-Makefile
	-ConnectMReport.pdf
	-README (This file)
 3. Environment: This program has been tested on Linux server and will run there
 4. Compiling: This program includes a Makefile

At command line in Linux, type make run. This compiles and runs ./ConnectM N M 
Program will expect 2 comand line agruments:
	1.N -> 	The size parameter for creating the NxN game board
		Must be an integer between 3 and 10.
	2.M -> 	The length parameter for the amount of sequential pieces to win the game
		Must be an integer between 1 and N.
 5.Running the Program:
	User interaction is needed for this program.
	The user will be prompts by two prompts at the beginning of the game.
	The user will alse be prompted to select a column to place a piece on each of their turns.

	Prompt 1:
	"What piece would you like X or O?"
	This prompt requires the user to enter either X or O.
	Any invalid inputs will cause the user to be defaulted to X.

	Prompt 2:
	"Would you like to go first [y][n]?"
	This prompt requires the user to enter either Y or N.
	Any invalid inputs will cause the user to be defaulted to Y.

	Turn prompt:
	"What column would you like to place your piece?"
	This prompt requires the users to enter an integer between/including 0 and N-1.
	Any invalid inputes will cause a loop to req
	

 CHANGELOG

v1 (01/27/2020)
The base game is complete, with a random computer player. All contained in ConnectM.cpp

v2.(02/02/2020)
Refactored into board, agent, and ConnectM files and classes.
Minimax search is implemented, max depth without performance suffering is 4.
Basic utility scoring function (BoardScore) is implemented.

v3.(02/18/2020)
Alpha beta pruning implentation has been started.
Need to re-evaluate utility function.

v4.(02/20/2020)
Alpha beta pruning implentation is completed.
Still modifying utility function to get desired result.

v5.(02/24/2020)
Final version of utility function is implemented. Took most scoring out, and narrowed it to
only scoring win/lose and giving points for placing pieces in the central columns.