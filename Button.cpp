#include <SFML/Graphics.hpp>
#include "Button.h"
#include <string>
using namespace std;

Button::Button(const std::string& textureName, const sf::Vector2f& position) {
    buttonTexture = TextureManager::GetTexture(textureName);
    buttonSprite.setTexture(buttonTexture);
    buttonSize = buttonTexture.getSize();
    buttonSprite.setPosition(position);
    visible = true;
}

void Button::Draw(sf::RenderWindow& window) {
    if (visible) {
        window.draw(buttonSprite);
    }
}

bool Button::IsClicked(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (buttonSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            mousePressed = true;
            return false;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        if (mousePressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (buttonSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                mousePressed = false;
                return true;
            }
        }
    }

    return false;
}

sf::Sprite& Button::GetSprite() {
    return buttonSprite;
}