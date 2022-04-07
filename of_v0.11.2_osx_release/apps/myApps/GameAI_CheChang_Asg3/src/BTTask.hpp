//
//  BTTask.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/26/22.
//

#ifndef BTTask_hpp
#define BTTask_hpp
#include "BehaviorTreeNode.hpp"
#include <vector>

class BTTask : public BehaviorTreeNode {
public:
    BTTask() = default;
    virtual bool Run() = 0; // returns a status of failure or success
    
    std::vector<BTTask*> children;
};


#endif /* BTTask_hpp */
