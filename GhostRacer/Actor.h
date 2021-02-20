#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
public:
    Actor(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double size, int depth, int VSpeed, int HSpeed, bool alive = true);
    virtual void doSomething() = 0;
    virtual bool isAlive() const;
    virtual bool isCollisionAvoidanceWorthy();
    StudentWorld* getWorld() const;
    int getVSpeed() const;
    void setVSpeed(int newVSpeed);
    int getHSpeed() const;
    void setHSpeed(int newHSpeed);
    virtual void die();
    
private:
    StudentWorld* m_world;
    bool m_alive;
    int m_VSpeed;
    int m_HSpeed;
};

#endif // ACTOR_H_
