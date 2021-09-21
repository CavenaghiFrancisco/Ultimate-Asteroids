#pragma once
#include <cmath>
#include "Textures.h"

class Player {
private:
	Vector2 position;
    Vector2 acceleration;
    Vector2 direction;
    float rotation;
    float radius;
    Color color;
    bool shield;
    bool bullet;
public:
    const int playerMaxShoots = 6;
    const int playerSpeed = 300;
    const int screenWidth = 1366;
    
    //Otra linea bugeada
    const int screenHeight = 768;
    Player();
    ~Player();
    Vector2 GetPosition();
    void DrawPlayer();
    void Movement();
    float GetRotation();
    void SetRotation(float _rotation);
    float GetRadius();
    void SetRadius(float r);
    void SetPositionX(float positionx);
    void SetPositionY(float positiony);
    void SetShield(bool shield);
    bool GetShield();
    void SetBullets(bool b);
    bool GetBullets();
    float Vector2Length(Vector2 v);
    Vector2 Vector2Subtract(Vector2 v1, Vector2 v2);
    float Vector2Angle(Vector2 v1, Vector2 v2);
};




