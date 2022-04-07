//
//  BTSequence.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/26/22.
//

#include "BTSequence.hpp"

bool BTSequence::Run() {
    for (BTTask* task : children) {
        if (!task->Run())
            return false;
    }
    return true;
}
