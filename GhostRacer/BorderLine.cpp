//
//  BorderLine.cpp
//  GhostRacer
//
//  Created by Justin Hee on 2/17/21.
//  Copyright © 2021 David Smallberg. All rights reserved.
//

#include "BorderLine.h"
#include "StudentWorld.h"
#include "GhostRacer.h"

BorderLine::BorderLine(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double size, int depth, int VSpeed, int HSpeed) :
Actor(world, imageID, startX, startY, startDirection, size, depth, VSpeed, HSpeed)
{}

void BorderLine::doSomething()
{
    int vert_speed = getVSpeed()-getWorld()->getGhostRacer()->getVSpeed();
    int horiz_speed = getHSpeed();
    
    int new_y = getY() + vert_speed;
    int new_x = getX() + horiz_speed;
    moveTo(new_x, new_y);
    if(getX() < 0 || getY() < 0 || getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT)
        die();
}

bool BorderLine::isCollisionAvoidanceWorthy() const
{
    return false;
}
