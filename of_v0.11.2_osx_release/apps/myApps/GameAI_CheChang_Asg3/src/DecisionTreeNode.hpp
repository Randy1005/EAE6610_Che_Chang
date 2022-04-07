//
//  DecisionTreeNode.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/12/22.
//

#ifndef DecisionTreeNode_hpp
#define DecisionTreeNode_hpp
#include "Boid.hpp"
#include "AMAction.hpp"

class DecisionTreeNode : public AMAction {
public:
    DecisionTreeNode();
    virtual DecisionTreeNode* MakeDecision() = 0;
};



#endif /* DecisionTreeNode_hpp */
