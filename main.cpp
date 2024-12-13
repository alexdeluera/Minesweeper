#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Board.h"
#include "Button.h"
#include "Tile.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");

    Board StartBoard;
    vector<vector<Tile>> grid;

    StartBoard.LoadRandBoard();
    grid = StartBoard.LoadMineField();

    sf::Sprite hidden_tile(TextureManager::GetTexture("tile_hidden"));
    sf::Vector2u tileSize = TextureManager::GetTexture("tile_hidden").getSize();

    sf::Vector2f facePosition(
        (window.getSize().x - TextureManager::GetTexture("face_happy").getSize().x) / 2,
        StartBoard.height * tileSize.y
    );
    Button face_happy("face_happy", facePosition);

    Button face_lose("face_lose", facePosition);
    face_lose.visible = false;

    Button face_win("face_win", facePosition);
    face_win.visible = false;

    sf::Vector2f debugPosition(
        (window.getSize().x - TextureManager::GetTexture("debug").getSize().x) / 2 + 2 * TextureManager::GetTexture("debug").getSize().x,
        StartBoard.height * tileSize.y
    );

    Button debug_button("debug", debugPosition);

    sf::Vector2f test_1Position(
        (window.getSize().x - TextureManager::GetTexture("test_1").getSize().x) / 2 + 3 * TextureManager::GetTexture("test_1").getSize().x,
        StartBoard.height * tileSize.y
    );
    Button test1_button("test_1", test_1Position);

    sf::Vector2f test_2Position(
        (window.getSize().x - TextureManager::GetTexture("test_2").getSize().x) / 2 + 4 * TextureManager::GetTexture("test_2").getSize().x,
        StartBoard.height * tileSize.y
    );
    Button test2_button("test_2", test_2Position);

    sf::Vector2f test_3Position(
        (window.getSize().x - TextureManager::GetTexture("test_3").getSize().x) / 2 + 5 * TextureManager::GetTexture("test_3").getSize().x,
        StartBoard.height * tileSize.y
    );
    Button test3_button("test_3", test_3Position);

    sf::Texture Fig_Texture = TextureManager::GetTexture("digits");
    vector<sf::IntRect> Fig_Pieces;
    for (int i = 0; i < 211; i += 21)
        Fig_Pieces.push_back(sf::IntRect(i, 0, 21, 32));
    vector<int> nums = StartBoard.Counter(StartBoard.mine_count);
    vector<sf::Sprite> Fig_Shown;

    for (int i = 0, j = 50; i < 3; i++) {
        Fig_Shown.push_back(sf::Sprite(Fig_Texture));
        Fig_Shown.at(i).setPosition(j, 512);
        j += 21;
        Fig_Shown.at(i).setTextureRect(Fig_Pieces.at(nums.at(i)));
    }

    /*---------- MAIN GAME LOOP ----------*/
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            window.setFramerateLimit(60);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && !StartBoard.Lose(grid)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (int i = 0; i < StartBoard.height; ++i) {
                        for (int j = 0; j < StartBoard.width; ++j) {
                            Tile& tile = grid[i][j];

                            if (tile.HandleLeftClick(mousePos, sf::Mouse::Left)) {
                                tile.Reveal(grid, i, j);

                                cout << "Tile [" << i << "][" << j << "] LEFT clicked!" << endl;
                            }
                        }
                    }
                }

                else if (event.mouseButton.button == sf::Mouse::Right) {
                    for (int i = 0; i < StartBoard.height; ++i) {
                        for (int j = 0; j < StartBoard.width; ++j) {
                            Tile& tile = grid[i][j];

                            if (tile.HandleRightClick(window, event)) {
                                cout << "Tile [" << i << "][" << j << "] RIGHT clicked!" << endl;
                            }
                            if (!tile.hidden) {
                                tile.flag = true;
                            }
                        }
                    }
                }
            }
        }

        if (test1_button.IsClicked(window, event)) {
            cout << "test board 1 clicked" << endl;
            StartBoard.LoadBoard("testboard1");
            grid = StartBoard.LoadMineField();
            face_lose.visible = false;
            face_win.visible = false;
            face_happy.visible = true;
        }

        if (test2_button.IsClicked(window, event)) {
            cout << "test board 2 clicked" << endl;
            StartBoard.LoadBoard("testboard2");
            grid = StartBoard.LoadMineField();
            face_lose.visible = false;
            face_win.visible = false;
            face_happy.visible = true;
        }

        if (test3_button.IsClicked(window, event)) {
            cout << "test board 3 clicked" << endl;
            StartBoard.LoadBoard("testboard3");
            grid = StartBoard.LoadMineField();
            face_lose.visible = false;
            face_win.visible = false;
            face_happy.visible = true;
        }

        if (debug_button.IsClicked(window, event) && !StartBoard.Win(grid)) {
            cout << "debug clicked" << endl;

            for (int i = 0; i < StartBoard.height; ++i) {
                for (int j = 0; j < StartBoard.width; ++j) {
                    Tile& tile = grid[i][j];

                    if (tile.mine == 1) {
                        tile.DebugMines();
                        window.draw(tile.GetMineSprite());
                    }
                }
            }
        }

        if (face_happy.IsClicked(window, event)) {
            cout << "face button clicked" << endl;
            StartBoard.LoadRandBoard();
            grid = StartBoard.LoadMineField();
            face_lose.visible = false;
            face_win.visible = false;
            face_happy.visible = true;

            Fig_Shown.clear();
            Fig_Pieces.clear();
            nums.clear();

            for (int i = 0; i < 211; i += 21)
                Fig_Pieces.push_back(sf::IntRect(i, 0, 21, 32));

            nums = StartBoard.Counter(StartBoard.mine_count);

        }

        window.clear();

        for (int i = 0, j = 50; i < 3; i++) {
            Fig_Shown.push_back(sf::Sprite(Fig_Texture));
            Fig_Shown.at(i).setPosition(j, 512);
            j += 21;
            Fig_Shown.at(i).setTextureRect(Fig_Pieces.at(nums.at(i)));
        }

        int k = 0;

        for (int i = 0; i < StartBoard.height; ++i) {
            for (int j = 0; j < StartBoard.width; ++j) {
                Tile& tile = grid[i][j];


                window.draw(tile.GetSprite());
                StartBoard.flag_count = k;

                if (tile.debug) {
                    window.draw(tile.GetMineSprite());
                }

                else if (tile.mine == 1 && !tile.hidden && !tile.debug) {
                    window.draw(tile.GetMineSprite());
                    face_lose.visible = true;
                    StartBoard.Lose(grid);
                    face_lose.Draw(window);
                }

                else if (tile.GetNearMines() != 0 && !tile.hidden && !tile.debug) {
                    window.draw(tile.GetNumSprite());
                }

                else if (tile.flag && tile.hidden) {
                    ++k;
                    window.draw(tile.GetFlagSprite());
                    StartBoard.flag_count = k;
                }

                else if (StartBoard.Win(grid)) {
                    face_win.Draw(window);
                    tile.flag = true;
                    face_win.visible = true;
                }

                else if (StartBoard.Lose(grid) && tile.mine == 1) {
                    tile.Reveal(grid, i, j);
                }
            }
        }

        face_happy.Draw(window);
        face_lose.Draw(window);
        face_win.Draw(window);
        debug_button.Draw(window);
        test1_button.Draw(window);
        test2_button.Draw(window);
        test3_button.Draw(window);


        for (int i = 0; i < 3; i++)
            window.draw(Fig_Shown.at(i));

        nums = StartBoard.Counter(StartBoard.mine_count - StartBoard.flag_count);
        for (int i = 0; i < 3; i++)
            Fig_Shown.at(i).setTextureRect(Fig_Pieces.at(nums.at(i)));

        window.display();
    }

    return 0;
}