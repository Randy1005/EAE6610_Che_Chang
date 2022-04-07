//
//  Boid.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/4/22.
//

#ifndef Boid_hpp
#define Boid_hpp

#include <stdio.h>
#include <vector>
#include <ofVec2f.h>
#include <ofMain.h>
#include "BreadCrumb.hpp"

#define DRAW_STROKE 2
#define MAX_BREADCRUMBS 1000
#define INTERVAL_BREADCRUMB 5

struct RigidBody {
    ofVec2f position;
    ofVec2f velocity;
    ofVec2f linear_acceleration;
    float orientation;
    float angular_velocity;
    float angular_acceleration;
    float mass;
};

struct DynamicSteeringOutput {
    ofVec2f linear_acceleration;
    float angular_acceleration;
};

class Boid {
public:
    Boid(float i_posx, float i_posy, float i_radius, float i_orientation, ofColor i_color, float i_window_width, float i_window_height);
    void Draw();
    void Update();
    
    
    // ---- movement algorithm functions ---- //
    // simple demo: moves along the edge
    ofVec2f MoveAlongWindowEdge();
    
    // seek (arrive)
    DynamicSteeringOutput Seek(ofVec2f i_target_pos, float i_max_linear_acceleration, float i_max_speed, float i_slow_radius, float i_target_radius, float i_time_to_target);
    
    // flee
    DynamicSteeringOutput Flee(ofVec2f i_target_pos, float i_max_linear_acceleration);
    
    // evade
    DynamicSteeringOutput Evade(RigidBody i_target_rb, float i_personal_radius, float i_max_linear_acceleration, float i_decay);
    
    // align
    DynamicSteeringOutput Align(float i_target_orientation, float i_max_angular_velocity, float i_max_angular_acceleration, float i_slow_angle, float i_target_angle, float i_time_to_target);
    
    // look where you're going
    DynamicSteeringOutput LookWhereYoureGoing();
    
    // wander
    DynamicSteeringOutput Wander(float i_wander_radius, float i_wander_rate, float i_max_linear_acceleration);
    
    RigidBody rigid_body;
    float radius;
    ofColor color;
    
    // recording mouse clicks
    int mouse_x = 0, mouse_y = 0;
private:
    // Maintain a vector of breadcrumbs
    std::vector<BreadCrumb*> breadcrumbs_;
    int breadcrumb_index_ = 0;
    
    // we wanna leave a breadcrumb every N frames
    size_t timer_ = INTERVAL_BREADCRUMB;
    
    float app_window_width_, app_window_height_;
    float nose_length_;
    float GetOrientationInDegrees();
    float MapOrientationToRange(float i_orientation);
    void WrapAround();
    
};



#endif /* Boid_hpp */
