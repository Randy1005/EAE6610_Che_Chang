//
//  FloatDecision.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/13/22.
//

#include "DTFloatDecision.hpp"

DTFloatDecision::DTFloatDecision() :
    DTDecision()
{
    
}

DecisionTreeNode* DTFloatDecision::GetBranch() {
    return (testValue >= valueToCheckAgainst) ? trueNode : falseNode;
}

