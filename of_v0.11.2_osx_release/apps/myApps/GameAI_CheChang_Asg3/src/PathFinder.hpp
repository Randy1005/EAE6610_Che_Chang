//
//  PathFinder.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/23/22.
//

#ifndef PathFinder_hpp
#define PathFinder_hpp
#include "TileGraph.hpp"
#include "Boid.hpp"

class PathFinder {
public:
    PathFinder(const HeuristicFunction& i_heuristicFunc, TileGraph* i_tileGraph);
    DynamicSteeringOutput PathFind(Boid* i_boid, ofVec2f& i_targetPosition);
    
    TileGraph* tileGraph;
    HeuristicFunction heuristicFunction;
    std::vector<Edge*> pathToTarget;
    size_t currentPathNodeId;
    
};

#endif /* PathFinder_hpp */
