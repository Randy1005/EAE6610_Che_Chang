//
//  BTPatrol.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/28/22.
//

#ifndef BTPatrol_hpp
#define BTPatrol_hpp
#include "BTTask.hpp"
#include "Boid.hpp"

class BTPatrol : public BTTask {
public:
    BTPatrol(Boid* i_monsterBoid);
    bool Run() override;
    
private:
    Boid* monsterBoid;
};

#endif /* BTPatrol_hpp */
