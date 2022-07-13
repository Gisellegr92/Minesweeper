#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Board.h"
#include "Game.h"
#include "MouseInteractionObject.h"

using namespace sf;

int main()
{
	vector<string> test_boards;
	test_boards.push_back("./boards/testboard1.brd");
	test_boards.push_back("./boards/testboard2.brd");
	test_boards.push_back("./boards/testboard3.brd");

	RenderWindow window(VideoMode(800, 600), "Minesweeper");

	Game game = Game();
	game.loadBoards(test_boards);
	game.setTextures();
	game.setBoard(game.getBoardByName("testboard1"));

	MouseInteractionObject debug_btn = MouseInteractionObject(*game.getTexture("debug"));
    MouseInteractionObject test1 = MouseInteractionObject(*game.getTexture("test_1"));
    MouseInteractionObject test2 = MouseInteractionObject(*game.getTexture("test_2"));
    MouseInteractionObject test3 = MouseInteractionObject(*game.getTexture("test_3"));
    MouseInteractionObject game_result = MouseInteractionObject(*game.getTexture("face_happy"));
    MouseInteractionObject mine_count1 = MouseInteractionObject(*game.getTexture("digits"));
    MouseInteractionObject mine_count2 = MouseInteractionObject(*game.getTexture("digits"));
    MouseInteractionObject mine_count3 = MouseInteractionObject(*game.getTexture("digits"));
    debug_btn.setPosition(512, 512);
    test1.setPosition(576, 512);
    test2.setPosition(640, 512);
    test3.setPosition(704, 512);
    game_result.setPosition(352, 512);
    mine_count1.setPosition(42, 512);
    mine_count2.setPosition(21, 512);
    mine_count3.setPosition(0, 512);

    game.loadGameWindow(game_result);

    Event event;
    vector<int> mine_count_display{ 
        game.getBoard()->getNumberOfMines(),-1,-1,-1 
    };

    cout << "Mine Count: " << game.getBoard()->getNumberOfMines() << endl;

    while (window.isOpen()) {
        mine_count_display.at(0) = game.getBoard()->getNumberOfMines();
        
        game.getDigitCodes(mine_count_display);

        /*cout << "Digits: ";
        for (int i = 3; i > 0; i--) {
            cout << mine_count_display[i];
        }
        cout << endl;*/
        mine_count1.showDigit(mine_count_display.at(1));
        mine_count2.showDigit(mine_count_display.at(2));
        mine_count3.showDigit(mine_count_display.at(3));

        int row = -1;
        int col = -1;
        bool right_click = false;
        bool left_click = false;

        while (window.pollEvent(event)) {
            switch (event.type) {
            case Event::Closed:
                window.close();
                break;

            case Event::MouseButtonPressed:
                col = floor(event.mouseButton.x / 32);
                row = floor(event.mouseButton.y / 32);
                if (event.mouseButton.button == sf::Mouse::Right) {
                    right_click = true;
                }
                else {
                    left_click = true;
                }
                break;

            default:
                break;
            }
        }
        /*if (row != -1 && col != -1) {
            cout << "row:" << row << ", col:" << col << endl;
        }*/

        //Reset the game when click the face button
        if (row == 16 || row == 17) {
            if (col == 11 || col == 12) {
                cout << "Face!" << endl;
                game.resetGame();
                game.loadGameWindow(game_result);
                mine_count_display.at(0) = game.getBoard()->getNumberOfMines();
            }
            //Reveal the mines when debug button is clicked 
            if (col == 16 || col == 17) {
                cout << "Debug Mode" << endl;
                game.revealMines();
            }
            //Game modality with the test board 1, when clicked the image Test#1
            if (col == 18 || col == 19) {
                game.setBoard(game.getBoardByName("testboard1"));
                cout << "Test1" << endl;
                game.loadGameWindow(game_result);
                mine_count_display.at(0) = game.getBoard()->getNumberOfMines();
            }
            //Game modality with the test board 2 when clicked the image Test#2
            if (col == 20 || col == 21) {
                cout << "Test2" << endl;
                game.setBoard(game.getBoardByName("testboard2"));
                game.loadGameWindow(game_result);
                mine_count_display.at(0) = game.getBoard()->getNumberOfMines();
            }
            //Game modality with the test board 3 when clicked the image Test#3
            if (col == 22 || col == 23) {
                cout << "Test3" << endl;
                game.setBoard(game.getBoardByName("testboard3"));
                game.loadGameWindow(game_result);
                mine_count_display.at(0) = game.getBoard()->getNumberOfMines();
            }
        }

        if (row < 16 && left_click && !game.isLose()) {
            MouseInteractionObject* clicked_tile = game.buttons[row][col];

            if (clicked_tile->isMine() && !clicked_tile->isFlag()) {
                game.setLose();
                game_result.setTexture(game.getTexture("face_lose"));
                if (!game.isBoardRevealed()) {
                    game.revealMines();
                }
            }
            else if (!clicked_tile->isFlag()) {
                clicked_tile->setReveal(true);
                if (clicked_tile->getMineCount() == 0) {
                    clicked_tile->recursiveReveal();
                }
            }
        }

        if (row < 16 && right_click && !game.isLose()) {
            MouseInteractionObject* clicked_tile = game.buttons[row][col];
            if (!clicked_tile->isRevealed() && !clicked_tile->isFlag()) {
                game.getBoard()->updateNumberOfMines(-1);
                clicked_tile->toggleFlag();
            }
            else if (clicked_tile->isFlag()) {
                game.getBoard()->updateNumberOfMines(1);
                clicked_tile->toggleFlag();
            }
        }

        window.clear(Color(255, 255, 255));
        window.draw(*debug_btn.getSprite());
        window.draw(*test1.getSprite());
        window.draw(*test2.getSprite());
        window.draw(*test3.getSprite());
        window.draw(*game_result.getSprite());
        window.draw(*mine_count1.getSprite());
        window.draw(*mine_count2.getSprite());
        window.draw(*mine_count3.getSprite());

        for (unsigned i = 0; i < game.buttons.size(); i++) {
            for (unsigned int j = 0; j < game.buttons[i].size(); j++) {
                window.draw(*game.tiles[i][j]->getSprite());
                MouseInteractionObject* current_tile = game.buttons[i][j];

                if (current_tile->isMine() && game.isBoardRevealed()) {
                    current_tile->setReveal(true);
                    current_tile->setTexture(game.getTexture("mine"));
                }
                if (current_tile->isMine() && !game.isBoardRevealed()) {
                    current_tile->setReveal(false);
                }

                if (!current_tile->isRevealed()) {
                    current_tile->setTexture(game.getTexture("tile_hidden"));
                }
                else {
                    if (!current_tile->isMine() && current_tile->getMineCount() == 0)
                        current_tile->setTexture(game.getTexture("tile_revealed"));
                    if (!current_tile->isMine() && current_tile->getMineCount() != 0) {
                        int number_mines = current_tile->getMineCount();
                        string digit_name = "number_" + to_string(number_mines);
                        //cout << "digit_name: " << digit_name << endl;
                        current_tile->setTexture(game.getTexture(digit_name));
                    }
                }

                window.draw(*current_tile->getSprite());

                if (current_tile->isFlag() && !current_tile->isRevealed()) {
                    current_tile->setTexture(game.getTexture("flag"));
                    window.draw(*current_tile->getSprite());
                }
            }
        }

        if (!game.isWin() && game.checkWinCondition()) {
            game.setWin();
            game_result.setTexture(game.getTexture("face_win"));
        }
      
        window.display();
    }

	return 0;
}