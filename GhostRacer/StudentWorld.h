#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;
class GhostRacer;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    GhostRacer* getGhostRacer() const;
    bool overlap(Actor* a1, Actor* a2) const;
    
private:
    std::vector<Actor*> m_actors;
    GhostRacer* m_GhostRacer;
    double m_lastBorderY;
};

#endif // STUDENTWORLD_H_
