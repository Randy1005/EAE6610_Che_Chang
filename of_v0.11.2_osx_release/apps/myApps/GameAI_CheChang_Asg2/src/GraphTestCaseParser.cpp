//
//  GraphTestCaseParser.cpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/21/22.
//

#include "GraphTestCaseParser.hpp"
GraphTestCaseParser::GraphTestCaseParser() {
    
}

Graph* GraphTestCaseParser::BuildGraph(std::string i_inputFileName) {
    Graph* resultGraph = new Graph();
    ofBuffer buffer = ofBufferFromFile(i_inputFileName);
    
    for (auto line : buffer.getLines()) {
        std::stringstream ss(line);
        
        float nodeIdA, nodeIdB, edgeCost;
        
        ss >> nodeIdA >> nodeIdB >> edgeCost;
        
//        std::cout << nodeIdA << " " << nodeIdB << " " << edgeCost << std::endl;
        
        // if node id A is already in the graph
        if (resultGraph->GetNodeById(nodeIdA)) {
            resultGraph->AddEdge(new Edge(resultGraph->GetNodeById(nodeIdA), new Node(nodeIdB), edgeCost));
        }
        
        // if node id B is already in the graph
        else if (resultGraph->GetNodeById(nodeIdB)) {
            resultGraph->AddEdge(new Edge(new Node(nodeIdA), resultGraph->GetNodeById(nodeIdB), edgeCost));
        }
        
        // if both are new nodes
        else if (!resultGraph->GetNodeById(nodeIdA) && !resultGraph->GetNodeById(nodeIdB)) {
            resultGraph->AddEdge(new Edge(new Node(nodeIdA), new Node(nodeIdB), edgeCost));
        }
        
        
    }
    

    return resultGraph;
    
    
    
}
