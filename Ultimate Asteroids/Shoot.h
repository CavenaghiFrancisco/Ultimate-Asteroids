#pragma once
#include "Textures.h"
class Shoot {
private:
    Vector2 position;
    Vector2 speed;
    float radius;
    float rotation;
    int lifeSpawn;
    bool active;
    Color color;
public:
	int playerMaxShoots = 5;
   
};

