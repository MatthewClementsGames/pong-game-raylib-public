#include "paddle.h"

Paddle::Paddle()
{

}

Paddle::~Paddle()
{
    UnloadTexture(paddleTexture); 
}

//-------------------- Paddle Tick -------------------- 
void Paddle::Tick()
{
    Draw(); 
}

//-------------------- Paddle Draw -------------------- 
void Paddle::Draw()
{
    DrawTextureEx(paddleTexture, paddleCurrentPos, 0.0f, paddleScaleSize, WHITE); 
}

//-------------------- Paddle Move -------------------- 
void Paddle::Move(int moveAmount)
{
    if(theProjectSettingsPtr != nullptr)
    {
        float bottomBounds = theProjectSettingsPtr->GetScreenHeight() - (paddleTexture.height * paddleScaleSize);

        if(paddleCurrentPos.y <= 0 && moveAmount == -1)
        {
            moveAmount = 0; 
        }
        else if(paddleCurrentPos.y >= bottomBounds && moveAmount == 1)
        {
            moveAmount = 0; 
        }
        paddleCurrentPos.y += moveAmount * (paddleMoveSpeed * theProjectSettingsPtr->GetSpeedScaleSize()) * theProjectSettingsPtr->GetDeltaTime(); 
    }
}

//-------------------- Get Paddle Collision Rectangle -------------------- 
Rectangle Paddle::GetPaddleCollisionRec()
{
    return Rectangle{paddleCurrentPos.x, paddleCurrentPos.y, (float) paddleTexture.width * paddleScaleSize, paddleTexture.height * paddleScaleSize};
}

//-------------------- Get Paddle Collision Top Rectangle -------------------- 
Rectangle Paddle::GetPaddleTopCollisionRec()
{
    return Rectangle {paddleCurrentPos.x, paddleCurrentPos.y, (float) paddleTexture.width * paddleScaleSize, (paddleTexture.height * paddleScaleSize) / 3}; 
}

//-------------------- Get Paddle Collision Middle Rectangle -------------------- 
Rectangle Paddle::GetPaddleMiddleCollisionRec()
{
    return Rectangle {paddleCurrentPos.x, paddleCurrentPos.y + (paddleTexture.height * paddleScaleSize / 3), (float) paddleTexture.width * paddleScaleSize, paddleTexture.height * paddleScaleSize / 3}; 
}

//-------------------- Get Paddle Collision Bottom Rectangle -------------------- 
Rectangle Paddle::GetPaddleBottomCollisionRec()
{
    return Rectangle {paddleCurrentPos.x, paddleCurrentPos.y + (paddleTexture.height * paddleScaleSize / 3 * 2), (float) paddleTexture.width * paddleScaleSize, paddleTexture.height * paddleScaleSize / 3}; 
}


