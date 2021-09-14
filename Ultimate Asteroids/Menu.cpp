#include "Menu.h"

Menu::Menu() {
}

Menu::~Menu() {
}

void Menu::Init() {
	backgroundTexture = LoadTexture("background.png");

}

void Menu::Input() {
	
}

void Menu::Update() {
	
}

void Menu::Draw() {
	BeginDrawing();
	ClearBackground(RAYWHITE);
	
	EndDrawing();
}

bool Menu::GetInited() {
	return menuInited;
}


bool Menu::ExitMenuGoToGame() {
	return goToGame;
}

bool Menu::ExitMenuGoToShop() {
	return goToShop;
}

bool Menu::ExitMenuGoToCredits() {
	return goToCredits;
}

bool Menu::ExitMenuGoToOptions() {
	return goToOptions;
}

bool Menu::ExitGame() {
	return exitGame;
}

void Menu::DeInit() {
	menuInited = false;
}


