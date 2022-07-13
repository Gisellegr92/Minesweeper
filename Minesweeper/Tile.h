#pragma once

/* Description for each tile, returns true if the tile has a mine or not and change or set mines */

class Tile {
    bool is_mine;
    
public:
    /* Default Constructor, take the variable boolean is_Mine and set it to be false  */
    Tile();
    /* Constructor with parameter*/
        Tile(bool is_mine);

    /* Change or set the variable boolean of the Tile Class to true */
    void setMine();
    /* return the variable of the Tile Class is_mine */
    bool isMine();
};