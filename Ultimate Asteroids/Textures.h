#pragma once
#include "raylib.h"

class Textures {
private:
	Texture2D texture;
	Rectangle frameRec;
	Vector2 position;
public:
	Textures();
	~Textures();
	Texture2D GetTexture();
	void SetTexture(Texture2D _texture);
	Rectangle GetFrameRec();
	void SetFrameRec(int frameRecWidth, int frameRecHeight);
	Vector2 GetPosition();
	void SetPosition(int x, int y);
	int GetWidth();
	void SetWidth(int width);
	int GetHeight();
	void SetHeight(int height);
	void SetTextureData(Texture2D texture, int posX, int posY, int width, int height);

};