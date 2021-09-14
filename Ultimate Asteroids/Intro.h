#pragma once
#include "raylib.h"
#include <string>
#include "Textures.h"
#include "GameManager.h"

using namespace std;

class Intro {
private:
	Music introLogoAudio;	
	Texture2D logoTexture;
	Textures* logo;
	GameManager* GM;
public:
	const int screenWidth = 1366;
	const int screenHeight = 768;
	Intro();
	~Intro();
	void StartIntro();
};

