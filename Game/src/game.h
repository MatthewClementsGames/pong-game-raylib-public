#include <memory>

class ProjectSettings; 
class SceneManager; 
class Player; 
class Ball; 
class ScoreManager; 

class Game
{
public: 
    Game(); 
private:
    void MainMenu();
    void PauseGame(); 
    void ResetGame(); 
    void GameOver(); 
    bool exitGame{false}; 

    std::shared_ptr<ProjectSettings> projectSettingsPtr; 
    std::shared_ptr<SceneManager> sceneManagerPtr; 
    std::shared_ptr<ScoreManager> scoreManagerPtr; 

    enum GameState{
        GAMESTATE_SINGLE_PLAYER,
        GAMESTATE_TWO_PLAYER
    };
    GameState selectedGameState; 
    void GameState();  
 
    std::shared_ptr<Player> playerOnePtr; 
    std::shared_ptr<Player> playerTwoPtr;

    std::shared_ptr<Ball> ballPtr; 

    bool hasSinglePlayerGameBeenContructed{false};
    bool hasTwoPlayerGameBeenConstructed{false}; 

}; 