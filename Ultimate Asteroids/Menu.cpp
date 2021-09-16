#include "Menu.h"

Menu::Menu() {
	menuInited = false;
}

Menu::~Menu() {
}

void Menu::Init() {
	SetTargetFPS(60);
	font = LoadFont("resources/fonts/pixantiqua.png");
	backgroundTexture = LoadTexture("background1.png");
	backgroundTexture.width = GetScreenWidth();
	backgroundTexture.height = GetScreenHeight();
	//button0Area = { 525,320,320,120 };
	buttonTexture = LoadTexture("button.png");
	buttonTexture.width = 410;
	buttonTexture.height = 200;
	button0Area = { (screenWidth / 2) - (buttonTexture.width / 2)+40, (screenHeight / 2) - (buttonTexture.height / 2)+30,410-80,200-60 };
	buttonPushedTexture = LoadTexture("button_pushed.png");
	buttonTexture.width = 400;
	buttonPushedTexture.height = 200;
	button0Pushed = new Textures();
	background = new Textures();
	button0 = new Textures;
	background->SetTextureData(backgroundTexture, 0, 0, backgroundTexture.width, backgroundTexture.height);
	button0->SetTextureData(buttonTexture, (screenWidth / 2) - (buttonTexture.width / 2), (screenHeight / 2) - (buttonTexture.height / 2), buttonTexture.width, buttonTexture.height);
	button0Pushed->SetTextureData(buttonPushedTexture, (screenWidth / 2) - (buttonTexture.width / 2), (screenHeight / 2) - (buttonTexture.height / 2), buttonTexture.width, buttonPushedTexture.height);
	scrolling = 0.0f;
	menuInited = true;
}

void Menu::Input() {
	
}

void Menu::Update() {
	scrolling -= 0.5f;
	if (scrolling <= -backgroundTexture.width * 2) scrolling = 0;
}

void Menu::Draw() {
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawTextureEx(backgroundTexture, { scrolling, 0 }, 0.0f, 2.0f, WHITE);
	DrawTextureEx(backgroundTexture, { backgroundTexture.width * 2 + scrolling, 0 }, 0.0f, 2.0f, WHITE);
	/*DrawRectangleRec(button0Area, RED);*/
	if (CheckCollisionPointRec(GetMousePosition(), button0Area)) {
		DrawTextureRec(button0->GetTexture(), button0->GetFrameRec(), button0->GetPosition(), WHITE);
		DrawText("PLAY", 590,350, 70, SKYBLUE);
	}
	else {
		DrawTextureRec(button0Pushed->GetTexture(), button0Pushed->GetFrameRec(), button0Pushed->GetPosition(), WHITE);
		DrawText("PLAY", 590, 350, 70, DARKGRAY);
	}
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


