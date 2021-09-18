#include "Menu.h"

Menu::Menu() {
	menuInited = false;
	goToGame = false;
	goToCredits = false;
	backgroundColor ={ (unsigned char)(GetRandomValue(0, 255)),(unsigned char)GetRandomValue(0, 255) , (unsigned char)GetRandomValue(0, 255) , 40 };
	title = new Textures();
	button0Pushed = new Textures();
	button1Pushed = new Textures();
	button2Pushed = new Textures();
	button3Pushed = new Textures();
	background = new Textures();
	button0 = new Textures;
	button1 = new Textures;
	button2 = new Textures;
	button3 = new Textures;
	credits = new Textures;
	returnButton = new Textures;
}

Menu::~Menu() {
	UnloadTexture(backgroundTexture);
	UnloadTexture(buttonPushedTexture);
	UnloadTexture(buttonTexture);
	UnloadTexture(titleTexture);
	UnloadTexture(buttonTexture);
	UnloadTexture(buttonTexture);
	UnloadTexture(buttonTexture);
	delete title;
	delete button0Pushed;
	delete button1Pushed;
	delete button2Pushed;
	delete button3Pushed;
	delete background;
	delete button0;
	delete button1;
	delete button2;
	delete button3;
}

void Menu::Init() {
	SetTargetFPS(60);
	backgroundTexture = LoadTexture("background1.png");
	backgroundTexture.width = GetScreenWidth();
	backgroundTexture.height = GetScreenHeight();
	button0Area = { 525,320,320,120 };
	buttonTexture = LoadTexture("button.png");
	buttonTexture.width = 410;
	buttonTexture.height = 200;
	button0Area = { (screenWidth / 2) - (buttonTexture.width / 2)+40, (screenHeight / 2) - (buttonTexture.height / 2)+30,410-80,200-60 };
	buttonPushedTexture = LoadTexture("button_pushed.png");
	buttonPushedTexture.width = 410;
	buttonPushedTexture.height = 200;
	titleTexture = LoadTexture("title.png");
	backgroundColorTexture = { 0,0,(float)GetScreenWidth(),(float)GetScreenHeight() };
	button1Area = { 545,485,260,60 };
	button2Area = { 545,585,260,60 };
	button3Area = { 545,685,260,60 };
	background->SetTextureData(backgroundTexture, 0, 0, backgroundTexture.width, backgroundTexture.height);
	button0->SetTextureData(buttonTexture, (screenWidth / 2) - (buttonTexture.width / 2), (screenHeight / 2) - (buttonTexture.height / 2), buttonTexture.width, buttonTexture.height);
	button0Pushed->SetTextureData(buttonPushedTexture, (screenWidth / 2) - (buttonTexture.width / 2), (screenHeight / 2) - (buttonTexture.height / 2), buttonTexture.width, buttonPushedTexture.height);
	buttonTexture.width = 310;
	buttonTexture.height = 100;
	buttonPushedTexture.width = 310;
	buttonPushedTexture.height = 100;
	returnButtonTexture = LoadTexture("returnButton.png");
	returnButtonTexture.width = 100;
	returnButtonTexture.height = 50;
	creditsTexture = LoadTexture("credits1.png");
	creditsTexture.width = screenWidth;
	creditsTexture.height = screenHeight;
	returnButtonArea = { GetScreenWidth() - (float)returnButtonTexture.width - 100, GetScreenHeight() - (float)returnButtonTexture.height - 50 , (float)returnButtonTexture.width,(float)returnButtonTexture.height };
	returnButton->SetTextureData(returnButtonTexture, GetScreenWidth() - returnButtonTexture.width-100, GetScreenHeight() - returnButtonTexture.height-50, returnButtonTexture.width, returnButtonTexture.height);
	button1->SetTextureData(buttonTexture, ((screenWidth / 2)- (buttonTexture.width / 2)) - 10, (screenHeight / 2) - (buttonTexture.height / 2)+130,310,100);
	button1Pushed->SetTextureData(buttonPushedTexture, (screenWidth / 2) - (buttonTexture.width / 2)-10, (screenHeight / 2) - (buttonTexture.height / 2)+130, 310, 100);
	button2->SetTextureData(buttonTexture, ((screenWidth / 2) - (buttonTexture.width / 2)) - 10, (screenHeight / 2) - (buttonTexture.height / 2) + 230, 310, 100);
	button2Pushed->SetTextureData(buttonPushedTexture, (screenWidth / 2) - (buttonTexture.width / 2) - 10, (screenHeight / 2) - (buttonTexture.height / 2) + 230, 310, 100);
	button3->SetTextureData(buttonTexture, ((screenWidth / 2) - (buttonTexture.width / 2)) - 10, (screenHeight / 2) - (buttonTexture.height / 2) + 330, 310, 100);
	button3Pushed->SetTextureData(buttonPushedTexture, (screenWidth / 2) - (buttonTexture.width / 2) - 10, (screenHeight / 2) - (buttonTexture.height / 2) + 330, 310, 100);
	title->SetTextureData(titleTexture, (screenWidth / 2) - (titleTexture.width / 2), (screenHeight *1/4) - (titleTexture.height / 2), titleTexture.width, titleTexture.height);
	credits->SetTextureData(creditsTexture, 0, 0, creditsTexture.width, creditsTexture.height);
	scrolling = 0.0f;
	menuInited = true;
}

void Menu::Input() {
	if (goToCredits) {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), returnButtonArea)) {
			goToCredits = false;
		}
	}
	else {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), button0Area)) 	{
			goToGame = true;
		}
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), button2Area)) {
			goToCredits = true;
		}
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), button3Area)) {
			exitGame = true;
		}
	}
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
		DrawRectangle(backgroundColorTexture.x, backgroundColorTexture.y, backgroundColorTexture.width, backgroundColorTexture.height, backgroundColor);
	if (!goToCredits) {
		DrawTextureRec(title->GetTexture(), title->GetFrameRec(), title->GetPosition(), WHITE);
		if (CheckCollisionPointRec(GetMousePosition(), button0Area)) {
			DrawTextureRec(button0->GetTexture(), button0->GetFrameRec(), button0->GetPosition(), WHITE);
			DrawText("PLAY", 590, 350, 70, SKYBLUE);
		}
		else {
			DrawTextureRec(button0Pushed->GetTexture(), button0Pushed->GetFrameRec(), button0Pushed->GetPosition(), WHITE);
			DrawText("PLAY", 590, 350, 70, DARKGRAY);
		}
		if (CheckCollisionPointRec(GetMousePosition(), button1Area)) {
			DrawTextureRec(button1->GetTexture(), button1->GetFrameRec(), button1->GetPosition(), WHITE);
			DrawText("RESOLUTION", 575, 500, 30, SKYBLUE);
		}
		else {
			DrawTextureRec(button1Pushed->GetTexture(), button1Pushed->GetFrameRec(), button1Pushed->GetPosition(), WHITE);
			DrawText("RESOLUTION", 575, 500, 30, DARKGRAY);
		}
		if (CheckCollisionPointRec(GetMousePosition(), button2Area)) {
			DrawTextureRec(button2->GetTexture(), button2->GetFrameRec(), button2->GetPosition(), WHITE);
			DrawText("CREDITS", 605, 600, 30, SKYBLUE);
		}
		else {
			DrawTextureRec(button2Pushed->GetTexture(), button2Pushed->GetFrameRec(), button2Pushed->GetPosition(), WHITE);
			DrawText("CREDITS", 605, 600, 30, DARKGRAY);
		}
		if (CheckCollisionPointRec(GetMousePosition(), button3Area)) {
			DrawTextureRec(button3->GetTexture(), button3->GetFrameRec(), button3->GetPosition(), WHITE);
			DrawText("EXIT", 630, 700, 30, SKYBLUE);
		}
		else {
			DrawTextureRec(button3Pushed->GetTexture(), button3Pushed->GetFrameRec(), button3Pushed->GetPosition(), WHITE);
			DrawText("EXIT", 630, 700, 30, DARKGRAY);
		}
	}
	else{
		//DrawRectangle(returnButtonArea.x, returnButtonArea.y, returnButtonArea.width, returnButtonArea.height,RED);
		DrawTextureRec(credits->GetTexture(), credits->GetFrameRec(), credits->GetPosition(), WHITE);
		DrawTextureRec(returnButton->GetTexture(), returnButton->GetFrameRec(), returnButton->GetPosition(), WHITE);
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


