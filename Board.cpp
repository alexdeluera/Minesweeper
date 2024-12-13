#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Tile.h"
#include "TextureManager.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

//Constructor
Board::Board() {
    ifstream file("boards/config.cfg");

    if (!file) {
        cout << "Error opening the file!" << endl;
    }

    string line;

    getline(file, line);
    width = stoi(line);

    getline(file, line);
    height = stoi(line);

    getline(file, line);
    mine_count = stoi(line);

    // Close the file
    file.close();

    tile_count = width * height;
    flag_count = 0;
}

void Board::LoadBoard(string board_filename) {
    board.clear();

    ifstream file("boards/" + board_filename + ".brd");
    if (!file) {
        cout << "Error opening the file!" << endl;
    }
    string line;
    while (getline(file, line)) {
        for (char each : line) {
            if (each == '1') {
                board.push_back(1);
            }
            else if (each == '0') {
                board.push_back(0);
            }
        }
    }
    file.close();
}

void Board::LoadRandBoard() {
    board.clear();

    board.resize(tile_count, 0);
    srand(time(0));

    vector<int> positions(tile_count);
    for (int i = 0; i < tile_count; i++) {
        positions[i] = i;
    }

    random_shuffle(positions.begin(), positions.end());

    for (int i = 0; i < mine_count; i++) {
        board[positions[i]] = 1;
    }
}

vector<vector<Tile>> Board::LoadMineField() {
    vector<vector<Tile>> grid(height, vector<Tile>(width));

    sf::Sprite hidden_tile(TextureManager::GetTexture("tile_hidden"));
    sf::Vector2u tileSize = TextureManager::GetTexture("tile_hidden").getSize();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            sf::Sprite sprite(hidden_tile);
            sprite.setPosition(j * tileSize.x, i * tileSize.y);

            grid[i][j] = Tile(sprite);
            grid[i][j].mine = (board[i * width + j]);
        }
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int adjacentMines = 0;

            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di == 0 && dj == 0) continue;

                    int neighborRow = i + di;
                    int neighborCol = j + dj;

                    if (neighborRow >= 0 && neighborRow < height && neighborCol >= 0 && neighborCol < width) {
                        int neighborIndex = neighborRow * width + neighborCol;

                        if (board[neighborIndex] == 1) {
                            adjacentMines++;
                        }
                    }
                }
            }

            grid[i][j].SetNearMines(adjacentMines);
        }
    }

    return grid;
}

bool Board::Win(vector<vector<Tile>>& grid) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Tile& tile = grid[i][j];

            if (tile.mine == 1 && !tile.hidden) {
                return false;
            }

            if (tile.mine == 0 && tile.hidden) {
                return false;
            }
        }
    }
    return true;
}

bool Board::Lose(vector<vector<Tile>>& grid) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Tile& tile = grid[i][j];

            if (tile.mine == 1 && !tile.hidden) {
                for (int x = 0; x < height; ++x) {
                    for (int y = 0; y < width; ++y) {
                        if (grid[x][y].mine == 1) {
                            grid[x][y].hidden = false;
                        }
                    }
                }
                return true;
            }
        }
    }
    return false;
}

vector<int> Board::Counter(int number) {
    vector<int> nums;

    if (number < -9) {
        nums.push_back(10);
        int temp = (number * -1) / 10;
        nums.push_back(temp);
        temp = (number * -1) % 10;
        nums.push_back(temp);
    }

    else if (number < 0) {
        nums.push_back(10);
        nums.push_back(0);
        nums.push_back(number * -1);
    }

    else if (number < 10) {
        nums.push_back(0);
        nums.push_back(0);
        nums.push_back(number);
    }

    else if (number < 100) {
        nums.push_back(0);
        int temp = number / 10;
        nums.push_back(temp);
        temp = number % 10;
        nums.push_back(temp);
    }

    else if (number < 1000) {
        int temp = number / 100;
        nums.push_back(temp);
        temp = number % 100;
        temp /= 10;
        nums.push_back(temp);
        temp = number % 10;
        nums.push_back(temp);
    }

    return nums;
}