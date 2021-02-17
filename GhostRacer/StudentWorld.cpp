#include "StudentWorld.h"
#include "GameConstants.h"
#include "GhostRacer.h"
#include "BorderLine.h"
//#include "Actor.h"
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
        
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
}

GhostRacer* StudentWorld::getGhostRacer() const
{
    return m_GhostRacer;
}

bool StudentWorld::overlap(Actor *a1, Actor *a2) const
{
    return false;
}

