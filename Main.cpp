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
	camera.setFrameralLimit(60);

	//Sprite sp("Test paint", "007.png");

	String paints [2];
	paints[0] = "007.png";
	paints[1] = "008.jpg";

	StorageImages stIm("Test paint", 2, paints);
	//std::cout << stIm.getImage(0)->getSize().x << stIm.getImage(0)->getSize().y << '\n';

	Sprite sp(&stIm, 1);

	Vector2f vertex [4] { Vector2f(0, 0), Vector2f(0,410), Vector2f(241, 410), Vector2f(241, 0) };

	StdGameObject Elve("Elve", Vector2f(400, 600), &sp, vertex, 4, "Test paint", Vector2f(241, 410));
	storage.AddObject(&Elve);

	storage.newSeriesIteration();
	storage.stepIteration().draw(&camera);
	camera.display();

	int i = 0;

	while (camera.isOpen())
	{
		i++;
		handlingEvent(&camera);
	
		storage.newSeriesIteration();
		storage.stepIteration().draw(&camera);
		camera.display();

		storage["Elve"].animation(1);
		//camera.display();
	};

	return 0;
}


//window.setFramerateLimit(60);