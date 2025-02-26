#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName) {
	string path = "images/";
	path += fileName + ".png";
	textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName) {
	//if the texture Doesn't exist...
	if (textures.find(textureName) == textures.end()) //not found
		LoadTexture(textureName);
	return textures[textureName];
}

void TextureManager::Clear() {
	textures.clear(); //get rid of all stored objects
}