//
//  Damageable.hpp
//  GhostRacer
//
//  Created by Justin Hee on 2/17/21.
//  Copyright © 2021 David Smallberg. All rights reserved.
//

#ifndef DAMAGEABLE_H
#define DAMAGEABLE_H

class Damageable
{
public:
    Damageable(int health);
    int getHealth() const;
    void damage(int health);
private:
    int m_health;
    
};

#endif /* DAMAGEABLE_H */
