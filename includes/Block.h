#pragma once
#include "GameObject.h"

class Block : public GameObject{
public:
    float width, height;
    int lifes;
    bool isActive;

    Block();

    void const draw() override;
};



