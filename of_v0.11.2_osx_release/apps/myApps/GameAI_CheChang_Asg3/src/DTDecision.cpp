//
//  Decision.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/13/22.
//

#include "DTDecision.hpp"

DTDecision::DTDecision() :
    DecisionTreeNode()
{
    
}

DecisionTreeNode* DTDecision::MakeDecision() {
    DecisionTreeNode* branch = GetBranch();
    return branch->MakeDecision();
}
