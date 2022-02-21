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


class Node {
public:
    Node(int i_id);
    int id;
};

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
};


class PathFindingList {
public:
    PathFindingList();
    NodeRecord GetSmallestElement();
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
    
    // pathfinding algorithms
    std::vector<Edge*> PathFindingDijkstra(Node* i_startNode, Node* i_endNode);
    
private:
    std::vector<Edge*> allEdges;
};


#endif /* Graph_hpp */
