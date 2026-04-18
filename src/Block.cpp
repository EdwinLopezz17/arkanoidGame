#include "../includes/Block.h"

Block::Block() {};

void const Block::draw() {
    if (isActive) {
        if (lifes <= 0) {isActive = false; return; }
        DrawRectangle(x+2, y+2, width, height, Fade(BLACK, 0.3f));
        DrawRectangle(x, y, width, height, color);
        DrawRectangle(x+2, y+2, width, 2, Fade(WHITE, 0.5f));
        DrawRectangle(x, y, 2, height, Fade(WHITE, 0.5f));
    }
}
