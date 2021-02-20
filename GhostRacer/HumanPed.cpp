//
//  HumanPed.cpp
//  GhostRacer
//
//  Created by Justin Hee on 2/17/21.
//  Copyright © 2021 David Smallberg. All rights reserved.
//

#include "HumanPed.h"
#include "StudentWorld.h"
#include "GhostRacer.h"

HumanPed::HumanPed(StudentWorld* world, double startX, double startY, int imageID, int startDirection, double size) :
Pedestrian(world, imageID, startX, startY, startDirection, size)
{}

void HumanPed::doSomething()
{
    if(!isAlive())
        return;
    if(getWorld()->overlap(this, getWorld()->getGhostRacer()))
    {
        die();
        getWorld()->getGhostRacer()->die();
        return;
    }
    
    int vert_speed = getVSpeed()-getWorld()->getGhostRacer()->getVSpeed();
    int horiz_speed = getHSpeed();
    double new_y = getY() + vert_speed;
    double new_x = getX() + horiz_speed;
    moveTo(new_x, new_y);
    if(getX() < 0 || getY() < 0 || getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT)
    {
        die();
        return;
    }
    setMovementPlanDistance(getMovementPlanDistance()-1);
    if(getMovementPlanDistance() > 0)
    {
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
     4. Decrement the human pedestrian’s movement plan distance.
     5. If the distance is greater than zero, then immediately return.
     6. Otherwise, it’s time to pick a new movement plan for the human pedestrian:
     a. Set the human pedestrian’s horizontal speed to a random integer from -3 to
     3, inclusive, NOT including zero.
     b. Set the length of the movement plan to a random integer between 4 and
     32, inclusive.
     c. Set the human pedestrian’s direction to 180 degrees if its new horizontal
     speed is less than zero. Otherwise set its direction to 0 degrees if its new
     horizontal speed is greater than zero.
     */
        
}
