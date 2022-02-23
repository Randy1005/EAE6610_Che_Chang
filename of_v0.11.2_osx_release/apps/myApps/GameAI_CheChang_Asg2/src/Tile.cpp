//
//  Tile.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/22/22.
//

#include "Tile.hpp"
#include <ofGraphics.h>

Tile::Tile(ofVec2f& i_worldPosition, ofVec2f& i_dimension) :
    worldPosition_(i_worldPosition),
    dimension_(i_dimension)
{
    
}

void Tile::Draw() {
    ofPushMatrix();
    
    if (!walkable) {
        // draw obstacle
        ofSetColor(ofColor::darkBlue);
        ofTranslate(worldPosition_.x, worldPosition_.y);
        ofDrawRectangle(0, 0, dimension_.x, dimension_.y);
    }
    
    
    ofPopMatrix();
}

ofVec2f Tile::GetWorldPosition() {
    return worldPosition_;
}
