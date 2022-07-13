#include "Tile.h"
#include <iostream>

using namespace std;

Tile::Tile() {
	is_mine = false;
}

Tile::Tile(bool is_mine) {
	this->is_mine = is_mine;
}

void Tile::setMine() {
	is_mine = true;
}

bool Tile::isMine() {
	return is_mine;
}