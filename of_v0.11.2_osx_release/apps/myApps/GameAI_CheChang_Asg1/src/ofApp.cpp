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
    all_boids.push_back(boid);
    
    boid2 = new Boid(600, 280, 10, 0, ofColor::green, ofGetWidth(), ofGetHeight());
    boid2->rigid_body.mass = 1.0f;
    all_boids.push_back(boid2);
    
    boid3 = new Boid(600, 340, 10, 0, ofColor::green, ofGetWidth(), ofGetHeight());
    boid3->rigid_body.mass = 1.0f;
    all_boids.push_back(boid3);
    
    boid4 = new Boid(600, 380, 10, 0, ofColor::green, ofGetWidth(), ofGetHeight());
    boid4->rigid_body.mass = 1.0f;
    all_boids.push_back(boid4);
    
    // this boid does not need to be drawn, it just has to always have the centroid velocity
    centroid = new Boid(0, 0, 10, 0, ofColor::black, ofGetWidth(), ofGetHeight());
    
    
    // TODO: figure out a procedure way to get these separation targets
    boid_sep_targets.push_back(boid2);
    boid_sep_targets.push_back(boid3);
    boid_sep_targets.push_back(boid4);
    
    boid2_sep_targets.push_back(boid);
    boid2_sep_targets.push_back(boid3);
    boid2_sep_targets.push_back(boid4);
    
    boid3_sep_targets.push_back(boid);
    boid3_sep_targets.push_back(boid2);
    boid3_sep_targets.push_back(boid4);
    
    boid4_sep_targets.push_back(boid);
    boid4_sep_targets.push_back(boid2);
    boid4_sep_targets.push_back(boid3);
    
    
    
    
    separation_behavior = new Separation(boid, boid_sep_targets, boid->radius + 2.0f, 0.01f, 6.0f);
    separation_behavior2 = new Separation(boid2, boid2_sep_targets, boid2->radius + 2.0f, 0.01f, 6.0f);
    separation_behavior3 = new Separation(boid3, boid3_sep_targets, boid3->radius + 2.0f, 0.01f, 6.0f);
    separation_behavior4 = new Separation(boid4, boid4_sep_targets, boid4->radius + 2.0f, 0.01f, 6.0f);
    
    
    velocitymatch_behavior = new VelocityMatch(boid, centroid, 0.2f, 0.5f);
    velocitymatch_behavior2 = new VelocityMatch(boid2, centroid, 2.0f, 0.5f);
    velocitymatch_behavior3 = new VelocityMatch(boid3, centroid, 2.0f, 0.5f);
    velocitymatch_behavior4 = new VelocityMatch(boid4, centroid, 2.0f, 0.5f);
    
    flocking_behavior = new Flocking(separation_behavior, velocitymatch_behavior, 1.0f, 0.3f, 0.8f, 0.01f, 0.02f);
    flocking_behavior2 = new Flocking(separation_behavior2, velocitymatch_behavior2, 1.0f, 0.3f, 0.8f, 0.1f, 0.02f);
    flocking_behavior3 = new Flocking(separation_behavior3, velocitymatch_behavior3, 1.0f, 0.3f, 0.8f, 0.1f, 0.02f);
    flocking_behavior4 = new Flocking(separation_behavior4, velocitymatch_behavior4, 1.0f, 0.3f, 0.8f, 0.1f, 0.02f);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    // update centroid velocity
    ofVec2f centroid_velocity(0, 0);
    float total_mass = 0;
    for (Boid* boid : all_boids) {
        centroid_velocity += boid->rigid_body.mass * boid->rigid_body.velocity;
        total_mass += boid->rigid_body.mass;
    }
    centroid_velocity /= total_mass;
    centroid->rigid_body.velocity = centroid_velocity;
    
    boid->Update();
    boid2->Update();
    boid3->Update();
    boid4->Update();
    
    if (scene_id == 0) {
        // seek scene
        boid->rigid_body.linear_acceleration = boid->Seek(ofVec2f(mouseX, mouseY), 0.2f, 2.0f, 20, 5, 0.5f).linear_acceleration;
    } else if (scene_id == 1) {
        // kinematic motion scene
        boid->rigid_body.velocity = boid->MoveAlongWindowEdge();
    } else if (scene_id == 2) {
        // wander scene
        DynamicSteeringOutput steering_output = boid->Wander(30.0f, 2.0f, 1.4f);
        boid->rigid_body.linear_acceleration = steering_output.linear_acceleration;
        boid->rigid_body.angular_acceleration = steering_output.angular_acceleration;
    } else {
        boid->rigid_body.linear_acceleration = boid->Seek(ofVec2f(mouseX, mouseY), 0.2f, 2.0f, 20, 5, 0.5f).linear_acceleration;
        boid2->rigid_body.linear_acceleration = flocking_behavior2->GetSteeringOutput().linear_acceleration;
        boid3->rigid_body.linear_acceleration = flocking_behavior3->GetSteeringOutput().linear_acceleration;
        boid4->rigid_body.linear_acceleration = flocking_behavior4->GetSteeringOutput().linear_acceleration;
        
    }
    
    
    
    boid->rigid_body.angular_acceleration = boid->LookWhereYoureGoing().angular_acceleration;

    boid2->rigid_body.angular_acceleration = boid2->LookWhereYoureGoing().angular_acceleration;
    
    boid3->rigid_body.angular_acceleration = boid3->LookWhereYoureGoing().angular_acceleration;
    
    boid4->rigid_body.angular_acceleration = boid4->LookWhereYoureGoing().angular_acceleration;
    

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    // gui
    gui_panel.draw();
    
    boid->Draw();
    boid2->Draw();
    boid3->Draw();
    boid4->Draw();
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
    
    // refactor this, this only records mouse input for 'boid'
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
