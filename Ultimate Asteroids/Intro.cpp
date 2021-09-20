#include "Intro.h"

Intro::Intro() {
	InitWindow(screenWidth, screenHeight, "Ultimate Asteroid");
	InitAudioDevice();
	introLogoAudio = LoadMusicStream("hoho1.mp3");
	logoTexture = LoadTexture("gamingdummies.png");
	logo = new Textures();
	logoTexture.width = 600;
	logoTexture.height = 700;
	logo->SetTextureData(logoTexture, (screenWidth / 2) - (logoTexture.width / 2), (screenHeight / 2) - (logoTexture.height / 2), 600, 700);
	GM = new GameManager();
	isOn = true;
}

Intro::~Intro() {
	delete logo;
	delete GM;
	UnloadMusicStream(introLogoAudio);
	UnloadTexture(logoTexture);
}

void Intro::StartIntro() {
	PlayMusicStream(introLogoAudio);
	bool isPlaying;
	int timePlayed;
	int totalTime = GetMusicTimeLength(introLogoAudio);
	
	while (GetMusicTimePlayed(introLogoAudio)<4) {
		BeginDrawing();
		int timePlayed = GetMusicTimePlayed(introLogoAudio);
		UpdateMusicStream(introLogoAudio);
		ClearBackground(BLACK);		
		DrawTextureRec(logo->GetTexture(), logo->GetFrameRec(), logo->GetPosition(), WHITE);
		EndDrawing();
	}
	while (!WindowShouldClose() && isOn) {
			GM->StartGameManager();
			isOn = GM->QuitGame();
	}
}
