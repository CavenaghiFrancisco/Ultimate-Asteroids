#pragma once
#include "Textures.h"
#include "Player.h"
#include "Shoot.h"

struct PowerUp {
	Vector2 position;
	float radius;
	bool active;
	bool alreadySpawned;
};

class Game {
private:
	bool gameInited;
	bool goToMenu;
	bool replay;
	bool isPaused;
	Player* player;
	Shoot* shoots[6];
	float scrolling;
	Texture2D backgroundGameTexture;
	Textures* backgroundGame;
	Color backgroundGameColor = { (unsigned char)(GetRandomValue(0, 255)),(unsigned char)GetRandomValue(0, 255) , (unsigned char)GetRandomValue(0, 255) , 40 };
	Rectangle backgroundColorTexture;
	Texture2D shipTexture;
	Textures* ship;
	Texture2D bigMeteorsTexture;
	Textures* bigMeteors;
	Texture2D mediumMeteorsTexture;
	Textures* mediumMeteors;
	Texture2D smallMeteorsTexture;
	Textures* smallMeteors;
	Texture2D sightTexture;
	Textures* sight;
	Texture2D moreBulletsTexture;
	Textures* moreBullets;
	Texture2D shieldTexture;
	Textures* shield;
	Texture2D rightClickTexture;
	Textures* rightClick;
	Texture2D leftClickTexture;
	Textures* leftClick;
	float timerPowerUp;
	PowerUp moreBulletsPowerUp;
	PowerUp shieldPowerUp;
public:
	const int screenWidth = 1366;
	const int screenHeight = 768;
	float currentScreenWidth = GetScreenWidth();
	float currentScreenHeight = GetScreenHeight();
	float windowReSizeWidth = currentScreenWidth / screenWidth;
	float windowReSizeHeight = currentScreenHeight / screenHeight;
	Game();
	~Game();
	bool GetInited();
	void InitGame();         // Initialize game
	void InputGame();
	void UpdateGame();       // Update game (one frame)
	void DrawGame();         // Draw game (one frame)
	void DeInitGame();       // Unload game
	void UpdateDrawFrame();  // Update and Draw (one frame)
	bool GoToMenu();
};


