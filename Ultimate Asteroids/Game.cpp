#include "Game.h"
#include <math.h>


#define PLAYER_BASE_SIZE    20.0f
#define PLAYER_SPEED        300.0f
#define PLAYER_MAX_SHOOTS   3

#define METEORS_SPEED       20
#define MAX_BIG_METEORS     8
#define MAX_MEDIUM_METEORS  16
#define MAX_SMALL_METEORS   32

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

struct Shoot {
    Vector2 position;
    Vector2 speed;
    float radius;
    float rotation;
    int lifeSpawn;
    bool active;
    Color color;
};

struct Meteor {
    Vector2 position;
    Vector2 speed;
    float radius;
    bool active;
    Color color;
};

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
  bool gameOver = false;
  bool pause = false;
  bool victory = false;

// NOTE: Defined triangle is isosceles with common angles of 70 degrees.

  
  Shoot shoot[PLAYER_MAX_SHOOTS] = { 0 };
  Meteor bigMeteor[MAX_BIG_METEORS] = { 0 };
  Meteor mediumMeteor[MAX_MEDIUM_METEORS] = { 0 };
  Meteor smallMeteor[MAX_SMALL_METEORS] = { 0 };

  int midMeteorsCount = 0;
  int smallMeteorsCount = 0;
  int destroyedMeteorsCount = 0;

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables


// Update game (one frame)


// Draw game (one frame)


// Update and Draw (one frame)


Game::Game() {
    gameInited = false;
}

Game::~Game() {
}

bool Game::GetInited() {
    return gameInited;
}

void Game::InitGame() {
    int posx, posy;
    int velx, vely;
    bool correctRange = false;
    victory = false;
    pause = false;
    player = new Player();

    // Initialization player

    destroyedMeteorsCount = 0;

    // Initialization shoot
    for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) {
        shoot[i].position = { 0, 0 };
        shoot[i].speed = { 0, 0 };
        shoot[i].radius = 2;
        shoot[i].active = false;
        shoot[i].lifeSpawn = 0;
        shoot[i].color = WHITE;
    }

    for (int i = 0; i < MAX_BIG_METEORS; i++) {
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
        velx = GetRandomValue(-METEORS_SPEED, METEORS_SPEED);
        vely = GetRandomValue(-METEORS_SPEED, METEORS_SPEED);

        while (!correctRange) {
            if (velx == 0 && vely == 0) {
                velx = GetRandomValue(-METEORS_SPEED, METEORS_SPEED);
                vely = GetRandomValue(-METEORS_SPEED, METEORS_SPEED);
            }
            else correctRange = true;
        }

        bigMeteor[i].speed = { (float)velx * GetFrameTime(), (float)vely * GetFrameTime() };
        bigMeteor[i].radius = 40;
        bigMeteor[i].active = true;
        bigMeteor[i].color = BLUE;
    }

    for (int i = 0; i < MAX_MEDIUM_METEORS; i++) {
        mediumMeteor[i].position = { -100, -100 };
        mediumMeteor[i].speed = { 0,0 };
        mediumMeteor[i].radius = 20;
        mediumMeteor[i].active = false;
        mediumMeteor[i].color = BLUE;
    }

    for (int i = 0; i < MAX_SMALL_METEORS; i++) {
        smallMeteor[i].position = { -100, -100 };
        smallMeteor[i].speed = { 0,0 };
        smallMeteor[i].radius = 10;
        smallMeteor[i].active = false;
        smallMeteor[i].color = BLUE;
    }

    midMeteorsCount = 0;
    smallMeteorsCount = 0;
    gameInited = true;
}



void Game::UpdateGame() {
    if (!gameOver) {
        if (IsKeyPressed('P')) pause = !pause;

        if (!pause) {


            // Player logic: speed
            player->UpdateSpeed();

            // Player logic: acceleration
            player->UpdateAcceleration();

            // Player logic: movement
            player->UpdatePosition();

            // Collision logic: player vs walls
            //if (player->GetPosition().x > screenWidth + player->GetRadius()) player->SetPositionX().x = -(player->GetRadius());
            //else if (player->GetPosition().x < -(player->GetRadius())) player->GetPosition().x = screenWidth + player->GetRadius();
            //if (player.position.y > (screenHeight + player->GetRadius())) player.position.y = -(player->GetRadius());
            //else if (player.position.y < -(player->GetRadius())) player.position.y = screenHeight + player->GetRadius();

            //// Player shoot logic
            //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            //    if (Vector2Length(Vector2Subtract(GetMousePosition(), player.position)) > 30.0f) {
            //        player.rotation = Vector2Angle(player.position, GetMousePosition()) + 90;
            //    }
            //    for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) {
            //        if (!shoot[i].active) {
            //            shoot[i].position = { player->GetPosition().x + (float)sin(player.rotation * DEG2RAD) * (player->GetRadius()), player.position.y - (float)cos(player.rotation * DEG2RAD) * (player->GetRadius()) };
            //            shoot[i].active = true;
            //            shoot[i].speed.x = 1.5 * (float)sin(player.rotation * DEG2RAD) * PLAYER_SPEED;
            //            shoot[i].speed.y = 1.5 * (float)cos(player.rotation * DEG2RAD) * PLAYER_SPEED;
            //            shoot[i].rotation = player.rotation;
            //            break;
            //        }
            //    }
            //}

            // Shoot life timer
            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) {
                if (shoot[i].active) shoot[i].lifeSpawn += GetFrameTime();
            }

            // Shot logic
            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) {
                if (shoot[i].active) {
                    // Movement
                    shoot[i].position.x += shoot[i].speed.x * GetFrameTime();
                    shoot[i].position.y -= shoot[i].speed.y * GetFrameTime();

                    // Collision logic: shoot vs walls
                    if (shoot[i].position.x > screenWidth + shoot[i].radius) {
                        shoot[i].active = false;
                        shoot[i].lifeSpawn = 0;
                    }
                    else if (shoot[i].position.x < 0 - shoot[i].radius) {
                        shoot[i].active = false;
                        shoot[i].lifeSpawn = 0;
                    }
                    if (shoot[i].position.y > screenHeight + shoot[i].radius) {
                        shoot[i].active = false;
                        shoot[i].lifeSpawn = 0;
                    }
                    else if (shoot[i].position.y < 0 - shoot[i].radius) {
                        shoot[i].active = false;
                        shoot[i].lifeSpawn = 0;
                    }

                    // Life of shoot
                    if (shoot[i].lifeSpawn >= 60) {
                        shoot[i].position = { 0, 0 };
                        shoot[i].speed = { 0, 0 };
                        shoot[i].lifeSpawn = 0;
                        shoot[i].active = false;
                    }
                }
            }

            // Collision logic: player vs meteors
           /* player.collider = { player->GetPosition().x , player.position.y , 12 };

            for (int a = 0; a < MAX_BIG_METEORS; a++) {
                if (CheckCollisionCircles({ player.collider.x, player.collider.y }, player->GetRadius(), bigMeteor[a].position, bigMeteor[a].radius) && bigMeteor[a].active) gameOver = true;
            }

            for (int a = 0; a < MAX_MEDIUM_METEORS; a++) {
                if (CheckCollisionCircles({ player.collider.x, player.collider.y }, player->GetRadius(), mediumMeteor[a].position, mediumMeteor[a].radius) && mediumMeteor[a].active) gameOver = true;
            }
            r
            for (int a = 0; a < MAX_SMALL_METEORS; a++) {
                if (CheckCollisionCircles({ player.collider.x, player.collider.y }, player->GetRadius(), smallMeteor[a].position, smallMeteor[a].radius) && smallMeteor[a].active) gameOver = true;
            }*/

            // Meteors logic: big meteors
            for (int i = 0; i < MAX_BIG_METEORS; i++) {
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
            for (int i = 0; i < MAX_MEDIUM_METEORS; i++) {
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
            for (int i = 0; i < MAX_SMALL_METEORS; i++) {
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
            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) {
                if ((shoot[i].active)) {
                    for (int a = 0; a < MAX_BIG_METEORS; a++) {
                        if (bigMeteor[a].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, bigMeteor[a].position, bigMeteor[a].radius)) {
                            shoot[i].active = false;
                            shoot[i].lifeSpawn = 0;
                            bigMeteor[a].active = false;
                            destroyedMeteorsCount++;

                            for (int j = 0; j < 2; j++) {
                                if (midMeteorsCount % 2 == 0) {
                                    mediumMeteor[midMeteorsCount].position = { bigMeteor[a].position.x, bigMeteor[a].position.y };
                                    mediumMeteor[midMeteorsCount].speed = { (float)cos(shoot[i].rotation * DEG2RAD) * METEORS_SPEED * -1 * GetFrameTime(), (float)sin(shoot[i].rotation * DEG2RAD) * METEORS_SPEED * -1 * GetFrameTime() };
                                }
                                else {
                                    mediumMeteor[midMeteorsCount].position = { bigMeteor[a].position.x, bigMeteor[a].position.y };
                                    mediumMeteor[midMeteorsCount].speed = { (float)cos(shoot[i].rotation * DEG2RAD) * METEORS_SPEED * GetFrameTime(), (float)sin(shoot[i].rotation * DEG2RAD) * METEORS_SPEED * GetFrameTime() };
                                }

                                mediumMeteor[midMeteorsCount].active = true;
                                midMeteorsCount++;
                            }
                            //bigMeteor[a].position =  {-100, -100};
                            bigMeteor[a].color = RED;
                            a = MAX_BIG_METEORS;
                        }
                    }

                    for (int b = 0; b < MAX_MEDIUM_METEORS; b++) {
                        if (mediumMeteor[b].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, mediumMeteor[b].position, mediumMeteor[b].radius)) {
                            shoot[i].active = false;
                            shoot[i].lifeSpawn = 0;
                            mediumMeteor[b].active = false;
                            destroyedMeteorsCount++;

                            for (int j = 0; j < 2; j++) {
                                if (smallMeteorsCount % 2 == 0) {
                                    smallMeteor[smallMeteorsCount].position = { mediumMeteor[b].position.x, mediumMeteor[b].position.y };
                                    smallMeteor[smallMeteorsCount].speed = { (float)cos(shoot[i].rotation * DEG2RAD) * METEORS_SPEED * -1 * GetFrameTime(), (float)sin(shoot[i].rotation * DEG2RAD) * METEORS_SPEED * -1 * GetFrameTime() };
                                }
                                else {
                                    smallMeteor[smallMeteorsCount].position = { mediumMeteor[b].position.x, mediumMeteor[b].position.y };
                                    smallMeteor[smallMeteorsCount].speed = { (float)cos(shoot[i].rotation * DEG2RAD) * METEORS_SPEED * GetFrameTime(), (float)sin(shoot[i].rotation * DEG2RAD) * METEORS_SPEED * GetFrameTime() };
                                }

                                smallMeteor[smallMeteorsCount].active = true;
                                smallMeteorsCount++;
                            }
                            //mediumMeteor[b].position =  {-100, -100};
                            mediumMeteor[b].color = GREEN;
                            b = MAX_MEDIUM_METEORS;
                        }
                    }

                    for (int c = 0; c < MAX_SMALL_METEORS; c++) {
                        if (smallMeteor[c].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, smallMeteor[c].position, smallMeteor[c].radius)) {
                            shoot[i].active = false;
                            shoot[i].lifeSpawn = 0;
                            smallMeteor[c].active = false;
                            destroyedMeteorsCount++;
                            smallMeteor[c].color = YELLOW;
                            // smallMeteor[c].position =  {-100, -100};
                            c = MAX_SMALL_METEORS;
                        }
                    }
                }
            }
        }

        if (destroyedMeteorsCount == MAX_BIG_METEORS + MAX_MEDIUM_METEORS + MAX_SMALL_METEORS) victory = true;
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

    if (!gameOver) {
        // Draw spaceship
        player->DrawPlayer();

        // Draw meteors
        for (int i = 0; i < MAX_BIG_METEORS; i++) {
            if (bigMeteor[i].active) DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, DARKGRAY);
        }

        for (int i = 0; i < MAX_MEDIUM_METEORS; i++) {
            if (mediumMeteor[i].active) DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, GRAY);
        }

        for (int i = 0; i < MAX_SMALL_METEORS; i++) {
            if (smallMeteor[i].active) DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, GRAY);
        }

        // Draw shoot
        for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) {
            if (shoot[i].active) DrawCircleV(shoot[i].position, shoot[i].radius, BLACK);
        }

        if (victory) DrawText("VICTORY", screenWidth / 2 - MeasureText("VICTORY", 20) / 2, screenHeight / 2, 20, LIGHTGRAY);

        if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);
    }
    else DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);

    EndDrawing();
}

void Game::UnloadGame() {
}

void Game::UpdateDrawFrame() {
    Game::UpdateGame();
    Game::DrawGame();
}