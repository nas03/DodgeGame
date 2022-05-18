
#include "save_game.h"
void SaveGame::writeHaveSaved(int save)
{
    std::ofstream inFile("have_saved.txt", std::ios::out | std::ios::trunc);
    if (inFile.is_open())
    {
        inFile << save;
    }
    else
    {
        std::cout << "not saved" << std::endl;
    }
}
void SaveGame::writeFireball(std::vector<std::vector <int> > fireballMap)
{
    
    std::ofstream inFile("fireballPos.txt",std::ios::out|std::ios::trunc);
    if (inFile.is_open())
    {
        for (int i = 0; i < fireballMap.size(); i++)
        {
            inFile << fireballMap[i][0] << " " << (fireballMap[i][1]) << "\n";
        }
    }
    else{
        std::cout << "Cant open file" << std::endl;
    }
    inFile.close();
}
void SaveGame::writeEffect(int score,int chooseChar, int health, int missileCd, int invincibleCd, int invincibleTime)
{
    std::ofstream inFile("effect.txt", std::ios::out|std::ios::trunc);
    if (inFile.is_open())
    {
        inFile << score << " " << chooseChar <<" " << health << " " << missileCd <<" " << invincibleCd <<" " << invincibleTime;
    }
    else{
        std::cout << "cant open effect file" << std::endl;
    }
    inFile.close();
}
void SaveGame::writeScore(int maxScore)
{
    std::ofstream inFile("max_score.txt", std::ios::out|std::ios::trunc);
    if (inFile.is_open())
    {
        inFile << maxScore;
    }
    else{
        std::cout << "cant open max_score file" << std::endl;
    }
    inFile.close();
}
std::vector <std::vector <int> > SaveGame::getFireball()
{
    std::vector <std::vector <int>> fireball;
    int id = 0;
    std::ifstream inFile("fireballPos.txt", std::ios::in);
    if (inFile.is_open())
    {
            std::string s;
            while(!inFile.eof())
            {
                fireball.push_back(std::vector <int> ());
                int x, y;
                inFile >> x >> y;
                fireball[id].push_back((x));
                fireball[id].push_back((y));
                id++;
            }
    }else
    {
        std::cerr <<"Cant open infile" << std::endl;
    }
    inFile.close();
    return fireball;
}
void SaveGame::writePlayer(int xpos, int ypos)
{
    std::ofstream inFile("playerPos.txt",std::ios::out|std::ios::trunc);
    if (inFile.is_open())
    {
        inFile << xpos <<" " << ypos << "\n";
    }
    else{
        std::cout << "Cant open file" << std::endl;
    }
    inFile.close();
}
std::vector <int> SaveGame::getPlayer()
{
    std::vector <int> playerPos(2);
    std::ifstream inFile("playerPos.txt", std::ios::in);
    if (inFile.is_open())
    {
        while(!inFile.eof())
        {
            inFile >> playerPos[0] >> playerPos[1];
        }
    }else
    {
        std::cout << "cant open playerPos file" << std::endl;
    }
    inFile.close();
    return playerPos;
}
int SaveGame::getMaxScore()
{
    std::ifstream inFile("max_score.txt", std::ios::in);
    int val;
    if (inFile.is_open())
    {
        while(!inFile.eof())
        {
            inFile >> val;
        }
    }
    else
    {
        std::cout << "cant open max_score file" << std::endl;
    }
    inFile.close();
    return val;
}
std::vector <int> SaveGame::getEffect()
{
    std::vector <int> effect(6);
    std::ifstream inFile("effect.txt", std::ios::in);
    int i = 0;
    if (inFile.is_open())
    {
        while(!inFile.eof())
        {
            inFile >> effect[i++];
        }
    }else
    {
        std::cout << "cant open getEffect file" << std::endl;
    }
    inFile.close();
    return effect;
}
int SaveGame::getHaveSaved()
{
    std::ifstream inFile("have_saved.txt", std::ios::in);
    int val;
    if (inFile.is_open())
    {
        while(!inFile.eof())
        {
            inFile >> val;
        }
    }
    else{
        std::cout << "Cant open haveSaved file" << std::endl;
    }
    return val;
}