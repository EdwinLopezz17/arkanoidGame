#ifndef ARKANOID_BALL_H
#define ARKANOID_BALL_H

#include <raylib.h>

class Ball {
public:
    float x, y;
    float radius;
    Color color;
    float total_speed;
    float speed_x;
    float speed_y;

    Ball(int screenWidth, int screenHeight);
    const void draw();
    void move(float deltaTime, int screenWidth, int screenHeight);;
};


#endif
