//
//  BorderLine.hpp
//  GhostRacer
//
//  Created by Justin Hee on 2/17/21.
//  Copyright © 2021 David Smallberg. All rights reserved.
//

#ifndef BORDERLINE_H
#define BORDERLINE_H

#include "Actor.h"

class BorderLine : public Actor
{
public:
    BorderLine(StudentWorld* world, int imageID, double startX, double startY, int startDirection = 0, double size = 2.0, int depth = 2, int VSpeed = -4, int HSpeed = 0);
    virtual void doSomething();
    virtual bool isCollisionAvoidanceWorthy() const;
};

#endif /* BORDERLINE_H */
