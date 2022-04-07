//
//  BreadCrumb.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/5/22.
//

#ifndef BreadCrumb_hpp
#define BreadCrumb_hpp

#include <stdio.h>
#include <ofMain.h>
#include <ofVec2f.h>

class BreadCrumb {
public:
    BreadCrumb(float i_posx, float i_posy, float i_radius, ofColor i_color);
    void Draw();
    
    ofVec2f position;
    ofColor color;
    float radius;
};


#endif /* BreadCrumb_hpp */
