//
//  GhostRacer.cpp
//  GhostRacer
//
//  Created by Justin Hee on 2/16/21.
//  Copyright © 2021 David Smallberg. All rights reserved.
//

#include "GhostRacer.h"
#include "StudentWorld.h"
#include <cmath>

GhostRacer::GhostRacer(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double size, int depth, int VSpeed, int HSpeed, int health, int holyWaterSpray) :
Actor(world, imageID, startX, startY, startDirection, size, depth, VSpeed, HSpeed),
Damageable(health),
m_holyWaterSpray(holyWaterSpray)
{

}
void GhostRacer::doSomething()
{
    if(!isAlive())
        return;
    if(getX() <= ROAD_CENTER - ROAD_WIDTH/2)
    {
        damage(10);
        setDirection(82);
        getWorld()->playSound(SOUND_VEHICLE_CRASH);
    }
    else if(getX() >= ROAD_CENTER + ROAD_WIDTH/2)
    {
        damage(10);
        setDirection(98);
        getWorld()->playSound(SOUND_VEHICLE_CRASH);
    }
    else
    {
        int ch;
        if(getWorld()->getKey(ch))
        {
            switch(ch)
            {
                case KEY_PRESS_SPACE:
                    if(m_holyWaterSpray>0)
                    {
                        //TODO: add holyWater object
                        m_holyWaterSpray--;
                        getWorld()->playSound(SOUND_PLAYER_SPRAY);
                    }
                    break;
                case KEY_PRESS_LEFT:
                    if(getDirection() < 114)
                        setDirection(getDirection()+8);
                    break;
                case KEY_PRESS_RIGHT:
                    if(getDirection() > 66)
                        setDirection(getDirection()-8);
                    break;
                case KEY_PRESS_UP:
                    if(getVSpeed() < 5)
                        setVSpeed(getVSpeed()+1);
                    break;
                case KEY_PRESS_DOWN:
                    if(getVSpeed() > -1)
                        setVSpeed(getVSpeed()-1);
                    break;
                default:
                    break;
            }
        }
    }
    double max_shift_per_tick = 4.0;
    int direction = getDirection();
    const double PI = 4 * atan(1.0);
    
    double delta_x = cos(direction*PI/180)*max_shift_per_tick;
    double cur_x = getX();
    double cur_y = getY();
    moveTo(cur_x + delta_x, cur_y);
    
    
}
bool GhostRacer::isCollisionAvoidanceWorthy() const
{
    return true;
}

bool GhostRacer::isAlive() const
{
    return getHealth() > 0;
}


