#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // ruleManager = make_unique<RuleManager>();
    // levels = {
    // {
    //     {0, 0, 1, 3, 2},
    //     {0, 0, 0, 0, 2},
    //     {0, 2, 1, 3, 0},
    //     {0, 0, 1, 3, 0},
    //     {1, 2, 3, 2, 1}
    // },
    // { 
    //     {1, 2, 3, 0, 1},
    //     {0, 2, 0, 1, 2},
    //     {2, 3, 1, 2, 3},
    //     {1, 2, 3, 1, 2},
    //     {3, 1, 0, 2, 1}
    // }
    // };

    vector < vector <int > > testLevel 
    = {
        {0, 0, 1, 3, 2},
        {0, 0, 0, 0, 2},
        {0, 2, 1, 3, 0},
        {0, 0, 1, 3, 0},
        {1, 2, 3, 2, 1}
    };


    font.load("pokemon-ds-font.ttf", 20);

    int gridSize = 5;
    int rows = gridSize + 1;
    int cols = gridSize + 1;

    tileGrid.resize(rows); 
    infoTileGrid.resize(rows);
    for (int i = 0; i < rows; i++) {
        tileGrid[i].resize(cols);
        infoTileGrid[i].resize(cols);
    }

    int startX = 100;
    int startY = 100;
    int spacing = (150 + 30);

    for (int row = 0; row < rows; row++) { 
        for (int col = 0; col < cols; col++) {

            int currX = col * spacing + startX;
            int currY = row * spacing + startY;


            if (row == gridSize && col == gridSize) {
                break;
            }

            if (row == gridSize || col == gridSize) {
                infoTileGrid[row][col] = make_unique<infoTile>(currX, currY, row, col);
                if (row == gridSize) {
                    infoTileGrid[row][col]->markColOn();
                }
                else {
                    infoTileGrid[row][col]->markRowOn();
                }
                    infoTileGrid[row][col]->countPoints(tileGrid);
            }

            else {
                tileGrid[row][col] = make_unique<gameTile>(currX, currY, row, col);
                if (testLevel[row][col] == 0) {
                    tileGrid[row][col]->setValue(tileType::VOLTORB);
                }
                else if (testLevel[row][col] == 1) {
                    tileGrid[row][col]->setValue(tileType::ONE);
                } 
                else if (testLevel[row][col] == 2) {
                    tileGrid[row][col]->setValue(tileType::TWO);
                } 
                else if (testLevel[row][col] == 3) {
                    tileGrid[row][col]->setValue(tileType::THREE);
                }
            
            }

        }
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    for (auto& row : tileGrid) {
        for (auto& tile : row) {
            if (tile) {
                tile->update();
            }
        }
    }
    // if (ruleManager->checkDefeat(tileGrid)) {
    //     // Handle defeat: reset game, show defeat message, etc.
    //     ofLog() << "Defeat! Try again.";
    //     currentLevel = 0;
    //     tileGrid.clear();
    //     infoTileGrid.clear();
    //     setup();


    // }
    // else if (ruleManager->checkVictory()) {
    //     // Handle victory: advance to next level, show victory message, etc.
    //     ofLog() << "Victory! Advancing to next level.";
    //     currentLevel++;
    //     if (currentLevel >= levels.size()) {
    //         ofLog() << "You've completed all levels!";
    //         // Optionally reset to level 0 or end the game
    //     } 
    //     else {
    //         tileGrid.clear();
    //         infoTileGrid.clear();
    //         setup();    
    //     }
    // }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(ofColor::darkSeaGreen);
    for (unsigned int row = 0; row < tileGrid.size(); row++) {
        for (unsigned int col = 0; col < tileGrid[row].size(); col++) {
            if (tileGrid[row][col]) { 
                tileGrid[row][col]->draw();
            }
            if (infoTileGrid[row][col]) {
                infoTileGrid[row][col]->draw();
            }
        }
    }


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
    for (unsigned int row = 0; row < tileGrid.size(); row++) {
        for (unsigned int col = 0; col < tileGrid[row].size(); col++) {
            if (tileGrid[row][col]) {
 
                if(tileGrid[row][col]->mouseHovering(x, y) && button == OF_MOUSE_BUTTON_1) {
                   tileGrid[row][col]->startFlip();
                }

                // else {
                //     tileGrid[row][col]->flipOff();
                // }
            }
        }

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



