#include "ofApp.h"

// TODO: implement "reappear from other side if boid goes out of range"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // test boid
    boid = new Boid(200, 400, 10, 0, ofColor::orange, ofGetWidth(), ofGetHeight());
    boid->rigid_body.velocity = ofVec2f(0.4f, 0.4f);



}

//--------------------------------------------------------------
void ofApp::update(){
    boid->Update();
}

//--------------------------------------------------------------
void ofApp::draw(){
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
    boid->mouse_x = x;
    boid->mouse_y = y;
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
