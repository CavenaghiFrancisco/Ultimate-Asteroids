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
	UnloadTexture(returnButtonTexture);
	UnloadTexture(creditsTexture);
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
	delete credits;
	delete returnButton;
}

void Menu::Init() {
	SetTargetFPS(60);
	InitAudioDevice();
	backgroundTexture = LoadTexture("background1.png");
	buttonTexture = LoadTexture("button.png");
	buttonPushedTexture = LoadTexture("button_pushed.png");
	titleTexture = LoadTexture("title.png");
	returnButtonTexture = LoadTexture("returnButton.png");
	creditsTexture = LoadTexture("credits1.png");
	menuSong = LoadMusicStream("menuSong.mp3");
	scrolling = 0.0f;
	menuInited = true;
	confirmation = LoadSound("confirmation.ogg");
	
}

void Menu::Input() {
	if (goToCredits) {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), returnButtonArea)) {
			goToCredits = false;
			PlaySound(confirmation);
		}
	}
	else {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), button0Area)) 	{
			goToGame = true;
			PlaySound(confirmation);
		}
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), button1Area)) {
			if (GetScreenWidth() == 1366) {
				SetWindowSize(1600, 900);
			}
			else {
				SetWindowSize(1366, 768);
			}
			PlaySound(confirmation);
		}
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), button2Area)) {
			goToCredits = true;
			PlaySound(confirmation);
		}
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), button3Area)) {
			exitGame = true;
			PlaySound(confirmation);
		}
	}
	PlayMusicStream(menuSong);
}

void Menu::Update() {
	UpdateMusicStream(menuSong);
	windowReSizeWidth = GetScreenWidth() / screenWidth;
	windowReSizeHeight = GetScreenHeight() / screenHeight;
	scrolling -= 0.5f;
	if (scrolling <= -backgroundTexture.width * 2) scrolling = 0;
	


	backgroundTexture.width = screenWidth;
	backgroundTexture.height = screenHeight  ;
	button0Area = { 525 * windowReSizeWidth  ,320 * windowReSizeHeight  ,320 * windowReSizeWidth  ,120 * windowReSizeHeight };


	backgroundColorTexture = { 0,0,(float)screenWidth*windowReSizeWidth  ,(float)screenHeight * windowReSizeHeight };
	button1Area = { 545 * windowReSizeWidth  ,485 * windowReSizeHeight  ,260 * windowReSizeWidth  ,60 * windowReSizeHeight };
	button2Area = { 545 * windowReSizeWidth  ,585 * windowReSizeHeight  ,260 * windowReSizeWidth ,60 * windowReSizeHeight };
	button3Area = { 545 * windowReSizeWidth  ,685 * windowReSizeHeight  ,260 * windowReSizeWidth  ,60 * windowReSizeHeight };

	

	returnButtonTexture.width = 100  ;
	returnButtonTexture.height = 50  ;

	creditsTexture.width = screenWidth * windowReSizeWidth;
	creditsTexture.height = screenHeight * windowReSizeHeight;
	returnButtonArea = { (screenWidth - (float)returnButtonTexture.width - 100) * windowReSizeWidth , (screenHeight - (float)returnButtonTexture.height - 50) * windowReSizeHeight   , ((float)returnButtonTexture.width) * windowReSizeWidth,(float)returnButtonTexture.height * windowReSizeHeight };






	background->SetTextureData(backgroundTexture, 0, 0, backgroundTexture.width * windowReSizeWidth, backgroundTexture.height * windowReSizeHeight);
	buttonTexture.width = 410;
	buttonTexture.height = 200;
	buttonPushedTexture.width = 410;
	buttonPushedTexture.height = 200;
	button0->SetTextureData(buttonTexture, ((screenWidth / 2) - (buttonTexture.width / 2)) * windowReSizeWidth, ((screenHeight / 2) - (buttonTexture.height / 2)) * windowReSizeHeight, buttonTexture.width * windowReSizeWidth, buttonTexture.height * windowReSizeHeight);
	button0Pushed->SetTextureData(buttonPushedTexture, ((screenWidth / 2) - (buttonTexture.width / 2)) * windowReSizeWidth, ((screenHeight / 2) - (buttonTexture.height / 2)) * windowReSizeHeight, buttonTexture.width * windowReSizeWidth, buttonPushedTexture.height * windowReSizeHeight);
	returnButton->SetTextureData(returnButtonTexture, (screenWidth - returnButtonTexture.width - 100) * windowReSizeWidth, (screenHeight - returnButtonTexture.height - 50) * windowReSizeHeight, returnButtonTexture.width * windowReSizeWidth, returnButtonTexture.height * windowReSizeHeight);
	buttonTexture.width = 310;
	buttonTexture.height = 100;
	buttonPushedTexture.width = 310;
	buttonPushedTexture.height = 100;
	button1->SetTextureData(buttonTexture, (((screenWidth / 2) - (buttonTexture.width / 2)) - 10) * windowReSizeWidth, ((screenHeight / 2) - (buttonTexture.height / 2) + 130) * windowReSizeHeight, 310 * windowReSizeWidth, 100 * windowReSizeHeight);
	button1Pushed->SetTextureData(buttonPushedTexture, ((screenWidth / 2) - (buttonTexture.width / 2) - 10) * windowReSizeWidth, ((screenHeight / 2) - (buttonTexture.height / 2) + 130) * windowReSizeHeight, 310 * windowReSizeWidth, 100 * windowReSizeHeight);
	button2->SetTextureData(buttonTexture, (((screenWidth / 2) - (buttonTexture.width / 2)) - 10) * windowReSizeWidth, ((screenHeight / 2) - (buttonTexture.height / 2) + 230) * windowReSizeHeight, 310 * windowReSizeWidth, 100 * windowReSizeHeight);
	button2Pushed->SetTextureData(buttonPushedTexture, ((screenWidth / 2) - (buttonTexture.width / 2) - 10) * windowReSizeWidth, ((screenHeight / 2) - (buttonTexture.height / 2) + 230) * windowReSizeHeight, 310 * windowReSizeWidth, 100 * windowReSizeHeight);
	button3->SetTextureData(buttonTexture, (((screenWidth / 2) - (buttonTexture.width / 2)) - 10) * windowReSizeWidth, ((screenHeight / 2) - (buttonTexture.height / 2) + 330) * windowReSizeHeight, 310 * windowReSizeWidth, 100 * windowReSizeHeight);
	button3Pushed->SetTextureData(buttonPushedTexture, ((screenWidth / 2) - (buttonTexture.width / 2) - 10) * windowReSizeWidth, ((screenHeight / 2) - (buttonTexture.height / 2) + 330) * windowReSizeHeight, 310 * windowReSizeWidth, 100 * windowReSizeHeight);
	title->SetTextureData(titleTexture, ((screenWidth / 2) - (titleTexture.width / 2)) * windowReSizeWidth, ((screenHeight * 1 / 4) - (titleTexture.height / 2)) * windowReSizeHeight, titleTexture.width*windowReSizeWidth, titleTexture.height*windowReSizeHeight);
	credits->SetTextureData(creditsTexture, 0, 0, creditsTexture.width, creditsTexture.height);
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
			DrawText("PLAY", 590 * windowReSizeWidth, 350*windowReSizeHeight, 70 * windowReSizeWidth, SKYBLUE);
		}
		else {
			DrawTextureRec(button0Pushed->GetTexture(), button0Pushed->GetFrameRec(), button0Pushed->GetPosition(), WHITE);
			DrawText("PLAY", 590 * windowReSizeWidth, 350 * windowReSizeHeight, 70 * windowReSizeWidth, DARKGRAY);
		}
		if (CheckCollisionPointRec(GetMousePosition(), button1Area)) {
			DrawTextureRec(button1->GetTexture(), button1->GetFrameRec(), button1->GetPosition(), WHITE);
			DrawText("RESOLUTION", 575 * windowReSizeWidth, 500 * windowReSizeHeight, 30 * windowReSizeWidth, SKYBLUE);
		}
		else {
			DrawTextureRec(button1Pushed->GetTexture(), button1Pushed->GetFrameRec(), button1Pushed->GetPosition(), WHITE);
			DrawText("RESOLUTION", 575 * windowReSizeWidth, 500 * windowReSizeHeight, 30 * windowReSizeWidth, DARKGRAY);
		}
		if (CheckCollisionPointRec(GetMousePosition(), button2Area)) {
			DrawTextureRec(button2->GetTexture(), button2->GetFrameRec(), button2->GetPosition(), WHITE);
			DrawText("CREDITS", 605 * windowReSizeWidth, 600 * windowReSizeHeight, 30 * windowReSizeWidth, SKYBLUE);
		}
		else {
			DrawTextureRec(button2Pushed->GetTexture(), button2Pushed->GetFrameRec(), button2Pushed->GetPosition(), WHITE);
			DrawText("CREDITS", 605 * windowReSizeWidth, 600 * windowReSizeHeight, 30 * windowReSizeWidth, DARKGRAY);
		}
		if (CheckCollisionPointRec(GetMousePosition(), button3Area)) {
			DrawTextureRec(button3->GetTexture(), button3->GetFrameRec(), button3->GetPosition(), WHITE);
			DrawText("EXIT", 630 * windowReSizeWidth, 700 * windowReSizeHeight, 30 * windowReSizeWidth, SKYBLUE);
		}
		else {
			DrawTextureRec(button3Pushed->GetTexture(), button3Pushed->GetFrameRec(), button3Pushed->GetPosition(), WHITE);
			DrawText("EXIT", 630 * windowReSizeWidth, 700 * windowReSizeHeight, 30 * windowReSizeWidth, DARKGRAY);
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


