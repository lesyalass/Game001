#pragma once
#include "Vector2f.h"
#include "String.h"

class StorageImages
{
	String name;
	sf::Image* images;
	int numberOfImages;

public:

	StorageImages() 
	{
		images = new sf::Image[1];
		name = "NULL";
		numberOfImages = 0;
	}

	StorageImages(String name, int numberOfImages, String* namesOfFiles)
	{
		this->numberOfImages = numberOfImages;
		this->name = name;
		images = new sf::Image[numberOfImages];
		sf::Image image;
		for (int i = 0; i < numberOfImages; i++)
		{
			image.loadFromFile(namesOfFiles[i].c_str());
			images[i] = image;
		}
	}

	StorageImages(StorageImages& stImages)
	{
		name = stImages.name;
		delete[] images;
		numberOfImages = stImages.numberOfImages;
		images = new sf::Image[stImages.numberOfImages];
		for (int i = 0; i < stImages.numberOfImages; i++)
		{
			images[i] = stImages.images[i];
		}
	}

	~StorageImages()
	{
		delete[] images;
	}

	StorageImages& operator = (StorageImages& stImages)
	{
		name = stImages.name;
		delete[] images;
		numberOfImages = stImages.numberOfImages;
		images = new sf::Image[stImages.numberOfImages];
		for (int i = 0; i < stImages.numberOfImages; i++)
		{
			images[i] = stImages.images[i];
		}
	}

	String getName()
	{
		return name;
	}

	sf::Image getImage (const int index)
	{
		return images[index];
	}
};



class Sprite          // What do we should to name it?
{
	int numberOfStorages;
	StorageImages* images;
//	sf::Texture texture;
//	sf::RectangleShape shape;

public:

//	sf::RectangleShape shape;

	sf::Image getImage(String nameStorage, const int index)
	{
		for (int i = 0; i < numberOfStorages; i++)
		{
			if (images[i].getName() == nameStorage)
				return images[i].getImage(index);
		}
		std::cout << "There is no image with name : " << nameStorage << std::endl;
		assert(false);
	}

	Sprite(StorageImages* images, int numberOfStorage, String nameFistStImages)
	{
		StorageImages* images = new StorageImages[numberOfStorage];
		for (int i = 0; i < numberOfStorage; i++)
		{
			this->images[i] = images[i];
		}
		
		//texture.loadFromImage(this->getImage(nameFistStImages, 0));
		//shape.setTexture(&texture);
	}

	Sprite(String imagesName, String nameOfFile)
	{
		StorageImages* images = new StorageImages[1];
		StorageImages image (imagesName, 1, &nameOfFile);
		images[0] = image;

		//texture.loadFromImage(this->getImage(imagesName, 0));
		//shape.setTexture(&texture);
	}

	~Sprite()
	{
		for (int i = 0; i < numberOfStorages; i++)
		{
			delete &images[i];
		}
		delete[] images;
	}
	/*
	void changeTexture(String nameStorage, const int index)
	{
		texture.loadFromImage(this->getImage(nameStorage, index));
	}

	void setSize(Vector2f size)
	{
		shape.setSize(sf::Vector2f(size.x, size.y));
	}
	*/
};




class GameObject
{
public:
	Vector2f position;
	String name;

	GameObject() {}

	GameObject(Vector2f v, String str): position(v), name(str) {}
};





class StdGameObject: public GameObject
{
	Sprite* sprite;
	Vector2f* vertexs;
	int numberOfVertex;
	String nameCurrentImage;
	int indexCurrentImage;

	sf::Texture texture;
	sf::RectangleShape shape;

public:

	StdGameObject(String name, Vector2f position, Sprite* sprite, Vector2f* vertexs, int numberOfVertex, String nameFistStImages)
	{
		this->name = name;
		this->position = position;
		this->sprite = sprite;
		this->numberOfVertex = numberOfVertex;
		this->vertexs = new Vector2f[numberOfVertex];
		for (int i = 0; i < numberOfVertex; i++)
			this->vertexs[i] = vertexs[i];
		texture.loadFromImage(sprite->getImage(nameFistStImages, 0));
		shape.setTexture(&texture);
	}

	StdGameObject(StdGameObject& gameObject)
	{
		delete[] vertexs;
		sprite = gameObject.sprite;
		numberOfVertex = gameObject.numberOfVertex;
		vertexs = new Vector2f[numberOfVertex];
		for (int i = 0; i < numberOfVertex; i++)
			this->vertexs[i] = vertexs[i];
		texture.loadFromImage(sprite->getImage(nameCurrentImage, indexCurrentImage));
		shape.setTexture(&texture);
	}

	~StdGameObject()
	{
		delete[] vertexs;
	}

	StdGameObject& operator = (StdGameObject& gameObject)
	{
		delete[] vertexs;
		sprite = gameObject.sprite;
		numberOfVertex = gameObject.numberOfVertex;
		vertexs = new Vector2f[numberOfVertex];
		for (int i = 0; i < numberOfVertex; i++)
			this->vertexs[i] = vertexs[i];
	}

	void setCurrentImage(String name, int index)
	{
		nameCurrentImage = name;
		indexCurrentImage = index;
		sf::Image im = sprite->getImage(name, index);
	}

	void setCurrentImageIndex(int index)
	{
		indexCurrentImage = index;
		sf::Image im = sprite->getImage(nameCurrentImage, index);
	}

	void changeTexture(String nameStorage, const int index)
	{
		texture.loadFromImage(sprite->getImage(nameStorage, index));
	}

	void setSize(Vector2f size)
	{
		shape.setSize(sf::Vector2f(size.x, size.y));
	}

	/*
	void draw(Camera* camera)
	{
		sprite->changeTexture(nameCurrentImage, indexCurrentImage);
		sprite->shape.setPosition(position.x, position.y);
		.draw(sprite->shape);
	}
	*/
};