//
//  Pedestrian.hpp
//  GhostRacer
//
//  Created by Justin Hee on 2/17/21.
//  Copyright © 2021 David Smallberg. All rights reserved.
//

#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include "Actor.h"


class Pedestrian : public Actor
{
public:
    Pedestrian(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double size, int depth = 0, int VSpeed = -4, int HSpeed = 0, int health = 2, int movementPlanDistance = 0);
    virtual bool isCollisionAvoidanceWorthy() const;
    virtual void doSomething();
    void setMovementPlanDistance(int d);
    int getMovementPlanDistance() const;
    void damage(int damage);
    int getHealth() const;
private:
    int m_movementPlanDistance;
    int m_health;
};

#endif /* PEDESTRIAN_H */

/*
 1. A zombie pedestrian object must have an image ID of IID_ZOMBIE_PED.
 2. A zombie pedestrian must always start at the proper location as passed into its
 constructor.
 3. A zombie pedestrian has a direction of 0 degrees.
 4. A zombie pedestrian has a size of 3.0.
 5. A zombie pedestrian has a depth of 0.
 6. A zombie pedestrian starts with a movement plan distance of 0, meaning it has no
 plan to move in its current direction.
 7. A zombie pedestrian has a starting vertical speed of -4.
 8. A zombie pedestrian has a starting horizontal speed of 0.
 9. A zombie pedestrian starts out in an “alive” state.
 10. A zombie pedestrian starts with 2 hit points.
 11. A zombie pedestrian starts with zero ticks until it grunts next.
 12. A zombie pedestrian is always a “collision avoidance-worthy actor”.
 
 
 
 1. A human pedestrian object must have an image ID of IID_HUMAN_PED.
 2. A human pedestrian must always start at the proper location as passed to its
 constructor.
 3. A human pedestrian has a direction of 0 degrees.
 4. A human pedestrian has a size of 2.0.
 5. A human pedestrian has a depth of 0.
 6. A human pedestrian starts with a movement plan distance of 0, meaning it starts
 with no plan to move in its current direction.
 7. A human pedestrian has a starting vertical speed of -4.
 8. A human pedestrian has a starting horizontal speed of 0.
 9. A human pedestrian starts out in an “alive” state.
 10. A human pedestrian starts with 2 hit points.
 11. A human pedestrian is always a “collision avoidance-worthy actor”.
 */
