#include "Player.h"



Player::Player() {
    
    position = { (float)screenWidth / 2, (float)screenHeight / 2};
    collider = { position.x,position.y };
    radius = 40;
    speed = { 0, 0 };
    acceleration = 0;
    rotation = 0;
    color = RED;
}

Player::~Player() {
}

float Player::Vector2Length(Vector2 v) {
    float result = sqrtf((v.x * v.x) + (v.y * v.y));
    return result;
}

Vector2 Player::Vector2Subtract(Vector2 v1, Vector2 v2) {
    Vector2 result = { v1.x - v2.x, v1.y - v2.y };
    return result;
}

float Player::Vector2Angle(Vector2 v1, Vector2 v2) {
    float result = atan2f(v2.y - v1.y, v2.x - v1.x) * (180.0f / PI);
    if (result < 0) result += 360.0f;
    return result;
}

void Player::UpdateSpeed() {
    speed.x = sin(rotation * DEG2RAD) * playerSpeed * GetFrameTime();
    speed.y = cos(rotation * DEG2RAD) * playerSpeed * GetFrameTime();
}

Vector2 Player::GetSpeed() {
	return speed;
}

float Player::GetAcceleration() {
	return acceleration;
}

void Player::UpdateAcceleration() {
    if (Vector2Length(Vector2Subtract(GetMousePosition(), position)) > 60.0f) {
        rotation = Vector2Angle(position, GetMousePosition()) + 90;
    }
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        if (acceleration < 3) acceleration += 0.3f * GetFrameTime();
    }
    else {
        if (acceleration > 0) acceleration -= 2.0f * GetFrameTime();
        if (acceleration < 0.1) acceleration = 0.1;
    }
}

Vector2 Player::GetPosition() {
	return position;
}

void Player::UpdatePosition() {
    position.x += (speed.x * acceleration);
    position.y -= (speed.y * acceleration);
}

float Player::GetRotation() {
    return rotation;
}

float Player::GetRadius() {
    return radius;
}

void Player::SetRotation(float _rotation) {
    rotation = _rotation;
}

void Player::SetPositionY(float positiony) {
    position.y = positiony;
}

void Player::SetPositionX(float positionx) {
    position.x = positionx;
}

void Player::DrawPlayer() {
    DrawCircle(position.x, position.y, radius, color);
}