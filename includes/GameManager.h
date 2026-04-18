#pragma once
#include "Block.h"

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
    for (auto &i : blocks_lv1) {
        for (auto &j: i) {
            j.draw();
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
