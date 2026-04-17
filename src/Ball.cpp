#include "../includes/Ball.h"
#include <cmath>

Ball::Ball(int screenWidth, int screenHeight) {
    color = ORANGE;
    radius = 5;
    total_speed = 300.0f;
    speed_x = GetRandomValue(-150,150);
    speed_y = sqrt(pow(total_speed,2) - pow(speed_x, 2)) * -1;
    x = (screenWidth/2) + 20;
    y = screenHeight - 150;
}

void const Ball::draw() {
    DrawCircle(x,y,radius,color);
}

void Ball::move(float deltaTime, int screenWidth, int screenHeight) {
    x += speed_x * deltaTime;
    y += speed_y * deltaTime;

    if (x-radius < 0) {
        x=radius;
        speed_x *=-1;
    }
    if (x+radius > screenWidth) {
        x=screenWidth-radius;
        speed_x *=-1;
    }
    if (y+radius > screenHeight) {
        y=screenHeight-radius;
        speed_y *= -1;
    }
    if (y < 0) {
        y=radius;
        speed_y *=-1;
    }
}
