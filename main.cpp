#include <iostream>
#include <raylib.h>
#include <cmath>
#include "Ball.h"
#include "Paddle.h"
#include "GameManager.h"
#include <vector>

void collisionBallPaddle(Ball& ball, Paddle paddle) {
    Rectangle rectBar = {paddle.x, paddle.y, paddle.width, paddle.height};
    if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, rectBar)) {
        float distanceToCenter = ball.x - (paddle.x + paddle.width/2);
        float relativePosition = distanceToCenter / (paddle.width/2);
        if (relativePosition > 1.0f) relativePosition = 0.9f;
        if (relativePosition < -1.0f) relativePosition = -0.9f;

        ball.speed_x = relativePosition * ball.total_speed;
        ball.speed_y = sqrt(pow(ball.total_speed,2) - pow(ball.speed_x,2))*-1;

        ball.y = paddle.y - ball.radius;
    }
}

int main() {

    int n_balls = 1;

    InitWindow(s_width, s_height, "Arkanoid Game");
    SetTargetFPS(60);

    std::vector<Ball> balls;
    balls.reserve(n_balls);
    for (int i = 0; i < n_balls; i++) {
        balls.emplace_back(Ball(s_width, s_height));
    }

    Paddle paddle = Paddle(s_width, s_height);

    resetLevel();
    while (!WindowShouldClose()) {

        float deltaTime = GetFrameTime();
        paddle.move(deltaTime, s_width);

        for (auto &b: balls) {
            collisionBallPaddle(b, paddle);

            for (auto & i : blocks_lv1) {
                bool choco = false;
                for (auto & j : i) {
                    if (!j.isActive) continue;
                    int direcction = collisionBallBlock(b, j);
                    if (direcction > 0){
                        j.lifes--;
                        if (direcction == 1) b.speed_x *= -1;
                        else if (direcction == 2) b.speed_y *= -1;
                        choco = true;
                        break;
                    }
                }
                if (choco) break;
            }
        }

        BeginDrawing();

        ClearBackground({58,50,45,255});

        drawBlocks();
        paddle.draw();

        for (auto &i: balls) {
            i.move(deltaTime, s_width, s_height);
            i.draw();
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
