#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ost.load("music_intro.mp3");
    ost.setLoop(true);

    vector<vector<int>> level_1 
    = {
        {0, 0, 1, 3, 2},
        {0, 0, 0, 0, 2},
        {0, 2, 1, 3, 0},
        {0, 0, 1, 3, 0},
        {1, 2, 3, 2, 1}
    };
    vector<vector<int>> level_2 
    = {
        {1, 2, 3, 0, 1},
        {0, 2, 0, 1, 2},
        {2, 3, 1, 2, 3},
        {1, 2, 3, 1, 2},
        {3, 1, 0, 2, 1}
    };

    levelList.clear();
    gameGrids lvl1 = gameGrids(level_1);
    levelList.push_back(lvl1);
    gameGrids lvl2 = gameGrids(level_2);
    levelList.push_back(lvl2);
    

    cout << "==========================================" << endl;
    cout << "Level: " << currentLevel << endl;
    victory = false;
    gameFinished = false;
    defeat = false;


    for (auto& grid : levelList) {
        for (auto& row : grid.tileGrid) {
            for (auto& tile : row) {
                if (tile) {
                    tile->flipOff();
                }
            }
        }
    }


    tileGrid = levelList[currentLevel].tileGrid;
    infoTileGrid = levelList[currentLevel].infoTileGrid;
    countTiles();

    font.load("pokemon-ds-font.ttf", 80);
    ost.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    if (!victory && !defeat) {
    for (auto& row : tileGrid) {
        for (auto& tile : row) {
            if (tile) {
                tile->update();
            }
        }
    }
    
    if (checkTimer > 0) {
        checkTimer--;
        if (checkTimer == 0) {
                if (checkDefeat()) {
                    defeat = true;
                }
                else if (checkVictory()) {
                    victory = true;
                }
            }
        }
    }
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
    if (victory) {
        ofSetBackgroundColor(ofColor::green);
        font.drawString("Victory! You've won!", ofGetWidth()/2 - 50, 100);
    }
    else if (defeat) {
        ofSetBackgroundColor(ofColor::red);
        font.drawString("Defeat! You lost.", ofGetWidth()/2 - 50, 100);
    }
    else if (gameFinished) {
        ofSetBackgroundColor(ofColor::white);
        font.drawString("Game finished. Press space to restart.", ofGetWidth()/2 - 50, 100);
    }


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (victory && key == ' ') {
        victory = false;
        if (currentLevel < levelList.size()) {
           currentLevel++; 
        }
        else {
            gameFinished = true;
        }
        tileGrid.clear();
        infoTileGrid.clear();
        setup();
    }
    if (defeat && key == ' ') {
        defeat = false;
        currentLevel = 0;
        tileGrid.clear();
        infoTileGrid.clear();
         setup();
    }

    if (gameFinished && key == ' ') {
        gameFinished = false;
        tileGrid.clear();
        infoTileGrid.clear();
        currentLevel = 0;
        setup();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    for (unsigned int row = 0; row < tileGrid.size(); row++) {
        for (unsigned int col = 0; col < tileGrid[row].size(); col++) {
            if (tileGrid[row][col]) {
                tileGrid[row][col]->isHovering(x, y);
            }
        }
    }
    
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
                    if (!tileGrid[row][col]->isFlipped()) {           
                        tileGrid[row][col]->startFlip();
                        cout << "Tile clicked: " << tileGrid[row][col]->getValueType() << endl;
                        cout << "at Row: " << row << " Col: " << col << endl;
                        countedTile = false;
                        if(!countedTile) {
                            updateTileCount(tileGrid[row][col]->getValueType());
                            countedTile = true;
                            checkTimer = 45;
                        }
                    }
                }

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

void ofApp::countTiles() {
    tileValueCounts[tileType::VOLTORB] = 0;
    tileValueCounts[tileType::ONE] = 0;
    tileValueCounts[tileType::TWO] = 0;
    tileValueCounts[tileType::THREE] = 0;

    for(unsigned int i = 0; i < tileGrid.size(); i++) {
        for(unsigned int j = 0; j < tileGrid[i].size(); j++) {
            if(tileGrid[i][j]) {
                tileValueCounts[tileGrid[i][j]->getValueType()]++;
            }
        }
    }


}

void ofApp::updateTileCount(tileType type) {
    if(tileValueCounts.find(type) != tileValueCounts.end()) {
        if (tileValueCounts[type] > 0) {
            tileValueCounts[type]--;
        }
        cout << "Updating tile count for: " << type << " to: " << tileValueCounts[type] << endl;
        cout << "------" << endl;
        cout << "current Count " << endl;
        for (auto it = tileValueCounts.begin(); it != tileValueCounts.end(); it++) {
            
            cout << it->first << " : " << it->second << endl;
        }
    }
}

bool ofApp::checkVictory() {
    // Win when there are no more Two's or Three's in the grid
    if (tileValueCounts[tileType::TWO] == 0 && tileValueCounts[tileType::THREE] == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool ofApp::checkDefeat() {
    for (unsigned int i = 0; i < tileGrid.size(); i++) {
        for (unsigned int j = 0; j < tileGrid[i].size(); j++) {
            if (tileGrid[i][j]) {
                if (tileGrid[i][j]->getValue() == tileType::VOLTORB) {
                    if (tileGrid[i][j]->isFlipped()) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void setupLevel() {

}

