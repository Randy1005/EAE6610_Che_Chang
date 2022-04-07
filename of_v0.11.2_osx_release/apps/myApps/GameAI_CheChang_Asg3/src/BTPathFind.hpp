//
//  BTPathFind.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/28/22.
//

#ifndef BTPathFind_hpp
#define BTPathFind_hpp

#include "BTTask.hpp"
#include "Boid.hpp"
#include "PathFinder.hpp"

class BTPathFind : public BTTask {
public:
    BTPathFind(Boid* i_charBoid, Boid* i_monsterBoid, PathFinder* i_pathFinder);
    bool Run() override;
    
    Boid* characterBoid;
    Boid* monsterBoid;
    PathFinder* pathFinder;
    
    
};

#endif /* BTPathFind_hpp */
