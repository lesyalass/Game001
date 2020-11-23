#pragma once
#include "SFML/Graphics.hpp"
#include "GameObjects.h"
#include "Storage.h"
#include "String.h"
#include "Vector2f.h"

int main()
{
	Storage storage;

	sf::Texture tx;
	std::cout << tx.getMaximumSize() << std::endl;

	Camera camera("My game", Vector2f(0, 0));
	storage.AddObject(&camera);

	Sprite sp("Test paint", "007.png");
	Vector2f vertex [4] { Vector2f(0, 0), Vector2f(0,410), Vector2f(241, 410), Vector2f(241, 0) };

	storage.AddObject(&(StdGameObject ("Elve", Vector2f(400, 600), &sp, vertex, 4, "Test paint", Vector2f(241, 410))));

	storage.newSeriesIteration();
	storage.stepIteration().draw(&camera);

	camera.display();

	while (true);

	return 0;
}
