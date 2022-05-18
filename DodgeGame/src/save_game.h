#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string.h>
#include <string>
class SaveGame
{
public:
    SaveGame();
    ~SaveGame();
    void writePlayer(int xpos, int ypos);
    void writeFireball(std::vector<std::vector <int> > fireballMap);
    void writeEffect(int score,int choosseChar,int health, int missicleCd, int invincibleCd, int invincibleTime);
    void writeScore(int maxScore);
    void writeHaveSaved(int save);
    std::vector <std::vector <int> > getFireball();
    std::vector <int> getPlayer();
    std::vector <int> getEffect();
    int getMaxScore();
    int getHaveSaved();
private:
};