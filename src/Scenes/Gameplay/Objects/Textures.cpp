#include "Textures.h"

Textures::Textures() {
}

Textures::~Textures() {
}

Texture2D Textures::GetTexture() {
	return texture;
}

void Textures::SetTexture(Texture2D _texture) {
	texture = _texture;
}

Rectangle Textures::GetFrameRec() {
	return frameRec;
}

void Textures::SetFrameRec(int frameRecWidth, int frameRecHeight) {

	frameRec.width = frameRecWidth;
	frameRec.height = frameRecHeight;
	frameRec.x = 0;
	frameRec.y = 0;
}

Vector2 Textures::GetPosition() {
	return position;
}

void Textures::SetPosition(int x, int y) {
	position.x = x;
	position.y = y;
}

int Textures::GetWidth() {
	return texture.width;
}

void Textures::SetWidth(int width) {
	texture.width = width;
}

int Textures::GetHeight() {
	return texture.height;
}

void Textures::SetHeight(int height) {
	texture.height = height;
}

void Textures::SetTextureData(Texture2D texture, int posX, int posY, int width, int height) {
	SetTexture(texture);
	SetWidth(width);
	SetHeight(height);
	SetPosition(posX, posY);
	SetFrameRec(width, height);
}

