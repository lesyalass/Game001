#pragma once
#include <math.h>
#include <cassert>
#include <iostream>
#include "SFML/Graphics.hpp"

struct Vector2f
{
    float x;
    float y;

    Vector2f() {}

    Vector2f(float x, float y)
    {
        this->x = x;
        this->y = y;
    };

    Vector2f(int x, int y)
    {
        this->x = x;
        this->y = y;
    };

    Vector2f(sf::Vector2f vector)
    {
        this->x = vector.x;
        this->y = vector.y;
    };

    Vector2f(sf::Vector2i vector)
    {
        this->x = vector.x;
        this->y = vector.y;
    };

    Vector2f operator + (Vector2f v)
    {
        return Vector2f(x + v.x, y + v.y);
    }
    Vector2f& operator += (Vector2f v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2f operator - (Vector2f v)
    {
        return Vector2f(x - v.x, y - v.y);
    }
    Vector2f& operator -= (Vector2f v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vector2f operator * (float v)
    {
        return Vector2f(x * v, y * v);
    }
    Vector2f& operator *= (float v)
    {
        x *= v;
        y *= v;
        return *this;
    }

    Vector2f operator / (float v)
    {
        assert(v);
        return Vector2f(x / v, y / v);
    }
    Vector2f& operator /= (float v)
    {
        assert(v);
        x /= v;
        y /= v;
        return *this;
    }

    float operator * (Vector2f v)
    {
        return x * v.x + y * v.y;
    }

    float mod()
    {
        return pow(x * x + y * y, 0.5);
    }

    float projection(Vector2f axis)
    {
        float scalarComposition = (*this) * axis;
        float moduleAxis = axis.mod();

        assert(moduleAxis != 0);

        return scalarComposition / moduleAxis;
    }

    Vector2f norm()
    {
        assert(this->mod());
        return (*this) / this->mod();
    }

    int vectComp(Vector2f v)
    {
        return (x * v.y - y * v.x);
    }
    friend Vector2f operator * (float f, Vector2f v);
    friend std::ostream& operator << (std::ostream& streamP, const Vector2f vector);
};

