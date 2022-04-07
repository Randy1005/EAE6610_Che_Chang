//
//  BoolAction.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/21/22.
//

#ifndef DTBoolAction_hpp
#define DTBoolAction_hpp

#include "DTAction.hpp"
/**
 * @brief if condition evaluates to true, traverse to trueNode, else loop back to the action itself
 *
 */

class DTBoolAction : public DTAction {
public:
    DTBoolAction(const std::string& i_name);
    
    std::function<bool()> condition;
    DecisionTreeNode* MakeDecision() override;
    
    DecisionTreeNode* trueNode;
    
    
};

#endif /* BoolAction_hpp */
