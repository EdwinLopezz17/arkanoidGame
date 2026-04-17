#include "../includes/Paddle.h"

Paddle::Paddle(int screenWidth, int screenHeight){
    width = 150;
    height = 15;
    color = WHITE;
    speed = 500.0f;
    x = (screenWidth/2) - (width/2);
    y = screenHeight - 30;
}

void const Paddle:: draw() {
    DrawRectangle(x,y,width, height, color);
}

void Paddle::move(float deltaT, int screenWidth) {
    if (IsKeyDown(KEY_A)) x -= speed * deltaT;
    if (IsKeyDown(KEY_D)) x += speed * deltaT;

    if (x <  0) x = 0;
    if (x + width > screenWidth) x = screenWidth - width;
}