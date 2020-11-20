#pragma once
#include "Vector2f.h"
#include "String.h"

class StorageImages
{
	String name;
	sf::Image* images;
	int numberOfImages;

public:

	StorageImages() {}

	StorageImages(String name, int numberOfImages, String* namesOfFiles)
	{
		this->numberOfImages = numberOfImages;
		this->name = name;
		images = new sf::Image[numberOfImages];
		for (int i = 0; i < numberOfImages; i++)
		{
			sf::Image image;
			image.loadFromFile(namesOfFiles[i].c_str());
		}
	}
};

class Sprite          // What do we should to name it?
{
	StorageImages* images;
	sf::Texture texture;
	sf::Sprite sprite;

public:

	Sprite(StorageImages* images, int numberOfStorage)
	{
		StorageImages* images = new StorageImages[numberOfStorage];
		!!!!!!!!
	}
};

class GameObject
{
public:
	Vector2f position;
	String name;

	GameObject() {}
};

class StdGameObject: public GameObject
{
	sf::Sprite* sprites;
	sf::Sprite* currentSprite;
	Vector2f* vertexs;
	int numberOfVertex;

public:

	StdGameObject(String name, Vector2f position, sf::Sprite* sprites, Vector2f* vertexs, int numberOfVertex)
	{
		this->name = name;
		this->position = position;
		this->sprites = sprites;
		currentSprite = &sprites[0];
		this->numberOfVertex = numberOfVertex;
		this->vertexs = new Vector2f[numberOfVertex];
		for (int i = 0; i < numberOfVertex; i++)
			this->vertexs[i] = vertexs[i];
	}

	StdGameObject(StdGameObject& gameObject)
	{
		delete[] vertexs;
		sprites = gameObject.sprites;
		currentSprite = &sprites[0];
		numberOfVertex = gameObject.numberOfVertex;
		vertexs = new Vector2f[numberOfVertex];
		for (int i = 0; i < numberOfVertex; i++)
			this->vertexs[i] = vertexs[i];
	}

	~StdGameObject()
	{
		delete[] vertexs;
	}

	StdGameObject& operator = (StdGameObject& gameObject)
	{
		delete[] vertexs;
		sprites = gameObject.sprites;
		currentSprite = &sprites[0];
		numberOfVertex = gameObject.numberOfVertex;
		vertexs = new Vector2f[numberOfVertex];
		for (int i = 0; i < numberOfVertex; i++)
			this->vertexs[i] = vertexs[i];
	}
};