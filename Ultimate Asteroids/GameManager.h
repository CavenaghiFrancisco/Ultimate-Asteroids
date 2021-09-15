#pragma once
#include "Menu.h"

enum class STATES { MENU, EXIT, GAME, SHOP };

class GameManager {
private:
	STATES currentState = STATES::MENU;
	bool isThisStateStarting = true;
	bool isPlaying;
	Menu* menu;
public:
	GameManager();
	~GameManager();
	STATES GetState();
	void SetState(STATES& states);
	void UpdateState(STATES states);
	bool ChangeState(STATES states);
	void StartGameManager();
	bool QuitGame();
};

