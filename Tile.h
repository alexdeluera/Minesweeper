#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TextureManager.h"
using namespace std;


class Tile {
public:
    // Constructor
    Tile(sf::Sprite sprite);
    Tile() : hidden(true), mine(0) {}

    //Functions
    bool Reveal(vector<vector<Tile>>& grid, int x, int y);
    void revealNeighbors(std::vector<std::vector<Tile>>& grid, int x, int y);
    bool isValid(int x, int y, int gridWidth, int gridHeight);
    void DebugMines();

    bool HandleLeftClick(sf::Vector2i mousePos, sf::Mouse::Button button);
    bool HandleRightClick(sf::RenderWindow& window, sf::Event& event);

    sf::Sprite& GetSprite();
    sf::Sprite& GetMineSprite();
    sf::Sprite& GetFlagSprite();
    sf::Sprite& GetNumSprite();
    void SetNearMines(int newValue);
    int GetNearMines() const;

    sf::Sprite sprite;
    sf::Sprite mineSprite;
    sf::Sprite flagSprite;
    sf::Sprite numSprite;
    bool hidden;
    bool flag;
    bool debug;
    int mine;
    bool mousePressed;
    int nearMines;
};