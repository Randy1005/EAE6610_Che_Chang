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
//    graph = new Graph();
//    Node* node1 = new Node(0);
//    Node* node2 = new Node(1);
//    Node* node3 = new Node(2);
//    Node* node4 = new Node(3);
//    Node* node5 = new Node(4);
//    Node* node6 = new Node(5);
//    Node* node7 = new Node(6);
//    Node* node8 = new Node(7);
//
//    graph->AddEdge(new Edge(node1, node2, 1.2));
//    graph->AddEdge(new Edge(node1, node3, 3.4));
//    graph->AddEdge(new Edge(node3, node4, 2.5));
//    graph->AddEdge(new Edge(node4, node5, 2.3));
//    graph->AddEdge(new Edge(node4, node6, 3.5));
//    graph->AddEdge(new Edge(node6, node7, 1.2));
//    graph->AddEdge(new Edge(node5, node7, 0.2));
//    graph->AddEdge(new Edge(node5, node8, 6.2));

    
    
    tcParser = new GraphTestCaseParser();
    graph = tcParser->BuildGraph("example.txt");
    
    
    Heuristics heuristics(HeuristicFunction::RANDOM, graph->GetNodeById(7));
    
    std::vector<Edge*> path = graph->PathFindingDijkstra(graph->GetNodeById(0), graph->GetNodeById(7));
    
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
