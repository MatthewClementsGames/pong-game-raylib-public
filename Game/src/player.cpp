#include "player.h"
#include "ball.h"
#include <iostream>

Player::Player(PlayerNumber playerNumber, std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<ProjectSettings> projectSettings)
{
    myPlayerNumber = playerNumber; 

    Paddle::theSceneManagerPtr = sceneManager; 
    Paddle::theProjectSettingsPtr = projectSettings; 

    if(theProjectSettingsPtr != nullptr) { Paddle::paddleScaleSize = theProjectSettingsPtr->GetAssetsScaleSize();} 

    SetPlayerStartPos(); 
}

//-------------------- Player Tick -------------------- 
void Player::Tick()
{
    if(theSceneManagerPtr != nullptr && theSceneManagerPtr->GetCurrentScene() == SceneManager::SCENE_GAME)
    {      
        Paddle::Tick();
    
        PlayerControls(); 
    }
}

//-------------------- Player Controls -------------------- 
void Player::PlayerControls()
{ 
    if(myPlayerNumber == PLAYER_ONE)
    {
        if(IsKeyDown(KEY_W))
        {
            Paddle::Move(-1); 
        }
        if(IsKeyDown(KEY_S))
        {
            Paddle::Move(1); 
        }
    }

    if(myPlayerNumber == PLAYER_TWO)
    {
        if(IsKeyDown(KEY_UP))
        {
            Paddle::Move(-1); 
        }
        if(IsKeyDown(KEY_DOWN))
        {
            Paddle::Move(1); 
        }
    }

    if(myPlayerNumber == PLAYER_AI)
    {
        AIPlayerControls(); 
    }
}

//-------------------- AI Player Controls -------------------- 
void Player::AIPlayerControls()
{
    if(theBallPtr != nullptr)
    {
        if(paddleCurrentPos.y < theBallPtr->GetBallPos().y)
        {
            Paddle::Move(1); 
        }
        
        if(paddleCurrentPos.y > theBallPtr->GetBallPos().y)
        {
            Paddle::Move(-1); 
        }
    }
}

//-------------------- AI Player Controls -------------------- 
void Player::SetPlayerStartPos()
{
    if(theProjectSettingsPtr != nullptr && myPlayerNumber == PLAYER_ONE)
    {
        playerStartPos = Vector2{paddleXStartPos, (float) Paddle::theProjectSettingsPtr->GetScreenHeight() / 2 - (paddleTexture.height * paddleScaleSize) / 2}; 
    }
    else if(theProjectSettingsPtr != nullptr) //Player Two or AI will always start on the right hand side. 
    {
        playerStartPos = Vector2{(Paddle::theProjectSettingsPtr->GetScreenWidth() - (paddleXStartPos + paddleTexture.width * paddleScaleSize)), (float) Paddle::theProjectSettingsPtr->GetScreenHeight() / 2 - (paddleTexture.height * paddleScaleSize) / 2}; 
    }

    paddleCurrentPos = playerStartPos; 
}

void Player::SetBallPtr(std::shared_ptr<Ball> ball)
{
    theBallPtr = ball;
}


