#pragma once

#include <raylib.h>

class GameObject {
public:
    float x, y;
    Color color;

    GameObject(){};
    virtual const void draw() {};

    ~GameObject() {};

};

