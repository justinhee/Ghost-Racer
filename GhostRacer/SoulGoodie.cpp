//
//  SoulGoodie.cpp
//  GhostRacer
//
//  Created by Justin Hee on 2/19/21.
//  Copyright © 2021 David Smallberg. All rights reserved.
//

#include "SoulGoodie.h"
#include "StudentWorld.h"
#include "GhostRacer.h"

SoulGoodie::SoulGoodie(StudentWorld* world, double startX, double startY, int imageID, int startDirection, double size, int depth, int VSpeed, int HSpeed) :
Actor(world, imageID, startX, startY, startDirection, size, depth, VSpeed, HSpeed)
{}

void SoulGoodie::doSomething()
{
    int vert_speed = getVSpeed() - getWorld()->getGhostRacer()->getVSpeed();
    int horiz_speed = getHSpeed();
    double new_y = getY() + vert_speed;
    double new_x = getX() + horiz_speed;
    moveTo(new_x, new_y);
    if(getX() < 0 || getY() < 0 || getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT)
    {
        die();
        return;
    }
    if(getWorld()->overlap(this, getWorld()->getGhostRacer()))
    {
        getWorld()->saveSoul();
        die();
        getWorld()->playSound(SOUND_GOT_SOUL);
        getWorld()->addtoScore(100);
    }
    setDirection(getDirection()+10);
    
}
