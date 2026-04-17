#include <iostream>
#include <raylib.h>
#include <cmath>
#include "Ball.h"
#include "Paddle.h"

const int s_width = 800;
const int s_height = 700;
const int fil_lv1= 14;
const int col_lv1= 18;
const int matriz_lv_1[fil_lv1][col_lv1] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1},
    {1,2,1,0,0,0,1,2,0,0,2,1,0,0,0,1,2,1},
    {1,2,1,0,1,0,1,0,0,0,0,1,0,1,0,1,2,1},
    {1,2,1,0,1,0,1,1,1,1,1,1,0,1,0,1,2,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {2,1,1,0,1,1,1,0,0,0,0,1,1,1,0,1,1,2},
    {2,2,1,0,0,0,0,0,1,1,0,0,0,0,0,1,2,2},
    {2,2,1,1,1,1,0,0,1,1,0,0,1,1,1,1,2,2},
    {2,2,2,2,2,1,0,0,0,0,0,0,1,2,2,2,2,2},
    {2,2,2,2,2,1,1,0,0,0,0,1,1,2,2,2,2,2},
    {2,2,2,2,2,2,1,1,0,0,1,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,2,2}
};

struct Block {
    float x, y;
    float width, height;
    Color color;
    int lifes;
    bool isActive = true;

    void drawBlock() {
        if (isActive) {
            DrawRectangle(x+2, y+2, width, height, Fade(BLACK, 0.3f));
            DrawRectangle(x, y, width, height, color);
            DrawRectangle(x+2, y+2, width, 2, Fade(WHITE, 0.5f));
            DrawRectangle(x, y, 2, height, Fade(WHITE, 0.5f));
        }
    }

};

Block blocks_lv1[fil_lv1][col_lv1];

void resetLevel() {
    Block block;
    block.width = (float)s_width / col_lv1;
    block.height = 24;

    for (int i = 0; i < fil_lv1; i++) {
        for (int j= 0; j < col_lv1; j++) {
            block.isActive = true;
            block.x = j * block.width;
            block.y = i * block.height + 50;

            int tipo = matriz_lv_1[i][j];

            if (tipo == 0) {
                block.color = RED;
                block.lifes = 1;
            }else if (tipo == 1) {
                block.color = GRAY;
                block.lifes = 2;
            }else if (tipo == 2) {
                block.isActive = false;
            }
            blocks_lv1[i][j] = block;
        }
    }
}

void drawBlocks() {
    for (int i = 0; i < fil_lv1; i++) {
        for (int j = 0; j < col_lv1; j++) {
            blocks_lv1[i][j].drawBlock();
        }
    }
}

int collisionBallBlock(Ball c, Block b) {
    Rectangle rectBar = {b.x, b.y, b.width, b.height};

    if (!CheckCollisionCircleRec({c.x, c.y}, c.radius, rectBar))
        return 0;

    //right - left
    if (c.y >= b.y && c.y + c.radius <= b.y + b.height) return 1;
    //up - down
    if (c.x >= b.x && c.x + c.radius <= b.x + b.width) return 2;

    return 2;
}

int main() {

    InitWindow(s_width, s_height, "Arkanoid Game");
    SetTargetFPS(60);

    Ball ball = Ball(s_width, s_height);
    Paddle paddle = Paddle(s_width, s_height);

    resetLevel();
    while (!WindowShouldClose()) {

        float deltaTime = GetFrameTime();
        paddle.move(deltaTime, s_width);

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

        for (int i = 0; i < fil_lv1; i++) {
            bool choco = false;
            for (int j = 0; j < col_lv1; j++) {
                if (!blocks_lv1[i][j].isActive) continue;
                int direcction = collisionBallBlock(ball, blocks_lv1[i][j]);

                if (direcction > 0){
                    blocks_lv1[i][j].lifes--;
                    if (blocks_lv1[i][j].lifes <= 0) {
                        blocks_lv1[i][j].isActive = false;
                    }
                    if (direcction == 1) ball.speed_x *= -1;
                    else if (direcction == 2) ball.speed_y *= -1;
                    choco = true;
                    break;
                }
            }
            if (choco) break;
        }

        BeginDrawing();

        ClearBackground({58,50,45,255});

        drawBlocks();
        paddle.draw();
        ball.move(deltaTime, s_width, s_height);
        ball.draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
