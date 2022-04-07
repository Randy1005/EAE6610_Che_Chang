//
//  UntilFail.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/26/22.
//

#ifndef UntilFail_hpp
#define UntilFail_hpp

#include "BTDecorator.hpp"

class BTUntilFail : public BTDecorator {
public:
    BTUntilFail() = default;
    bool Run() override;
};

#endif /* UntilFail_hpp */
