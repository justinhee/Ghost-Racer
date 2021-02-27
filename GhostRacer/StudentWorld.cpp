#include "StudentWorld.h"
#include "GameConstants.h"

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
: GameWorld(assetPath), m_GhostRacer(nullptr), m_lastBorderY(0), m_savedSouls(0), m_score(0)
{}

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
        if(m_savedSouls >= getLevel()*2+5)
        {
            //TODO: award bonus points
            return GWSTATUS_FINISHED_LEVEL;
        }
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
    
    //ADD ZOMBIE CABS
    int ChanceVehicle = max(100 - getLevel()*10, 20);
    if(randInt(0, ChanceVehicle-1) == 0)
    {
        //randomizes order of checking lanes
        int laneOrder[] = {0,1,2};
        for(int i = 0; i < 3; i++)
        {
            int r = randInt(i, 2);
            int temp = laneOrder[i];
            laneOrder[i] = laneOrder[r];
            laneOrder[r] = temp;
        }
        
        
        //checks each lane
        for(int i = 0; i < 3; i++)
        {
            Actor *top = nullptr;
            Actor* bottom = nullptr;
            closestCollisionActorTopAndBottomLane(laneOrder[i], top, bottom);
            
            int center = ROAD_CENTER + (laneOrder[i]-1)*ROAD_WIDTH/3;
            
            
            
            
            if(bottom == nullptr || bottom->getY() > VIEW_HEIGHT/3)
            {
                int vert_speed = getGhostRacer()->getVSpeed()+randInt(2, 4);
                Actor* newCab =new ZombieCab(this, center, SPRITE_HEIGHT/2);
                newCab->setVSpeed(vert_speed);
                m_actors.push_back(newCab);
                break;
            }
            else if(top == nullptr || top->getY() < VIEW_HEIGHT * 2 / 3)
            {
                int vert_speed = getGhostRacer()->getVSpeed()-randInt(2, 4);
                Actor* newCab =new ZombieCab(this, center, VIEW_HEIGHT - SPRITE_HEIGHT/2);
                newCab->setVSpeed(vert_speed);
                m_actors.push_back(newCab);
                break;
            }
        }
        
        
        
        
        
        
        
        
        
        
        
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
        
    
    
    //TODO: update text!!!
    
    
    
    
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

void StudentWorld::addActor(Actor* actor)
{
    m_actors.push_back(actor);
}

bool StudentWorld::sprayFirstAppropriateActor(Actor *a)
{
    for(vector<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++)
    {
        if(overlap(a, *p))
        {
            return (*p)->beSprayedIfAppropriate();
            
        }
    }
    return false;
}


void StudentWorld::closestCollisionActorTopAndBottomLane(int lane, Actor* closestToTop, Actor* closestToBottom)
{
    int left_bound = LEFT_EDGE + lane * ROAD_WIDTH/3;
    int right_bound = left_bound + ROAD_WIDTH/3;
    for(vector<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++)
    {
        if((*p)->isCollisionAvoidanceWorthy())
        {
            int x = (*p)->getX();
            int y = (*p)->getY();
            if(x >= left_bound && x < right_bound)
            {
                if(!closestToBottom || y < closestToBottom->getY())
                    closestToBottom = *p;
                if(!closestToTop || y > closestToTop->getY())
                    closestToTop = *p;
            }
        }
    }
}

void StudentWorld::closestCollisionActorFrontBack(Actor* a, Actor* front, Actor* back)
{
    for(int i = 0; i < 3; i++)
    {
        int left_bound = LEFT_EDGE + i * ROAD_WIDTH/3;
        int right_bound = left_bound + ROAD_WIDTH/3;
        //if a is in the current lane
        if(a->getX() >= left_bound && a->getX() < right_bound)
        {
            for(vector<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++)
            {
                if((*p)->isCollisionAvoidanceWorthy())
                {
                    //if p is in front of a
                    if((*p)->getY() > a->getY())
                    {
                        if(!front)
                            front = *p;
                        else
                        {
                            int minFrontGap = front->getY() - a->getY();
                            int frontGap = (*p)->getY() - a->getY();
                            if(frontGap < minFrontGap)
                                front = *p;
                        }
                    }
                    //if p is behind a
                    else if((*p)->getY() < a->getY())
                    {
                        if(!back)
                            back = *p;
                        else
                        {
                            int minBackGap = a->getY() - back->getY();
                            int backGap = a->getY() - (*p)->getY();
                            if(backGap < minBackGap)
                                back = *p;
                        }
                    }
                }
            }
            break;
        }
    }
}


