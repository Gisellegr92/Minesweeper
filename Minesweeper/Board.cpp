#include "Board.h"
#include <iostream>
#include <fstream>
#include <cstdlib>



Board::Board() {
	
	number_of_mines = 0;
	length = 25; 
	height = 16;  
}

Board::Board(int length, int height) {
	number_of_mines = 0;
	this->length = length;
	this->height = height;
}

void Board::readFromFile(string &path) {
	ifstream file(path);
	string line;

	if (!file.is_open()) {
		cout << "Unable to open board file: " << path << endl;
		exit(-1);
	}

	height = 0;
	while(file >> line) {
		vector<Tile> tile_row;
		length = line.length();
		// cout << "Debug: " << line << endl << length << endl;
	
		for (unsigned int i = 0; i < length; ++i) {
			Tile tile;
			// cout << i << ":" << line[i] << " ";
			if (line[i] == '1') {
				// cout << "here" << i << endl; 
				number_of_mines++;
				tile = Tile(true); 
				
			} else {
				tile = Tile(false);
			}

			tile_row.push_back(tile);
		}
		// cout << endl;

		tiles_matrix.push_back(tile_row);
		height++;
	}
	
	printBoard();
}

void Board::printBoard() {
	for (unsigned int i = 0; i < height; ++i) {
		for (unsigned int j = 0; j < length; ++j) {
			 //cout << i << ":" << j << ":" << tiles_matrix[i][j].isMine() << endl;;
			tiles_matrix[i][j].isMine() ? cout << '1' : cout << '0';
		}
		cout << endl;
	}
	cout << endl;
}

int Board::getLength() {
	return length;
}

int Board::getHeight() {
	return height;
}

int Board::getNumberOfMines() {
	return number_of_mines;
}


void Board::updateNumberOfMines(int difference) {
	number_of_mines += difference;
}

bool Board::isMine(int row, int column) {
	return tiles_matrix[row][column].isMine();
}


void Board::randomizeBoard() {
	number_of_mines = 50;

	for (int i = 0; i < height; ++i) {
		vector<Tile> tile_row;
		for (int j = 0; j < length; ++j) {
			Tile tile = Tile(false);
			tile_row.push_back(tile);
		}
		tiles_matrix.push_back(tile_row);
	}

	int counter = 0;
	while (counter < number_of_mines) {
		int row = rand() % height;
		int col = rand() % length;

		if (!tiles_matrix[row][col].isMine()) {
			tiles_matrix[row][col].setMine();
			counter++;
		}
	}
}

int* Board::getNumberOfMinesPtr() {
	int* ptr = &number_of_mines;
	return ptr;
}