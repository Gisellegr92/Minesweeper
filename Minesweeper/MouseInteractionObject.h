#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

/*This class is for MouseInteactionObject objects that creates the functions used for the events in the Game class*/

class MouseInteractionObject
{
    Texture texture;
    Sprite sprite;

    bool is_revealed;
    bool is_mine;
    bool is_flag;

    int adjacent_mines_count;
    vector<MouseInteractionObject*> adjacent_tiles;

public:
    /* Constructors: Default and parameterized */
    MouseInteractionObject() = default;
    MouseInteractionObject(Texture texture);
    
    /* This pointer function returns an Sprite object*/
    Sprite *getSprite();
    /*Change or set a Texture object*/
    void setTexture(Texture* texture);
    /*Set the position of the Sprite object using floats x and y */
    void setPosition(float x, float y);

    /*Return the mines count on tile*/
    int getMineCount();
    /*Increment the mines counting so we keep track of the mines in the board */
    void incrementMineCount();
    /* Set the digits image in the program using the dimension of the PNG file */
    void showDigit(int digit);

    /*Set or change the variables is_releaved and is_mine*/
    void setReveal(bool is_revealed);
    void setMine(bool is_mine);

    /*Change the variable bool is_flag to the opposite value */
    void toggleFlag();

    /*Return the variables of the class MouseInteractionObject*/
    bool isRevealed();
    bool isMine();
    bool isFlag();

    /*A recursive function with the base case that return if is the tile is a flag, otherwise loop 
    through the tiles and revealead the tiles with no mines and the adjacents if they are not mines */
    void recursiveReveal();

    /*This function set the adjacent tiles in a vector*/
    void addAdjacentTile(MouseInteractionObject* adjacent);
};

