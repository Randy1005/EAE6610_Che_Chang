//
//  Graph.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/19/22.
//

#include "Graph.hpp"



Edge::Edge(Node* i_fromNode, Node* i_toNode, float i_cost) {
    this->fromNode_ = i_fromNode;
    this->toNode_ = i_toNode;
    this->cost_ = i_cost;
}

float Edge::GetCost() {
    return cost_;
}

Node* Edge::GetFromNode() {
    return fromNode_;
}

Node* Edge::GetToNode() {
    return toNode_;
}

Graph::Graph() {
    
}

void Graph::AddEdge(Edge *i_newEdge) {
    allEdges.push_back(i_newEdge);
}

std::vector<Edge*> Graph::GetConnections(Node *i_fromNode) {
    std::vector<Edge*> result;
    for (auto& edge : allEdges) {
        if (edge->GetFromNode() == i_fromNode) {
            result.push_back(edge);
        }
    }
    
    return result;
}

Node* Graph::GetNodeById(int i_nodeId) {
    for (Edge* edge : allEdges) {
        if (edge->GetFromNode()->id == i_nodeId) {
            return edge->GetFromNode();
        }
        
        if (edge->GetToNode()->id == i_nodeId) {
            return edge->GetToNode();
        }
    }
    
    return nullptr;
}


PathFindingList::PathFindingList() {
    
}

NodeRecord PathFindingList::GetSmallestElement() {
    // sort the pathfinding list using costSoFar (ascending)
    std::sort(nodeRecordList.begin(), nodeRecordList.end(), [](NodeRecord& left, NodeRecord& right) {
        return left.costSoFar < right.costSoFar;
    });
    
    return nodeRecordList.at(0);
}

NodeRecord PathFindingList::GetSmallestElementByEstimatedCost() {
    // sort the pathfinding list using estimated total cost (ascending)
    std::sort(nodeRecordList.begin(), nodeRecordList.end(), [](NodeRecord& left, NodeRecord& right) {
        return left.estimatedTotalCost < right.estimatedTotalCost;
    });
    
    return nodeRecordList.at(0);
}


bool PathFindingList::Contains(Node *i_nodeToCheck) {
    return std::find_if(std::begin(nodeRecordList), std::end(nodeRecordList), [&] (NodeRecord const& nodeRecord) { return nodeRecord.node == i_nodeToCheck; }) != std::end(nodeRecordList);
}

NodeRecord PathFindingList::Find(Node *i_nodeToFind) {
    std::vector<NodeRecord>::iterator it = std::find_if(std::begin(nodeRecordList), std::end(nodeRecordList), [&] (NodeRecord& nodeRecord) { return nodeRecord.node == i_nodeToFind; });
    
    return *it;
}

void PathFindingList::Remove(Node* i_nodeToRemove) {
    for (std::vector<NodeRecord>::iterator iter = nodeRecordList.begin(); iter != nodeRecordList.end(); ++iter) {
        if (iter->node == i_nodeToRemove) {
            nodeRecordList.erase(iter);
            break;
        }
            
    }
}


std::vector<Edge*> Graph::PathFindingDijkstra(Node* i_startNode, Node* i_goalNode) {
    
    // initialize node record for the start node
    NodeRecord startNodeRecord;
    startNodeRecord.node = i_startNode;
    startNodeRecord.edge = new Edge(nullptr, nullptr, 0);
    startNodeRecord.costSoFar = 0.0f;
    
    // maintain open and closed list
    PathFindingList* openList = new PathFindingList();
    PathFindingList* closedList = new PathFindingList();
    
    openList->nodeRecordList.push_back(startNodeRecord);
    
    
    NodeRecord currentNodeRecord;
    
    while (openList->nodeRecordList.size() > 0) {
        
        // get the smallest element in the open list (smallest cost so far)
        currentNodeRecord = openList->GetSmallestElement();
        
        NodeRecord endNodeRecord;
        
        // if it is the goal node, then terminate
        if (currentNodeRecord.node == i_goalNode) break;
        
        // otherwise get its outgoing edges
        std::vector<Edge*> connections = GetConnections(currentNodeRecord.node);
        
        // loop through each connection in turn
        for (Edge* edge : connections) {
            // get the cost estimate for the goal node
            Node* endNode = edge->GetToNode();
            float endNodeCost = currentNodeRecord.costSoFar + edge->GetCost();
            
            // skip if the node is closed (if closed list contains the end node)
            if (closedList->Contains(endNode)) continue;
            
            // it is open, and we've found a worse route
            else if (openList->Contains(endNode)) {
                endNodeRecord = openList->Find(endNode);
                
                if (endNodeRecord.costSoFar <= endNodeCost) continue;
            }
            // otherwise we know we found an unvisited node, make a record for it
            else {
                endNodeRecord.node = endNode;
                endNodeRecord.edge = nullptr;
                endNodeRecord.costSoFar = 0.0f;
            }
            
            // update end node record
            endNodeRecord.edge = edge;
            endNodeRecord.costSoFar = endNodeCost;
            
            // add the end node to open list
            if (!openList->Contains(endNode))
                openList->nodeRecordList.push_back(endNodeRecord);
        }
        
        // we've finished looking at all outgoing edges
        // of the current node, add it to closed list
        // remove it from open list
        closedList->nodeRecordList.push_back(currentNodeRecord);
        openList->Remove(currentNodeRecord.node);
    }
    
    // we're here because we don't have more node to search, or
    // we've found the goal, decide which
    std::vector<Edge*> pathList;
    if (currentNodeRecord.node != i_goalNode) {
        // no solution
        pathList.resize(0);
        return pathList;
    }
    else {
        NodeRecord tmpCurrentNodeRecord = currentNodeRecord;
        while (tmpCurrentNodeRecord.node != i_startNode) {
            pathList.push_back(tmpCurrentNodeRecord.edge);
            
            tmpCurrentNodeRecord = closedList->Find(tmpCurrentNodeRecord.edge->GetFromNode());
        }
        
        // reverse the result path list
        std::reverse(pathList.begin(), pathList.end());
    }

    
    // cleanup open / closed list?
    return pathList;
    
}


std::vector<Edge*> Graph::PathFindingAStar(Node* i_startNode, Node* i_goalNode, Heuristics i_heuristics) {
    
    // initialize node record for the start node
    NodeRecord startNodeRecord;
    startNodeRecord.node = i_startNode;
    startNodeRecord.edge = new Edge(nullptr, nullptr, 0);
    startNodeRecord.costSoFar = 0.0f;
    startNodeRecord.estimatedTotalCost = i_heuristics.GetHeuristicCost(i_startNode);
    
    // maintain open and closed list
    PathFindingList* openList = new PathFindingList();
    PathFindingList* closedList = new PathFindingList();
    
    openList->nodeRecordList.push_back(startNodeRecord);
    
    NodeRecord currentNodeRecord;
    
    while (openList->nodeRecordList.size() > 0) {
        
        currentNodeRecord = openList->GetSmallestElementByEstimatedCost();
        
        NodeRecord endNodeRecord;
        
        // to cache heuristic, so we don't have to call the possibly
        // expensive function everytime
        float endNodeHeuristic;
        
        // if it is the goal node, then terminate
        if (currentNodeRecord.node == i_goalNode) break;
        
        // otherwise get its outgoing edges
        std::vector<Edge*> connections = GetConnections(currentNodeRecord.node);
        
        // loop through each connection in turn
        for (Edge* edge : connections) {
            // get the cost estimate for the goal node
            Node* endNode = edge->GetToNode();
            float endNodeCost = currentNodeRecord.costSoFar + edge->GetCost();
            
            // if the node is closed we may have to skip or
            // remove it from the closed list
            if (closedList->Contains(endNode)) {
                
                // find the record corresponding to the node
                NodeRecord endNodeRecord = closedList->Find(endNode);
                
                // if we didn't find a shorter route, skip
                if (endNodeRecord.costSoFar <= endNodeCost) continue;
                
                // otherwise remove from closed list
                closedList->Remove(endNodeRecord.node);
                
                // calculate heuristic
                endNodeHeuristic = endNodeRecord.estimatedTotalCost - endNodeCost;
                
            }
            // skip if the node is open and we didn't find a
            // better route
            else if (openList->Contains(endNode)) {
                // find the record corresponding to the node
                NodeRecord endNodeRecord = openList->Find(endNode);
                
                // if our route is no better, skip
                if (endNodeRecord.costSoFar <= endNodeCost) continue;
                
                // calculate heuristic
                endNodeHeuristic = endNodeRecord.estimatedTotalCost - endNodeCost;
                
            }
            // otherwise we know we have an unvisited node
            else {
                // make a record for it
                endNodeRecord.node = endNode;
                
                // calculate heuristic
                endNodeHeuristic = i_heuristics.GetHeuristicCost(endNode);
            }
            
            // update cost, estimate and edge
            endNodeRecord.costSoFar = endNodeCost;
            endNodeRecord.edge = edge;
            endNodeRecord.estimatedTotalCost = endNodeCost + endNodeHeuristic;
            
            // add the node to the open list
            if (!openList->Contains(endNode))
                openList->nodeRecordList.push_back(endNodeRecord);
            
        }
        
        // finished looking at the outgoing edges of the current node
        // add the node to closed list
        // remove it from open list
        openList->Remove(currentNodeRecord.node);
        closedList->nodeRecordList.push_back(currentNodeRecord);
    }
    
    // now we've either found a solution or ran out of nodes to search

    std::vector<Edge*> pathList;
    if (currentNodeRecord.node != i_goalNode) {
        // no solution
        pathList.resize(0);
        return pathList;
    }
    else {
        NodeRecord tmpCurrentNodeRecord = currentNodeRecord;
        while (tmpCurrentNodeRecord.node != i_startNode) {
            pathList.push_back(tmpCurrentNodeRecord.edge);
            
            tmpCurrentNodeRecord = closedList->Find(tmpCurrentNodeRecord.edge->GetFromNode());
        }
        
        // reverse the result path list
        std::reverse(pathList.begin(), pathList.end());
    }

    
    // cleanup open / closed list?
    return pathList;
}


