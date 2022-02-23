//
//  Tile.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/22/22.
//

#ifndef Tile_hpp
#define Tile_hpp

#include "ofVec2f.h"
#include "Node.hpp"

class Tile {
public:
    Tile(ofVec2f& i_worldPosition, ofVec2f& i_dimension);
    void Draw();
    ofVec2f GetWorldPosition();
    
    bool walkable = true;
    
    
private:
    ofVec2f worldPosition_;
    ofVec2f dimension_;
    
    
};



#endif /* Tile_hpp */
