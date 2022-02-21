//
//  GraphTestCaseParser.hpp
//  GameAI_CheChang_Asg1
//
//  Created by 張哲 on 2/21/22.
//

#ifndef GraphTestCaseParser_hpp
#define GraphTestCaseParser_hpp

#include "Graph.hpp"
#include "ofMain.h"
#include <string>

class GraphTestCaseParser {
public:
    GraphTestCaseParser();
    Graph* BuildGraph(std::string i_inputFileName);
    
};

#endif /* GraphTestCaseParser_hpp */
