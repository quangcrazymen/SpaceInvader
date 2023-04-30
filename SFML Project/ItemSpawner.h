#pragma once
#include <SFML/Graphics.hpp>

class ItemSpawner
{
public:
	virtual void spawnItem(
		sf::Vector2f spawnLocation) = 0;

};

