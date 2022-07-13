#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "MouseInteractionObject.h"
#include "Board.h"

using namespace std;
using namespace sf;

/*This clase is going to define the game logic and use the class MouseInteractionObject functions and objects and also the members of the class Board*/

class Game {

	map<string, Board> all_boards;
	bool is_board_revealed;

	bool win;
	bool lose;

	map<string, Texture> textures;

public:
	vector<vector<MouseInteractionObject*> > buttons; //vector cointaining MouseInteractionObject objects that are going to be defined as buttons
	vector<vector<MouseInteractionObject*> > tiles;   //vector cointaining MouseInteractionObject objects that are going to be defined as tiles
	Board curr_board;   

	/* Default Constructor, set all the bool variables to false */
	Game();

	/*Takes the vector cointing the strings (name of the boards), and load all the boards to a map to access the boards*/
	void loadBoards(vector<string>);

	/*Set the board object created in the Game class*/
	void setBoard(Board board);

	/*Returns the Boards pointer object so it can be accessed from outside the class*/
	Board* getBoard();
	/*Return one of the boards already loaded*/
	Board getBoardByName(string board_name);
	/*Logic of the digits that are going to be displayed in the program */
	void getDigitCodes(vector<int>&);

	/* reveales the tiles that are mines */
	void revealMines();
	bool isBoardRevealed();

	/*Create a board with 50 mines in random position*/
	void resetGame();
	/*Set the variables in the Game class*/
	void setWin();
	void setLose();
	bool isLose();
	bool isWin();
	/*Logic to check is game is won*/
	bool checkWinCondition();
	/*Set the images in the program */
	void setTextures();
	/*Get an indiviual imagen set in the program*/
	Texture* getTexture(string texture_name);

	/*Load and configure the images, position, */
	void loadGameWindow(MouseInteractionObject& objects);
private:
	/*function that logically set the adjacent tiles */
	void setAdjacentTiles();
};