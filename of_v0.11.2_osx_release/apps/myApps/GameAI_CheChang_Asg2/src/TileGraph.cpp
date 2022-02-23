//
//  TileGraph.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/22/22.
//

#include "TileGraph.hpp"

TileGraph::TileGraph(int i_resolutionX, int i_resolutionY, float i_appWidth, float i_appHeight) :
    resolutionX(i_resolutionX),
    resolutionY(i_resolutionY),
    appWidth(i_appWidth),
    appHeight(i_appHeight)
{
    
}

void TileGraph::GenerateTiles() {
    float tileSizeX = appWidth / resolutionX;
    float tileSizeY = appHeight / resolutionY;
    
    for (size_t i = 0; i < resolutionX; i++) {
        for (size_t j = 0; j < resolutionY; j++) {
            ofVec2f tilePositon(j * tileSizeX, i * tileSizeY);
            ofVec2f tileDimension(tileSizeX, tileSizeY);
            allTiles.push_back(new Tile(tilePositon, tileDimension));
            
        }
    }
    
}

Tile* TileGraph::FindTileByPosition(ofVec2f &i_position) {
    
    
    
}

void TileGraph::Draw() {
    for (Tile* tile : allTiles)
        tile->Draw();
}
