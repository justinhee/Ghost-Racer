#include "StudentWorld.h"
#include "GameConstants.h"
#include "GhostRacer.h"
#include "BorderLine.h"
#include "ZombiePed.h"
#include "HumanPed.h"
#include "SoulGoodie.h"
//#include "Actor.h"

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

const int LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH/2;
const int RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH/2;


GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_GhostRacer = nullptr;
    m_savedSouls = 0;
    m_lastBorderY = 0;
    
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    //create GhostRacer
    m_GhostRacer = new GhostRacer(this);
    m_actors.push_back(m_GhostRacer);
    
    //create Yellow BorderLines
    int n = VIEW_HEIGHT/SPRITE_HEIGHT;
    for(int j = 0; j < n; j++)
    {
        m_actors.push_back(new BorderLine(this,IID_YELLOW_BORDER_LINE, LEFT_EDGE, j*SPRITE_HEIGHT));
        m_actors.push_back(new BorderLine(this,IID_YELLOW_BORDER_LINE, RIGHT_EDGE, j*SPRITE_HEIGHT));
    }
    
    //create White BorderLines
    int m = VIEW_HEIGHT/(4*SPRITE_HEIGHT);
    for(int j = 0; j < m; j++)
    {
        m_actors.push_back(new BorderLine(this, IID_WHITE_BORDER_LINE, LEFT_EDGE + ROAD_WIDTH/3, j*(4*SPRITE_HEIGHT)));
        m_actors.push_back(new BorderLine(this, IID_WHITE_BORDER_LINE, RIGHT_EDGE - ROAD_WIDTH/3, j*(4*SPRITE_HEIGHT)));
        m_lastBorderY = j*(4*SPRITE_HEIGHT);
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    //ACTORS DO SOMETHING
    for(vector<Actor*>::iterator p = m_actors.begin(); p!= m_actors.end(); p++)
    {
        if((*p)->isAlive())
            (*p)->doSomething();
        if(!getGhostRacer()->isAlive())
            return GWSTATUS_PLAYER_DIED;
        //if ghost racer completed the level, add bonues points and return finish
    }
    
    //UPDATE POSITION OF LAST WHITE BORDER LINE
    m_lastBorderY += -4-getGhostRacer()->getVSpeed();
    
    //DELETE DEAD ACTORS
    for(vector<Actor*>::iterator p = m_actors.begin(); p!= m_actors.end();)
    {
        if(!(*p)->isAlive())
        {
            Actor* temp = *p;
            p = m_actors.erase(p);
            delete temp;
        }
        else
            p++;

    }
    
    //ADD NEW BORDER LINES
    int new_border_y = VIEW_HEIGHT-SPRITE_HEIGHT;
    int delta_y = new_border_y - m_lastBorderY;
    if(delta_y >= SPRITE_HEIGHT)
    {
        m_actors.push_back(new BorderLine(this,IID_YELLOW_BORDER_LINE, LEFT_EDGE, new_border_y));
        m_actors.push_back(new BorderLine(this,IID_YELLOW_BORDER_LINE, RIGHT_EDGE, new_border_y));
    }
    if(delta_y >= 4*SPRITE_HEIGHT)
    {
        m_actors.push_back(new BorderLine(this, IID_WHITE_BORDER_LINE, LEFT_EDGE + ROAD_WIDTH/3, new_border_y));
        m_actors.push_back(new BorderLine(this, IID_WHITE_BORDER_LINE, RIGHT_EDGE - ROAD_WIDTH/3, new_border_y));
        m_lastBorderY = new_border_y;
    }
    
    //ADD NEW ZOMBIE PEDESTRIANS
    int chanceZombiePed = max(100-getLevel()*10, 20);
    if(randInt(0, chanceZombiePed-1) == 0)
    {
        m_actors.push_back(new ZombiePed(this, randInt(0, VIEW_WIDTH), VIEW_HEIGHT));
    }
    
    
    
    
    //ADD NEW HUMAN PEDESTRIANS
    int chanceHumanPed = max(200-getLevel()*10, 30);
    if(randInt(0, chanceHumanPed-1)==0)
    {
        m_actors.push_back(new HumanPed(this, randInt(0, VIEW_WIDTH), VIEW_HEIGHT));
    }
    
    //ADD NEW LOST SOUL GOODIES
    //TODO: check interval for randInt
    if(randInt(0, 99) == 0)
    {
        m_actors.push_back(new SoulGoodie(this, randInt(0, VIEW_WIDTH), VIEW_HEIGHT));
    }
        
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for(vector<Actor*>::iterator p = m_actors.begin(); p != m_actors.end();)
    {
        Actor* temp = *p;
        p = m_actors.erase(p);
        delete temp;
    }
}

GhostRacer* StudentWorld::getGhostRacer() const
{
    return m_GhostRacer;
}

//TODO:
bool StudentWorld::overlap(Actor* a1, Actor* a2) const
{
    double delta_x = abs(a1->getX() - a2->getX());
    double delta_y = abs(a1->getY() - a2->getY());
    double radius_sum = a1->getRadius() + a2->getRadius();
    if(delta_x < radius_sum*.25 && delta_y < radius_sum*.6)
    {
        std::cerr<<"collision" << endl;
        return true;
        
    }
    return false;
}

void StudentWorld::saveSoul()
{
    m_savedSouls++;
}

void StudentWorld::addtoScore(int score)
{
    m_score += score;
}
