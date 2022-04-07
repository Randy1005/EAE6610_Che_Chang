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

// generate edges for all tiles in the tile graph, also assign real
// world positions
void TileGraph::GenerateEdges() {
    float tileSizeX = appWidth / resolutionX;
    float tileSizeY = appHeight / resolutionY;
    float defaultNodeCost = 1.0f;
    ofVec2f tileCenterOffset(tileSizeX/2, tileSizeY/2);
    
    for (int id = 0; id < allTiles.size(); id++) {
        
        Node* currentNode = this->GetNodeById(id);
        if (!currentNode)
            currentNode = new Node(id);
        
        currentNode->nodeWorldPosition = allTiles[id]->GetWorldPosition() + tileCenterOffset;
        
        // now create edges from this node to its right / left /
        // down / up
        
        // edge to left node
        if (id - 1 >= 0) {
            Node* leftNode = this->GetNodeById(id-1);
            if (!leftNode) {
                // if left node is not created
                leftNode = new Node(id-1);
            }

            
            leftNode->nodeWorldPosition = allTiles[id-1]->GetWorldPosition() + tileCenterOffset;
            this->AddEdge(new Edge(currentNode, leftNode, defaultNodeCost));
        }
        // edge to right node
        if (id + 1 < resolutionX) {
            Node* rightNode = this->GetNodeById(id+1);
            if (!rightNode) {
                // if right node is not created
                rightNode = new Node(id+1);
            }

            rightNode->nodeWorldPosition = allTiles[id+1]->GetWorldPosition() + tileCenterOffset;
            this->AddEdge(new Edge(currentNode, rightNode, defaultNodeCost));
        }
        // edge to up node
        if (id - resolutionX >= 0) {
            Node* upNode = this->GetNodeById(id - resolutionX);
            if (!upNode) {
                // if up node is not created
                upNode = new Node(id - resolutionX);
            }
            
            upNode->nodeWorldPosition = allTiles[id - resolutionX]->GetWorldPosition() + tileCenterOffset;
            this->AddEdge(new Edge(currentNode, upNode, defaultNodeCost));

        }
        // edge to down node
        if (id + resolutionX < resolutionX * resolutionY) {
            Node* downNode = this->GetNodeById(id + resolutionX);
            if (!downNode) {
                // if down node is not created
                downNode = new Node(id + resolutionX);
            }
            
            downNode->nodeWorldPosition = allTiles[id + resolutionX]->GetWorldPosition() + tileCenterOffset;
            this->AddEdge(new Edge(currentNode, downNode, defaultNodeCost));
        }
    }
}



void TileGraph::Draw() {
    for (Tile* tile : allTiles)
        tile->Draw();
}
