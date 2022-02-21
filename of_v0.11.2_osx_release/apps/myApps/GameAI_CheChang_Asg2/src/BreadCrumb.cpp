//
//  BreadCrumb.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/5/22.
//

#include "BreadCrumb.hpp"

BreadCrumb::BreadCrumb(float i_posx, float i_posy, float i_radius, ofColor i_color) {
    this->position = ofVec2f(i_posx, i_posy);
    this->color = i_color;
    this->radius = i_radius;
}

void BreadCrumb::Draw() {
    ofPushMatrix();
    
    ofTranslate(position.x, position.y);
    ofSetColor(color);
    ofDrawCircle(0, 0, radius);
    
    ofPopMatrix();
}
