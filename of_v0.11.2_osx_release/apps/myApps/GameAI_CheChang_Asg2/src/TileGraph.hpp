//
//  TileGraph.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/22/22.
//

#ifndef TileGraph_hpp
#define TileGraph_hpp

#include "Graph.hpp"
#include "Tile.hpp"

class TileGraph : public Graph {
public:
    using Graph::Graph;
    
    TileGraph(int i_resolutionX, int i_resolutionY, float i_appWidth, float i_appHeight);
    void Draw();
    void GenerateTiles();
    void GenerateEdges();
    
    std::vector<Tile*> allTiles;
    int resolutionX;
    int resolutionY;
    float appWidth;
    float appHeight;
    
};

#endif /* TileGraph_hpp */
