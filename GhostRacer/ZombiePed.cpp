//
//  ZombiePed.cpp
//  GhostRacer
//
//  Created by Justin Hee on 2/17/21.
//  Copyright © 2021 David Smallberg. All rights reserved.
//

#include "ZombiePed.h"
#include "StudentWorld.h"
#include "GhostRacer.h"

ZombiePed::ZombiePed(StudentWorld* world, double startX, double startY, int imageID, int startDirection, double size, int timeToGrunt) :
Pedestrian(world, imageID, startX, startY, startDirection, size),
m_timeToGrunt(timeToGrunt)
{}

void ZombiePed::doSomething()
{
    if(!isAlive())
        return;
    if(getWorld()->overlap(this, getWorld()->getGhostRacer()))
    {
        damage(2);
        getWorld()->getGhostRacer()->damage(5);
        return;
    }
    int delta_x = getX() - getWorld()->getGhostRacer()->getX();
    if(delta_x > -30 && delta_x < 0)
    {
        setDirection(270);
        setHSpeed(1);
    }
    else if(delta_x > 0 && delta_x < 30)
    {
        setDirection(270);
        setHSpeed(-1);
    }
    else if(delta_x == 0)
    {
        setDirection(270);
        setHSpeed(0);
    }
    //c) decrease number of ticks before it grunts next
    m_timeToGrunt--;
    
    if(m_timeToGrunt <= 0)
    {
        getWorld()->playSound(SOUND_ZOMBIE_ATTACK);
        m_timeToGrunt = 20;
    }
    
    //MOVE
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
    
    if(getMovementPlanDistance() > 0)
    {
        setMovementPlanDistance(getMovementPlanDistance()-1);
        return;
    }
    else {
        int newHSpeed = 0;
        while(newHSpeed == 0)
        {
            newHSpeed = randInt(-3, 3);
        }
        setHSpeed(newHSpeed);
        int newDistance = randInt(4, 32);
        setMovementPlanDistance(newDistance);
        if(newHSpeed < 0)
            setDirection(180);
        else
            setDirection(0);
    }
    /*
     5. If the zombie pedestrian’s movement plan distance is greater than zero, then
     decrement it by one and immediately return.
    6. Otherwise, it’s time to pick a new movement plan for the zombie pedestrian:
    a. Set the zombie pedestrian’s horizontal speed to a random integer from -3
    to 3 inclusive, NOT including zero.
    b. Set the movement plan distance to a random integer between 4 and 32,
    inclusive.
    c. Set the zombie pedestrian’s direction to 180 degrees if its new horizontal
    speed is less than zero. Otherwise, set its direction to 0 degrees if its new
    horizontal speed is greater than zero.
     */
    
    
}
