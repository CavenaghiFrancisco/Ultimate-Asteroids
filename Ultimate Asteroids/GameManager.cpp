#include "GameManager.h"
#include <iostream>



GameManager::GameManager() {
	isPlaying = true;
}

GameManager::~GameManager() {
}

STATES GameManager::GetState() {
	return currentState;
}

void GameManager::SetState(STATES& states) {
	currentState = states;
}

bool GameManager::ChangeState(STATES states) {
	if (currentState == states) {
		return false;
	}
	else {
		SetState(states);
		return true;
	}
}



void GameManager::StartGameManager() {
	UpdateState(GetState());
}

bool GameManager::QuitGame() {
	return isPlaying;
}

void GameManager::UpdateState(STATES states) {
	switch (GetState()) {
	case STATES::MENU:
		if (isThisStateStarting) {
			menu = new Menu();
			isThisStateStarting = false;
		}
		if (!(menu->GetInited())) {
			menu->Init();
		}
		menu->Input();
		menu->Update();
		menu->Draw();
		if (menu->ExitMenuGoToGame()) {
			currentState = STATES::GAME;
			menu->DeInit();
			delete menu;
			isThisStateStarting = true;
		}
		else if (menu->ExitGame()) {
			currentState = STATES::EXIT;
			menu->DeInit();
			delete menu;
			isThisStateStarting = true;
		}
		break;
	case STATES::GAME:
		if (isThisStateStarting) {
			game = new Game();
			isThisStateStarting = false;
		}
		if (!(game->GetInited())) {
			game->InitGame();
		}
		game->UpdateDrawFrame();
		if (game->GoToMenu()) {
			currentState = STATES::MENU;
			game->DeInitGame();
			delete game;
			isThisStateStarting = true;
		}
		break;
	/*case STATES::SHOP:
		break;*/
	case STATES::EXIT:
		isPlaying = false;
		break;
	default:
		break;
	}
}
