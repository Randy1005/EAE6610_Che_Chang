//
//  BTPathFind.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/28/22.
//

#include "BTPathFind.hpp"

BTPathFind::BTPathFind(Boid* i_charBoid, Boid* i_monsterBoid, PathFinder* i_pathFinder) :
    characterBoid(i_charBoid),
    monsterBoid(i_monsterBoid),
    pathFinder(i_pathFinder),
    BTTask()
{
    
}

bool BTPathFind::Run() {
    if ((characterBoid->rigid_body.position - monsterBoid->rigid_body.position).length() <= 4)
        return true;
    else {
        DynamicSteeringOutput steeringOutput = pathFinder->PathFind(monsterBoid, characterBoid->rigid_body.position);
        
        monsterBoid->rigid_body.linear_acceleration = steeringOutput.linear_acceleration;
        monsterBoid->rigid_body.angular_acceleration = steeringOutput.angular_acceleration;
        
        return false;
    }
}




