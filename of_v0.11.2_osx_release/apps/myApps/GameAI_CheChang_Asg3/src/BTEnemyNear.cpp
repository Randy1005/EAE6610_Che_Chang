//
//  BTEnemyNear.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/27/22.
//

#include "BTEnemyNear.hpp"
BTEnemyNear::BTEnemyNear(Boid* i_charBoid, Boid* i_monsterBoid) :
    characterBoid(i_charBoid),
    monsterBoid(i_monsterBoid),
    BTTask()
{
    
}


bool BTEnemyNear::Run() {
    if ((characterBoid->rigid_body.position - monsterBoid->rigid_body.position).length() < 100.0f)
    {
        std::cout << "Monster: Enemy is near.\n";
        return true;
    }
    
    return false;
}


