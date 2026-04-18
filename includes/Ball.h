#pragma once

#include "GameObject.h"

class Ball : public GameObject {
public:
    float radius;
    float total_speed;
    float speed_x;
    float speed_y;

    Ball(int screenWidth, int screenHeight);

    void const draw() override;

    void move(float deltaTime, int screenWidth, int screenHeight);

};


