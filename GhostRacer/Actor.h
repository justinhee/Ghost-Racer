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
    int getNumSprays() const;
    void increaseSprays(int amt);
    void spin();
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
    HealingGoodie(StudentWorld* world, double startX, double startY);
    virtual void doSomething();
    virtual void doActivity(GhostRacer* gr);
    virtual int getScoreIncrease() const;
    virtual bool selfDestructs() const;
    virtual bool isSprayable() const;
    
};

//HOLYWATERGOODIE CLASS
class HolyWaterGoodie : public GhostRacerActivatedObject
{
public:
    HolyWaterGoodie(StudentWorld* world, double startX, double startY);
    virtual void doSomething();
    virtual void doActivity(GhostRacer* gr);
    virtual int getScoreIncrease() const;
    virtual bool selfDestructs() const;
    virtual bool isSprayable() const;
};

//OILSLICK CLASS
class OilSlick : public GhostRacerActivatedObject
{
public:
    OilSlick(StudentWorld* world, double startX, double startY);
    virtual void doSomething();
    virtual void doActivity(GhostRacer* gr);
    virtual int getScoreIncrease() const;
    virtual int getSound() const;
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

