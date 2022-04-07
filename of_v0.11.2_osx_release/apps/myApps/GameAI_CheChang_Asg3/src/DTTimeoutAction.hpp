//
//  TimeoutAction.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/23/22.
//

#ifndef DTTimeoutAction_hpp
#define DTTimeoutAction_hpp
#include "DTAction.hpp"


/**
 *  @brief if timeOut evaluates to true, traverse to trueNode, else loop back to the action itself
 *
 */

class DTTimeoutAction : public DTAction {
public:
    DTTimeoutAction(const std::string& i_name, const float i_timeoutSeconds);
    
    
    DecisionTreeNode* MakeDecision() override;
    DecisionTreeNode* trueNode;
    
private:
    float _timeoutFrames;
};

#endif /* TimeoutAction_hpp */
