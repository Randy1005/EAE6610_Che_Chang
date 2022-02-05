#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // test boid
    boid = new Boid(ofGetWidth() / 2, ofGetHeight() / 2, 10, 0, ofColor::orange);
    boid->rigid_body.velocity = ofVec2f(0.4f, 0.4f);
    boid->rigid_body.acceleration = ofVec2f(0.01f, -0.02f);
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
