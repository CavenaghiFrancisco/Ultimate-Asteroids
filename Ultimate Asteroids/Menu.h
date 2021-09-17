#pragma once
#include "Textures.h"

class Menu {
private:
	bool menuInited;
	bool goToGame;
	bool goToShop;
	bool goToCredits;
	bool goToOptions;
	bool exitGame;
	int option;
	float scrolling;
	Rectangle button0Area;
	Texture2D backgroundTexture;
	Textures* background;
	Texture2D buttonTexture;
	Textures* button0;
	Texture2D buttonPushedTexture;
	Textures* button0Pushed;
	Texture2D titleTexture;
	Textures* title;
	Font font;
public:
	const float screenWidth = 1366;
	const float screenHeight = 768;
	float currentScreenWidth = GetScreenWidth();
	float currentScreenHeight = GetScreenHeight();
	float windowReSizeWidth = currentScreenWidth / screenWidth;
	float windowReSizeHeight = currentScreenHeight / screenHeight;
	Menu();
	~Menu();
	void Init();
	void Input();
	void Update();
	void Draw();
	void DeInit();
	bool GetInited();
	bool ExitGame();
	bool ExitMenuGoToCredits();
	bool ExitMenuGoToOptions();
	bool ExitMenuGoToGame();
	bool ExitMenuGoToShop();
};




