#include "raylib.h"
#include "scenemanager.h"
#include "projectsettings.h"
#include <memory>

#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

class ScoreManager
{
public: 

    enum PlayerScore
    {
        PLAYER_ONE_SCORE, 
        PLAYER_TWO_SCORE
    }; 

    ScoreManager(std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<ProjectSettings> projectSettings);

    void Tick(); 

    int GetScore(PlayerScore playerscore); 
    void AddToScore(PlayerScore playerscore, int scoreToAdd);
    void CheckIfPlayerHasWon(); 
    void DisplayScore(); 
protected:

private:
    std::shared_ptr<SceneManager> sceneManagerPtr; 
    std::shared_ptr<ProjectSettings> projectSettingsPtr; 
    
    int playerOneScore{0}; 
    int playerTwoScore{0}; 

    const int winningScore{11}; 

    const float playerOneScoreTextPadding{30.0f};
    const float playerTwoScoreTextPadding{30.0f};
}; 

#endif