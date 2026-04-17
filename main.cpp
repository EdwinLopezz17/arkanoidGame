#include <iostream>
#include <raylib.h>
#include <cmath>

const int s_width = 900;
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
            DrawRectangle(x,y,width,height,color);
            float thick = .5f;
            DrawRectangleLinesEx({ (float)x, (float)y, (float)width, (float)height }, thick, WHITE);
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
    float total_speed = 300.0f;
    float speed_x = GetRandomValue(-150, 150);
    float speed_y = sqrt(pow(total_speed, 2) - pow(speed_x, 2)) * -1;

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

int collisionBallBlock(Circle c, Block b) {
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
    srand(time(nullptr));
    InitWindow(s_width, s_height, "Arkanoid Project");
    SetTargetFPS(60);

    Bar bar{};
    bar.width = 150;
    bar.height = 15;
    bar.x = (s_width/2) - (bar.width/2);
    bar.y = s_height - 50;
    bar.color = WHITE;
    bar.speed = 500.0f;

    Circle ball{};
    ball.radius = 5;
    ball.x = (s_width/2) - ball.radius;
    ball.y = s_height - 200;
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
            if (relativePosition > 1.0f) relativePosition = 0.9f;
            if (relativePosition < -1.0f) relativePosition = -0.9f;

            ball.speed_x = relativePosition * ball.total_speed;
            ball.speed_y = sqrt(pow(ball.total_speed,2) - pow(ball.speed_x,2))*-1;

            ball.y = bar.y - ball.radius;
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
        bar.draw();
        ball.move(deltaTime);
        ball.draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
