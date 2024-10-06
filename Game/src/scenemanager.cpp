#include "scenemanager.h"
#include "raylib.h"

SceneManager::SceneManager(std::shared_ptr<ProjectSettings> projectSettings)
{
    theProjectSettingsPtr = projectSettings; 
    currentScene = SCENE_RAYLIB_SPLASH_SCREEN;
}

SceneManager::~SceneManager()
{
    UnloadTexture(raylibSplashScreenIcon); 
    UnloadTexture(mcSplashScreenTexture); 
    UnloadTexture(mainMenuScreenTexture); 
    UnloadTexture(gameBackgroundTexture); 
    UnloadTexture(pauseMenuScreenTexture); 
    UnloadTexture(gameOverPlayerOneWonScreenTexture); 
    UnloadTexture(gameOverPlayerTwoWonScreenTexture); 
}

//-------------------- Scene Manager Tick -------------------- 
void SceneManager::Tick()
{
    switch (currentScene)
    {
    case SCENE_RAYLIB_SPLASH_SCREEN:
        DrawRaylibSplashScreen();
        break;
    case SCENE_MC_SPLASH_SCREEN:
        DrawMCSplashScreenScene();
        break;
    case SCENE_MAIN_MENU:
        DrawMainMenuScene();
        break;
    case SCENE_GAME:
        DrawGameScene();
        break;
    case SCENE_PAUSE:
        DrawPauseScene();
        break;
    case SCENE_GAME_OVER:
        DrawGameOverScene(); 
        break;
    }
}

//-------------------- Switch Scene -------------------- 
void SceneManager::SwitchScene(scene newScene)
{
    currentScene = newScene;
}

//-------------------- Draw Raylib Splash Screen -------------------- 
void SceneManager::DrawRaylibSplashScreen()
{
    if (theProjectSettingsPtr != nullptr)
    {
        ClearBackground(RAYWHITE);
        Vector2 raylibIconPosition{};
        raylibIconPosition.x = ((float)theProjectSettingsPtr->GetScreenWidth() / 2.0f) - (((float)raylibSplashScreenIcon.width * theProjectSettingsPtr->GetRaylibIconScaleSize()) / 2.0f);
        raylibIconPosition.y = ((float)theProjectSettingsPtr->GetScreenHeight() / 2.0f) - (((float)raylibSplashScreenIcon.height * theProjectSettingsPtr->GetRaylibIconScaleSize()) / 2.0f);

        DrawTextureEx(raylibSplashScreenIcon, raylibIconPosition, 0.0f, theProjectSettingsPtr->GetRaylibIconScaleSize(), WHITE);

        raylibSplashScreenActiveTime -= theProjectSettingsPtr->GetDeltaTime();
        if (raylibSplashScreenActiveTime <= 0.0f)
        {
            SwitchScene(SCENE_MC_SPLASH_SCREEN);
        }
    }
}

//-------------------- Draw Splash Screen -------------------- 
void SceneManager::DrawMCSplashScreenScene()
{
    if (theProjectSettingsPtr != nullptr)
    {
        ClearBackground(BLACK);
        DrawTextureEx(mcSplashScreenTexture, Vector2{0,0}, 0.0f, theProjectSettingsPtr->GetAssetsScaleSize(), WHITE);

        mcSplashScreenActiveTime -= theProjectSettingsPtr->GetDeltaTime();
        if (mcSplashScreenActiveTime <= 0.0f)
        {
            SwitchScene(SCENE_MAIN_MENU);
        }
    }
}

//-------------------- Draw Main Menu -------------------- 
void SceneManager::DrawMainMenuScene()
{
    if(theProjectSettingsPtr != nullptr)
    {
        ClearBackground(BLACK);
        DrawTextureEx(mainMenuScreenTexture, Vector2 {0,0}, 0.0f, theProjectSettingsPtr->GetBackgroundScaleSize(), WHITE); 
    }
}

//-------------------- Draw Game Scene -------------------- 
void SceneManager::DrawGameScene()
{
    if(theProjectSettingsPtr != nullptr)
    {
        ClearBackground(BLACK);
        DrawTextureEx(gameBackgroundTexture, Vector2{0, 0}, 0.0f, theProjectSettingsPtr->GetBackgroundScaleSize(), WHITE);
    }
}

//-------------------- Draw Pause Scene -------------------- 
void SceneManager::DrawPauseScene()
{
    if(theProjectSettingsPtr != nullptr)
    {
        ClearBackground(BLACK);
        DrawTextureEx(pauseMenuScreenTexture, Vector2{0, 0}, 0.0f, theProjectSettingsPtr->GetBackgroundScaleSize(), WHITE);
    }
}

//-------------------- Draw Game Over Scene -------------------- 
void SceneManager::DrawGameOverScene()
{
    if(theProjectSettingsPtr != nullptr)
    {
        ClearBackground(BLACK);
        if(playerWinner == 1)
        {
            DrawTextureEx(gameOverPlayerOneWonScreenTexture, Vector2{0, 0}, 0.0f, theProjectSettingsPtr->GetBackgroundScaleSize(), WHITE);
        }
        else if(playerWinner == 2)
        {
             DrawTextureEx(gameOverPlayerTwoWonScreenTexture, Vector2{0, 0}, 0.0f, theProjectSettingsPtr->GetBackgroundScaleSize(), WHITE);
        }
    }
}

//-------------------- Set the Player Winner -------------------- 
void SceneManager::SetPlayerWinner(int playerNumber)
{
    playerWinner = playerNumber; 
}
