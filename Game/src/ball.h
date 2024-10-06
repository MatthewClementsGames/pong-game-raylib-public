#include "raylib.h"
#include "projectsettings.h"
#include "scenemanager.h"
#include <iostream>

class Player;
class ScoreManager; 

class Ball
{
public:
    Ball(std::shared_ptr<ProjectSettings> projectSettings, std::shared_ptr<SceneManager> sceneManager, 
         std::shared_ptr<ScoreManager> scoreManager, std::shared_ptr<Player> playerOne, std::shared_ptr<Player> playerTwo);

    ~Ball(); 
    
    void Tick();

    Vector2 GetBallPos(); 
protected:


private:

    std::shared_ptr<ProjectSettings> theProjectSettingsPtr;
    std::shared_ptr<SceneManager> theSceneManagerPtr;

    std::shared_ptr<Player> playerOnePtr;
    std::shared_ptr<Player> playerTwoPtr;

    std::shared_ptr<ScoreManager> theScoreManagerPtr;

    Texture2D ballTexture {LoadTexture("assets/ball.png")}; 
    Vector2 ballStartPos {0, 0}; 
    Vector2 ballCurrentPos{Vector2{0,0}}; 
    Vector2 ballVelocity {Vector2{0,0}}; 
    float ballSpeed {290.0f}; 
    float ballScaleSize{}; 

    void BallMovement(); 
    void ResetBall(); 
    void BallPaddleCollisionCheck(); 
    void CheckWhereBallCollidedOnThePaddle(std::shared_ptr<Player> playerPaddle); 
    void CheckBallGoal(); 
    void CheckTopBottomBounds(); 


}; 