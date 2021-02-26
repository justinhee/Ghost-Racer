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
    Actor(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double size, int depth, double VSpeed = 0, double HSpeed = 0, bool alive = true);
    virtual void doSomething() = 0;
    virtual bool isAlive() const;
    virtual bool isCollisionAvoidanceWorthy();
    StudentWorld* getWorld() const;
    double getVSpeed() const;
    void setVSpeed(double newVSpeed);
    double getHSpeed() const;
    void setHSpeed(double newHSpeed);
    virtual void die();
    virtual void move();
    
private:
    StudentWorld* m_world;
    bool m_alive;
    int m_VSpeed;
    int m_HSpeed;
};

//GHOSTRACER CLASS
class GhostRacer : public Actor
{
public:
    GhostRacer(StudentWorld* world, int imageID = IID_GHOST_RACER, double startX = 128, double startY = 32, int startDirection = 90, double size = 4.0, int depth = 0, double VSpeed = 0, double HSpeed = 0, int health = 100, int holyWaterSpray = 10);
    virtual void doSomething();
    virtual bool isCollisionAvoidanceWorthy() const;
    virtual void die();
    void damage(int damage);
    void heal(int health);
    int getHealth() const;
private:
    int m_holyWaterSpray;
    int m_health;
};

//BORDERLINE CLASS
class BorderLine : public Actor
{
public:
    BorderLine(StudentWorld* world, int imageID, double startX, double startY, int startDirection = 0, double size = 2.0, int depth = 2, double VSpeed = -4, double HSpeed = 0);
    virtual void doSomething();
};

//PEDESTRIAN CLASS
class Pedestrian : public Actor
{
public:
    Pedestrian(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double size, int depth = 0, double VSpeed = -4, double HSpeed = 0, int health = 2, int movementPlanDistance = 0);
    virtual bool isCollisionAvoidanceWorthy() const;
    virtual void doSomething();
    void setMovementPlanDistance(int d);
    int getMovementPlanDistance() const;
    virtual void damage(int damage);
    int getHealth() const;
private:
    int m_movementPlanDistance;
    int m_health;
};

//ZOMBIEPEDESTRIAN CLASS
class ZombiePed : public Pedestrian
{
public:
    ZombiePed(StudentWorld* world, double startX, double startY, int imageID = IID_ZOMBIE_PED, int startDirection = 0, double size = 3.0, int timeToGrunt = 0);
    virtual void doSomething();
    virtual void damage(int damage);
private:
    int m_timeToGrunt;
};

//HUMANPEDESTRIAN CLASS
class HumanPed : public Pedestrian
{
public:
    HumanPed(StudentWorld* world, double startX, double startY, int imageID = IID_HUMAN_PED, int startDirection = 0, double size = 2.0);
    virtual void doSomething();
};

//SOULGOODIE CLASS
class SoulGoodie : public Actor
{
public:
    SoulGoodie(StudentWorld* world, double startX, double startY, int imageID = IID_SOUL_GOODIE, int startDirection = 0, double size = 4.0, int depth = 2, double VSpeed = -4, double HSpeed = 0);
    virtual void doSomething();
};

//HEALINGGOODIE CLASS
class HealingGoodie : public Actor
{
public:
    HealingGoodie(StudentWorld* world, double startX, double startY, int imageID = IID_HEAL_GOODIE, int startDirection = 0, double size = 1.0, int depth = 2, double VSpeed = -4, double HSpeed = 0);
    virtual void doSomething();
    
};

//HOLYWATERPROJECTILE CLASS
class HolyWaterProjectile : public Actor
{
public:
    HolyWaterProjectile(StudentWorld* world, double startX, double startY, int startDirection, int imageID = IID_HOLY_WATER_PROJECTILE, double size = 1.0, int depth = 1, int distanceToGo = 160);
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
