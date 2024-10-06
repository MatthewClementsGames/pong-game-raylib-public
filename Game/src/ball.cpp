#include "ball.h"
#include <raylib.h>
#include "player.h"
#include "scoremanager.h"
#include <iostream>

Ball::Ball(std::shared_ptr<ProjectSettings> projectSettings, std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<ScoreManager> scoreManager, std::shared_ptr<Player> playerOne, std::shared_ptr<Player> playerTwo)
{
    theProjectSettingsPtr = projectSettings; 
    theSceneManagerPtr = sceneManager; 
    theScoreManagerPtr = scoreManager; 

    playerOnePtr = playerOne; 
    playerTwoPtr = playerTwo; 

    if(theProjectSettingsPtr != nullptr)
    {
        ballStartPos.x =  ((float) theProjectSettingsPtr->GetScreenWidth() / 2.0f) - ((float) ballTexture.width / 2.0f);
        ballStartPos.y =  ((float) theProjectSettingsPtr->GetScreenHeight() / 2.0f) - ((float) ballTexture.height / 2.0f);
    }

    ballCurrentPos.x = ballStartPos.x; 
    ballCurrentPos.y = ballStartPos.y; 

    ballVelocity.x = ballSpeed * theProjectSettingsPtr->GetSpeedScaleSize(); 
    ballVelocity.y = 0.0f; 

    ballScaleSize = theProjectSettingsPtr->GetAssetsScaleSize(); 
}

Ball::~Ball()
{
    UnloadTexture(ballTexture); 
} 

//-------------------- Ball Tick -------------------- 
void Ball::Tick()
{
    BallMovement(); 

    CheckBallGoal(); 

    CheckTopBottomBounds(); 

    BallPaddleCollisionCheck(); 

    DrawTextureEx(ballTexture, Vector2{ballCurrentPos.x, ballCurrentPos.y}, 0.0f, theProjectSettingsPtr->GetAssetsScaleSize(), WHITE); 
}

//-------------------- Ball Movement -------------------- 
void Ball::BallMovement()
{ 
    ballCurrentPos.x += ballVelocity.x * theProjectSettingsPtr->GetDeltaTime(); 
    ballCurrentPos.y += ballVelocity.y * theProjectSettingsPtr->GetDeltaTime(); 
}

//-------------------- Ball/Paddle Collision Check -------------------- 
void Ball::BallPaddleCollisionCheck()
{
    if(theProjectSettingsPtr != nullptr && playerOnePtr != nullptr && playerTwoPtr != nullptr)
    {
        Rectangle ballCollisionRec {ballCurrentPos.x, ballCurrentPos.y, (float) ballTexture.width * ballScaleSize, (float) ballTexture.height * ballScaleSize}; 

        if(CheckCollisionRecs(ballCollisionRec, playerOnePtr->GetPaddleCollisionRec()))
        {
           CheckWhereBallCollidedOnThePaddle(playerOnePtr);
           ballCurrentPos.x += ballCollisionRec.width/2;
           ballVelocity.x *= -1;
        }
        else if(CheckCollisionRecs(ballCollisionRec, playerTwoPtr->GetPaddleCollisionRec()))
        {
            CheckWhereBallCollidedOnThePaddle(playerTwoPtr);
            ballCurrentPos.x -= ballCollisionRec.width/2;
            ballVelocity.x *= -1;   
        }
    }
}

//-------------------- Paddle Collision Pos Check -------------------- 
void Ball::CheckWhereBallCollidedOnThePaddle(std::shared_ptr<Player> playerPaddle)
{
    float ballBottom = ballCurrentPos.y + ((float)ballTexture.height * ballScaleSize); 

    if(ballBottom < (playerPaddle->GetPaddleMiddleCollisionRec().y)
        && ballBottom > playerPaddle->GetPaddleTopCollisionRec().y)
        {
            ballVelocity.y = -0.75f * (ballSpeed * theProjectSettingsPtr->GetSpeedScaleSize());
        }
    else if(ballBottom > playerPaddle->GetPaddleMiddleCollisionRec() .y + playerPaddle->GetPaddleMiddleCollisionRec().height 
            && ballBottom > playerPaddle->GetPaddleBottomCollisionRec().y)
        {
            ballVelocity.y = 0.75f * (ballSpeed * theProjectSettingsPtr->GetSpeedScaleSize());
        }
}

//-------------------- Check If Goal Has Been Scored -------------------- 
void Ball::CheckBallGoal()
{
    Rectangle ballCollisionRec {ballCurrentPos.x, ballCurrentPos.y, (float) ballTexture.width * ballScaleSize, (float) ballTexture.height * ballScaleSize}; 

    if(ballCurrentPos.x <= (0 - ballCollisionRec.width))
    {
        ResetBall(); 
        ballVelocity.x *= -1; 
        theScoreManagerPtr->AddToScore(ScoreManager::PLAYER_TWO_SCORE, 1);       
    }

    if(ballCurrentPos.x >= (theProjectSettingsPtr->GetScreenWidth() + ballCollisionRec.width))
    {
        ResetBall(); 
        ballVelocity.x *= -1; 
        theScoreManagerPtr->AddToScore(ScoreManager::PLAYER_ONE_SCORE, 1); 
    }
}

//-------------------- Check Ball against Top/Bottom Bounds -------------------- 
void Ball::CheckTopBottomBounds()
{   
    Rectangle ballCollisionRec {ballCurrentPos.x, ballCurrentPos.y, (float) ballTexture.width * ballScaleSize, (float) ballTexture.height * ballScaleSize}; 

    if(ballCurrentPos.y <= 0)
    {
        ballCurrentPos.y += ballCollisionRec.height / 2; 
        ballVelocity.y *= -1; 
    }
    else if (ballCurrentPos.y >= (theProjectSettingsPtr->GetScreenHeight() - ballCollisionRec.height / 2))
    {
        ballCurrentPos.y -= ballCollisionRec.height / 2;
        ballVelocity.y *= -1;
    }
}   

//-------------------- Reset Ball -------------------- 
void Ball::ResetBall()
{
    ballCurrentPos.x = ballStartPos.x; 
    ballCurrentPos.y = ballStartPos.y; 

    ballVelocity.y = 0.0f; 
}

//-------------------- Get Ball Pos -------------------- 
Vector2 Ball::GetBallPos()
{
    return Vector2 {ballCurrentPos.x, ballCurrentPos.y}; 
}