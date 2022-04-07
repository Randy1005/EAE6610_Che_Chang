//
//  FloatDecision.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/13/22.
//

#ifndef DTFloatDecision_hpp
#define DTFloatDecision_hpp
#include "DTDecision.hpp"

class DTFloatDecision : public DTDecision {
public:
    DTFloatDecision();
    DecisionTreeNode* GetBranch() override;
    
    float testValue;
    float valueToCheckAgainst;
};

#endif /* FloatDecision_hpp */
