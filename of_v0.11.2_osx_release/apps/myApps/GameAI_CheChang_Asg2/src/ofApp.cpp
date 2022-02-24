#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(1080, 800);
    
    gui_panel.setup();
    
    gui_panel.add(wallModeBtn.setup("Draw Obstacles"));
    gui_panel.add(pathFindModeBtn.setup("Path Find"));
    gui_panel.add(resetBtn.setup("Reset Obstacles and Clear Pathlist"));

    
    wallModeBtn.addListener(this, &ofApp::WallModeButtonPressed);
    pathFindModeBtn.addListener(this, &ofApp::PathFindModeButtonPressed);
    resetBtn.addListener(this, &ofApp::ResetButtonPressed);
    
    // test boid
    boid = new Boid(600, 220, 8, 0, ofColor::orange, ofGetWidth(), ofGetHeight());
    boid->rigid_body.mass = 30.0f; // leader boid
    boid->rigid_body.angular_velocity = 0.0f;
    boid->rigid_body.angular_acceleration = 0.0f;
    
    
    // test graph
    tcParser = new GraphTestCaseParser();
    graph = tcParser->BuildGraph("hsinchu.txt");
   
    // example graph cartesian coordinates
//    graph->GetNodeById(1)->nodeWorldPosition = ofVec2f(0, 0);
//    graph->GetNodeById(2)->nodeWorldPosition = ofVec2f(2.2f, 3.2f);
//    graph->GetNodeById(3)->nodeWorldPosition = ofVec2f(0, 2.5f);
//    graph->GetNodeById(4)->nodeWorldPosition = ofVec2f(5.3f, 1.5f);
//    graph->GetNodeById(5)->nodeWorldPosition = ofVec2f(7, 1);
//    graph->GetNodeById(6)->nodeWorldPosition = ofVec2f(7, 3.2f);
//    graph->GetNodeById(7)->nodeWorldPosition = ofVec2f(8, 1.5f);
//    graph->GetNodeById(8)->nodeWorldPosition = ofVec2f(6.5f, 0);
//    graph->GetNodeById(9)->nodeWorldPosition = ofVec2f(3.8f, 6.7f);
//    graph->GetNodeById(10)->nodeWorldPosition = ofVec2f(12.0f, 2.1f);
//    graph->GetNodeById(11)->nodeWorldPosition = ofVec2f(16.0f, 5.8f);
//    graph->GetNodeById(12)->nodeWorldPosition = ofVec2f(2.5f, 18.0f);
    
    
    
    Heuristics heuristics(HeuristicFunction::MANHATTAN_DIST, graph->GetNodeById(10));
    auto startTime = std::chrono::steady_clock::now();
//    std::vector<Edge*> path = graph->PathFindingAStar(graph->GetNodeById(1), graph->GetNodeById(10), heuristics);
//     std::vector<Edge*> path = graph->PathFindingDijkstra(graph->GetNodeById(1), graph->GetNodeById(934));
    
    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;
    std::cout << "run time: " << elapsed.count() * 1000.0f << std::endl;
    
    // tile graph set up
    tileGraph = new TileGraph(40, 40, ofGetWidth(), ofGetHeight());
    tileGraph->GenerateTiles();
    tileGraph->GenerateEdges();

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    boid->Update();
    
    
    if (mode == 0) {

    } else if (mode == 1 && pathToTarget.size() != 0) {
        
        // if we haven't reached our targe yet
        Edge* currentSeekingEdge = pathToTarget[currentPathNodeId];
        ofVec2f seekTargetPosition = currentSeekingEdge->GetToNode()->nodeWorldPosition;
        if ((boid->rigid_body.position - seekTargetPosition).length() >= 4) {
            // continue seeking
            boid->rigid_body.linear_acceleration = boid->Seek(seekTargetPosition, 0.2f, 2.0f, 30, 3.5, 0.24f).linear_acceleration;
        }
        else {
            // seek next node
            if (currentPathNodeId + 1 < pathToTarget.size())
                currentPathNodeId++;
        }
        
    }
    
    
    boid->rigid_body.angular_acceleration = boid->LookWhereYoureGoing().angular_acceleration;

}

//--------------------------------------------------------------
void ofApp::draw(){
    // gui
    gui_panel.draw();
    
    boid->Draw();
    
    tileGraph->Draw();
}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    float tileSizeX = ofGetWidth() / (float)tileGraph->resolutionX;
    float tileSizeY = ofGetHeight() / (float)tileGraph->resolutionY;
    
    ofVec2f targetTileIndex2D = ofVec2f(floor(x/tileSizeX), floor(y/tileSizeY));
    
    int targetTileIndex1D = (int)targetTileIndex2D.x + tileGraph->resolutionX * (int)targetTileIndex2D.y;
    
    ofVec2f characterTileIndex2D = ofVec2f(floor(boid->rigid_body.position.x/tileSizeX), floor(boid->rigid_body.position.y/tileSizeY));
    int characterTileIndex1D = (int)characterTileIndex2D.x + tileGraph->resolutionX * (int)characterTileIndex2D.y;
    
    if (mode == 0) {
        // wall mode
        
        
        tileGraph->allTiles.at(targetTileIndex1D)->walkable = false;
        
        // remove all edges associated with this tile node
        // !! this somehow doesn't eliminate all 8 edges in between one
        // !! node and its adjacent nodes
        for (std::vector<Edge*>::iterator it = tileGraph->allEdges.begin(); it != tileGraph->allEdges.end(); ++it) {
            // edges to this node
            if ((*it)->GetToNode()->id == targetTileIndex1D || (*it)->GetFromNode()->id == targetTileIndex1D)
                tileGraph->allEdges.erase(it);
        }
    }
    else if (mode == 1) {
        // path find mode
        Heuristics heuristics(HeuristicFunction::EUCLIDEAN_DIST, tileGraph->GetNodeById(targetTileIndex1D));
        
        pathToTarget = tileGraph->PathFindingAStar(tileGraph->GetNodeById(characterTileIndex1D), tileGraph->GetNodeById(targetTileIndex1D), heuristics);
        
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::WallModeButtonPressed() {
    mode = 0;
}

void ofApp::PathFindModeButtonPressed() {
    mode = 1;
}

void ofApp::ResetButtonPressed() {
    boid->rigid_body.position = ofVec2f(600, 220);
    boid->rigid_body.linear_acceleration = ofVec2f(0, 0);
    boid->rigid_body.velocity = ofVec2f(0, 0);
    boid->rigid_body.angular_velocity = 0.0f;
    boid->rigid_body.angular_acceleration = 0.0f;
    
    pathToTarget.clear();
    
    // set all tiles back to walkable
    for (Tile* tile : tileGraph->allTiles) {
        if (!tile->walkable)
            tile->walkable = true;
    }
    
    // regenerate edges
    tileGraph->allEdges.clear();
    tileGraph->GenerateEdges();
    
    
}
