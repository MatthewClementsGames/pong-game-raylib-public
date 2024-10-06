#include "game.h"
#include <raylib.h>
#include "player.h"
#include "ball.h"
#include "scenemanager.h"
#include "projectsettings.h"
#include "scoremanager.h"


Game::Game()
{
    projectSettingsPtr = std::make_shared<ProjectSettings>(); 

    InitWindow(projectSettingsPtr->GetScreenWidth(), projectSettingsPtr->GetScreenHeight(), "PONG!");

    sceneManagerPtr = std::make_shared<SceneManager>(projectSettingsPtr); 

    SetTargetFPS(60);
 
    while (!exitGame)
    {
        if(IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()) {exitGame = true;}

        BeginDrawing();
        ClearBackground(WHITE); 
        sceneManagerPtr->Tick();

        switch(sceneManagerPtr->GetCurrentScene())
        {
            case SceneManager::SCENE_RAYLIB_SPLASH_SCREEN:
            break;
            case SceneManager::SCENE_MC_SPLASH_SCREEN:
            break;
            case SceneManager::SCENE_MAIN_MENU:
            MainMenu(); 
            break; 
            case SceneManager::SCENE_GAME:
            if(IsKeyPressed(KEY_P)) {sceneManagerPtr->SwitchScene(SceneManager::SCENE_PAUSE); }
            GameState(); 
            break;
            case SceneManager::SCENE_PAUSE:
            PauseGame(); 
            break;
            case SceneManager::SCENE_GAME_OVER:
            GameOver(); 
            break;
        }
        EndDrawing();
    }

    CloseWindow();
}

//-------------------- Game State -------------------- 
void Game::GameState()
{
    if(selectedGameState == GAMESTATE_SINGLE_PLAYER)
    {
        //Setup/Create Single Player
        if(!hasSinglePlayerGameBeenContructed)
        {
            scoreManagerPtr = std::make_shared<ScoreManager>(sceneManagerPtr, projectSettingsPtr); 

            playerOnePtr = std::make_shared<Player>(Player::PLAYER_ONE,sceneManagerPtr, projectSettingsPtr); 
            playerTwoPtr = std::make_shared<Player>(Player::PLAYER_AI,sceneManagerPtr, projectSettingsPtr); 

            ballPtr = std::make_shared<Ball>(projectSettingsPtr, sceneManagerPtr, scoreManagerPtr, playerOnePtr, playerTwoPtr); 

            playerTwoPtr->SetBallPtr(ballPtr);

            hasSinglePlayerGameBeenContructed = true; 
        }

        if(playerOnePtr != nullptr && ballPtr != nullptr && playerTwoPtr != nullptr && scoreManagerPtr != nullptr) 
        {
            playerOnePtr->Tick();
            playerTwoPtr->Tick();
            ballPtr->Tick(); 
            scoreManagerPtr->Tick(); 
        }
    }
    else if(selectedGameState == GAMESTATE_TWO_PLAYER)
    {
        //Setup/Create Two Player Game
        if(!hasTwoPlayerGameBeenConstructed)
        {
            scoreManagerPtr = std::make_shared<ScoreManager>(sceneManagerPtr, projectSettingsPtr); 

            playerOnePtr = std::make_shared<Player>(Player::PLAYER_ONE,sceneManagerPtr, projectSettingsPtr);
            playerTwoPtr = std::make_shared<Player>(Player::PLAYER_TWO,sceneManagerPtr, projectSettingsPtr);

            ballPtr = std::make_shared<Ball>(projectSettingsPtr, sceneManagerPtr, scoreManagerPtr,  playerOnePtr, playerTwoPtr); 

            hasTwoPlayerGameBeenConstructed = true; 
        }

        if (playerOnePtr != nullptr && playerTwoPtr != nullptr && ballPtr != nullptr && scoreManagerPtr != nullptr)
        {
            playerOnePtr->Tick(); 
            playerTwoPtr->Tick();
            scoreManagerPtr->Tick();
            ballPtr->Tick(); 
        }
    }
}

//-------------------- Main Menu -------------------- 
void Game::MainMenu()
{
    //Start One Player Game
    if(IsKeyPressed(KEY_ONE))
    {
        selectedGameState = GAMESTATE_SINGLE_PLAYER;
        if(sceneManagerPtr != nullptr)
        {
            sceneManagerPtr->SwitchScene(SceneManager::SCENE_GAME); 
        }
    }
    //Start Two Player Game
    if(IsKeyPressed(KEY_TWO))
    {
        selectedGameState = GAMESTATE_TWO_PLAYER; 
        if(sceneManagerPtr != nullptr)
        {
            sceneManagerPtr->SwitchScene(SceneManager::SCENE_GAME); 
        }
    }
    //Exit Game
    if(IsKeyPressed(KEY_THREE))
    {
        exitGame = true; 
    }
}

//-------------------- Pause Game -------------------- 
void Game::PauseGame()
{
    //Resume Game
    if(IsKeyPressed(KEY_R))
    {
        sceneManagerPtr->SwitchScene(SceneManager::SCENE_GAME); 
    }
    //Back to Main Menu
    if(IsKeyPressed(KEY_M))
    {
        sceneManagerPtr->SwitchScene(SceneManager::SCENE_MAIN_MENU); 
        ResetGame(); 
    }
    //Exit the Game
    if(IsKeyPressed(KEY_E))
    {
        exitGame = true; 
    }
}

//-------------------- Game Over -------------------- 
void Game::GameOver()
{
    //Restart Game
    if(IsKeyPressed(KEY_R))
    {
        sceneManagerPtr->SwitchScene(SceneManager::SCENE_GAME); 
        ResetGame(); 
    }
    //Back to Main Menu
    if(IsKeyPressed(KEY_M))
    {
        sceneManagerPtr->SwitchScene(SceneManager::SCENE_MAIN_MENU); 
        ResetGame(); 
    }
}


//-------------------- Reset Game -------------------- 
void Game::ResetGame()
{
    if(selectedGameState == GAMESTATE_SINGLE_PLAYER)
    {
        playerOnePtr.reset(); 
        playerTwoPtr.reset(); 
        ballPtr.reset(); 
        scoreManagerPtr.reset(); 
        hasSinglePlayerGameBeenContructed = false; 
    }
    else if(selectedGameState == GAMESTATE_TWO_PLAYER)
    {
        playerOnePtr.reset(); 
        playerTwoPtr.reset(); 
        ballPtr.reset(); 
        scoreManagerPtr.reset(); 
        hasTwoPlayerGameBeenConstructed = false; 
    }
}

