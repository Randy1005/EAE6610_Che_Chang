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
        
        resultGraph->AddEdge(new Edge(new Node(nodeIdA), new Node(nodeIdB), edgeCost));
        
    }
    

    return resultGraph;
    
    
    
}
