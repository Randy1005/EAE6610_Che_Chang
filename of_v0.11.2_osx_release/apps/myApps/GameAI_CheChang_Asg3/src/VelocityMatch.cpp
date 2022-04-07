//
//  VelocityMatch.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/9/22.
//

#include "VelocityMatch.hpp"

VelocityMatch::VelocityMatch(Boid* i_character_boid, Boid* i_target_boid, float i_max_linear_acceleration, float i_time_to_target)
{
    this->character_boid = i_character_boid;
    this->target_boid = i_target_boid;
    this->max_linear_acceleration = i_max_linear_acceleration;
    this->time_to_target = i_time_to_target;
}

DynamicSteeringOutput VelocityMatch::GetSteeringOutput() {
    DynamicSteeringOutput output;
    output.linear_acceleration = target_boid->rigid_body.velocity - character_boid->rigid_body.velocity;
    output.linear_acceleration /= time_to_target;
    
    if (output.linear_acceleration.length() > max_linear_acceleration) {
        output.linear_acceleration.normalize();
        output.linear_acceleration *= max_linear_acceleration;
    }
    
    output.angular_acceleration = 0.0f;
    return output;
}


