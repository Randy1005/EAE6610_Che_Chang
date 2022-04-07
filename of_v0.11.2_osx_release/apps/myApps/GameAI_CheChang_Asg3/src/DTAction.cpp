//
//  Action.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/12/22.
//

#include "DTAction.hpp"

DTAction::DTAction(const std::string& i_name) :
    name(i_name),
    DecisionTreeNode()
{
    
}

void DTAction::Run() {
    action();
}

DecisionTreeNode* DTAction::MakeDecision() {
    return this;
}
