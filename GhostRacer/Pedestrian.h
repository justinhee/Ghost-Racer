//
//  Pedestrian.hpp
//  GhostRacer
//
//  Created by Justin Hee on 2/17/21.
//  Copyright © 2021 David Smallberg. All rights reserved.
//

#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include "Actor.h"
#include "Damageable.h"

class Pedestrian : public Actor, public Damageable
{
public:
    Pedestrian(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double size, int depth, int VSpeed = -4, int HSpeed = 0, int health = 2, int movementPlanDistance = 0);
    virtual bool isCollisionAvoidanceWorthy() const;
private:
    int m_movementPlanDistance;
};

#endif /* PEDESTRIAN_H */
