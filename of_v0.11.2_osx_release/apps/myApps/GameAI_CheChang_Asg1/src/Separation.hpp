//
//  Separation.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/9/22.
//

#ifndef Separation_hpp
#define Separation_hpp

#include <stdio.h>
#include <vector>
#include "Boid.hpp"


class Separation {
public:
    Boid* character_boid;
    std::vector<Boid*> target_boids;
    float evade_personal_radius;
    float evade_max_linear_acceleration;
    float evade_decay;
    
    Separation(Boid* i_character_boid, std::vector<Boid*>& i_target_boids, float i_personal_radius, float i_max_linear_acceleration, float i_decay);
    DynamicSteeringOutput GetSteeringOutput();
    
    
};

#endif /* Separation_hpp */
