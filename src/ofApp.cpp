#include "ofApp.h"

/*
    Author's Note:
        Welcome to Voltorb Switch (not voltorb flip). A totally not rip-off of the casino game
        from Pokemon HeartGold-SoulSilver. This project may seem a lot more daunting than the PA0, but don't worry
        The author is here to help!

        I wrote all the comments with the idea that you at least ran the program first and played a bit with the game. 
        I tried to make it as fun as possible so good luck!

        ps. don't hate the author if this project is too hard, it's fault of the staff, not the author. 
*/

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
/*
    Alright, this part is basically running at the start of the program. So it only runs 1 time.
    In that time it's basically just allocating the necessary files and data that it will use throughout the program. 
*/

    Databank::getInstance();


    gameManager = new GameManager();

}

//--------------------------------------------------------------

//--------------------------------------------------------------

// The update method for the game. Update + draw methods are the core loop of the game.
void ofApp::update(){
    gameManager->update();
    // testBombTile->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetBackgroundColor(60,60,60,255); // This is the green background color.
    // explosionFrame.draw(ofGetWidth()/2, ofGetHeight()/4, explosionFrame.getWidth(), explosionFrame.getHeight());

    // testBombTile -> draw();
    gameManager->drawBoard();
    gameManager->showPoints();
    gameManager->showRules();
    ofSetColor(ofColor::white);
    ofDrawLine(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight());
    
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
   gameManager->mousePressed(x, y, button);

    // testBombTile->tileFlipTrigger();
    // testPointTile->tileFlipTrigger();
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



