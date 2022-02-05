//
//  Boid.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/4/22.
//
#include "Boid.hpp"

Boid::Boid(float i_posx, float i_posy, float i_radius, float i_orientation, ofColor i_color) {
    this->rigid_body.position = ofVec2f(i_posx, i_posy);
    this->radius = i_radius;
    this->rigid_body.orientation = i_orientation;
    this->color = i_color;
    this->nose_length_ = 2 * this->radius;
}

void Boid::Draw() {
    ofPushMatrix();
    // Translate coords to the boid's position
    ofTranslate(rigid_body.position.x, rigid_body.position.y);
    
    // Rotate coords to the boid's orientation
    ofRotateZDeg(GetOrientationInDegrees());
    
    ofSetLineWidth(DRAW_STROKE);
    ofSetColor(color);
    ofDrawCircle(0, 0, radius);
    ofSetColor(color);
    ofDrawTriangle(0, radius, 0, -radius, nose_length_, 0);

    ofPopMatrix();
}

void Boid::Update() {
    // insert movement algorithms here
    
    // rotate to the moving direction
    rigid_body.orientation = ofVec2f(1.0, 0).angle(rigid_body.velocity) * PI / 180.0f;
    
    rigid_body.velocity += rigid_body.acceleration;
    rigid_body.position += rigid_body.velocity;
}

float Boid::GetOrientationInDegrees() {
    return (rigid_body.orientation * 180.0f) / PI;
}




