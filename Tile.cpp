#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <string>
#include <fstream>
#include <iostream>

Tile::Tile(sf::Sprite Sprite) {
    sprite = Sprite;
    hidden = true;
    mine = 0;
    flag = false;
    debug = false;
    mousePressed = false;
    nearMines = 0;

    mineSprite.setTexture(TextureManager::GetTexture("mine"));
    flagSprite.setTexture(TextureManager::GetTexture("flag"));
    numSprite.setTexture(TextureManager::GetTexture("tile_hidden"));
}

bool Tile::Reveal(std::vector<std::vector<Tile>>& grid, int x, int y) {

    if (nearMines == 0 && mine != 1) {
        revealNeighbors(grid, x, y);
    }

    if (mine == 1) {
        hidden = false;
        sprite.setTexture(TextureManager::GetTexture("tile_revealed"));
        mineSprite.setPosition(sprite.getPosition());
    }

    else {
        hidden = false;
        sprite.setTexture(TextureManager::GetTexture("tile_revealed"));

        return true;
    }
}

bool Tile::isValid(int x, int y, int gridWidth, int gridHeight) {
    return (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight);
}

void Tile::revealNeighbors(std::vector<std::vector<Tile>>& grid, int x, int y) {
    if (!isValid(x, y, grid.size(), grid[0].size())) {
        return;
    }

    if (!grid[x][y].hidden) {
        return;
    }

    grid[x][y].hidden = false;
    grid[x][y].sprite.setTexture(TextureManager::GetTexture("tile_revealed"));

    //cout << "Revealing tile at (" << x << ", " << y << "), nearMines: " << grid[x][y].nearMines << endl;

    if (grid[x][y].nearMines == 0) {
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;
                Reveal(grid, x + dx, y + dy);
            }
        }
    }
}

void Tile::DebugMines() {
    debug = !debug;
    if (debug) {
        hidden = false;
        sprite.setTexture(TextureManager::GetTexture("tile_revealed"));
        mineSprite.setPosition(sprite.getPosition());
    }
    else {
        hidden = true;
        sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
    }
}

bool Tile::HandleLeftClick(sf::Vector2i mousePos, sf::Mouse::Button button) {
    if (sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        if (button == sf::Mouse::Left && hidden && !flag) {
            return true;
        }
    }
    return false;
}

bool Tile::HandleRightClick(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            flag = !flag;
            flagSprite.setTexture(TextureManager::GetTexture("flag"));
            flagSprite.setPosition(sprite.getPosition());
            return true;
        }
    }
    return false;
}

sf::Sprite& Tile::GetSprite() {
    return sprite;
}

sf::Sprite& Tile::GetMineSprite() {
    return mineSprite;
}

sf::Sprite& Tile::GetFlagSprite() {
    flagSprite.setPosition(sprite.getPosition());
    return flagSprite;
}

sf::Sprite& Tile::GetNumSprite() {
    hidden = false;

    sprite.setTexture(TextureManager::GetTexture("tile_revealed"));

    if (nearMines == 1) {
        numSprite.setTexture(TextureManager::GetTexture("number_1"));
        numSprite.setPosition(sprite.getPosition());
    }

    if (nearMines == 2) {
        numSprite.setTexture(TextureManager::GetTexture("number_2"));
        numSprite.setPosition(sprite.getPosition());
    }

    if (nearMines == 3) {
        numSprite.setTexture(TextureManager::GetTexture("number_3"));
        numSprite.setPosition(sprite.getPosition());
    }

    if (nearMines == 4) {
        numSprite.setTexture(TextureManager::GetTexture("number_4"));
        numSprite.setPosition(sprite.getPosition());
    }

    if (nearMines == 5) {
        numSprite.setTexture(TextureManager::GetTexture("number_5"));
        numSprite.setPosition(sprite.getPosition());
    }

    if (nearMines == 6) {
        numSprite.setTexture(TextureManager::GetTexture("number_6"));
        numSprite.setPosition(sprite.getPosition());
    }

    if (nearMines == 7) {
        numSprite.setTexture(TextureManager::GetTexture("number_7"));
        numSprite.setPosition(sprite.getPosition());
    }

    if (nearMines == 8) {
        numSprite.setTexture(TextureManager::GetTexture("number_8"));
        numSprite.setPosition(sprite.getPosition());
    }

    return numSprite;
}

void Tile::SetNearMines(int newValue) {
    nearMines = newValue;
}

int Tile::GetNearMines() const {
    return nearMines;
}