//
//  BTSelector.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/26/22.
//

#include "BTSelector.hpp"



/**
 Selector: if one child task failed, continue to the next child
 fail if all children fail
 */
bool BTSelector::Run() {
    for (BTTask* task : children) {
        if (task->Run())
            return true;
    }
    
    return false;
}
