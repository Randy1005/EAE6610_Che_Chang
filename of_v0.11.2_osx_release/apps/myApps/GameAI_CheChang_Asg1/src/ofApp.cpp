#include "ofApp.h"

// TODO: implement "reappear from other side if boid goes out of range"

//--------------------------------------------------------------
void ofApp::setup(){
    // test boid
    boid = new Boid(500, 320, 10, 0, ofColor::orange, ofGetWidth(), ofGetHeight());
    boid->rigid_body.linear_acceleration = ofVec2f(-0.15f, 0.01f);
    
    boid2 = new Boid(500, 400, 10, 0, ofColor::green, ofGetWidth(), ofGetHeight());
    boid2->rigid_body.linear_acceleration = ofVec2f(-0.15f, 0.01f);
}

//--------------------------------------------------------------
void ofApp::update(){
    boid->Update();
    boid2->Update();
    
    boid->rigid_body.linear_acceleration = boid->Evade(boid2->rigid_body, boid->radius + 5.0f, 0.02f, 0.1f).linear_acceleration;
    
    boid->rigid_body.angular_acceleration = boid->LookWhereYoureGoing().angular_acceleration;

    
    boid2->rigid_body.angular_acceleration = boid2->LookWhereYoureGoing().angular_acceleration;
    

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    boid->Draw();
    boid2->Draw();
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
