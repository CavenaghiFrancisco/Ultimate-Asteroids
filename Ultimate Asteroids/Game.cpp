#include "Game.h"
#include <math.h>



const int maxBigMeteors = 1;
const int maxMediumMeteors = maxBigMeteors * 2;
const int maxSmallMeteors = maxMediumMeteors * 2;
const int meteorSpeed = 30;
struct Meteor {
    Vector2 position;
    Vector2 speed;
    float rotation;
    float radius;
    bool active;
    Color color;
};

bool gameOver = false;
bool pause = false;
bool victory = false;
 
Meteor bigMeteor[maxBigMeteors] = { 0 };
Meteor mediumMeteor[maxMediumMeteors] = { 0 };
Meteor smallMeteor[maxSmallMeteors] = { 0 };

int midMeteorsCount = 0;
int smallMeteorsCount = 0;
int destroyedMeteorsCount = 0;




Game::Game() {
    gameInited = false;
}

Game::~Game() {

}

bool Game::GetInited() {
    return gameInited;
}

void Game::InitGame() {
    HideCursor();
    shieldPowerUp = { {(float)GetRandomValue(100,(GetScreenHeight() - 100)),(float)GetRandomValue(100,GetScreenHeight() - 100)},60,false,false };
    moreBulletsPowerUp = { {(float)GetRandomValue(100,(GetScreenHeight() - 100)),(float)GetRandomValue(100,GetScreenHeight() - 100)},60,false,false };
    backgroundColorTexture = { 0,0,(float)GetScreenWidth(),(float)GetScreenHeight() };
    int posx, posy;
    int velx, vely;
    bool correctRange = false;
    victory = false;
    pause = false;
    timerPowerUp = 0.0f;
    player = new Player();
    backgroundGame = new Textures();
    ship = new Textures();
    bigMeteors = new Textures();
    mediumMeteors = new Textures();
    smallMeteors = new Textures();
    sight = new Textures();
    moreBullets = new Textures();
    shield = new Textures();
    rightClick = new Textures();
    leftClick = new Textures();
    buttonPause = new Textures();
    buttonResumePlayAgain = new Textures();
    buttonMenuExit = new Textures();
    // Initialization player

    destroyedMeteorsCount = 0;

    // Initialization shoot
    for (int i = 0; i < player->playerMaxShoots; i++) {
        shoots[i] = new Shoot();
    }

    for (int i = 0; i < maxBigMeteors; i++) {
        posx = GetRandomValue(0, screenWidth);

        while (!correctRange) {
            if (posx > screenWidth / 2 - 150 && posx < screenWidth / 2 + 150) posx = GetRandomValue(0, screenWidth);
            else correctRange = true;
        }

        correctRange = false;

        posy = GetRandomValue(0, screenHeight);

        while (!correctRange) {
            if (posy > screenHeight / 2 - 150 && posy < screenHeight / 2 + 150)  posy = GetRandomValue(0, screenHeight);
            else correctRange = true;
        }

        bigMeteor[i].position = { (float)posx, (float)posy };

        correctRange = false;
        velx = GetRandomValue(-meteorSpeed, meteorSpeed);
        vely = GetRandomValue(-meteorSpeed, meteorSpeed);

        while (!correctRange) {
            if (velx == 0 && vely == 0) {
                velx = GetRandomValue(-meteorSpeed, meteorSpeed);
                vely = GetRandomValue(-meteorSpeed, meteorSpeed);
            }
            else correctRange = true;
        }

        bigMeteor[i].speed = { (float)velx * GetFrameTime(), (float)vely * GetFrameTime() };
        bigMeteor[i].radius = 60;
        bigMeteor[i].active = true;
        bigMeteor[i].rotation = GetRandomValue(0,340);
        bigMeteor[i].color = BLUE;
    }

    for (int i = 0; i < maxMediumMeteors; i++) {
        mediumMeteor[i].position = { -100, -100 };
        mediumMeteor[i].speed = { 0,0 };
        mediumMeteor[i].radius = 40;
        mediumMeteor[i].active = false;
        mediumMeteor[i].color = BLUE;
        mediumMeteor[i].rotation = GetRandomValue(0, 340);
    }

    for (int i = 0; i < maxSmallMeteors; i++) {
        smallMeteor[i].position = { -100, -100 };
        smallMeteor[i].speed = { 0,0 };
        smallMeteor[i].radius = 20;
        smallMeteor[i].active = false;
        smallMeteor[i].color = BLUE;
        smallMeteor[i].rotation = GetRandomValue(0, 340);
    }

    midMeteorsCount = 0;
    smallMeteorsCount = 0;
    gameInited = true;
    scrolling = 0;
    sightTexture = LoadTexture("sight.png");
    sightTexture.width = 30;
    sightTexture.height = 30;
    backgroundGameTexture = LoadTexture("background1.png");
    backgroundGameTexture.width = GetScreenWidth();
    backgroundGameTexture.height = GetScreenHeight();
    backgroundGame->SetTextureData(backgroundGameTexture, 0, 0, backgroundGame->GetWidth(), backgroundGame->GetHeight());
    shipTexture = LoadTexture("Lv3.png");
    shipTexture.width = player->GetRadius();
    shipTexture.height = player->GetRadius();
    bigMeteorsTexture = LoadTexture("meteors0.png");
    bigMeteorsTexture.width = bigMeteor->radius;
    bigMeteorsTexture.height = bigMeteor->radius;
    mediumMeteorsTexture = LoadTexture("meteors1.png");
    mediumMeteorsTexture.width = mediumMeteor->radius;
    mediumMeteorsTexture.height =mediumMeteor->radius;
    smallMeteorsTexture = LoadTexture("meteors2.png");
    smallMeteorsTexture.width = smallMeteor->radius;
    smallMeteorsTexture.height = smallMeteor->radius;
    shieldTexture = LoadTexture("shieldPowerUp.png");
    shieldTexture.width = 60;
    shieldTexture.height = 60;
    shield->SetTextureData(shieldTexture, shieldPowerUp.position.x, shieldPowerUp.position.y, shieldTexture.width, shieldTexture.height);
    moreBulletsTexture = LoadTexture("moreBulletsPowerUp.png");
    moreBulletsTexture.width = 60;
    moreBulletsTexture.height = 60;
    moreBullets->SetTextureData(moreBulletsTexture, moreBulletsPowerUp.position.x, moreBulletsPowerUp.position.y, moreBulletsTexture.width, moreBulletsTexture.height);
    rightClickTexture = LoadTexture("rightClick.png");
    rightClickTexture.width = 80;
    rightClickTexture.height = 80;
    rightClick->SetTextureData(rightClickTexture, GetScreenWidth() / 2 + 20, GetScreenHeight() - rightClickTexture.height - 20, rightClickTexture.width, rightClickTexture.height);
    leftClickTexture = LoadTexture("leftClick.png");
    leftClickTexture.width = 80;
    leftClickTexture.height = 80;
    leftClick->SetTextureData(leftClickTexture, GetScreenWidth() / 2 - leftClickTexture.width -20, GetScreenHeight() - leftClickTexture.height - 20, leftClickTexture.width, leftClickTexture.height);
    buttonPauseTexture = LoadTexture("pause.png");
    buttonPauseTexture.width = 100;
    buttonPauseTexture.height = 100;
    buttonTexture = LoadTexture("button.png");
    buttonTexture.width = 310;
    buttonTexture.height = 100;
    buttonPushedTexture = LoadTexture("button_pushed.png");
    buttonPushedTexture.width = 310;
    buttonPushedTexture.height = 100;
    buttonPause->SetTextureData(buttonPauseTexture, GetScreenWidth() - buttonPauseTexture.width, 0, buttonPauseTexture.width, buttonPauseTexture.height);
    buttonP = { buttonPause->GetPosition().x,buttonPause->GetPosition().y ,(float)buttonPause->GetWidth() ,(float)buttonPause->GetHeight() };
    buttonResumePlayAgain->SetTextureData(buttonPushedTexture, GetScreenWidth()/2 - buttonTexture.width - 20, GetScreenHeight()/2 + 50, buttonTexture.width, buttonTexture.height);
    buttonMenuExit->SetTextureData(buttonPushedTexture, GetScreenWidth() / 2 + 20, GetScreenHeight() / 2 + 50, buttonTexture.width, buttonTexture.height);
    buttonResumeArea = { buttonResumePlayAgain->GetPosition().x,buttonResumePlayAgain->GetPosition().y,(float)buttonResumePlayAgain->GetWidth(),(float)buttonResumePlayAgain->GetHeight() };
    buttonExitArea = { buttonMenuExit->GetPosition().x,buttonMenuExit->GetPosition().y,(float)buttonMenuExit->GetWidth(),(float)buttonMenuExit->GetHeight() };


}

void Game::InputGame() {
    if (victory) {
        if (IsKeyPressed(KEY_ENTER)) {
            goToMenu = true;
        }
    }
}



void Game::UpdateGame() {
    if (!gameOver) {
        if (CheckCollisionPointRec(GetMousePosition(), buttonP) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !victory) {
            pause = !pause;
        }
        if (!pause) {

            timerPowerUp += GetFrameTime();
            if (timerPowerUp > 5 && !moreBulletsPowerUp.active && !moreBulletsPowerUp.alreadySpawned) {
                moreBulletsPowerUp.active = true;
                moreBulletsPowerUp.alreadySpawned = true;
            }
            if (timerPowerUp > 10 && !shieldPowerUp.active && !shieldPowerUp.alreadySpawned) {
                shieldPowerUp.active = true;
                shieldPowerUp.alreadySpawned = true;
            }
            scrolling -= 0.5f;
            if (scrolling <= -backgroundGameTexture.width * 2) scrolling = 0;
            ship->SetTextureData(shipTexture, player->GetPosition().x - player->GetRadius() / 2, player->GetPosition().y - player->GetRadius() / 2, player->GetRadius(), player->GetRadius());
            // Player logic: movement
            player->Movement();

            //Collision logic: player vs walls
            if (player->GetPosition().x > screenWidth + player->GetRadius()) player->SetPositionX(-(player->GetRadius()));
            else if (player->GetPosition().x < -(player->GetRadius())) player->SetPositionX(screenWidth + player->GetRadius());
            if (player->GetPosition().y > (screenHeight + player->GetRadius())) player->SetPositionY(-(player->GetRadius()));
            else if (player->GetPosition().y < -(player->GetRadius())) player->SetPositionY(screenHeight + player->GetRadius());

            // Player shoot logic
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (player->Vector2Length(player->Vector2Subtract(GetMousePosition(), player->GetPosition())) > 30.0f) {
                    player->SetRotation(player->Vector2Angle(player->GetPosition(), GetMousePosition()) + 90);
                }
                for (int i = 0; i < (player->GetBullets() ? player->playerMaxShoots : player->playerMaxShoots / 2); i++) {
                    if (!shoots[i]->GetActive()) {
                        shoots[i]->SetPositionX(player->GetPosition().x + (float)sin(player->GetRotation() * DEG2RAD) * (player->GetRadius()));
                        shoots[i]->SetPositionY(player->GetPosition().y - (float)cos(player->GetRotation() * DEG2RAD) * (player->GetRadius()));
                        shoots[i]->SetActive(true);
                        shoots[i]->SetSpeedX(1.5 * (float)sin(player->GetRotation() * DEG2RAD) * player->playerSpeed);
                        shoots[i]->SetSpeedY(1.5 * (float)cos(player->GetRotation() * DEG2RAD) * player->playerSpeed);
                        shoots[i]->SetRotation(player->GetRotation());
                        break;
                    };

                }
            }


            // Shoot life timer
            for (int i = 0; i < (player->GetBullets() ? player->playerMaxShoots : player->playerMaxShoots / 2); i++) {
                shoots[i]->LifeTimer();
            }

            // Shot logic
            for (int i = 0; i < (player->GetBullets() ? player->playerMaxShoots : player->playerMaxShoots / 2); i++) {
                shoots[i]->Shot();
            }



            // Collision logic: player vs meteors

            if (CheckCollisionCircles({ player->GetPosition().x, player->GetPosition().y }, player->GetRadius(), shieldPowerUp.position, shieldPowerUp.radius) && shieldPowerUp.active) {
                player->SetShield(true);
                shieldPowerUp.active = false;
            }

            if (CheckCollisionCircles({ player->GetPosition().x, player->GetPosition().y }, player->GetRadius(), moreBulletsPowerUp.position, moreBulletsPowerUp.radius) && moreBulletsPowerUp.active) {
                player->SetBullets(true);
                moreBulletsPowerUp.active = false;
            }

            for (int a = 0; a < maxBigMeteors; a++) {
                if (CheckCollisionCircles({ player->GetPosition().x, player->GetPosition().y }, player->GetRadius(), bigMeteor[a].position, bigMeteor[a].radius) && bigMeteor[a].active && !player->GetShield()) gameOver = true;
                else if (CheckCollisionCircles({ player->GetPosition().x, player->GetPosition().y }, player->GetRadius(), bigMeteor[a].position, bigMeteor[a].radius) && bigMeteor[a].active && player->GetShield()) {
                    bigMeteor[a].active = false;
                    destroyedMeteorsCount += 7;
                    player->SetShield(false);
                }
            }

            for (int a = 0; a < maxMediumMeteors; a++) {
                if (CheckCollisionCircles({ player->GetPosition().x,  player->GetPosition().y }, player->GetRadius(), mediumMeteor[a].position, mediumMeteor[a].radius) && mediumMeteor[a].active && !player->GetShield()) gameOver = true;
                else if (CheckCollisionCircles({ player->GetPosition().x, player->GetPosition().y }, player->GetRadius(), mediumMeteor[a].position, mediumMeteor[a].radius) && mediumMeteor[a].active && player->GetShield()) {
                    mediumMeteor[a].active = false;
                    destroyedMeteorsCount += 3;
                    player->SetShield(false);
                }
            }
            for (int a = 0; a < maxSmallMeteors; a++) {
                if (CheckCollisionCircles({ player->GetPosition().x,  player->GetPosition().y }, player->GetRadius(), smallMeteor[a].position, smallMeteor[a].radius) && smallMeteor[a].active && !player->GetShield()) gameOver = true;
                else if (CheckCollisionCircles({ player->GetPosition().x, player->GetPosition().y }, player->GetRadius(), smallMeteor[a].position, smallMeteor[a].radius) && smallMeteor[a].active && player->GetShield()) {
                    smallMeteor[a].active = false;
                    destroyedMeteorsCount += 1;
                    player->SetShield(false);
                }
            }

            // Meteors logic: big meteors
            for (int i = 0; i < maxBigMeteors; i++) {
                if (bigMeteor[i].active) {
                    // Movement
                    bigMeteor[i].position.x += bigMeteor[i].speed.x;
                    bigMeteor[i].position.y += bigMeteor[i].speed.y;

                    // Collision logic: meteor vs wall
                    if (bigMeteor[i].position.x > screenWidth + bigMeteor[i].radius) bigMeteor[i].position.x = -(bigMeteor[i].radius);
                    else if (bigMeteor[i].position.x < 0 - bigMeteor[i].radius) bigMeteor[i].position.x = screenWidth + bigMeteor[i].radius;
                    if (bigMeteor[i].position.y > screenHeight + bigMeteor[i].radius) bigMeteor[i].position.y = -(bigMeteor[i].radius);
                    else if (bigMeteor[i].position.y < 0 - bigMeteor[i].radius) bigMeteor[i].position.y = screenHeight + bigMeteor[i].radius;
                }
            }

            // Meteors logic: medium meteors
            for (int i = 0; i < maxMediumMeteors; i++) {
                if (mediumMeteor[i].active) {
                    // Movement
                    mediumMeteor[i].position.x += mediumMeteor[i].speed.x * 3;
                    mediumMeteor[i].position.y += mediumMeteor[i].speed.y * 3;

                    // Collision logic: meteor vs wall
                    if (mediumMeteor[i].position.x > screenWidth + mediumMeteor[i].radius) mediumMeteor[i].position.x = -(mediumMeteor[i].radius);
                    else if (mediumMeteor[i].position.x < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.x = screenWidth + mediumMeteor[i].radius;
                    if (mediumMeteor[i].position.y > screenHeight + mediumMeteor[i].radius) mediumMeteor[i].position.y = -(mediumMeteor[i].radius);
                    else if (mediumMeteor[i].position.y < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.y = screenHeight + mediumMeteor[i].radius;
                }
            }

            // Meteors logic: small meteors
            for (int i = 0; i < maxSmallMeteors; i++) {
                if (smallMeteor[i].active) {
                    // Movement
                    smallMeteor[i].position.x += smallMeteor[i].speed.x * 5;
                    smallMeteor[i].position.y += smallMeteor[i].speed.y * 5;

                    // Collision logic: meteor vs wall
                    if (smallMeteor[i].position.x > screenWidth + smallMeteor[i].radius) smallMeteor[i].position.x = -(smallMeteor[i].radius);
                    else if (smallMeteor[i].position.x < 0 - smallMeteor[i].radius) smallMeteor[i].position.x = screenWidth + smallMeteor[i].radius;
                    if (smallMeteor[i].position.y > screenHeight + smallMeteor[i].radius) smallMeteor[i].position.y = -(smallMeteor[i].radius);
                    else if (smallMeteor[i].position.y < 0 - smallMeteor[i].radius) smallMeteor[i].position.y = screenHeight + smallMeteor[i].radius;
                }
            }

            // Collision logic: player-shoots vs meteors
            for (int i = 0; i < (player->GetBullets() ? player->playerMaxShoots : player->playerMaxShoots / 2); i++) {
                if ((shoots[i]->GetActive())) {
                    for (int a = 0; a < maxBigMeteors; a++) {
                        if (bigMeteor[a].active && CheckCollisionCircles(shoots[i]->GetPosition(), shoots[i]->GetRadius(), bigMeteor[a].position, bigMeteor[a].radius)) {
                            shoots[i]->SetActive(false);
                            shoots[i]->SetLifeSpawn(0);
                            bigMeteor[a].active = false;
                            destroyedMeteorsCount++;

                            for (int j = 0; j < 2; j++) {
                                if (midMeteorsCount % 2 == 0) {
                                    mediumMeteor[midMeteorsCount].position = { bigMeteor[a].position.x, bigMeteor[a].position.y };
                                    mediumMeteor[midMeteorsCount].speed = { (float)cos(shoots[i]->GetRotation() * DEG2RAD) * meteorSpeed * -1 * GetFrameTime(), (float)sin(shoots[i]->GetRotation() * DEG2RAD) * meteorSpeed * -1 * GetFrameTime() };
                                }
                                else {
                                    mediumMeteor[midMeteorsCount].position = { bigMeteor[a].position.x, bigMeteor[a].position.y };
                                    mediumMeteor[midMeteorsCount].speed = { (float)cos(shoots[i]->GetRotation() * DEG2RAD) * meteorSpeed * GetFrameTime(), (float)sin(shoots[i]->GetRotation() * DEG2RAD) * meteorSpeed * GetFrameTime() };
                                }

                                mediumMeteor[midMeteorsCount].active = true;
                                midMeteorsCount++;
                            }
                            bigMeteor[a].color = RED;
                            a = maxBigMeteors;
                        }
                    }

                    for (int b = 0; b < maxMediumMeteors; b++) {
                        if (mediumMeteor[b].active && CheckCollisionCircles(shoots[i]->GetPosition(), shoots[i]->GetRadius(), mediumMeteor[b].position, mediumMeteor[b].radius)) {
                            shoots[i]->SetActive(false);
                            shoots[i]->SetLifeSpawn(0);
                            mediumMeteor[b].active = false;
                            destroyedMeteorsCount++;

                            for (int j = 0; j < 2; j++) {
                                if (smallMeteorsCount % 2 == 0) {
                                    smallMeteor[smallMeteorsCount].position = { mediumMeteor[b].position.x, mediumMeteor[b].position.y };
                                    smallMeteor[smallMeteorsCount].speed = { (float)cos(shoots[i]->GetRotation() * DEG2RAD) * meteorSpeed * -1 * GetFrameTime(), (float)sin(shoots[i]->GetRotation() * DEG2RAD) * meteorSpeed * -1 * GetFrameTime() };
                                }
                                else {
                                    smallMeteor[smallMeteorsCount].position = { mediumMeteor[b].position.x, mediumMeteor[b].position.y };
                                    smallMeteor[smallMeteorsCount].speed = { (float)cos(shoots[i]->GetRotation() * DEG2RAD) * meteorSpeed * GetFrameTime(), (float)sin(shoots[i]->GetRotation() * DEG2RAD) * meteorSpeed * GetFrameTime() };
                                }

                                smallMeteor[smallMeteorsCount].active = true;
                                smallMeteorsCount++;
                            }
                            mediumMeteor[b].color = GREEN;
                            b = maxMediumMeteors;
                        }
                    }

                    for (int c = 0; c < maxSmallMeteors; c++) {
                        if (smallMeteor[c].active && CheckCollisionCircles(shoots[i]->GetPosition(), shoots[i]->GetRadius(), smallMeteor[c].position, smallMeteor[c].radius)) {
                            shoots[i]->SetActive(false);
                            shoots[i]->SetLifeSpawn(0);
                            smallMeteor[c].active = false;
                            destroyedMeteorsCount++;
                            smallMeteor[c].color = YELLOW;
                            c = maxSmallMeteors;
                        }
                    }
                }
            }
        }
    }
        if (destroyedMeteorsCount == maxBigMeteors + maxMediumMeteors + maxSmallMeteors) {
            victory = true;
        }
        else {
            if (IsKeyPressed(KEY_ENTER)) {
                InitGame();
                gameOver = false;
            }
        }
    
}

void Game::DrawGame() {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawTextureEx(backgroundGameTexture, { scrolling, 0 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(backgroundGameTexture, { backgroundGameTexture.width * 2 + scrolling, 0 }, 0.0f, 2.0f, WHITE);
    DrawRectangle(backgroundColorTexture.x, backgroundColorTexture.y, backgroundColorTexture.width, backgroundColorTexture.height, backgroundGameColor);

    if (!gameOver) {
        // Draw spaceship
        DrawTexturePro(shipTexture, ship->GetFrameRec(), { player->GetPosition().x,  player->GetPosition().y, (float)shipTexture.width *2.0f , (float)shipTexture.height * 2.0f }, { (float)shipTexture.width,(float)shipTexture.height }, player->GetRotation(), WHITE);
        // Draw meteors
        for (int i = 0; i < maxBigMeteors; i++) {
            bigMeteors->SetTextureData(bigMeteorsTexture, bigMeteor[i].position.x, bigMeteor[i].position.y , bigMeteor->radius, bigMeteor->radius);
            if (bigMeteor[i].active) {
                //DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, DARKGRAY);
                DrawTexturePro(bigMeteorsTexture, bigMeteors->GetFrameRec(), { bigMeteors->GetPosition().x,  bigMeteors->GetPosition().y, (float)bigMeteorsTexture.width * 2.0f , (float)bigMeteorsTexture.height * 2.0f }, { (float)bigMeteorsTexture.width,(float)bigMeteorsTexture.height }, bigMeteor[i].rotation >= 360 ? bigMeteor[i].rotation = 0 : bigMeteor[i].rotation += 1, WHITE);
            }
        }

        for (int i = 0; i < maxMediumMeteors; i++) {
            mediumMeteors->SetTextureData(mediumMeteorsTexture, mediumMeteor[i].position.x, mediumMeteor[i].position.y, mediumMeteor->radius, mediumMeteor->radius);
            if (mediumMeteor[i].active) {
                //DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, DARKGRAY);
                DrawTexturePro(mediumMeteorsTexture, mediumMeteors->GetFrameRec(), { mediumMeteors->GetPosition().x,  mediumMeteors->GetPosition().y, (float)mediumMeteorsTexture.width * 2.0f , (float)mediumMeteorsTexture.height * 2.0f }, { (float)mediumMeteorsTexture.width,(float)mediumMeteorsTexture.height }, mediumMeteor[i].rotation >= 360 ? mediumMeteor[i].rotation = 0 : mediumMeteor[i].rotation += 1, WHITE);
            }
        }

        for (int i = 0; i < maxSmallMeteors; i++) {
            smallMeteors->SetTextureData(smallMeteorsTexture, smallMeteor[i].position.x, smallMeteor[i].position.y, smallMeteor->radius, smallMeteor->radius);
            if (smallMeteor[i].active) {
                //DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, DARKGRAY);
                DrawTexturePro(smallMeteorsTexture, smallMeteors->GetFrameRec(), { smallMeteors->GetPosition().x,  smallMeteors->GetPosition().y, (float)smallMeteorsTexture.width * 2.0f , (float)smallMeteorsTexture.height * 2.0f }, { (float)smallMeteorsTexture.width,(float)smallMeteorsTexture.height }, smallMeteor[i].rotation >= 360 ? smallMeteor[i].rotation = 0 : smallMeteor[i].rotation += 1, WHITE);
            }
        }
        if (shieldPowerUp.active) {
            DrawTextureRec(shieldTexture, shield->GetFrameRec(), shield->GetPosition(), WHITE);
        }
        if (moreBulletsPowerUp.active) {
            DrawTextureRec(moreBulletsTexture, moreBullets->GetFrameRec(), moreBullets->GetPosition(), WHITE);
        }
        DrawTextureEx(sightTexture, { GetMousePosition().x - sightTexture.width / 2,GetMousePosition().y - sightTexture.height / 2 }, 0.0f, 1.0f, WHITE);
        if(player->GetShield())player->DrawPlayer();
        // Draw shoot
        for (int i = 0; i < (player->GetBullets() ? player->playerMaxShoots : player->playerMaxShoots / 2); i++) {
            if (shoots[i]->GetActive()) DrawCircleV(shoots[i]->GetPosition(), shoots[i]->GetRadius(), SKYBLUE);
        }
        DrawTextureRec(rightClickTexture, rightClick->GetFrameRec(), rightClick->GetPosition(), WHITE);
        DrawTextureRec(leftClickTexture, leftClick->GetFrameRec(), leftClick->GetPosition(), WHITE);
        DrawTextureRec(buttonPauseTexture, buttonPause->GetFrameRec(), buttonPause->GetPosition(), WHITE);
        if (victory) {
            { DrawText("VICTORY", screenWidth / 2 - MeasureText("VICTORY", 80) / 2, screenHeight / 2 - 40, 80, LIGHTGRAY); }
            if (CheckCollisionPointRec(GetMousePosition(), buttonResumeArea)) {
                buttonResumePlayAgain->SetTexture(buttonTexture);
                DrawTextureRec(buttonTexture, buttonResumePlayAgain->GetFrameRec(), buttonResumePlayAgain->GetPosition(), WHITE);
            }
            else {
                buttonResumePlayAgain->SetTexture(buttonPushedTexture);
                DrawTextureRec(buttonPushedTexture, buttonResumePlayAgain->GetFrameRec(), buttonResumePlayAgain->GetPosition(), WHITE);
            }
            if (CheckCollisionPointRec(GetMousePosition(), buttonExitArea)) {
                buttonMenuExit->SetTexture(buttonTexture);
                DrawTextureRec(buttonTexture, buttonMenuExit->GetFrameRec(), buttonMenuExit->GetPosition(), WHITE);
            }
            else {
                buttonMenuExit->SetTexture(buttonPushedTexture);
                DrawTextureRec(buttonPushedTexture, buttonMenuExit->GetFrameRec(), buttonMenuExit->GetPosition(), WHITE);
            }
        }

        if (pause) {
            DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY); 
            /*DrawRectangle(buttonResumeArea.x+20, buttonResumeArea.y+10, buttonResumeArea.width-30, buttonResumeArea.height-20, RED);
            DrawRectangle(buttonExitArea.x+20, buttonExitArea.y+10, buttonExitArea.width-30, buttonExitArea.height-20, RED);*/
            if (CheckCollisionPointRec(GetMousePosition(), buttonResumeArea)) {
                buttonResumePlayAgain->SetTexture(buttonTexture);
                DrawTextureRec(buttonTexture, buttonResumePlayAgain->GetFrameRec(), buttonResumePlayAgain->GetPosition(), WHITE);
            }
            else {
                buttonResumePlayAgain->SetTexture(buttonPushedTexture);
                DrawTextureRec(buttonPushedTexture, buttonResumePlayAgain->GetFrameRec(), buttonResumePlayAgain->GetPosition(), WHITE);
            }
            if (CheckCollisionPointRec(GetMousePosition(), buttonExitArea)) {
                buttonMenuExit->SetTexture(buttonTexture);
                DrawTextureRec(buttonTexture, buttonMenuExit->GetFrameRec(), buttonMenuExit->GetPosition(), WHITE);
            }
            else {
                buttonMenuExit->SetTexture(buttonPushedTexture);
                DrawTextureRec(buttonPushedTexture, buttonMenuExit->GetFrameRec(), buttonMenuExit->GetPosition(), WHITE);
            }            
        }
    }
    else DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);

    EndDrawing();
}

void Game::DeInitGame() {
    ShowCursor();
}


void Game::UpdateDrawFrame() {
    Game::InputGame();
    Game::UpdateGame();
    Game::DrawGame();
}

bool Game::GoToMenu() {
    return goToMenu;
}
