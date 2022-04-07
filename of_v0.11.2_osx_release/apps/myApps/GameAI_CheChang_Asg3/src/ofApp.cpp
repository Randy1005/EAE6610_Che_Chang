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
    
    // shelter
    shelterPosition = ofVec2f(800, 600);
    
    // flag
    flagPosition = ofVec2f(200, 700);
    
    // character boid
    boid = new Boid(600, 220, 8, 0, ofColor::orange, ofGetWidth(), ofGetHeight());
    boid->rigid_body.mass = 15.0f; // leader boid
    boid->rigid_body.angular_velocity = 0.0f;
    boid->rigid_body.angular_acceleration = 0.0f;
    
    // monster boid
    monster = new Boid(300, 400, 10, 0, ofColor::purple, ofGetWidth(), ofGetHeight());
    monster->rigid_body.mass = 30.0f;
    monster->rigid_body.angular_velocity = 0.0f;
    monster->rigid_body.angular_acceleration = 0.0f;
    
    
    // test graph
//    tcParser = new GraphTestCaseParser();
//    graph = tcParser->BuildGraph("hsinchu.txt");
   
    
    // tile graph set up
    tileGraph = new TileGraph(40, 40, ofGetWidth(), ofGetHeight());
    tileGraph->GenerateTiles();
    tileGraph->GenerateEdges();

    // set up path finder
    pathFinder = new PathFinder(HeuristicFunction::EUCLIDEAN_DIST, tileGraph);
    
    // set up decision tree nodes
    isMassBiggerThan = new DTFloatDecision();
    isMassBiggerThan->valueToCheckAgainst = 20.0f;
    
    wanderAction = new DTBoolAction("wander");
    pathFindToShelterAction = new DTBoolAction("path find to shelter");
    pathFindToFlagAction = new DTTimeoutAction("path find to flag position", 10.0f);
    
    dummyAction = new DTAction("just a dummy action so the tree doesn't traverse to null nodes");
    dummyAction2 = new DTAction("just a dummy action so the tree doesn't traverse to null nodes");
    
    
    isMassBiggerThan->trueNode = wanderAction;
    isMassBiggerThan->falseNode = pathFindToFlagAction;
    isMassBiggerThan->testValue = boid->rigid_body.mass;
    
    // if wander action node condition evaluates to true, path find to shelter
    wanderAction->trueNode = pathFindToShelterAction;
    
    // when pathfinding to flag action times out, traverse to its true node
    pathFindToFlagAction->trueNode = dummyAction;
    
    pathFindToShelterAction->trueNode = dummyAction2;
    
    // wander action node condition: when mouse gets too close to boid
    wanderAction->condition = [this]() {
        return (boid->rigid_body.position - mousePosition).length() < 30.0f;
    };
    
    
    
    // set up wanderAction node action and condition
    wanderAction->action = [this]() {
        boid->rigid_body.linear_acceleration = boid->Wander(20.0f, 8.0f, 0.01f).linear_acceleration;
    };
    
    
    // set up pathFindToShelterAction node action
    pathFindToShelterAction->action = [this]() {
        std::cout << "boid pathfind to shelter" << std::endl;
        DynamicSteeringOutput pathfindSteeringOutput = pathFinder->PathFind(boid, shelterPosition);
        boid->rigid_body.linear_acceleration = pathfindSteeringOutput.linear_acceleration;
        boid->rigid_body.angular_velocity = pathfindSteeringOutput.angular_acceleration;
    };
    
    // set up pathFindToFlagAction node action
    pathFindToFlagAction->action = [this]() {
        std::cout << "boid pathfind to flag" << std::endl;
        DynamicSteeringOutput pathfindSteeringOutput = pathFinder->PathFind(boid, flagPosition);
        boid->rigid_body.linear_acceleration = pathfindSteeringOutput.linear_acceleration;
        boid->rigid_body.angular_velocity = pathfindSteeringOutput.angular_acceleration;
        
    };
    
    dummyAction->action = [this]() {
        std::cout << "doing nothing" << std::endl;
    };
    
    dummyAction2->action = [this]() {
        std::cout << "doing nothing" << std::endl;
    };
    
    // set up behavior tree nodes
    rootSelector = new BTSelector();
    huntSequence = new BTSequence();
    untilFailNode = new BTUntilFail();
    isEnemyNearNode = new BTEnemyNear(boid, monster);
    patrolNode = new BTPatrol(monster);
    pathFindToCharacterNode = new BTPathFind(boid, monster, pathFinder);
    
    rootSelector->children.push_back(untilFailNode);
    rootSelector->children.push_back(patrolNode);
    
    untilFailNode->child = huntSequence;
    
    huntSequence->children.push_back(isEnemyNearNode);
    huntSequence->children.push_back(pathFindToCharacterNode);
}

//--------------------------------------------------------------
void ofApp::update(){
    boid->Update();
    monster->Update();
    
    
    // !! run Decision Tree traveral: should do a instanceof check, then cast, then run action
    
    // !! run Behavior Tree traversal
    rootSelector->Run();
    
    
    boid->rigid_body.angular_acceleration = boid->LookWhereYoureGoing().angular_acceleration;

}

//--------------------------------------------------------------
void ofApp::draw(){
    // gui
    gui_panel.draw();
    
    boid->Draw();
    monster->Draw();
    
    tileGraph->Draw();
    
    // draw a eclipse representing shelter
    ofSetColor(ofColor::darkRed);
    ofDrawEllipse(shelterPosition.x, shelterPosition.y, 40, 50);
    
    // draw a eclipse representing flag
    ofSetColor(ofColor::darkGrey);
    ofDrawEllipse(flagPosition.x, flagPosition.y, 40, 20);
}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    mousePosition = ofVec2f(x, y);
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
