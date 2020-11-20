#pragma once
#include <cassert>
#include <iostream>
#include "Vector2f.h"
#include "String.h"
#include "GameObjects.h"

// You have to no named your game objects as "NULL"


struct Node
{
	GameObject* object;
	Node* next;
};

std::ostream& operator << (std::ostream& streamP, const GameObject& object)
{
	streamP << object.position << ' ' << object.name << std::endl;
	return streamP;
}


class Storage
{
	Node* head = NULL;
	Node* iter;

public:
	Storage() :head(NULL), iter(head)
	{

	}

	~Storage()
	{
		Node* pointer = head;
		while (pointer)
		{
			Node* newPointer = pointer->next;
			delete pointer;
			pointer = newPointer;
		}
	}

	void CreateObject(GameObject* object)
	{
		head = new Node{ object, head };
	}

	void DeleteObject(String name)
	{
		Node* pointer = head;
		if (head->object->name == name)
		{
			Node* newHead = head->next;
			delete head;
			head = newHead;
			return;
		}
		while (pointer)
		{
			if (pointer->next->object->name == name)
			{
				Node* newPointer = pointer->next->next;
				delete pointer->next;
				pointer->next = newPointer;
				return;
			}
			pointer = pointer->next;
		}
		std::cout << "There is no object with name : " << name << std::endl;
	}

	GameObject& operator [] (String name) 
	{
		Node* pointer = head;
		while (pointer)
		{
			if (pointer->object->name == name)
			{
				return *(pointer->object);
			}
			pointer = pointer->next;
		}
		std::cout << "There is no object with name : " << name << std::endl;
	}

	GameObject& operator [] (int index)
	{
		Node* pointer = head;
		for (int i = 0; i < index; ++i)
		{
			assert(pointer);
			pointer = pointer->next;
		}
		GameObject& res = *(pointer->object);
		return res;
	}

	void newSeriesIteration()
	{
		iter = head;
	}

	GameObject& stepIteration()
	{
		if (iter == NULL)
		{
			GameObject res{ Vector2f(0, 0), "NULL" };
			return res;
		}
		GameObject& returnObject = *(iter->object);
		iter = iter->next;
		return returnObject;
	}

	int len()
	{
		Node* pointer = head;
		int i = 0;
		while (pointer)
		{
			i++;
			pointer = pointer->next;
		}
		return i;
	}
};

std::ostream& operator << (std::ostream& streamP, Storage& stor)
{
	stor.newSeriesIteration();
	GameObject object = stor.stepIteration();
	while (object.name != "NULL")
	{
		streamP << object << std::endl;
		object = stor.stepIteration();
	}
	return streamP;
}
