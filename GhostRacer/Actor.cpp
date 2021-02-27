#include "Actor.h"
#include "StudentWorld.h"

const double PI = 4 * atan(1.0);

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
//goodies, projetile
//ACTOR IMPLEMENTATION
Actor::Actor(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double size, int depth, double VSpeed, double HSpeed) : GraphObject(imageID, startX, startY, startDirection, size, depth), m_world(world), m_alive(true), m_VSpeed(VSpeed), m_HSpeed(HSpeed)
{}

bool Actor::isAlive() const
{
    return m_alive;
}

bool Actor::isCollisionAvoidanceWorthy() const
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

bool Actor::beSprayedIfAppropriate()
{
    return false;
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
    if(m_health <= 0)
    {
        getWorld()->playSound(soundWhenDie());
        die();
        return true;
    }
    else
        getWorld()->playSound(soundWhenHurt());
    return false;
}

int Agent::soundWhenDie() const
{
    return SOUND_NONE;
}
int Agent::soundWhenHurt() const
{
    return SOUND_NONE;
}

//SPRAY IMPLEMENTATION
Spray::Spray(StudentWorld* world, double startX, double startY, int startDirection) :
Actor(world, IID_HOLY_WATER_PROJECTILE, startX, startY, startDirection, 1.0, 1),
m_distanceToGo(160)
{}

void Spray::doSomething()
{
    if(!isAlive())
        return;
    if(getWorld()->sprayFirstAppropriateActor(this))
    {
        die();
        return;
    }
    moveForward(SPRITE_HEIGHT);
    m_distanceToGo-=SPRITE_HEIGHT;
    
    if(getX() < 0 || getY() < 0 || getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT || m_distanceToGo <= 0)
    {
        die();
        return;
    }
    
    
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
    if(getX() <= ROAD_CENTER - ROAD_WIDTH/2 && getDirection() > 90)
    {
        damage(10);
        setDirection(82);
        getWorld()->playSound(SOUND_VEHICLE_CRASH);
    }
    else if(getX() >= ROAD_CENTER + ROAD_WIDTH/2 && getDirection() < 90)
    {
        damage(10);
        setDirection(98);
        getWorld()->playSound(SOUND_VEHICLE_CRASH);
    }
    else
    {
        int ch;
        if(getWorld()->getKey(ch))
        {
            switch(ch)
            {
                case KEY_PRESS_SPACE:
                    //TODO:
                    if(m_holyWaterSpray>0)
                    {
                        int x = getX() + SPRITE_HEIGHT*cos(PI*getDirection()/180);
                        int y = getY() + SPRITE_HEIGHT*sin(PI*getDirection()/180);
                        getWorld()->addActor(new Spray(getWorld(), x, y, getDirection()));
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

int GhostRacer::soundWhenDie() const
{
    return SOUND_PLAYER_DIE;
}

int GhostRacer::getNumSprays() const
{
    return m_holyWaterSpray;
}

void GhostRacer::increaseSprays(int amt)
{
    m_holyWaterSpray += amt;
}

void GhostRacer::spin()
{
    int dTheta = randInt(5, 20);
    if(randInt(0, 1))
        dTheta = dTheta*-1;
    int newDirection = getDirection() + dTheta;
    if(newDirection < 60)
        newDirection = 60;
    else if(newDirection > 120)
        newDirection = 120;
    setDirection(newDirection);
    
}


//BORDERLINE IMPLEMENTATION
BorderLine::BorderLine(StudentWorld* world, int imageID, double startX, double startY) :
Actor(world, imageID, startX, startY, 0, 2.0, 2, -4, 0)
{}

void BorderLine::doSomething()
{
    move();
}

//PEDESTRIAN IMPLEMENTATION
Pedestrian::Pedestrian(StudentWorld* world, int imageID, double startX, double startY, double size) :
Agent(world, imageID, startX, startY, 0, size, 2, -4, 0),

m_movementPlanDistance(0)
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
ZombiePed::ZombiePed(StudentWorld* world, double startX, double startY) :
Pedestrian(world, IID_ZOMBIE_PED, startX, startY, 3.0),
m_timeToGrunt(0)
{}

void ZombiePed::doSomething()
{
    if(!isAlive())
        return;
    if(getWorld()->overlap(this, getWorld()->getGhostRacer()))
    {
        if(damage(2))
        {
            getWorld()->addtoScore(150);
        }
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

bool ZombiePed::beSprayedIfAppropriate()
{
    if(damage(1) && !getWorld()->overlap(this, getWorld()->getGhostRacer()))
    {
        getWorld()->addtoScore(150);
        if(randInt(1, 5)==1)
        {
            getWorld()->addActor(new HealingGoodie(getWorld(), getX(), getY()));
            
        }
    }
        
    return true;
        
    /*When damaged (e.g., by holy water sprays), a zombie pedestrian must do the
     following:
     o It must reduce its hit points by the specified amount of damage hit points.
     o If its hit points reach zero or below, the zombie pedestrian must:
     ▪ Set its status to not-alive, so it will be removed by StudentWorld
     later in this tick.
     ▪ Play a sound of SOUND_PED_DIE.
     ▪ If the zombie ped does not currently overlap with Ghost Racer
     (i.e., it didn’t die due to Ghost Racer colliding with it), then there
     is a 1 in 5 chance that the zombie ped will add a new healing
     goodie at its current position.
     ▪ Ensure the player receives 150 points.
     o Otherwise (the zombie ped still has hit points left), play a sound of
     SOUND_PED_HURT*/
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
HumanPed::HumanPed(StudentWorld* world, double startX, double startY) :
Pedestrian(world, IID_HUMAN_PED, startX, startY, 2.0)
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

bool HumanPed::beSprayedIfAppropriate()
{
    if(getDirection()==180)
        setDirection(0);
    else
        setDirection(180);
    setHSpeed(-1*getHSpeed());
    getWorld()->playSound(SOUND_PED_HURT);
    return true;
    
    /*● A human pedestrian is affected by holy water. When damaged by holy water the
     human pedestrian will reverse its direction:
     o Ignore all hit point damage (holy water doesn’t actually injure the
     pedestrian)
     o Change its current horizontal speed by multiplying it by -1 (e.g., if the ped
     was going left at 2 pixels/tick, it must change its direction to right at 2
     pixels/tick).
     o Change the direction the human is facing (e.g., from 0 to 180 degrees, or
     180 degrees to 0) as appropriate.
     o The human pedestrian must play a sound of SOUND_PED_HURT.*/
}

ZombieCab::ZombieCab(StudentWorld* world, double startX, double startY) :
Agent(world, IID_ZOMBIE_CAB, startX, startY, 90, 4.0, 3, 0, 0), m_hasDamagedGhostRacer(false), m_movementPlanDistance(0)
{}
void ZombieCab::doSomething()
{
    if(!isAlive())
        return;
    if(getWorld()->overlap(this, getWorld()->getGhostRacer()) && !m_hasDamagedGhostRacer)
    {
        getWorld()->playSound(SOUND_VEHICLE_CRASH);
        getWorld()->getGhostRacer()->damage(20);
        //if left of racer
        if(getX() <= getWorld()->getGhostRacer()->getX())
        {
            setHSpeed(-5);
            setDirection(120+randInt(0, 20));
        }
        else if(getX() > getWorld()->getGhostRacer()->getX())
        {
            setHSpeed(5);
            setDirection(60-randInt(0, 20));
        }
        m_hasDamagedGhostRacer = true;
    }

    //MOVE
    if(!move())
        return;
    
    
    
    Actor* closestFrontCollision = nullptr;
    Actor* closestBackCollision = nullptr;
    getWorld()->closestCollisionActorFrontBack(this, closestFrontCollision, closestBackCollision);
    
    //if faster than racer
    if(getVSpeed() > getWorld()->getGhostRacer()->getVSpeed())
    {
        //if the there's something in front that's not the racer and is within 96, decrease vpseed by .5
        if(closestFrontCollision && closestFrontCollision->getY() - getY() < 96)
        {
            setVSpeed(getVSpeed()-.5);
            return;
        }
    }
    //if same or slower than racer
    else
    {
        //if there's something in back that's not the racer and is within 96, inrease vspeed by .5
        if(closestBackCollision && closestBackCollision != getWorld()->getGhostRacer() && getY() - closestBackCollision->getY() < 96)
        {
            setVSpeed(getVSpeed()+.5);
            return;
        }
    }
    
    //6. decrement movement plan distance
    m_movementPlanDistance--;
    
    //7. if movement plan distance is greater than 0, return
    if(m_movementPlanDistance > 0)
        return;
    //8. choose new movement plan for cab
    else
    {
        m_movementPlanDistance = randInt(4, 32);
        setVSpeed(getVSpeed() + randInt(-2, 2));
    }
}
bool ZombieCab::beSprayedIfAppropriate()
{//TODO: finish with oil slick
    if(damage(1))
    {
        getWorld()->addtoScore(200);
        if(randInt(1, 5)==1)
            getWorld()->addActor(new OilSlick(getWorld(), getX(), getY()));
    }
    return true;
}
int ZombieCab::soundWhenHurt() const
{
    return SOUND_VEHICLE_HURT;
}
int ZombieCab::soundWhenDie() const
{
    return SOUND_VEHICLE_DIE;
}









//GHOSTRACERACTIVATEDOBJECT IMPLEMENTATION
GhostRacerActivatedObject::GhostRacerActivatedObject(StudentWorld* world, int imageID, double startX, double startY, double size, int dir) :
Actor(world, imageID, startX, startY, dir, size, 2, -4)
{}

void GhostRacerActivatedObject::doSomething()
{
    if(!move())
        return;
    
    if(getWorld()->overlap(this, getWorld()->getGhostRacer()))
    {
        doActivity(getWorld()->getGhostRacer());
        if(selfDestructs())
            die();
        getWorld()->playSound(getSound());
        getWorld()->addtoScore(getScoreIncrease());
    }
}

bool GhostRacerActivatedObject::beSprayedIfAppropriate()
{
    if(isSprayable())
    {
        die();
        return true;
    }
    return false;
    
}

      // Return the sound to be played when the object is activated.
int GhostRacerActivatedObject::getSound() const
{
    return SOUND_GOT_GOODIE;
}






//SOULGOODIE IMPLEMENTATION
SoulGoodie::SoulGoodie(StudentWorld* world, double startX, double startY) :
GhostRacerActivatedObject(world, IID_SOUL_GOODIE, startX, startY, 4, 0)
{}

void SoulGoodie::doActivity(GhostRacer *gr)
{
    getWorld()->saveSoul();
}

int SoulGoodie::getScoreIncrease() const
{
    return 100;
}

int SoulGoodie::getSound() const
{
    return SOUND_GOT_SOUL;
}

bool SoulGoodie::selfDestructs() const
{
    return true;
}
 bool SoulGoodie::isSprayable() const
{
    return false;
}

void SoulGoodie::doSomething()
{
    GhostRacerActivatedObject::doSomething();
    setDirection(getDirection()+10);
}

//HEALINGGOODIE IMPLEMENTATION
HealingGoodie::HealingGoodie(StudentWorld* world, double startX, double startY) :
GhostRacerActivatedObject(world, IID_HEAL_GOODIE, startX, startY, 1, 0)
{}

void HealingGoodie::doSomething()
{
    GhostRacerActivatedObject::doSomething();
}

void HealingGoodie::doActivity(GhostRacer* gr)
{
    gr->heal(10);
}
int HealingGoodie::getScoreIncrease() const
{
    return 250;
}
bool HealingGoodie::selfDestructs() const
{
    return true;
}
bool HealingGoodie::isSprayable() const
{
    return true;
}

//HOLYWATERGOODIE IMPLEMENTATION

HolyWaterGoodie::HolyWaterGoodie(StudentWorld* world, double startX, double startY) :
GhostRacerActivatedObject(world, IID_HOLY_WATER_GOODIE, startX, startY, 2, 90)
{}
void HolyWaterGoodie::doSomething()
{
    GhostRacerActivatedObject::doSomething();
}

void HolyWaterGoodie::doActivity(GhostRacer* gr)
{
    gr->increaseSprays(10);
}

int HolyWaterGoodie::getScoreIncrease() const
{
    return 50;
}
bool HolyWaterGoodie::selfDestructs() const
{
    return true;
}
bool HolyWaterGoodie::isSprayable() const
{
    return true;
}


//OILSLICK IMPLEMENTATION

OilSlick::OilSlick(StudentWorld* world, double startX, double startY) :
GhostRacerActivatedObject(world, IID_OIL_SLICK, startX, startY, randInt(2, 5), 0)
{}

void OilSlick::doSomething()
{
    GhostRacerActivatedObject::doSomething();
}
void OilSlick::doActivity(GhostRacer* gr)
{
    gr->spin();
}
int OilSlick::getScoreIncrease() const
{
    return 0;
}

int OilSlick::getSound() const
{
    return SOUND_OIL_SLICK;
}

bool OilSlick::selfDestructs() const
{
    return false;
}

bool OilSlick::isSprayable() const
{
    return false;
}














