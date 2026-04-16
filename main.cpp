#include <iostream>
#include <raylib.h>
#include <cmath>

const int s_width = 900;
const int s_height = 700;
const int fil_lv1= 10;
const int col_lv1= 20;
const int matriz_lv_1[fil_lv1][col_lv1] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,1,1,1,0,0,0,1,1,0,0,0,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

struct Block {
    float x, y;
    float width, height;
    Color color;
    int tipe;
    int lifes;
    bool isActive = true;

    void drawBlock() {
        if (isActive) {
            DrawRectangle(x,y,width,height,color);
            float thick = .5f;
            DrawRectangleLinesEx({ (float)x, (float)y, (float)width, (float)height }, thick, WHITE);
        }
    }

};

Block blocks_lv1[fil_lv1][col_lv1];

void resetLevel() {
    Block block;
    block.width = s_width/(col_lv1+2);
    block.height = 20;
    for (int i = 0; i < fil_lv1; i++) {
        for (int j= 0; j < col_lv1; j++) {
            block.x = (j*block.width) + block.width;
            block.y = i*block.height;
            if (matriz_lv_1[i][j] == 0) {
                block.tipe = 0;
                block.color = RED;
                block.lifes = 1;
            } else if (matriz_lv_1[i][j] == 1) {
                block.tipe = 1;
                block.color = GRAY;
                block.lifes = 2;
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

struct Bar {
    float x, y;
    float width, height;
    Color color;
    float speed;

    void draw() {
        DrawRectangle(x,y,width,height,color);
    }

};

struct Circle {
    float x, y;
    float radius;
    Color color;
    float total_speed = 200.0f;
    float speed_x = 180;
    float speed_y = total_speed - speed_x;

    void draw() {
        DrawCircle(x,y,radius,color);
    }

    void move(float deltaTime) {

        x += speed_x * deltaTime;
        y += speed_y * deltaTime;

        if (x-radius <= 0) {
            x=radius;
            speed_x*=-1;
        }
        if (x + radius >= s_width) {
            x = s_width - radius;
            speed_x *= -1;
        }
        if (y - radius <= 0) {
            y = radius;
            speed_y *= -1;
        }
        if (y + radius >= s_height) {
            y = s_height - radius;
            speed_y *= -1;
        }

    }
};

bool collisionBallBlock(Circle c, Block b) {
    Rectangle rectBar = {b.x, b.y, b.width, b.height};

    return CheckCollisionCircleRec({c.x, c.y}, c.radius, rectBar);
}

int main() {

    InitWindow(s_width, s_height, "Arkanoid Project");
    SetTargetFPS(60);

    Bar bar{};
    bar.width = 150;
    bar.height = 15;
    bar.x = (s_width/2) - (bar.width/2);
    bar.y = s_height - 200;
    bar.color = WHITE;
    bar.speed = 500.0f;

    Circle ball{};
    ball.radius = 5;
    ball.x = (s_width/2) - ball.radius;
    ball.y = s_height/2;
    ball.color = ORANGE;
    ball.total_speed = 200.0f;

    resetLevel();
    while (!WindowShouldClose()) {

        float deltaTime = GetFrameTime();
        if (IsKeyDown(KEY_A) && bar.x>0) {
            bar.x -= bar.speed * deltaTime;
            if (bar.x<0) bar.x = 0;
        }
        if (IsKeyDown(KEY_D) && bar.x + bar.width < s_width) {
            bar.x += bar.speed * deltaTime;
            if (bar.x + bar.width > s_width) bar.x = s_width - bar.width;
        }

        Rectangle rectBar = {bar.x, bar.y, bar.width, bar.height};
        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, rectBar)) {
            float distanceToCenter = ball.x - (bar.x + bar.width/2);
            float relativePosition = distanceToCenter / (bar.width/2);

            ball.speed_x = relativePosition * ball.total_speed;
            ball.speed_y = sqrt(pow(ball.total_speed,2) - pow(ball.speed_x,2))*-1;

            ball.y = bar.y - ball.radius;
        }

        for (int i = 0; i < fil_lv1; i++) {
            for (int j = 0; j < col_lv1; j++) {
                if (!blocks_lv1[i][j].isActive) continue;
                if (collisionBallBlock(ball, blocks_lv1[i][j])) {
                    blocks_lv1[i][j].lifes--;
                    if (blocks_lv1[i][j].lifes <= 0) {
                        blocks_lv1[i][j].isActive = false;
                    }
                }
            }
        }

        BeginDrawing();

        ClearBackground({58,50,45,255});

        drawBlocks();
        bar.draw();
        ball.move(deltaTime);
        ball.draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
