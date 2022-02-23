//
//  Graph.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/19/22.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <vector>
#include <algorithm>
#include "Node.hpp"
#include "Heuristics.hpp"
#include "ofVec2f.h"




class Edge {
public:
    Edge(Node* i_fromNode, Node* i_toNode, float i_cost);
    
    float GetCost();
    Node* GetFromNode();
    Node* GetToNode();

private:
    Node* fromNode_;
    Node* toNode_;
    float cost_;
    
    
};


struct NodeRecord {
    Node* node;
    Edge* edge;
    float costSoFar;
    float estimatedTotalCost;
};


class PathFindingList {
public:
    PathFindingList();
    NodeRecord GetSmallestElement();
    NodeRecord GetSmallestElementByEstimatedCost();
    bool Contains(Node* i_nodeToCheck);
    NodeRecord Find(Node* i_nodeToFind);
    void Remove(Node* i_nodeToRemove);
    
    std::vector<NodeRecord> nodeRecordList;
    
};



class Graph {
public:
    Graph();
    void AddEdge(Edge* i_newEdge);
    std::vector<Edge*> GetConnections(Node* i_fromNode);
    Node* GetNodeById(int i_nodeId);
    
    // pathfinding algorithms
    std::vector<Edge*> PathFindingDijkstra(Node* i_startNode, Node* i_goalNode);
    
    std::vector<Edge*> PathFindingAStar(Node* i_startNode, Node* i_goalNode, Heuristics i_heuristics);
    
    std::vector<Edge*> allEdges;
};


#endif /* Graph_hpp */
