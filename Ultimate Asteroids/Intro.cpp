#include "Intro.h"

Intro::Intro() {
	InitWindow(screenWidth, screenHeight, "Ultimate Asteroid");
	InitAudioDevice();
	introLogoAudio = LoadMusicStream("hoho1.mp3");
	logoTexture = LoadTexture("gamingdummies.png");
	logo = new Textures();
	GM = new GameManager();
}

Intro::~Intro() {
	delete logo;
	UnloadMusicStream(introLogoAudio);
	UnloadTexture(logoTexture);
}

void Intro::StartIntro() {
	PlayMusicStream(introLogoAudio);
	bool isPlaying;
	int timePlayed;
	int totalTime = GetMusicTimeLength(introLogoAudio);
	logo->SetTextureData(logoTexture, screenWidth / 2 - logo->GetWidth() / 2, screenHeight / 2 - logo->GetHeight() / 2, 600, 700);
	DrawTextureRec(logo->GetTexture(), logo->GetFrameRec(), logo->GetPosition(), WHITE);
	while (GetMusicTimePlayed(introLogoAudio)<4) {
		BeginDrawing();
		int timePlayed = GetMusicTimePlayed(introLogoAudio);
		UpdateMusicStream(introLogoAudio);
		ClearBackground(BLACK);
		EndDrawing();
	}
	GM->StartGameManager();
}
