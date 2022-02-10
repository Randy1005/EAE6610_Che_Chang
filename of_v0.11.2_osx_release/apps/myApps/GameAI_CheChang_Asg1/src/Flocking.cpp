//
//  Flocking.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/9/22.
//

#include "Flocking.hpp"

Flocking::Flocking(Separation* i_separation_behavior, VelocityMatch* i_velmatch_behavior, float i_separation_weight, float i_velmatch_weight, float i_arrive_weight, float i_max_linear_accel, float i_max_angular_accel) {
    this->separation_behavior = i_separation_behavior;
    this->velmatch_behavior = i_velmatch_behavior;
    this->velmatch_weight = i_velmatch_weight;
    this->separation_weight = i_separation_weight;
    this->arrive_weight = i_arrive_weight;
    this->max_linear_accel = i_max_linear_accel;
    this->max_angular_accel = i_max_angular_accel;
}

DynamicSteeringOutput Flocking::GetSteeringOutput() {
    DynamicSteeringOutput output;
    
    output.linear_acceleration = ofVec2f(0, 0);
    output.angular_acceleration = 0.0f;
    
    output.linear_acceleration += separation_weight * separation_behavior->GetSteeringOutput().linear_acceleration;

    
    output.linear_acceleration += velmatch_weight * velmatch_behavior->GetSteeringOutput().linear_acceleration;

    
    
    // assemble all boids into a new vector
    std::vector<Boid*> all_boids;
    for (Boid* boid : separation_behavior->target_boids) {
        all_boids.push_back(boid);
    }
    all_boids.push_back(separation_behavior->character_boid);
    
    // calculate mass center position
    ofVec2f center_mass_pos(0, 0);
    float total_mass = 0;
    for (Boid* boid : all_boids) {
        total_mass += boid->rigid_body.mass;
        center_mass_pos += boid->rigid_body.mass * boid->rigid_body.position;
    }
    center_mass_pos /= total_mass;
    
    
    DynamicSteeringOutput seek_output = separation_behavior->character_boid->Seek(center_mass_pos, max_linear_accel, 0.1f, 5.0f, 1.0f, 0.5f);
    output.linear_acceleration += seek_output.linear_acceleration;
    
    // crop to max
    float accel_mag = output.linear_acceleration.length();
    output.linear_acceleration.normalize();
    output.linear_acceleration *= max(accel_mag, max_linear_accel);
    output.angular_acceleration = max(output.angular_acceleration, max_angular_accel);
    
    return output;
    
    
}
