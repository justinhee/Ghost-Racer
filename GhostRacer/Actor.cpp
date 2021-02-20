#include "Actor.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double size, int depth, int VSpeed, int HSpeed, bool alive) : GraphObject(imageID, startX, startY, startDirection, size, depth),m_VSpeed(VSpeed), m_HSpeed(HSpeed), m_alive(alive), m_world(world)
{}

bool Actor::isAlive() const
{
    return m_alive;
}

bool Actor::isCollisionAvoidanceWorthy()
{
    return false;
}

StudentWorld* Actor::getWorld() const
{
    return m_world;
}

int Actor::getVSpeed() const
{
    return m_VSpeed;
}

void Actor::setVSpeed(int newVSpeed)
{
    m_VSpeed = newVSpeed;
}

int Actor::getHSpeed() const
{
    return m_HSpeed;
}

void Actor::setHSpeed(int newHSpeed)
{
    m_HSpeed = newHSpeed;
}

void Actor::die()
{
    m_alive = false;
}


