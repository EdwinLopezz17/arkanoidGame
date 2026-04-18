#pragma once

#include "GameObject.h"

class Paddle: public GameObject {
public:
    float width, height;
    float speed;

    Paddle(int screenWidth, int screenHeight);
    void const draw() override;
    void move(float deltaTIme, int screenWidth);
};

