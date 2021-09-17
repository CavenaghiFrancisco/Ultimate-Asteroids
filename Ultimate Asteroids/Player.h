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
public:
    const int playerSize = 20;
    const int playerSpeed = 300;
    const int playerMaxShoots = 5;
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
    void SetRotation(float _rotation);
    float GetRadius();
    void SetPositionX(float positionx);
    void SetPositionY(float positiony);
    float Vector2Length(Vector2 v);
    Vector2 Vector2Subtract(Vector2 v1, Vector2 v2);
    float Vector2Angle(Vector2 v1, Vector2 v2);

};




