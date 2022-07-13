#include <iostream>
#include "Game.h"

using namespace std;

Game::Game() {
	is_board_revealed = false;
	win = false;
	lose = false;
}


void Game::loadBoards(vector<string> paths) {
	map<string, Board> boards;
	for (unsigned int i = 0; i < paths.size(); ++i) {
		Board board;
		board.readFromFile(paths[i]);
		string path = paths[i];
		unsigned int begin = path.find_last_of("/") + 1;
		unsigned int end = path.find(".brd");
		string name = path.substr(begin, end-begin);
		//cout << "Debug:" << name << endl;
		all_boards.emplace(name, board);
	}
}

void Game::setBoard(Board board) {
	curr_board = board;
}

Board* Game::getBoard()
{
	Board* ptr = &curr_board;
	return ptr;
}


Board Game::getBoardByName(string board_name) {
	if (all_boards.find(board_name) != all_boards.end()) {
		return all_boards[board_name];
	}
	cout << "There is no board with name: " << board_name;
	exit(-2); 
}

void Game::getDigitCodes(vector<int>& in_data) {
	bool negative = false;

	if (in_data.at(0) < 0) {
		negative = true;
		in_data.at(0) *= -1;
	}

	string number = to_string(in_data.at(0));

	if (number.length() == 1) {
		in_data.at(1) = stoi(number);
		in_data.at(2) = 0;
		negative ? in_data.at(3) = 10 : in_data.at(3) = 0;
	}
	if (number.length() == 2) {
		in_data.at(1) = stoi(number.substr(1, 1));
		in_data.at(2) = stoi(number.substr(0, 1));
		negative ? in_data.at(3) = 10 : in_data.at(3) = 0;
	}
	if (number.length() == 3) {
		in_data.at(1) = stoi(number.substr(2, 1));
		in_data.at(2) = stoi(number.substr(1, 1));
		in_data.at(3) = stoi(number.substr(0, 1));
	}
}

 
void Game::revealMines() {
	is_board_revealed = !is_board_revealed;
}

bool Game::isBoardRevealed() {
	return is_board_revealed;
}


void Game::resetGame() {
	curr_board = Board();
	curr_board.randomizeBoard();
}

void Game::setWin() {
	win = true;
}

void Game::setLose() {
	lose = true;
}

bool Game::isLose() {
	return lose;
}

bool Game::isWin() {
	return win;
}

bool Game::checkWinCondition()
{
	win = true;
	for (int i = 0; i < buttons.size(); i++) {
		for (int j = 0; j < buttons.at(0).size(); j++) {
			if (buttons.at(i).at(j)->isMine())
				continue;
			if (!buttons.at(i).at(j)->isRevealed() || (buttons.at(i).at(j)->isMine() && !buttons.at(i).at(j)->isFlag()))
				win = false;
		}
	}
	if (getBoard()->getNumberOfMines() != 0)
	{
		win = false;
	}
	return win;
}

void Game::setTextures() {
	string imagePaths[] = {
		"./images/debug.png",
		"./images/digits.png",
		"./images/face_happy.png",
		"./images/face_lose.png",
		"./images/face_win.png",
		"./images/flag.png",
		"./images/mine.png",
		"./images/number_1.png",
		"./images/number_2.png",
		"./images/number_3.png",
		"./images/number_4.png",
		"./images/number_5.png",
		"./images/number_6.png",
		"./images/number_7.png",
		"./images/number_8.png",
		"./images/test_1.png",
		"./images/test_2.png",
		"./images/test_3.png",
		"./images/tile_hidden.png",
		"./images/tile_revealed.png"
	};

	for (string path : imagePaths) {
		Texture texture;
		if (!texture.loadFromFile(path)) {
			cout << "Error while loading image from file with path: " << path;
			exit(-1);
		}
		texture.setSmooth(true);

		unsigned int  begin = path.find_last_of("/") + 1;
		unsigned int end = path.find(".png");
		string name = path.substr(begin, end-begin);
		textures.emplace(name, texture);
	}
}

Texture* Game::getTexture(string texture_name) {
	if (textures.find(texture_name) != textures.end()) {
		return &textures[texture_name];
	}
	cout << "There is no image with name: " << texture_name;
	exit(-2); 
}


void Game::loadGameWindow(MouseInteractionObject &game_result) {
	game_result.setTexture(getTexture("face_happy"));
	lose = false;
	win = false;
	is_board_revealed = false;

	buttons.clear();
	tiles.clear();
	for (int i = 0; i < curr_board.getHeight(); i++) {
		vector<MouseInteractionObject*> row;
		vector<MouseInteractionObject*> revealed_row;

		for (int j = 0; j < curr_board.getLength(); j++) {
			MouseInteractionObject *revealed_tile = new MouseInteractionObject(*getTexture("tile_revealed"));
			MouseInteractionObject *tile = new MouseInteractionObject(*getTexture("tile_hidden"));

			tile->setMine(curr_board.isMine(i, j));
			
			revealed_tile->setPosition(j * 32, i * 32);
			tile->setPosition(j * 32, i * 32);  
			row.push_back(tile);
			revealed_row.push_back(revealed_tile);
		}
		
		buttons.push_back(row);
		tiles.push_back(revealed_row);
	}

	setAdjacentTiles();
}

void Game::setAdjacentTiles()
{
	for (unsigned int i = 0; i < buttons.size(); i++) {
		for (unsigned j = 0; j < buttons[0].size(); j++) {
			MouseInteractionObject* curr_obj = buttons[i][j];

			for (int row = -1; row <= 1; row++) {
				for (int column = -1; column <= 1; column++) {
					if (row == 0 && column == 0) {
						continue;
					}
					try {
						MouseInteractionObject* adjacent_tile = buttons.at(i + column).at(j + row);
						if (adjacent_tile->isMine()) {
							curr_obj->incrementMineCount();
						}
						curr_obj->addAdjacentTile(adjacent_tile);
					}
					catch (const out_of_range& e) {
						// Do Nothing
					}
				}
			}
		}
	}
}
