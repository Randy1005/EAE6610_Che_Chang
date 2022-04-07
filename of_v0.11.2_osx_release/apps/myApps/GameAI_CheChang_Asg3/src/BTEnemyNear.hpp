//
//  BTEnemyNear.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/27/22.
//

#ifndef BTEnemyNear_hpp
#define BTEnemyNear_hpp
#include "BTTask.hpp"
#include "Boid.hpp"

class BTEnemyNear : public BTTask {
public:
    BTEnemyNear(Boid* i_charBoid, Boid* i_monsterBoid);
    bool Run() override;
    
private:
    Boid* characterBoid;
    Boid* monsterBoid;
};

#endif /* BTEnemyNear_hpp */
