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
m_health(health),
m_movementPlanDistance(movementPlanDistance)
{}

bool Pedestrian::isCollisionAvoidanceWorthy() const
{
    return true;
}

void Pedestrian::doSomething()
{}

void Pedestrian::setMovementPlanDistance(int d)
{
    m_movementPlanDistance = d;
}

int Pedestrian::getMovementPlanDistance() const
{
    return m_movementPlanDistance;
}

void Pedestrian::damage(int damage)
{
    m_health -= damage;
    if(m_health < 0)
        die();
}

int Pedestrian::getHealth() const
{
    return m_health;
}
