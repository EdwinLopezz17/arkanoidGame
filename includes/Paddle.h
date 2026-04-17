#ifndef ARKANOID_PADDLE_H
#define ARKANOID_PADDLE_H

#include <raylib.h>

class Paddle {
public:
    float x, y;
    float width, height;
    Color color;
    float speed;

    Paddle(int screenWidth, int screenHeight);
    void const draw();
    void move(float deltaTIme, int screenWidth);
};



#endif
