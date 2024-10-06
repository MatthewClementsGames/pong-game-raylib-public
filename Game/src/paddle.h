#include "raylib.h"
#include "projectsettings.h"
#include "scenemanager.h"

#ifndef PADDLE_H
#define PADDLE_H

class Paddle
{
public: 
    Paddle(); 
    ~Paddle(); 

    void Tick(); 

    Rectangle GetPaddleCollisionRec();  
    Rectangle GetPaddleTopCollisionRec();
    Rectangle GetPaddleMiddleCollisionRec(); 
    Rectangle GetPaddleBottomCollisionRec(); 

protected: 
    
    std::shared_ptr<ProjectSettings> theProjectSettingsPtr;
    std::shared_ptr<SceneManager> theSceneManagerPtr;

    void Draw();

    void Move(int moveAmount);

    Vector2 paddleCurrentPos {};

    float paddleXStartPos {5.0f};

    Texture2D paddleTexture {LoadTexture("assets/paddle.png")};
    
    float paddleScaleSize {};

private:

    float paddleMoveSpeed {200.0f};
    Rectangle paddleCollisionRec{}; 

}; 
#endif
