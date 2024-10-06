#include "raylib.h"

#ifndef PROJECT_SETTINGS_H
#define PROJECT_SETTINGS_H

class ProjectSettings
{
public: 
    ProjectSettings(); 
    
    int GetScreenWidth() const { return screenWidth; }; 
    int GetScreenHeight() const { return screenHeight; }; 

    float GetBackgroundScaleSize() const { return backgroundScaleSize; }; 
    float GetAssetsScaleSize() const { return assetsScaleSize; }; 
    float GetRaylibIconScaleSize() const { return raylibIconScaleSize; }; 

    float GetSpeedScaleSize() const { return speedScaleSize; };

    float GetDeltaTime() { return GetFrameTime(); };

private: 

    const int screenWidth {960}; 
    const int screenHeight {540}; 

    const float backgroundScaleSize {2.0f}; 
    const float assetsScaleSize {2.0f}; 
    const float raylibIconScaleSize{ 1.0f }; 
    const float speedScaleSize{2.0f}; 

public: 

}; 
#endif