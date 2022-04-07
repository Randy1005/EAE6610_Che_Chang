//
//  Action.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/12/22.
//

#ifndef DTAction_hpp
#define DTAction_hpp
#include "DecisionTreeNode.hpp"
#include <string>
#include <functional>

class DTAction : public DecisionTreeNode {
public:
    DTAction(const std::string& i_name);
    DecisionTreeNode* MakeDecision() override;
    void Run();
    
    std::string name;
    
    std::function<void()> action;
};

#endif /* Action_hpp */
