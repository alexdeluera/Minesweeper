#include <SFML/Graphics.hpp>
#include <string>
#include "TextureManager.h"

class Button {
public:
    // Constructor
    Button(const std::string& textureName, const sf::Vector2f& position);

    //Functions
    void Draw(sf::RenderWindow& window);
    bool IsClicked(sf::RenderWindow& window, sf::Event& event);
    sf::Sprite& GetSprite();

    bool visible;

private:
    sf::Texture buttonTexture;
    sf::Sprite buttonSprite;
    sf::Vector2u buttonSize;
    bool mousePressed = false;
};