#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
//goodies, projetile
//ACTOR IMPLEMENTATION
Actor::Actor(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double size, int depth, double VSpeed, double HSpeed) : GraphObject(imageID, startX, startY, startDirection, size, depth), m_world(world), m_alive(true), m_VSpeed(VSpeed), m_HSpeed(HSpeed)
{}

bool Actor::isAlive() const
{
    return m_alive;
}

bool Actor::isCollisionAvoidanceWorthy()
{
    return false;
}

StudentWorld* Actor::getWorld() const
{
    return m_world;
}

double Actor::getVSpeed() const
{
    return m_VSpeed;
}

void Actor::setVSpeed(double newVSpeed)
{
    m_VSpeed = newVSpeed;
}

double Actor::getHSpeed() const
{
    return m_HSpeed;
}

void Actor::setHSpeed(double newHSpeed)
{
    m_HSpeed = newHSpeed;
}

void Actor::die()
{
    m_alive = false;
}

bool Actor::move()
{
    double vert_speed = getVSpeed()-getWorld()->getGhostRacer()->getVSpeed();
    double horiz_speed = getHSpeed();
    
    double new_y = getY() + vert_speed;
    double new_x = getX() + horiz_speed;
    moveTo(new_x, new_y);
    if(getX() < 0 || getY() < 0 || getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT)
    {
        die();
        return false;
    }
    return true;

}

//AGENT IMPLEMENTATION
Agent::Agent(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double size, int hp, double VSpeed, double HSpeed) : Actor(world, imageID, startX, startY, startDirection, size, 0, VSpeed, HSpeed), m_health(hp)
{}

bool Agent::isCollisionAvoidanceWorthy() const
{
    return true;
}

int Agent::getHealth() const
{
    return m_health;
}

void Agent::heal(int health)
{
    if(m_health + health > 100)
        m_health = 100;
    else
        m_health += health;
}

bool Agent::damage(int damage)
{
    m_health -= damage;
    if(m_health < 0)
    {
        getWorld()->playSound(soundWhenDie());
        die();
        return true;
    }
    else
        getWorld()->playSound(soundWhenHurt());
    return false;
}



//GHOSTRACER IMPLEMENTATION
GhostRacer::GhostRacer(StudentWorld* world) :
Agent(world, IID_GHOST_RACER, 128, 32, 90, 4.0, 100, 0, 0),
m_holyWaterSpray(10)
{}

void GhostRacer::doSomething()
{
    if(!isAlive())
        return;
    if(getX() <= ROAD_CENTER - ROAD_WIDTH/2)
    {
        damage(10);
        setDirection(82);
    }
    else if(getX() >= ROAD_CENTER + ROAD_WIDTH/2)
    {
        damage(10);
        setDirection(98);
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

void GhostRacer::die()
{
    Actor::die();
    getWorld()->decLives();
}

int GhostRacer::soundWhenHurt() const
{
    return SOUND_VEHICLE_CRASH;
}

int GhostRacer::soundWhenDie() const
{
    return SOUND_PLAYER_DIE;
}


//BORDERLINE IMPLEMENTATION
BorderLine::BorderLine(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double size, int depth, double VSpeed, double HSpeed) :
Actor(world, imageID, startX, startY, startDirection, size, depth, VSpeed, HSpeed)
{}

void BorderLine::doSomething()
{
    move();
}

//PEDESTRIAN IMPLEMENTATION
Pedestrian::Pedestrian(StudentWorld* world, int imageID, double startX, double startY, double size, double VSpeed, double HSpeed, int health, int movementPlanDistance) :
Agent(world, imageID, startX, startY, 0, size, 2, -4, 0),
m_movementPlanDistance(movementPlanDistance)
{}

void Pedestrian::moveAndPossiblyPickPlan()
{
    if(!move())
    {
        return;
    }
    if(--m_movementPlanDistance <= 0)
    {
        int newHSpeed = 0;
        while(newHSpeed == 0)
        {
            newHSpeed = randInt(-3, 3);
        }
        setHSpeed(newHSpeed);
        int newDistance = randInt(4, 32);
        m_movementPlanDistance = newDistance;
        if(newHSpeed < 0)
            setDirection(180);
        else
            setDirection(0);
    }
}

int Pedestrian::soundWhenHurt() const
{
    return SOUND_PED_HURT;
}

int Pedestrian::soundWhenDie() const
{
    return SOUND_PED_DIE;
}



//ZOMBIEPEDESTRIAN IMPLEMENTATION
ZombiePed::ZombiePed(StudentWorld* world, double startX, double startY, double size, int timeToGrunt) :
Pedestrian(world, IID_ZOMBIE_PED, startX, startY, 0, size),
m_timeToGrunt(timeToGrunt)
{}

void ZombiePed::doSomething()
{
    if(!isAlive())
        return;
    if(getWorld()->overlap(this, getWorld()->getGhostRacer()))
    {
        damage(2);
        getWorld()->getGhostRacer()->damage(5);
        return;
    }
    double delta_x = getX() - getWorld()->getGhostRacer()->getX();
    if(delta_x > -30 && delta_x < 0)
    {
        setDirection(270);
        setHSpeed(1);
    }
    else if(delta_x > 0 && delta_x < 30)
    {
        setDirection(270);
        setHSpeed(-1);
    }
    else if(delta_x == 0)
    {
        setDirection(270);
        setHSpeed(0);
    }
    //c) decrease number of ticks before it grunts next
    m_timeToGrunt--;
    
    if(m_timeToGrunt <= 0)
    {
        getWorld()->playSound(SOUND_ZOMBIE_ATTACK);
        m_timeToGrunt = 20;
    }
    
    //MOVE
    moveAndPossiblyPickPlan();

    
}

//bool ZombiePed::damage(int damage)
//{
//
//    if(Pedestrian::damage(damage) && !getWorld()->overlap(this, getWorld()->getGhostRacer()))
//    {
//        if(randInt(1,5)==1)
//        {
//            getWorld()->addActor(new HealingGoodie(getWorld(), getX(), getY()));
//        }
//    }
//    return !isAlive();
//
//}

//HUMANPEDESTRIAN IMPLEMENTATION
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
    
    moveAndPossiblyPickPlan();
}

//SOULGOODIE IMPLEMENTATION
SoulGoodie::SoulGoodie(StudentWorld* world, double startX, double startY, int imageID, int startDirection, double size, int depth, double VSpeed, double HSpeed) :
Actor(world, imageID, startX, startY, startDirection, size, depth, VSpeed, HSpeed)
{}

void SoulGoodie::doSomething()
{
    move();
    if(getWorld()->overlap(this, getWorld()->getGhostRacer()))
    {
        getWorld()->saveSoul();
        die();
        getWorld()->playSound(SOUND_GOT_SOUL);
        getWorld()->addtoScore(100);
    }
    setDirection(getDirection()+10);
    
}

//HEALINGGOODIEIMPLEMENTATION
HealingGoodie::HealingGoodie(StudentWorld* world, double startX, double startY, int imageID, int startDirection, double size, int depth, double VSpeed, double HSpeed) :
Actor(world, IID_HEAL_GOODIE, startX, startY, startDirection, size, depth, VSpeed, HSpeed)
{}
void HealingGoodie::doSomething()
{
    move();
    if(getWorld()->overlap(this, getWorld()->getGhostRacer()))
    {
        getWorld()->getGhostRacer()->heal(10);
        die();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->addtoScore(250);
    }
}

//HOLYWATERPROJECTILE IMPLEMENTATION
HolyWaterProjectile::HolyWaterProjectile(StudentWorld* world, double startX, double startY, int startDirection, int imageID, double size, int depth, int distanceToGo) :
Actor(world, imageID, startX, startY, startDirection, size, depth),
m_distanceToGo(distanceToGo)
{}






















//#include "Actor.h"
//#include "StudentWorld.h"
//
//
//Actor::Actor(StudentWorld* sw, int imageID, double x, double y, double size, int dir, int depth, double VSpeed) : GraphObject(imageID, x, y, dir, size, depth), m_world(sw), m_alive(true), m_VSpeed(VSpeed)
//{}
//
////      // Is this actor dead?
//bool Actor::isDead() const
//{
//    return !m_alive;
//}
////
////      // Mark this actor as dead.
//void Actor::die()
//{
//    m_alive = false;
//}
////
////      // Get this actor's world
//StudentWorld* Actor::world() const
//{
//    return m_world;
//}
////
////      // Get this actor's vertical speed.
//double Actor::getVerticalSpeed() const
//{
//    return m_VSpeed;
//}
////
////      // Set this actor's vertical speed.
//void Actor::setVerticalSpeed(double speed)
//{
//    m_VSpeed = speed;
//}
////
////      // If this actor is affected by holy water projectiles, then inflict that
////      // affect on it and return true; otherwise, return false.
//bool Actor::beSprayedIfAppropriate()
//{
//    return false;
//}
////
////      // Does this object affect zombie cab placement and speed?
////    virtual bool isCollisionAvoidanceWorthy() const;
////
////      // Adjust the x coordinate by dx to move to a position with a y coordinate
////      // determined by this actor's vertical speed relative to GhostRacser's
////      // vertical speed.  Return true if the new position is within the view;
////      // otherwise, return false, with the actor dead.
//bool Actor::moveRelativeToGhostRacerVerticalSpeed(double dx)
//{
//    double vert_speed = getVerticalSpeed()-world()->getGhostRacer()->getVerticalSpeed();
//    double new_y = getY() + vert_speed;
//    double new_x = getX() + dx;
//    moveTo(new_x, new_y);
//    if(getX() < 0 || getY() < 0 || getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT)
//    {
//        die();
//        return false;
//    }
//    return true;
//
//}
////
////};
////
//
////BORDERLINE
//
//BorderLine::BorderLine(StudentWorld* sw, double x, double y, int imageID) :
//Actor(sw, imageID, x, y, 2.0, 0, 2, -4.0)
//{}
////    virtual void doSomething();
////};
////
////class Agent : public Actor
////{
////public:
////    Agent(StudentWorld* sw, int imageID, double x, double y, double size, int dir, int hp);
////    virtual bool isCollisionAvoidanceWorthy() const;
////
////      // Get hit points.
////    int getHP() const;
////
////      // Increase hit points by hp.
////    void getHP(int hp) const;
////
////      // Do what the spec says happens when hp units of damage is inflicted.
////      // Return true if this agent dies as a result, otherwise false.
////    virtual bool takeDamageAndPossiblyDie(int hp);
////
////      // What sound should play when this agent is damaged but does not die?
////    virtual int soundWhenHurt();
////
////      // What sound should play when this agent is damaged and dies?
////    virtual int soundWhenDie();
////};
////
////class GhostRacer : public Agent
////{
////public:
////    GhostRacer(StudentWorld* sw, double x, double y);
////    virtual void doSomething();
////    virtual int soundWhenDie() const;
////
////      // How many holy water projectiles does the object have?
////    int getNumSprays() const;
////
////      // Increase the number of holy water projectiles the object has.
////    void increaseSprays(int amt);
////
////      // Spin as a result of hitting an oil slick.
////    void spin();
////};
////
////class Pedestrian : public Agent
////{
////public:
////    Pedestrian(StudentWorld* sw, int imageID, double x, double y, double size);
////    virtual int soundWhenHurt() const;
////    virtual int soundWhenDie() const;
////
////      // Get the pedestrian's horizontal speed
////    int getHorizSpeed() const;
////
////      // Set the pedestrian's horizontal speed
////    void setHorizSpeed(int s);
////
////      // Move the pedestrian.  If the pedestrian doesn't go off screen and
////      // should pick a new movement plan, pick a new plan.
////    void moveAndPossiblyPickPlan();
////};
////
////class HumanPedestrian : public Pedestrian
////{
////public:
////    HumanPedestrian(StudentWorld* sw, double x, double y);
////    virtual void doSomething();
////    virtual bool beSprayedIfAppropriate();
////    virtual bool takeDamageAndPossiblyDie(int hp);
////};
////
////class ZombiePedestrian : public Pedestrian
////{
////public:
////    ZombiePedestrian(StudentWorld* sw, double x, double y);
////    virtual void doSomething();
////    virtual bool beSprayedIfAppropriate();
////};
////
////class ZombieCab : public Agent
////{
////public:
////    ZombieCab(StudentWorld* sw, double x, double y);
////    virtual void doSomething();
////    virtual bool beSprayedIfAppropriate();
////};
////
////class Spray : public Actor
////{
////public:
////    Spray(StudentWorld* sw, double x, double y, int dir);
////    virtual void doSomething();
////};
////
////class GhostRacerActivatedObject : public Actor
////{
////public:
////    GhostRacerActivatedObject(StudentWorld* sw, int imageID, double x, double y, double size, int dir);
////    virtual bool beSprayedIfAppropriate();
////
////      // Do the object's special activity (increase health, spin Ghostracer, etc.)
////    virtual void doActivity(GhostRacer* gr) = 0;
////
////      // Return the object's increase to the score when activated.
////    virtual int getScoreIncrease() const = 0;
////
////      // Return the sound to be played when the object is activated.
////    virtual int getSound() const;
////
////      // Return whether the object dies after activation.
////    virtual bool selfDestructs() const = 0;
////
////      // Return whether the object is affected by a holy water projectile.
////    virtual bool isSprayable() const = 0;
////};
////
////class OilSlick : public GhostRacerActivatedObject
////{
////public:
////    OilSlick(StudentWorld* sw, double x, double y);
////    virtual void doSomething();
////    virtual void doActivity(GhostRacer* gr);
////    virtual int getScoreIncrease() const;
////    virtual int getSound() const;
////    virtual bool selfDestructs() const;
////    virtual bool isSprayable() const;
////};
////
////class HealingGoodie : public GhostRacerActivatedObject
////{
////public:
////    HealingGoodie(StudentWorld* sw, double x, double y);
////    virtual void doSomething();
////    virtual void doActivity(GhostRacer* gr);
////    virtual int getScoreIncrease() const;
////    virtual bool selfDestructs() const;
////    virtual bool isSprayable() const;
////};
////
////class HolyWaterGoodie : public GhostRacerActivatedObject
////{
////public:
////    HolyWaterGoodie(StudentWorld* sw, double x, double y);
////    virtual void doSomething();
////    virtual void doActivity(GhostRacer* gr);
////    virtual int getScoreIncrease() const;
////    virtual bool selfDestructs() const;
////    virtual bool isSprayable() const;
////};
////
////class SoulGoodie : public GhostRacerActivatedObject
////{
////public:
////    SoulGoodie(StudentWorld* sw, double x, double y);
////    virtual void doSomething();
////    virtual void doActivity(GhostRacer* gr);
////    virtual int getScoreIncrease() const;
////    virtual int getSound() const;
////    virtual bool selfDestructs() const;
////    virtual bool isSprayable() const;
////};
//
//
