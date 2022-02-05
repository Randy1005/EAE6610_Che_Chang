//
//  Boid.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/4/22.
//

#ifndef Boid_hpp
#define Boid_hpp

#include <stdio.h>
#include <ofVec2f.h>
#include <ofMain.h>

#define DRAW_STROKE 2

struct RigidBody {
    ofVec2f position;
    ofVec2f velocity;
    ofVec2f acceleration;
    float orientation;
};

class Boid {
public:
    Boid(float i_posx, float i_posy, float i_radius, float i_orientation, ofColor i_color);
    void Draw();
    void Update();
    
    RigidBody rigid_body;
    float radius;
    ofColor color;
private:
    float nose_length_;
    float GetOrientationInDegrees();
    
    
};



#endif /* Boid_hpp */
