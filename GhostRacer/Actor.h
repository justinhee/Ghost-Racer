#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


class StudentWorld;

//ACTOR CLASS
class Actor : public GraphObject
{
public:
    Actor(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double size, int depth, double VSpeed = 0, double HSpeed = 0);
    virtual void doSomething() = 0;
    virtual bool isAlive() const;
    virtual bool isCollisionAvoidanceWorthy() const;
    StudentWorld* getWorld() const;
    double getVSpeed() const;
    void setVSpeed(double newVSpeed);
    double getHSpeed() const;
    void setHSpeed(double newHSpeed);
    virtual void die();
    virtual bool move();
    virtual bool beSprayedIfAppropriate();
    
private:
    StudentWorld* m_world;
    bool m_alive;
    int m_VSpeed;
    int m_HSpeed;
};

//AGENT CLASS
class Agent : public Actor
{
public:
    Agent(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double size, int hp, double VSpeed, double HSpeed);
    virtual bool isCollisionAvoidanceWorthy() const;

      // Get hit points.
    int getHealth() const;

      // Increase hit points by hp.
    void heal(int health);

      // Do what the spec says happens when hp units of damage is inflicted.
      // Return true if this agent dies as a result, otherwise false.
    virtual bool damage(int damage);

      // What sound should play when this agent is damaged but does not die?
    virtual int soundWhenHurt() const;

      // What sound should play when this agent is damaged and dies?
    virtual int soundWhenDie() const;
private:
    int m_health;
};








//GHOSTRACER CLASS
class GhostRacer : public Agent
{
public:
    GhostRacer(StudentWorld* world);
    virtual void doSomething();
    virtual void die();
    virtual int soundWhenDie() const;
private:
    int m_holyWaterSpray;
};

//BORDERLINE CLASS
class BorderLine : public Actor
{
public:
    BorderLine(StudentWorld* world, int imageID, double startX, double startY, int startDirection = 0, double size = 2.0, int depth = 2, double VSpeed = -4, double HSpeed = 0);
    virtual void doSomething();
};

//PEDESTRIAN CLASS
class Pedestrian : public Agent
{
public:
    Pedestrian(StudentWorld* world, int imageID, double startX, double startY, double size);
    void moveAndPossiblyPickPlan();
    virtual int soundWhenHurt() const;
    virtual int soundWhenDie() const;
private:
    int m_movementPlanDistance;
};

//ZOMBIEPEDESTRIAN CLASS
class ZombiePed : public Pedestrian
{
public:
    ZombiePed(StudentWorld* world, double startX, double startY);
    virtual void doSomething();
    virtual bool beSprayedIfAppropriate();
private:
    int m_timeToGrunt;
};

//HUMANPEDESTRIAN CLASS
class HumanPed : public Pedestrian
{
public:
    HumanPed(StudentWorld* world, double startX, double startY);
    virtual void doSomething();
    virtual bool beSprayedIfAppropriate();
};

//ZOMBIECAB CLASS
class ZombieCab : public Agent
{
public:
    ZombieCab(StudentWorld* world, double startX, double startY);
    virtual void doSomething();
    virtual bool beSprayedIfAppropriate();
    virtual int soundWhenHurt() const;
    virtual int soundWhenDie() const;
private:
    bool m_hasDamagedGhostRacer;
    int m_movementPlanDistance;
};


//GHOSTRACERACTIVATEDOBJECT CLASS
class GhostRacerActivatedObject : public Actor
{
public:
    GhostRacerActivatedObject(StudentWorld* sw, int imageID, double x, double y, double size, int dir);
    virtual void doSomething();
    virtual bool beSprayedIfAppropriate();

      // Do the object's special activity (increase health, spin Ghostracer, etc.)
    virtual void doActivity(GhostRacer* gr) = 0;

      // Return the object's increase to the score when activated.
    virtual int getScoreIncrease() const = 0;

      // Return the sound to be played when the object is activated.
    virtual int getSound() const;

      // Return whether the object dies after activation.
    virtual bool selfDestructs() const = 0;

      // Return whether the object is affected by a holy water projectile.
    virtual bool isSprayable() const = 0;
};

//SOULGOODIE CLASS
class SoulGoodie : public GhostRacerActivatedObject
{
public:
    SoulGoodie(StudentWorld* world, double startX, double startY);
    virtual void doActivity(GhostRacer *gr);
    virtual int getScoreIncrease() const;
    virtual int getSound() const;
    virtual bool selfDestructs() const;
    virtual void doSomething();
    virtual bool isSprayable() const;
};

//HEALINGGOODIE CLASS
class HealingGoodie : public GhostRacerActivatedObject
{
public:
    HealingGoodie(StudentWorld* world, double startX, double startYZ);
    virtual void doSomething();
    virtual void doActivity(GhostRacer* gr);
    virtual int getScoreIncrease() const;
    virtual bool selfDestructs() const;
    virtual bool isSprayable() const;
    
};






//SPRAY CLASS
class Spray : public Actor
{
public:
    Spray(StudentWorld* world, double startX, double startY, int startDirection);
    virtual void doSomething();
private:
    int m_distanceToGo;
    
};


#endif // ACTOR_H_




















//// Possible interfaces for actors.  You may use all, some, or none
//// of this, as you wish.
//
//// One of the design goals is to reduce the coupling between StudentWorld.h
//// and Actor.h as much as possible.  Notice that in fact, Actor.h
//// does not need to include StudentWorld.h at all.
//
//#ifndef ACTOR_INCLUDED
//#define ACTOR_INCLUDED
//
//#include "GraphObject.h"
//
//class StudentWorld;
//
//class Actor : public GraphObject
//{
//public:
////    Actor(StudentWorld* sw, int imageID, double x, double y, double size, int dir, int depth, double VSpeed);
//
//      // Action to perform for each tick.
//    virtual void doSomething() = 0;
//
//      // Is this actor dead?
//    bool isDead() const;
//
//      // Mark this actor as dead.
//    void die();
//
//      // Get this actor's world
//    StudentWorld* world() const;
//
//      // Get this actor's vertical speed.
//    double getVerticalSpeed() const;
//
//      // Set this actor's vertical speed.
//    void setVerticalSpeed(double speed);
//
//      // If this actor is affected by holy water projectiles, then inflict that
//      // affect on it and return true; otherwise, return false.
//    virtual bool beSprayedIfAppropriate();
//
//      // Does this object affect zombie cab placement and speed?
//    virtual bool isCollisionAvoidanceWorthy() const;
//
//      // Adjust the x coordinate by dx to move to a position with a y coordinate
//      // determined by this actor's vertical speed relative to GhostRacser's
//      // vertical speed.  Return true if the new position is within the view;
//      // otherwise, return false, with the actor dead.
//    virtual bool moveRelativeToGhostRacerVerticalSpeed(double dx);
//private:
//    StudentWorld* m_world;
//    bool m_alive;
//    double m_VSpeed;
//    double m_HSpeed;
//
//};
//
//class BorderLine : public Actor
//{
//public:
//    BorderLine(StudentWorld* sw, double x, double y, int imageID);
//    virtual void doSomething();
//};
//
//class Agent : public Actor
//{
//public:
//    Agent(StudentWorld* sw, int imageID, double x, double y, double size, int dir, int hp);
//    virtual bool isCollisionAvoidanceWorthy() const;
//
//      // Get hit points.
//    int getHP() const;
//
//      // Increase hit points by hp.
//    void getHP(int hp) const;
//
//      // Do what the spec says happens when hp units of damage is inflicted.
//      // Return true if this agent dies as a result, otherwise false.
//    virtual bool takeDamageAndPossiblyDie(int hp);
//
//      // What sound should play when this agent is damaged but does not die?
//    virtual int soundWhenHurt();
//
//      // What sound should play when this agent is damaged and dies?
//    virtual int soundWhenDie();
//};
//
//class GhostRacer : public Agent
//{
//public:
//    GhostRacer(StudentWorld* sw, double x, double y);
//    virtual void doSomething();
//    virtual int soundWhenDie() const;
//
//      // How many holy water projectiles does the object have?
//    int getNumSprays() const;
//
//      // Increase the number of holy water projectiles the object has.
//    void increaseSprays(int amt);
//
//      // Spin as a result of hitting an oil slick.
//    void spin();
//};
//
//class Pedestrian : public Agent
//{
//public:
//    Pedestrian(StudentWorld* sw, int imageID, double x, double y, double size);
//    virtual int soundWhenHurt() const;
//    virtual int soundWhenDie() const;
//
//      // Get the pedestrian's horizontal speed
//    int getHorizSpeed() const;
//
//      // Set the pedestrian's horizontal speed
//    void setHorizSpeed(int s);
//
//      // Move the pedestrian.  If the pedestrian doesn't go off screen and
//      // should pick a new movement plan, pick a new plan.
//    void moveAndPossiblyPickPlan();
//};
//
//class HumanPedestrian : public Pedestrian
//{
//public:
//    HumanPedestrian(StudentWorld* sw, double x, double y);
//    virtual void doSomething();
//    virtual bool beSprayedIfAppropriate();
//    virtual bool takeDamageAndPossiblyDie(int hp);
//};
//
//class ZombiePedestrian : public Pedestrian
//{
//public:
//    ZombiePedestrian(StudentWorld* sw, double x, double y);
//    virtual void doSomething();
//    virtual bool beSprayedIfAppropriate();
//};
//
//class ZombieCab : public Agent
//{
//public:
//    ZombieCab(StudentWorld* sw, double x, double y);
//    virtual void doSomething();
//    virtual bool beSprayedIfAppropriate();
//};
//
//class Spray : public Actor
//{
//public:
//    Spray(StudentWorld* sw, double x, double y, int dir);
//    virtual void doSomething();
//};
//
//class GhostRacerActivatedObject : public Actor
//{
//public:
//    GhostRacerActivatedObject(StudentWorld* sw, int imageID, double x, double y, double size, int dir);
//    virtual bool beSprayedIfAppropriate();
//
//      // Do the object's special activity (increase health, spin Ghostracer, etc.)
//    virtual void doActivity(GhostRacer* gr) = 0;
//
//      // Return the object's increase to the score when activated.
//    virtual int getScoreIncrease() const = 0;
//
//      // Return the sound to be played when the object is activated.
//    virtual int getSound() const;
//
//      // Return whether the object dies after activation.
//    virtual bool selfDestructs() const = 0;
//
//      // Return whether the object is affected by a holy water projectile.
//    virtual bool isSprayable() const = 0;
//};
//
//class OilSlick : public GhostRacerActivatedObject
//{
//public:
//    OilSlick(StudentWorld* sw, double x, double y);
//    virtual void doSomething();
//    virtual void doActivity(GhostRacer* gr);
//    virtual int getScoreIncrease() const;
//    virtual int getSound() const;
//    virtual bool selfDestructs() const;
//    virtual bool isSprayable() const;
//};
//
//class HealingGoodie : public GhostRacerActivatedObject
//{
//public:
//    HealingGoodie(StudentWorld* sw, double x, double y);
//    virtual void doSomething();
//    virtual void doActivity(GhostRacer* gr);
//    virtual int getScoreIncrease() const;
//    virtual bool selfDestructs() const;
//    virtual bool isSprayable() const;
//};
//
//class HolyWaterGoodie : public GhostRacerActivatedObject
//{
//public:
//    HolyWaterGoodie(StudentWorld* sw, double x, double y);
//    virtual void doSomething();
//    virtual void doActivity(GhostRacer* gr);
//    virtual int getScoreIncrease() const;
//    virtual bool selfDestructs() const;
//    virtual bool isSprayable() const;
//};
//
//class SoulGoodie : public GhostRacerActivatedObject
//{
//public:
//    SoulGoodie(StudentWorld* sw, double x, double y);
//    virtual void doSomething();
//    virtual void doActivity(GhostRacer* gr);
//    virtual int getScoreIncrease() const;
//    virtual int getSound() const;
//    virtual bool selfDestructs() const;
//    virtual bool isSprayable() const;
//};
//
//#endif // ACTOR_INCLUDED

/*If the zombie cab is not currently alive, its doSomething() method must return
 immediately – none of the following steps should be performed.
 2. If the zombie cab overlaps with the Ghost Racer:
 a. If the zombie cab has already damaged Ghost Racer, it must immediately
 skip to step 3.
 b. Otherwise…
 c. Play a sound of SOUND_VEHICLE_CRASH.
 d. The zombie cab must do 20 points of damage to the Ghost Racer (see
 Ghost Racer’s section on what it does when it’s damaged).
 39
 e. If the zombie cab is to the left of the Ghost Racer or has the same X
 coordinate as Ghost Racer then the zombie cab must:
 i. Set its horizontal speed to -5.
 ii. Set its direction equal to: 120 degrees plus a random integer
 between [0,20).
 f. If the zombie cab is right of the Ghost Racer then it must:
 i. Set its horizontal speed to 5.
 ii. Set its direction equal to: 60 degrees minus a random integer
 between [0,20).
 g. The zombie cab must remember that it has now damaged Ghost Racer (so
 it doesn’t repeat the above steps for this zombie cab during subsequent
 ticks, even if the cab still overlaps with the Ghost Racer).
 3. The zombie cab must then move, using the following algorithm:
 a. Let vert_speed = the zombie cab’s current vertical speed - Ghost Racer’s
 current vertical speed
 b. Let horiz_speed = the zombie cab’s horizontal speed
 c. Let new_y = zombie cab’s current y + vert_speed
 d. Let new_x = zombie cab’s current x + horiz_speed
 e. Adjust the zombie cab’s location to new_x, new_y using the
 GraphObject::moveTo() method.
 f. If the zombie cab has gone off of the screen (either its X or Y coordinate is
 less than zero, or its X coordinate is > VIEW_WIDTH, or its Y coordinate
 > VIEW_HEIGHT), it must set its status to not-alive, so it will be
 removed by StudentWorld later in this tick. It must then immediately
 return.
 4. If the zombie cab’s vertical speed is greater than Ghost Racer’s vertical speed (so
 the cab is moving up the screen) and there is a "collision-avoidance worthy" actor
 in the zombie cab's lane that is in front of that zombie cab:
 a. If the closest such actor is less than 96 vertical pixels in front of the
 zombie cab, decrease the zombie cab's vertical speed by .5 and
 immediately return.
 5. If the zombie cab's vertical speed is the same as or slower than Ghost Racer's
 vertical speed (so the cab is moving down the screen or holding steady with Ghost
 Racer) and there is a "collision-avoidance worthy" actor in the zombie cab's lane
 that is behind that zombie cab:
 a. If the closest such actor is less than 96 vertical pixels behind the zombie
 cab and is not Ghost Racer, increase the zombie cab's vertical speed by .5
 and immediately return.
 6. Decrement the zombie cab’s movement plan distance by one.
 7. If the zombie cab’s movement plan distance is greater than zero, then
 immediately return.
 8. Otherwise, it’s time to pick a new movement plan for the zombie cab:
 a. Set the zombie cab’s movement plan distance to a random integer between
 4 and 32, inclusive.
 b. Set the zombie cab’s vertical speed to its vertical speed + a random integer
 between -2 and 2, inclusive.*/
