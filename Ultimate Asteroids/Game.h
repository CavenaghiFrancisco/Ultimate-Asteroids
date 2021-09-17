#pragma once
#include "Textures.h"
#include "Player.h"


class Game {
private:
	bool gameInited;
	bool goToMenu;
	bool replay;
	bool isPaused;
	Player* player;
public:
	const int screenWidth = 1366;
	const int screenHeight = 768;
	float currentScreenWidth = GetScreenWidth();
	float currentScreenHeight = GetScreenHeight();
	float windowReSizeWidth = currentScreenWidth / screenWidth;
	float windowReSizeHeight = currentScreenHeight / screenHeight;
	Game();
	~Game();
	/*void Init();
	void Input();
	void Update();
	void Draw();
	void DeInit();
	
	bool GetPause();
	void SetPause(bool value);
	bool RePlay();
	void SetReplay();
	bool ExitGameGoToMenu();
	void SetGameGoToMenu();*/
	bool GetInited();
	void InitGame();         // Initialize game
	void UpdateGame();       // Update game (one frame)
	void DrawGame();         // Draw game (one frame)
	void UnloadGame();       // Unload game
	void UpdateDrawFrame();  // Update and Draw (one frame)
	
};


