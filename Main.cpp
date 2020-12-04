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

	Camera camera("My game", Vector2f(0, 0));
	storage.AddObject(&camera);
	camera.setFrameralLimit(60);


	
	Vector2f downWallVertexs[4];
	downWallVertexs[0] = Vector2f(0, 0);
	downWallVertexs[1] = Vector2f(0, 400);
	downWallVertexs[2] = Vector2f(1980, 400);
	downWallVertexs[3] = Vector2f(1980, 0);
	Wall downWall("downWall", Vector2f(0, 1080), downWallVertexs, 4, Vector2f(1980, 0), 10000);
	storage.AddObject(&downWall);

	Vector2f upWallVertexs[4];
	upWallVertexs[0] = Vector2f(0, 0);
	upWallVertexs[1] = Vector2f(1980, 0);
	upWallVertexs[2] = Vector2f(1980, 400);
	upWallVertexs[3] = Vector2f(0, 400);
	Wall upWall("upWall", Vector2f(0, 0), upWallVertexs, 4, Vector2f(1980, 0), 10000);
	storage.AddObject(&upWall);

	Vector2f leftWallVertexs[4];
	leftWallVertexs[0] = Vector2f(0, 0);
	leftWallVertexs[1] = Vector2f(-400, 0);
	leftWallVertexs[2] = Vector2f(-400, 1080);
	leftWallVertexs[3] = Vector2f(0, 1080);
	Wall leftWall("leftWall", Vector2f(0, 0), leftWallVertexs, 4, Vector2f(0, 1080), 10000);
	storage.AddObject(&leftWall);

	Vector2f rightWallVertexs[4];
	rightWallVertexs[0] = Vector2f(0, 0);
	rightWallVertexs[1] = Vector2f(0, 1080);
	rightWallVertexs[2] = Vector2f(400, 1080);
	rightWallVertexs[3] = Vector2f(400, 0);
	Wall rightWall("rightWall", Vector2f(1980, 0), rightWallVertexs, 4, Vector2f(0, 1080), 10000);
	storage.AddObject(&rightWall);

	//std::cout << rightWall.name << '\n';
	


	String paints[1];
	paints[0] = "036.png";

	StorageImages stIm("Test paint", 1, paints);

	Sprite sp(&stIm, 1);

	Sprite nulll();

	Vector2f vertex[16]{ Vector2f(0,  0),  Vector2f(0,  16), Vector2f(0,  32), Vector2f(0,  48),
						   Vector2f(0,  64), Vector2f(8,  64), Vector2f(16, 64), Vector2f(24, 64),
						   Vector2f(32, 64), Vector2f(32, 48), Vector2f(32, 32), Vector2f(32, 16),
						   Vector2f(32, 0),  Vector2f(24, 0),  Vector2f(16, 0),  Vector2f(8,   0) };

	StdGameObject Elve ("Elve",  Vector2f(415, 587), &sp, vertex, 16, "Test paint", Vector2f(32, 64), Vector2f(16, 32), 1);
	StdGameObject Elve1("Elve1", Vector2f(400, 478), &sp, vertex, 16, "Test paint", Vector2f(32, 64), Vector2f(16, 32), 1);

	Elve.setVelosity(Vector2f(30, 0));
	Elve1.setVelosity(Vector2f(-30, 0));

	storage.AddObject(&Elve);
	storage.AddObject(&Elve1);

	//std::cout << Elve.isCollide(downWall);

	
	Vector2f g (0, 10);

	sf::Clock clock;
	int time = clock.getElapsedTime().asMilliseconds() + 400;
	srand(time);

	float time1 = clock.getElapsedTime().asSeconds();
	float time2 = clock.getElapsedTime().asSeconds();

	float dt;

	while (camera.isOpen())
	{
		time1 = clock.getElapsedTime().asSeconds();
		dt = time1 - time2;
		std::cout << 1.0 / (time1 - time2);
		time2 = time1;
		std::cout << "\n";

		handlingEvent(&camera);
		
		//std::cout << storage["Elve"].isCollide(storage["downWall"]) << '\n';

		Iterator iter(&storage);
		while (true)
		{
			GameObject& gameObject = iter.stepIteration();
			if (gameObject.name == "NULL")
				break;
			gameObject.draw(&camera);
			gameObject.animation(dt);
		}

		Iterator iter2(&storage);
		while (true)
		{
			GameObject& gameObject = iter2.stepIteration();
			if (gameObject.name == "NULL")
				break;
			gameObject.nullChangeImpulse();
			Iterator iter1(&storage);
			while (true)
			{
				GameObject& gObj = iter1.stepIteration();
				if (gObj.name == "NULL")
					break;
				Vector2f v = gameObject.isCollide(gObj);
				gameObject.resolutionCollision(gObj, v);
				//std::cout << gameObject.name << ' ' << gameObject.changeImpulse << '\n';
			}
		}

		Iterator iter3(&storage);
		while(true)
		{
			GameObject& gameObject = iter3.stepIteration();
			if (gameObject.name == "NULL")
				break;
			gameObject.gravitation(g, dt);
			gameObject.move(dt);
			gameObject.changeVelosity();
		}
		camera.display();
	};
	
	return 0;
}


//window.setFramerateLimit(60);