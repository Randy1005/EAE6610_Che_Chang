//
//  VelocityMatch.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/9/22.
//

#ifndef VelocityMatch_hpp
#define VelocityMatch_hpp

#include <stdio.h>
#include <vector>
#include "Boid.hpp"

class VelocityMatch {
public:
    Boid* character_boid, *target_boid;
    float max_linear_acceleration;
    float time_to_target;
    
    VelocityMatch(Boid* i_character_boid, Boid* i_target_boid, float i_max_linear_acceleration, float i_time_to_target);
    
    DynamicSteeringOutput GetSteeringOutput();
    
};

#endif /* VelocityMatch_hpp */
