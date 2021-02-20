//
//  HumanPed.hpp
//  GhostRacer
//
//  Created by Justin Hee on 2/17/21.
//  Copyright © 2021 David Smallberg. All rights reserved.
//

#ifndef HUMANPED_H
#define HUMANPED_H

#include "GameConstants.h"
#include "Pedestrian.h"

class StudentWorld;
class HumanPed : public Pedestrian
{
public:
    HumanPed(StudentWorld* world, double startX, double startY, int imageID = IID_HUMAN_PED, int startDirection = 0, double size = 2.0);
    virtual void doSomething();
};

#endif /* HUMANPED_H */
