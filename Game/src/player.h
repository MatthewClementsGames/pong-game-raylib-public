#include "paddle.h"
#include <iostream>

class Ball; 

class Player : public Paddle
{
public: 

    enum PlayerNumber{
        PLAYER_ONE,
        PLAYER_TWO,
        PLAYER_AI
    }; 

    Player(PlayerNumber playerNumber, std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<ProjectSettings> projectSettings); 

    void Tick(); 

    void SetBallPtr(std::shared_ptr<Ball> ball); 

protected: 


private: 

    std::shared_ptr<Ball> theBallPtr; 

    PlayerNumber myPlayerNumber; 

    Vector2 playerStartPos {}; 

    void PlayerControls(); 
    void AIPlayerControls(); 
    
    void SetPlayerStartPos(); 

}; 