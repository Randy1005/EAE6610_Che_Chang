//
//  BTPatrol.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/28/22.
//

#include "BTPatrol.hpp"

BTPatrol::BTPatrol(Boid* i_monsterBoid) :
    monsterBoid(i_monsterBoid),
    BTTask()
{
    
}

bool BTPatrol::Run() {
    DynamicSteeringOutput steeringOutput = monsterBoid->Wander(20.0f, 8.0f, 0.015f);
    monsterBoid->rigid_body.linear_acceleration = steeringOutput.linear_acceleration;
    monsterBoid->rigid_body.angular_acceleration = steeringOutput.angular_acceleration;
    
    return true;
}
