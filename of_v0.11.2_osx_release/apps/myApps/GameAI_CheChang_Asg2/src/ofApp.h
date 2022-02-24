#pragma once
#include "Boid.hpp"
#include "ofMain.h"
#include "ofxGui.h"
#include "Separation.hpp"
#include "VelocityMatch.hpp"
#include "Flocking.hpp"
#include "GraphTestCaseParser.hpp"
#include "TileGraph.hpp"
#include <chrono>

class ofApp : public ofBaseApp {
    
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
    void WallModeButtonPressed();
    void PathFindModeButtonPressed();
    void ResetButtonPressed();

    
    std::vector<Boid*> boid_sep_targets;
    std::vector<Boid*> boid2_sep_targets;
    std::vector<Boid*> boid3_sep_targets;
    std::vector<Boid*> boid4_sep_targets;
    std::vector<Boid*> boid5_sep_targets;
    std::vector<Boid*> boid6_sep_targets;
    Separation* separation_behavior;
    Separation* separation_behavior2;
    Separation* separation_behavior3;
    Separation* separation_behavior4;
    Separation* separation_behavior5;
    Separation* separation_behavior6;
    VelocityMatch* velocitymatch_behavior;
    VelocityMatch* velocitymatch_behavior2;
    VelocityMatch* velocitymatch_behavior3;
    VelocityMatch* velocitymatch_behavior4;
    VelocityMatch* velocitymatch_behavior5;
    VelocityMatch* velocitymatch_behavior6;
    Flocking* flocking_behavior;
    Flocking* flocking_behavior2;
    Flocking* flocking_behavior3;
    Flocking* flocking_behavior4;
    Flocking* flocking_behavior5;
    Flocking* flocking_behavior6;



    Boid* boid;
    Boid* boid2;
    Boid* boid3;
    Boid* boid4;
    Boid* boid5;
    Boid* boid6;
    
    Boid* centroid;
    std::vector<Boid*> all_boids;
    int mode = 0;


    // gui buttons
    ofxPanel gui_panel;
    ofxButton wallModeBtn;
    ofxButton pathFindModeBtn;
    ofxButton resetBtn;
    
    
    // graph
    Graph* graph;
    GraphTestCaseParser* tcParser;
    
    // tile graph
    TileGraph* tileGraph;
    
    // path list
    std::vector<Edge*> pathToTarget;
    int currentPathNodeId = 0;
};
