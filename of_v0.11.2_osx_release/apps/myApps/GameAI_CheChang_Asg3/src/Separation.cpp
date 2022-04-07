//
//  Separation.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/9/22.
//

#include "Separation.hpp"


Separation::Separation(Boid* i_character_boid, std::vector<Boid*>& i_target_boids, float i_personal_radius, float i_max_linear_acceleration, float i_decay) {
    this->character_boid = i_character_boid;
    this->target_boids = i_target_boids;
    this->evade_personal_radius = i_personal_radius;
    this->evade_max_linear_acceleration = i_max_linear_acceleration;
    this->evade_decay = i_decay;
}

DynamicSteeringOutput Separation::GetSteeringOutput() {
    DynamicSteeringOutput accumulated_output;
    accumulated_output.linear_acceleration = ofVec2f(0.0f, 0.0f);
    for (auto& target_boid : target_boids) {
        accumulated_output.linear_acceleration += character_boid->Evade(target_boid->rigid_body, evade_personal_radius, evade_max_linear_acceleration, evade_decay).linear_acceleration;
    }
    
    accumulated_output.linear_acceleration.normalize();
    accumulated_output.linear_acceleration *= evade_max_linear_acceleration;
    
    return accumulated_output;
}


