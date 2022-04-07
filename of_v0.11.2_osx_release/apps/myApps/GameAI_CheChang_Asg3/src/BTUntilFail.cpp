//
//  UntilFail.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/26/22.
//

#include "BTUntilFail.hpp"

bool BTUntilFail::Run() {
    while (true) {
        if (!child->Run())
            return false;
    }
    
    return true;
}
