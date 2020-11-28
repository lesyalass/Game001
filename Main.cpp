#pragma once
#include "SFML/Graphics.hpp"
#include "GameObjects.h"
#include "Storage.h"
#include "String.h"
#include "Vector2f.h"

void handlingEvent(Camera* camera)
{
	sf::Event event;
	while (camera->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			camera->close();
	}
}

int main()
{
	Storage storage;

	//sf::Texture tx;
	//std::cout << tx.getMaximumSize() << std::endl;

	Camera camera("My game", Vector2f(0, 0));
	storage.AddObject(&camera);

	//Sprite sp("Test paint", "007.png");

	String paints [2];
	paints[0] = "007.png";
	paints[1] = "008.jpg";

	StorageImages stIm("Test paint", 2, paints);

	Sprite sp(&stIm, 1);

	Vector2f vertex [4] { Vector2f(0, 0), Vector2f(0,410), Vector2f(241, 410), Vector2f(241, 0) };

	StdGameObject Elve("Elve", Vector2f(400, 600), &sp, vertex, 4, "Test paint", Vector2f(241, 410));

	storage.AddObject(&Elve);

	storage.newSeriesIteration();
	storage.stepIteration().draw(&camera);
	camera.display();

	int i = 0;

	while (true)
	{
		i++;
		handlingEvent(&camera);
		storage["Elve"].changeTexture();

		storage.newSeriesIteration();
		storage.stepIteration().draw(&camera);
		camera.display();

		if (i == 5)
		{
			storage[0].setCurrentImage("Test paint", 1);   
		}

		if (i == 10)
		{
			i = 0;

			storage["Elve"].setCurrentImage("Test paint", 0);
		}
		//camera.display();
	};

	return 0;
}
