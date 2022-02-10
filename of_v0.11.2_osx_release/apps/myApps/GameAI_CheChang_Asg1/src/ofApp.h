#pragma once
#include "Boid.hpp"
#include "ofMain.h"
#include "ofxGui.h"
#include "Separation.hpp"
#include "VelocityMatch.hpp"
#include "Flocking.hpp"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // mode change buttons
    void SeekModeButtonPressed();
    void KinematicModeButtonPressed();
    void WanderModeButtonPressed();
    void FlockingModeButtonPressed();
    
    std::vector<Boid*> boid_sep_targets;
    std::vector<Boid*> boid2_sep_targets;
    std::vector<Boid*> boid3_sep_targets;
    std::vector<Boid*> boid4_sep_targets;
    Separation* separation_behavior;
    Separation* separation_behavior2;
    Separation* separation_behavior3;
    Separation* separation_behavior4;
    VelocityMatch* velocitymatch_behavior;
    VelocityMatch* velocitymatch_behavior2;
    VelocityMatch* velocitymatch_behavior3;
    VelocityMatch* velocitymatch_behavior4;
    Flocking* flocking_behavior;
    Flocking* flocking_behavior2;
    Flocking* flocking_behavior3;
    Flocking* flocking_behavior4;



    Boid* boid;
    Boid* boid2;
    Boid* boid3;
    Boid* boid4;
    Boid* centroid;
    std::vector<Boid*> all_boids;
    int scene_id;


    // gui buttons
    ofxPanel gui_panel;
    ofxButton seek_mode_btn;
    ofxButton kinematic_motion_mode_btn;
    ofxButton wander_mode_btn;
    ofxButton flocking_mode_btn;
		
};
