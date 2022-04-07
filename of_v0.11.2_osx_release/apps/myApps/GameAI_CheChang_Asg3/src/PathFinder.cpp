//
//  PathFinder.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 3/23/22.
//

#include "PathFinder.hpp"

PathFinder::PathFinder(const HeuristicFunction& i_heuristicFunc, TileGraph* i_tileGraph) :
    heuristicFunction(i_heuristicFunc),
    tileGraph(i_tileGraph),
    currentPathNodeId(0)
{
    
}


DynamicSteeringOutput PathFinder::PathFind(Boid* i_boid, ofVec2f& i_targetPosition) {
    DynamicSteeringOutput output;
    
    if (pathToTarget.size() == 0) {
        // no path to pathfind with, so generate a path, but output zero steering output
        
        // quantize world position to tile graph
        float tileSizeX = ofGetWidth() / (float)tileGraph->resolutionX;
        float tileSizeY = ofGetHeight() / (float)tileGraph->resolutionY;
        
        ofVec2f targetTileIndex2D = ofVec2f(floor(i_targetPosition.x / tileSizeX), floor(i_targetPosition.y / tileSizeY));
        
        int targetTileIndex1D = (int)targetTileIndex2D.x + tileGraph->resolutionX * (int)targetTileIndex2D.y;
        
        ofVec2f characterTileIndex2D = ofVec2f(floor(i_boid->rigid_body.position.x/tileSizeX), floor(i_boid->rigid_body.position.y/tileSizeY));
        int characterTileIndex1D = (int)characterTileIndex2D.x + tileGraph->resolutionX * (int)characterTileIndex2D.y;
        
        Heuristics heuristics(heuristicFunction, tileGraph->GetNodeById(targetTileIndex1D));
        
        pathToTarget = tileGraph->PathFindingAStar(tileGraph->GetNodeById(characterTileIndex1D), tileGraph->GetNodeById(targetTileIndex1D), heuristics);
        
        output.linear_acceleration = ofVec2f(0, 0);
        output.angular_acceleration = 0.0f;
        
    } else {
        Edge* currentSeekingEdge = pathToTarget[currentPathNodeId];
        ofVec2f seekTargetPosition = currentSeekingEdge->GetToNode()->nodeWorldPosition;
        
        // if we haven't reached next node yet
        if ((i_boid->rigid_body.position - seekTargetPosition).length() >= 4) {
            // continue seeking
            output.linear_acceleration = i_boid->Seek(seekTargetPosition, 0.2f, 2.0f, 30, 3.5, 0.24f).linear_acceleration;
            output.angular_acceleration = i_boid->LookWhereYoureGoing().angular_acceleration;
            
        } else {
            // seek next node
            if (currentPathNodeId + 1 < pathToTarget.size())
                currentPathNodeId++;
            else {
                // reached target
                output.linear_acceleration = ofVec2f(0, 0);
                output.angular_acceleration = 0.0f;
                // reset counter
                currentPathNodeId = 0;
                // clear path
                pathToTarget.clear();
            }
        }
        
    }
    
    return output;
    
    
}
