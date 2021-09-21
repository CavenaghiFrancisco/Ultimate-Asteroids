#pragma once
#include "Textures.h"
class Shoot {
private:
    Vector2 position;
    Vector2 speed;
    float radius;
    int lifeSpawn;
    bool active;
    float rotation;
    Color color;
public:
    const float screenWidth = 1366;
    const float screenHeight = 768;
    Shoot();
    ~Shoot();
    Vector2 GetPosition();
    void SetPositionX(float _positionx);
    void SetPositionY(float _positiony);
    Vector2 GetSpeed();
    void SetSpeedX(float _speedx);
    void SetSpeedY(float _speedy);
    float GetRadius();
    void SetRadius(float _radius);
    int GetLifeSpawn();
    void SetLifeSpawn(float _lifespawn);
    bool GetActive();
    void SetActive(float _active);
    void LifeTimer();
    void Shot();
    void SetRotation(float r);
    float GetRotation();
};

