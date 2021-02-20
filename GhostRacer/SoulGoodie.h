//
//  SoulGoodie.hpp
//  GhostRacer
//
//  Created by Justin Hee on 2/19/21.
//  Copyright © 2021 David Smallberg. All rights reserved.
//

#ifndef SOULGOODIE_H
#define SOULGOODIE_H

#include "Actor.h"
#include "GameConstants.h"

class SoulGoodie : public Actor
{
public:
    SoulGoodie(StudentWorld* world, double startX, double startY, int imageID = IID_SOUL_GOODIE, int startDirection = 0, double size = 4.0, int depth = 2, int VSpeed = -4, int HSpeed = 0);
    virtual void doSomething();
};

#endif /* SOULGOODIE_H */
