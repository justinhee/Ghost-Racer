//
//  Pedestrian.cpp
//  GhostRacer
//
//  Created by Justin Hee on 2/17/21.
//  Copyright © 2021 David Smallberg. All rights reserved.
//

#include "Pedestrian.h"


Pedestrian::Pedestrian(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double size, int depth, int VSpeed, int HSpeed, int health, int movementPlanDistance) :
Actor(world, imageID, startX, startY, startDirection, size, depth, VSpeed, HSpeed),
Damageable(health),
m_movementPlanDistance(movementPlanDistance)
{}

bool Pedestrian::isCollisionAvoidanceWorthy() const
{
    return true;
}
