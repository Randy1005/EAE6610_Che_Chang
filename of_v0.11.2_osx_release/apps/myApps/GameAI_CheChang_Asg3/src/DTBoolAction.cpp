//
//  BoolAction.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/21/22.
//

#include "DTBoolAction.hpp"

DTBoolAction::DTBoolAction(const std::string& i_name) :
    DTAction(i_name)
{
    
}





DecisionTreeNode* DTBoolAction::MakeDecision() {
    return condition() ? trueNode->MakeDecision() : this;
}
