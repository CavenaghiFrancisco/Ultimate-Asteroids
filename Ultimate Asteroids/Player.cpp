#include "Player.h"



Player::Player() {
    
    position = { (float)screenWidth / 2, (float)screenHeight / 2};
    radius = 40;
    acceleration = { 0,0 };
    direction = { 0,0 };
    rotation = 0;
    color = { (unsigned char)113,(unsigned char)216 , (unsigned char)228 , 150 };
    shield = false;
    bullet = false;
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

void Player::Movement() {
    direction.x = GetMousePosition().x - position.x;
    direction.y = GetMousePosition().y - position.y;
        
    rotation = Vector2Angle(position, GetMousePosition()) + 90;
    
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        acceleration.x += direction.x / (sqrt((direction.x * direction.x) + direction.y * direction.y));
        acceleration.y += direction.y / (sqrt((direction.x * direction.x) + direction.y * direction.y));
    }

    position.x += acceleration.x * GetFrameTime()*2;
    position.y += acceleration.y * GetFrameTime()*2;
}



Vector2 Player::GetPosition() {
	return position;
}



float Player::GetRotation() {
    return rotation;
}

float Player::GetRadius() {
    return radius;
}

void Player::SetRadius(float r) {
    radius = r;
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

void Player::SetShield(bool shield) {
    this->shield = shield;
}

void Player::SetBullets(bool b) {
    bullet = b;
}
bool Player::GetBullets() {
    return bullet;
}

bool Player::GetShield() {
    return shield;
}

void Player::DrawPlayer() {
    DrawCircle(position.x, position.y, radius, color);
}