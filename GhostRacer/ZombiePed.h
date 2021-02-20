//
//  ZombiePed.hpp
//  GhostRacer
//
//  Created by Justin Hee on 2/17/21.
//  Copyright © 2021 David Smallberg. All rights reserved.
//

#ifndef ZOMBIEPED_H
#define ZOMBIEPED_H
#include "GameConstants.h"
#include "Pedestrian.h"

class StudentWorld;
class ZombiePed : public Pedestrian
{
public:
    ZombiePed(StudentWorld* world, double startX, double startY, int imageID = IID_ZOMBIE_PED, int startDirection = 0, double size = 3.0, int timeToGrunt = 0);
    virtual void doSomething();
private:
    int m_timeToGrunt;
};


#endif /* ZOMBIEPED_H */
