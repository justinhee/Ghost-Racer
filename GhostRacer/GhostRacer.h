//
//  GhostRacer.hpp
//  GhostRacer
//
//  Created by Justin Hee on 2/16/21.
//  Copyright © 2021 David Smallberg. All rights reserved.
//
#ifndef GHOSTRACER_H
#define GHOSTRACER_H

#include "Actor.h"
#include "GameConstants.h"
#include "Damageable.h"

class GhostRacer : public Actor, public Damageable
{
public:
    GhostRacer(StudentWorld* world, int imageID = IID_GHOST_RACER, double startX = 128, double startY = 32, int startDirection = 90, double size = 4.0, int depth = 0, int VSpeed = 0, int HSpeed = 0, int health = 100, int holyWaterSpray = 10);
    virtual void doSomething();
    virtual bool isCollisionAvoidanceWorthy() const;
    virtual bool isAlive() const;
private:
    int m_speed;
    int m_holyWaterSpray;
};

#endif /* GHOSTRACER_H */
