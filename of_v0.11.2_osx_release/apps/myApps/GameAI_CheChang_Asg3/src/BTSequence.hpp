//
//  BTSequence.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/26/22.
//

#ifndef BTSequence_hpp
#define BTSequence_hpp
#include "BTTask.hpp"

class BTSequence : public BTTask {
public:
    BTSequence() = default;
    bool Run() override;
    
};

#endif /* BTSequence_hpp */
