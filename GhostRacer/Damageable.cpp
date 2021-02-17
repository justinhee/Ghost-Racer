//
//  Damageable.cpp
//  GhostRacer
//
//  Created by Justin Hee on 2/17/21.
//  Copyright © 2021 David Smallberg. All rights reserved.
//

#include "Damageable.h"

Damageable::Damageable(int health) : m_health(health)
{}


int Damageable::getHealth() const
{
    return m_health;
}

void Damageable::damage(int health)
{
    m_health -= health;
}
