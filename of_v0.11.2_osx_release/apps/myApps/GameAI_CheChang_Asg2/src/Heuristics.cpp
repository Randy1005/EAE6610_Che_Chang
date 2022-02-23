//
//  Heuristics.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/21/22.
//

#include "Heuristics.hpp"


Heuristics::Heuristics(HeuristicFunction i_heuristicFunc, Node* i_goalNode) :
    heuristicFunction_(i_heuristicFunc),
    goalNode_(i_goalNode)
{
    
}

float Heuristics::GetHeuristicCost(Node* i_startNode) {
    switch (heuristicFunction_) {
        case HeuristicFunction::RANDOM:
            return ((ofRandomf() + 1.0f) * 2);
            // return 0.0f;
            break;
        
        case HeuristicFunction::EUCLIDEAN_DIST:
            return (goalNode_->nodeWorldPosition - i_startNode->nodeWorldPosition).length();
            break;
        
        case HeuristicFunction::MANHATTAN_DIST:
            return abs(goalNode_->nodeWorldPosition.x - i_startNode->nodeWorldPosition.x) + abs(goalNode_->nodeWorldPosition.y - i_startNode->nodeWorldPosition.y);
            break;
            
        default:
            break;
    }
}


