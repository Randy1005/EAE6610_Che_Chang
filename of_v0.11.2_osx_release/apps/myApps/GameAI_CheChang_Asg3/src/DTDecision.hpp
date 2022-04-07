//
//  Decision.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/13/22.
//

#ifndef DTDecision_hpp
#define DTDecision_hpp

#include "DecisionTreeNode.hpp"

class DTDecision : public DecisionTreeNode {
public:
    DTDecision();
    // carry out the test, differs depending on what kind of decision we want
    // could be a float decision, or maybe a Vec2f decision
    virtual DecisionTreeNode* GetBranch() = 0;
    
    // Walk through the tree
    DecisionTreeNode* MakeDecision() override;
    
    DecisionTreeNode* trueNode;
    DecisionTreeNode* falseNode;
};



#endif /* Decision_hpp */
