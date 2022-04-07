//
//  BTSelector.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/26/22.
//

#ifndef BTSelector_hpp
#define BTSelector_hpp

#include "BTTask.hpp"

class BTSelector : public BTTask {
public:
    BTSelector() = default;
    bool Run() override;
};

#endif /* BTSelector_hpp */
