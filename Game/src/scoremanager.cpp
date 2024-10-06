#include "scoremanager.h"

ScoreManager::ScoreManager(std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<ProjectSettings> projectSettings)
{
    sceneManagerPtr = sceneManager; 
    projectSettingsPtr = projectSettings; 

    playerOneScore = 0; 
    playerTwoScore = 0;
}

//-------------------- Score Manager Tick -------------------- 
void ScoreManager::Tick()
{
    DisplayScore(); 
}

//-------------------- Display Score -------------------- 
void ScoreManager::DisplayScore()
{
    if(sceneManagerPtr->GetCurrentScene() == SceneManager::SCENE_GAME)
    {
        float middleOfScreen = ((float) projectSettingsPtr->GetScreenWidth()/2.0f) - 10.0f; 

        DrawText(TextFormat("%i", playerOneScore), (int) (middleOfScreen - playerOneScoreTextPadding), 10, 30, WHITE); //Player One Score
        DrawText(TextFormat("%i", playerTwoScore), (int) (middleOfScreen + playerTwoScoreTextPadding), 10, 30, WHITE); //Player Two Score
    } 
}

//-------------------- Add To Score -------------------- 
void ScoreManager::AddToScore(PlayerScore playerscore, int scoreToAdd)
{
    if(playerscore == PLAYER_ONE_SCORE)
    {
        playerOneScore += scoreToAdd; 
    }
    else if(playerscore == PLAYER_TWO_SCORE)
    {
        playerTwoScore += scoreToAdd; 
    }

    CheckIfPlayerHasWon(); 
}

//-------------------- Check if a Player has won -------------------- 
void ScoreManager::CheckIfPlayerHasWon()
{ 
    if(playerOneScore >= winningScore)
    {
        if(sceneManagerPtr != nullptr)
        {
            sceneManagerPtr->SetPlayerWinner(1); 
            sceneManagerPtr->SwitchScene(SceneManager::SCENE_GAME_OVER); 
        }
    }
    else if(playerTwoScore >= winningScore)
    {
         if(sceneManagerPtr != nullptr)
        {
            sceneManagerPtr->SetPlayerWinner(2); 
            sceneManagerPtr->SwitchScene(SceneManager::SCENE_GAME_OVER); 
        }
    }
}

//-------------------- Get Score -------------------- 
int ScoreManager::GetScore(PlayerScore playerscore)
{
    if(playerscore == PLAYER_ONE_SCORE)
    {
        return playerOneScore; 
    }
    else
    {
        return playerTwoScore; 
    }
}
