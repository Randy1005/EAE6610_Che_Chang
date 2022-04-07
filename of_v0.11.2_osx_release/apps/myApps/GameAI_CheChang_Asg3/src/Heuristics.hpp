//
//  Heuristics.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/21/22.
//

#ifndef Heuristics_hpp
#define Heuristics_hpp

#include "ofMath.h"
#include "ofVec2f.h"
#include "Node.hpp"

enum class HeuristicFunction {
  RANDOM, EUCLIDEAN_DIST, MANHATTAN_DIST
};

class Heuristics {
public:
    Heuristics(HeuristicFunction i_heuristicFunc, Node* i_goalNode);
    float GetHeuristicCost(Node* i_startNode);
    
private:
    HeuristicFunction heuristicFunction_;
    Node* goalNode_;
};



#endif /* Heuristics_hpp */
