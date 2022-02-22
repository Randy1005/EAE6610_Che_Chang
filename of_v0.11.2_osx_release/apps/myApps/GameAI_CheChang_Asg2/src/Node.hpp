//
//  Node.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/22/22.
//

#ifndef Node_hpp
#define Node_hpp

#include "ofVec2f.h"

class Node {
public:
    Node(int i_id);
    int id;
    ofVec2f nodeWorldPosition_;
};

#endif /* Node_hpp */
