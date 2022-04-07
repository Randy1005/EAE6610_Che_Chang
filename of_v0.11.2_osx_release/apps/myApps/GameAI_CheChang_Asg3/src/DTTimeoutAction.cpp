//
//  TimeoutAction.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/23/22.
//

#include "DTTimeoutAction.hpp"

DTTimeoutAction::DTTimeoutAction(const std::string& i_name, const float i_timeoutSeconds) :
    DTAction(i_name)
{
    _timeoutFrames = i_timeoutSeconds * 60.0f; // assuming 60 fps
}

DecisionTreeNode* DTTimeoutAction::MakeDecision() {
    if (_timeoutFrames--)
        return this;
    else {
        std::cout << "timed out, traverse to true node." << std::endl;
        return trueNode;
    }
}
