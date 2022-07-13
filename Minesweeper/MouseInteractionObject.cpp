#include <iostream>
#include "MouseInteractionObject.h"

using namespace std;

MouseInteractionObject::MouseInteractionObject(Texture texture) {
	this->texture = texture;   
	sprite.setTexture(this->texture);

	is_revealed = false;
	is_mine = false;
	is_flag = false;
	adjacent_mines_count = 0;
}

Sprite* MouseInteractionObject::getSprite()
{
	return &sprite;
}

void MouseInteractionObject::setTexture(Texture* texture)
{
	this->texture = *texture;
}

void MouseInteractionObject::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void MouseInteractionObject::showDigit(int digit)
{
	sprite.setTextureRect(IntRect(digit * 21, 0, 21, 32)); //231 x 32, each digit is 231/11 = 21 width 
}

int MouseInteractionObject::getMineCount()
{
    //cout << "Mine count on tile: " << adjacent_mines_count << endl;
	return adjacent_mines_count;
}

void MouseInteractionObject::incrementMineCount()
{
    adjacent_mines_count++;
}

void MouseInteractionObject::setReveal(bool is_revealed)
{
	this->is_revealed = is_revealed;
}

void MouseInteractionObject::setMine(bool is_mine)
{
	this->is_mine = is_mine;
}

void MouseInteractionObject::toggleFlag()
{
	is_flag = !is_flag;
}

bool MouseInteractionObject::isRevealed()
{
	return is_revealed;
}

bool MouseInteractionObject::isMine()
{
	return is_mine;
}

bool MouseInteractionObject::isFlag()
{
	return is_flag;
}

void MouseInteractionObject::recursiveReveal() {
	if (is_flag) {
		return;
	}
	is_revealed = true;
    for (MouseInteractionObject* adjacent : adjacent_tiles) {
        /*if (adjacent == nullptr) {
            continue;
        }*/
        if (adjacent->adjacent_mines_count == 0 && !adjacent->is_revealed && !adjacent->isFlag()) {
            adjacent->recursiveReveal();
        }

        adjacent->is_revealed = true;
        if (adjacent->isFlag()) {
            adjacent->is_revealed = false;
        }

    }
}

void MouseInteractionObject::addAdjacentTile(MouseInteractionObject* adjacent)
{
	adjacent_tiles.push_back(adjacent);
}
