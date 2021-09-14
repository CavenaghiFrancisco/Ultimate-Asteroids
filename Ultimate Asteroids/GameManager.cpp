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
		break;
	case STATES::GAME:
		break;
	case STATES::SHOP:
		break;
	case STATES::EXIT:
		isPlaying = false;
		break;
	default:
		break;
	}
}
