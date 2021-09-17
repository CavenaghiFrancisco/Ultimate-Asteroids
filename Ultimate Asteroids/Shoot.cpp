#include "Shoot.h"

Shoot::Shoot() {
        position = { 0, 0 };
        speed = { 0, 0 };
        radius = 2;
        active = false;
        lifeSpawn = 0;
        color = WHITE;
}

Shoot::~Shoot() {
}

Vector2 Shoot::GetPosition() {
    return position;
}

void Shoot::SetPositionX(float _positionx) {
    position.x = _positionx;
}

void Shoot::SetPositionY(float _positiony) {
    position.y = _positiony;
}

Vector2 Shoot::GetSpeed() {
    return speed;
}

void Shoot::SetSpeedX(float _speedx) {
    speed.x = _speedx;
}

void Shoot::SetSpeedY(float _speedy) {
    speed.y = _speedy;
}

float Shoot::GetRadius() {
    return radius;
}

void Shoot::SetRadius(float _radius) {
    radius = _radius;
}

float Shoot::GetRotation() {
    return rotation;
}

void Shoot::SetRotation(float _rotation) {
    rotation = _rotation;
}

int Shoot::GetLifeSpawn() {
    return lifeSpawn;
}

void Shoot::SetLifeSpawn(float _lifespawn) {
    lifeSpawn = _lifespawn;
}

bool Shoot::GetActive() {
    return active;
}

void Shoot::SetActive(float _active) {
    active = _active;
}

void Shoot::LifeTimer() {
        if (active) lifeSpawn += GetFrameTime();
}

void Shoot::Shot() {
    if (active) {
        // Movement
        position.x += speed.x * GetFrameTime();
        position.y -= speed.y * GetFrameTime();

        // Collision logic: shoot vs walls
        if (position.x > screenWidth + radius) {
            active = false;
            lifeSpawn = 0;
        }
        else if (position.x < 0 - radius) {
            active = false;
            lifeSpawn = 0;
        }
        if (position.y > screenHeight + radius) {
            active = false;
            lifeSpawn = 0;
        }
        else if (position.y < 0 - radius) {
            active = false;
            lifeSpawn = 0;
        }

        // Life of shoot
        if (lifeSpawn >= 60) {
            position = { 0, 0 };
            speed = { 0, 0 };
            lifeSpawn = 0;
            active = false;
        }
    }
}

