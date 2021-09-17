#pragma once
#include <cmath>
#include "Textures.h"

class Player {
private:
	Vector2 position;
    Vector2 speed;
    float acceleration;
    float rotation;
    Vector2 collider;
    float radius;
    Color color;
    float shipHeight;
    const int playerSize = 20;
    const int playerSpeed = 300;
    const int playerMaxShoots = 5;
public:
    const int screenWidth = 1366;
    //Otra linea bugeada
    const int screenHeight = 768;
    Player();
    ~Player();
    Vector2 GetSpeed();
    void UpdateSpeed();
    float GetAcceleration();
    void UpdateAcceleration();
    Vector2 GetPosition();
    void UpdatePosition();
    void DrawPlayer();
    float GetRotation();
    float GetRadius();
    void SetPositionX();
    void SetPositionY();

};




