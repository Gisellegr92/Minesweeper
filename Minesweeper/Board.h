#pragma once
#include <vector>
#include <string>
#include "Tile.h"

using namespace std;

/* This class create Board objects, inherits Tile since the board is conformed by Tile Objects */
class Board {

    vector<vector<Tile>>tiles_matrix;  //A cointainer for the Tiles objects
    int number_of_mines;               //Variable to count the number of mines in Board objects
    int length;                                          
    int height;
    
public:
    /*Set the default values. Number of mines start at 0, length and height are given in PDF */
    Board(); 
    /*Constructor whit parameters*/
    Board(int length, int width);
    
    /*Read the boards given:  1, 2, 3,...using input file stream */
    void readFromFile(string &path);
    /*Print the board loaded with readFromFile function returns 1 if there is mine and 0 if is not mine using the function from Tile class IsMine()*/
    void printBoard();

    /*This functions return length, height and number of mines of the board so it can be accessed from outside classes*/
    int getLength();
    int getHeight();    
    int getNumberOfMines();
    int* getNumberOfMinesPtr(); // This pointer function helps to optimize the time of execution of the program

    /*Update the number of Mines and the digits that is displayed in the window Minesweeper*/
    void updateNumberOfMines(int numer_of_mines);
    /*Return true or false checking the tiles of the board if is mine or not, differs from isMine() because it need the position of the tile*/
    bool isMine(int row, int column);
    /*Every time a board is reset, mines are going to chage their position in a random way, not quantity*/
    void randomizeBoard();
};