//
//  BTDecorator.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/26/22.
//

#ifndef BTDecorator_hpp
#define BTDecorator_hpp
#include "BTTask.hpp"

class BTDecorator : public BTTask {
public:
    BTDecorator() = default;
    BTTask* child; 
};

#endif /* BTDecorator_hpp */
