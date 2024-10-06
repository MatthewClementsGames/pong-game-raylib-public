
#include "projectsettings.h"
#include "raylib.h"
#include <memory>

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

class SceneManager
{

public:  
    SceneManager(std::shared_ptr<ProjectSettings> projectSettings); 
    ~SceneManager(); 

    void Tick(); 

    enum scene{
        SCENE_RAYLIB_SPLASH_SCREEN,
        SCENE_MC_SPLASH_SCREEN,
        SCENE_MAIN_MENU, 
        SCENE_GAME,
        SCENE_PAUSE,
        SCENE_GAME_OVER
    };
    
    void SwitchScene(scene newScene); 

    void SetPlayerWinner(int playerNumber); 

private:

    std::shared_ptr<ProjectSettings> theProjectSettingsPtr; 

    scene currentScene {};
  
    void DrawRaylibSplashScreen(); 
    void DrawMCSplashScreenScene();
    void DrawMainMenuScene();
    void DrawGameScene(); 
    void DrawPauseScene(); 
    void DrawGameOverScene(); 

    Texture2D raylibSplashScreenIcon{ LoadTexture("assets/RaylibICON.png") }; //Raylib Splash Screen Icon
    float raylibSplashScreenActiveTime{ 3.0f };

    Texture2D mcSplashScreenTexture{LoadTexture("assets/MatthewClementsGamesSplashScreen.png")};  //Splash Texture      
    float mcSplashScreenActiveTime {3.0f};
    
    Texture2D mainMenuScreenTexture{LoadTexture("assets/MainMenu.png")};  //Menu Texture
    Texture2D gameBackgroundTexture {LoadTexture("assets/GameBackground.png")};  //Game Texture
    Texture2D pauseMenuScreenTexture {LoadTexture("assets/PauseMenu.png")};  //Pause Game Texture
    Texture2D gameOverPlayerOneWonScreenTexture {LoadTexture("assets/GameOverPlayerOneWon.png")};  //Game Over Scene Player One Won
    Texture2D gameOverPlayerTwoWonScreenTexture {LoadTexture("assets/GameOverPlayerTwoWon.png")};  //Game Over Texture Player Two Won
    
    int playerWinner{}; 

public: 
    scene GetCurrentScene() const {return currentScene; };     

}; 
#endif