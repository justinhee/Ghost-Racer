
#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

const int LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH/2;
const int RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH/2;

class Actor;
class GhostRacer;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    GhostRacer* getGhostRacer() const;
    bool overlap(Actor* a1, Actor* a2) const;
    void saveSoul();
    void addActor(Actor* actor);
    bool sprayFirstAppropriateActor(Actor* a);
    void closestCollisionActorTopAndBottomLane(int lane, Actor*& closestToTop, Actor*& closestToBottom);
    void closestCollisionActorFrontBack(Actor* a, Actor*& front, Actor*& back);
    
private:
    std::vector<Actor*> m_actors;
    GhostRacer* m_GhostRacer;
    double m_lastBorderY;
    int m_savedSouls;
    int m_score;
    int m_bonus;
};

#endif // STUDENTWORLD_H_


