#pragma once
#include "Vector2f.h"
#include "String.h"


class Camera;
class GameObject;
class Sprite;
class StdGameObject;
class StorageImages;


float max(float a, float b)
{
	if (a > b)
		return a;
	return b;
}


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
			std::cout << image.loadFromFile(namesOfFiles[i].c_str()) << '\n';                                       //!!!!!!!!
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

		return *this;
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

	sf::Image* getImage(String nameStorage, const int index)
	{
		for (int i = 0; i < numberOfStorages; i++)
		{
			if (images[i].getName() == nameStorage)
				return &images[i].getImage(index);
		}
		std::cout << "There is no image with name : " << nameStorage << std::endl;
		assert(false);
	}

	Sprite(StorageImages* images, int numberOfStorage, String nameFistStImages)
	{
		images = new StorageImages[numberOfStorage];
		this->numberOfStorages = numberOfStorage;
		for (int i = 0; i < numberOfStorage; i++)
		{
			this->images[i] = images[i];
		}
		
		//texture.loadFromImage(this->getImage(nameFistStImages, 0));
		//shape.setTexture(&texture);
	}

	Sprite(String imagesName, String nameOfFile)
	{
		images = new StorageImages[1];
		numberOfStorages = 1;
		StorageImages image (imagesName, 1, &nameOfFile);
		images[0] = image;

		//texture.loadFromImage(this->getImage(imagesName, 0));
		//shape.setTexture(&texture);
	}

	~Sprite()
	{
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

	GameObject(Vector2f v, String str) : position(v), name(str) {}

	virtual void draw(Camera* camera) {}
};


class Camera: public GameObject
{
	sf::RenderWindow window;
	Vector2f velosity;
	int sizeWindowX;
	int sizeWindowY;
	sf::Color windowColor;
	sf::VideoMode videoMode;

public:

	Camera(String name, Vector2f position, int sizeWindowX = 1960, int sizeWindowY = 1080, sf::Color color = sf::Color(0,0,0))
	{
		this->name = name;
		this->position = position;
		sf::VideoMode videoMode(sizeWindowX, sizeWindowY);
		windowColor = color;
		sf::RenderWindow window(videoMode, name.c_str());
	}

	bool objectInDrawableSpace(sf::Vector2f pos, int charactSize)
	{
		return (pos.x > charactSize) && (pos.y > charactSize) && (pos.x < charactSize + sizeWindowX) && (pos.y > charactSize + sizeWindowY);
	}

	void draw(sf::Shape* shape, int charactSize)
	{
		sf::Vector2f shapePosition = shape->getPosition() - sf::Vector2f(position.x, position.y);
		if (objectInDrawableSpace(shapePosition, charactSize))
		{
			shape->setPosition(shapePosition);
			window.draw(*shape);
		}
	}

	bool pollEvent(sf::Event& event)
	{
		return window.pollEvent(event);
	}

	void display()
	{
		window.display();
		window.clear();
	}

	void displayWithoutClear()           // You need double draw background objects and 
	{
		window.display();
	}
};





class StdGameObject: public GameObject
{
	Sprite* sprite;
	Vector2f* vertexs;
	Vector2f size;
	int numberOfVertex;
	String nameCurrentImage;
	int indexCurrentImage;
	int characteristicSize;

	sf::Texture texture;
	sf::RectangleShape shape;

public:

	void setSize(Vector2f size)
	{
		this->size = size;
		shape.setSize(sf::Vector2f(size.x, size.y));
		characteristicSize = max(size.x, size.y);
	}

	StdGameObject(String name, Vector2f position, Sprite* sprite, Vector2f* vertexs, int numberOfVertex, String nameFistStImages, Vector2f size)
	{
		this->name = name;
		this->position = position;
		this->sprite = sprite;
		this->numberOfVertex = numberOfVertex;
		this->vertexs = new Vector2f[numberOfVertex];

		for (int i = 0; i < numberOfVertex; i++)
			this->vertexs[i] = vertexs[i];

		texture.create(size.x, size.y);
		texture.update(*(sprite->getImage(nameFistStImages, 0)));
		shape.setTexture(&texture);

		this->setSize(size);
	}

	StdGameObject(StdGameObject& gameObject)
	{
		delete[] vertexs;
		sprite = gameObject.sprite;
		numberOfVertex = gameObject.numberOfVertex;
		vertexs = new Vector2f[numberOfVertex];
		for (int i = 0; i < numberOfVertex; i++)
			this->vertexs[i] = vertexs[i];
		texture.loadFromImage(*(sprite->getImage(nameCurrentImage, indexCurrentImage)));
		shape.setTexture(&texture);

		this->setSize(gameObject.size);
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
		sf::Image im = *(sprite->getImage(name, index));
	}

	void setCurrentImageIndex(int index)
	{
		indexCurrentImage = index;
		sf::Image im = *(sprite->getImage(nameCurrentImage, index));
	}

	void changeTexture(String nameStorage, const int index)
	{
		texture.loadFromImage(*(sprite->getImage(nameStorage, index)));
	}
	
	void draw(Camera* camera)
	{
		this->changeTexture(nameCurrentImage, indexCurrentImage);
		this->shape.setPosition(position.x, position.y);
		camera->draw(&shape, characteristicSize);
	}
	
};