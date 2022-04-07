//
//  Flocking.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/9/22.
//

#ifndef Flocking_hpp
#define Flocking_hpp

#include <stdio.h>
#include <vector>
#include "Separation.hpp"
#include "VelocityMatch.hpp"

class Flocking {
public:
    VelocityMatch* velmatch_behavior;
    Separation* separation_behavior;
    float velmatch_weight;
    float separation_weight;
    float arrive_weight;
    float max_linear_accel;
    float max_angular_accel;
    
    // 3 steering behavior blending: separation, velocity match, and arrive
    Flocking(Separation* i_separation_behavior, VelocityMatch* i_velmatch_behavior, float i_separation_weight, float i_velmatch_weight, float i_arrive_weight, float i_max_linear_accel, float i_max_angular_accel);
    
    DynamicSteeringOutput GetSteeringOutput();
};

#endif /* Flocking_hpp */
