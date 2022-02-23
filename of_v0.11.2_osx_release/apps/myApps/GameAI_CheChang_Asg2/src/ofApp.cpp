#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(1080, 800);
    
    gui_panel.setup();
    
    gui_panel.add(wallModeBtn.setup("Draw Obstacles"));
    gui_panel.add(pathFindModeBtn.setup("Path Find"));

    
    wallModeBtn.addListener(this, &ofApp::WallModeButtonPressed);
    pathFindModeBtn.addListener(this, &ofApp::PathFindModeButtonPressed);

    
    // test boid
    boid = new Boid(600, 220, 10, 0, ofColor::orange, ofGetWidth(), ofGetHeight());
    boid->rigid_body.mass = 30.0f; // leader boid
    
    
    // test graph
    tcParser = new GraphTestCaseParser();
    graph = tcParser->BuildGraph("USA-road-d.NY.gr");
    
    // example.txt graph cartesian coordinates
//    graph->GetNodeById(0)->nodeWorldPosition_ = ofVec2f(0, 0);
//    graph->GetNodeById(1)->nodeWorldPosition_ = ofVec2f(2.2f, 3.2f);
//    graph->GetNodeById(2)->nodeWorldPosition_ = ofVec2f(0, 2.5f);
//    graph->GetNodeById(3)->nodeWorldPosition_ = ofVec2f(5.3f, 1.5f);
//    graph->GetNodeById(4)->nodeWorldPosition_ = ofVec2f(7, 1);
//    graph->GetNodeById(5)->nodeWorldPosition_ = ofVec2f(7, 3.2f);
//    graph->GetNodeById(6)->nodeWorldPosition_ = ofVec2f(8, 1.5f);
//    graph->GetNodeById(7)->nodeWorldPosition_ = ofVec2f(6.5f, 0);
    
    
    
//    Heuristics heuristics(HeuristicFunction::RANDOM, graph->GetNodeById(300));
    
//     std::vector<Edge*> path = graph->PathFindingAStar(graph->GetNodeById(2), graph->GetNodeById(300), heuristics);
//     std::vector<Edge*> path = graph->PathFindingDijkstra(graph->GetNodeById(2), graph->GetNodeById(300));
    
    
    // tile graph set up
    tileGraph = new TileGraph(50, 50, ofGetWidth(), ofGetHeight());
    tileGraph->GenerateTiles();

}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    boid->Update();
    
    
    if (mode == 0) {
        // wall mode
//        boid->rigid_body.linear_acceleration = boid->Seek(ofVec2f(mouseX, mouseY), 0.2f, 2.0f, 20, 5, 0.5f).linear_acceleration;
    } else if (mode == 1) {
        
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
    
    
    if (mode == 0) {
        // wall mode
        float tileSizeX = ofGetWidth() / (float)tileGraph->resolutionX;
        float tileSizeY = ofGetHeight() / (float)tileGraph->resolutionY;
        
        ofVec2f tileIndex2D = ofVec2f(floor(x/tileSizeX), floor(y/tileSizeY));
        
        int tileIndex1D = (int)tileIndex2D.x + tileGraph->resolutionX * (int)tileIndex2D.y;
        
        tileGraph->allTiles.at(tileIndex1D)->walkable = false;
    }
    else if (mode == 1) {
        // path find mode
        
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
