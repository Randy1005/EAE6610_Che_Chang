#include "ofApp.h"

// TODO: implement "reappear from other side if boid goes out of range"

//--------------------------------------------------------------
void ofApp::setup(){
    gui_panel.setup();
    
    gui_panel.add(seek_mode_btn.setup("seek"));
    gui_panel.add(kinematic_motion_mode_btn.setup("kinematic motion"));
    gui_panel.add(wander_mode_btn.setup("wander"));
    gui_panel.add(flocking_mode_btn.setup("flocking"));
    
    seek_mode_btn.addListener(this, &ofApp::SeekModeButtonPressed);
    kinematic_motion_mode_btn.addListener(this, &ofApp::KinematicModeButtonPressed);
    wander_mode_btn.addListener(this, &ofApp::WanderModeButtonPressed);
    flocking_mode_btn.addListener(this, &ofApp::FlockingModeButtonPressed);
    
    // test boid
    boid = new Boid(600, 220, 10, 0, ofColor::orange, ofGetWidth(), ofGetHeight());
    boid->rigid_body.mass = 30.0f; // leader boid
    
    
    // test graph

    tcParser = new GraphTestCaseParser();
    graph = tcParser->BuildGraph("USA-road-d.NY.gr");
    
    // example.txt cartesian coordinates
//    graph->GetNodeById(0)->nodeWorldPosition_ = ofVec2f(0, 0);
//    graph->GetNodeById(1)->nodeWorldPosition_ = ofVec2f(2.2f, 3.2f);
//    graph->GetNodeById(2)->nodeWorldPosition_ = ofVec2f(0, 2.5f);
//    graph->GetNodeById(3)->nodeWorldPosition_ = ofVec2f(5.3f, 1.5f);
//    graph->GetNodeById(4)->nodeWorldPosition_ = ofVec2f(7, 1);
//    graph->GetNodeById(5)->nodeWorldPosition_ = ofVec2f(7, 3.2f);
//    graph->GetNodeById(6)->nodeWorldPosition_ = ofVec2f(8, 1.5f);
//    graph->GetNodeById(7)->nodeWorldPosition_ = ofVec2f(6.5f, 0);
    
    
    
    Heuristics heuristics(HeuristicFunction::RANDOM, graph->GetNodeById(300));
    
//     std::vector<Edge*> path = graph->PathFindingAStar(graph->GetNodeById(2), graph->GetNodeById(300), heuristics);
     std::vector<Edge*> path = graph->PathFindingDijkstra(graph->GetNodeById(2), graph->GetNodeById(300));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    boid->Update();
    
    
    if (scene_id == 0) {
        // seek scene
        boid->rigid_body.linear_acceleration = boid->Seek(ofVec2f(mouseX, mouseY), 0.2f, 2.0f, 20, 5, 0.5f).linear_acceleration;
    } else if (scene_id == 1) {
       
    } else if (scene_id == 2) {
        
    } else {
        
        
    }
    
    
    
    boid->rigid_body.angular_acceleration = boid->LookWhereYoureGoing().angular_acceleration;

}

//--------------------------------------------------------------
void ofApp::draw(){
    // gui
    gui_panel.draw();
    
    boid->Draw();
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

void ofApp::SeekModeButtonPressed() {
    scene_id = 0;
    boid->rigid_body.position = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
}

void ofApp::KinematicModeButtonPressed() {
    scene_id = 1;
    boid->rigid_body.position = ofVec2f(50, ofGetHeight() - 50);
}

void ofApp::WanderModeButtonPressed() {
    scene_id = 2;
    boid->rigid_body.position = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
}

void ofApp::FlockingModeButtonPressed() {
    scene_id = 3;
    boid->rigid_body.position = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
}
