#include "ofApp.h"

//TODO: FIX gameFinished


//--------------------------------------------------------------
void ofApp::setup(){
    ost.load("Sounds/music_intro.mp3");
    ost.setLoop(true);
    pointMult_sfx.load("Sounds/sfx/pointIncreaseSfx.mp3");
    pointsTallied_sfx.load("Sounds/sfx/pointsTallied.mp3");
    levelBeat_sfx.load("Sounds/sfx/levelBeat.mp3");
    rules.load("Assets/rules.png");
    points.load("Assets/points.png");
        
    for (int i = 0; i < 9; i++) { 
        ofImage voltorbImage = ofImage();
        voltorbImage.load("Assets/Animations/explode_frames/explode_" + ofToString(i) + ".png");
        voltorb_explosion.push_back(voltorbImage);
    }

    for (int i = 0; i < 4; i++) { 
        ofImage successImage = ofImage();
        successImage.load("Assets/Animations/success_frames/success_" + ofToString(i) + ".png");
        success_animations.push_back(successImage);
    }

    setupLevel();

    font.load("pokemon-ds-font.ttf", 40);
    titleFont.load("Silkscreen-Regular.ttf", 100);
    ost.setVolume(0.50);
    // ost.play();

    currentPoints = 1; 
    pullPointsFromBank();
    checkTimer = 15;

}

//--------------------------------------------------------------
void ofApp::setupLevel() {
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
    
    vector<vector<int>> level_3 
    = {
        {1, 2, 3, 1, 1},
        {0, 2, 0, 1, 2},
        {2, 0, 1, 2, 0},
        {1, 2, 3, 1, 2},
        {3, 1, 0, 0, 1}
    };

    levelList.clear();
    gameGrids lvl1 = gameGrids(level_1, voltorb_explosion, success_animations);
    levelList.push_back(lvl1);
    gameGrids lvl2 = gameGrids(level_2, voltorb_explosion, success_animations);
    levelList.push_back(lvl2);
    gameGrids lvl3 = gameGrids(level_3, voltorb_explosion, success_animations);
    levelList.push_back(lvl3);

    for (auto& grid : levelList) {
        for (auto& row : grid.tileGrid) {
            for (auto& tile : row) {
                if (tile) {
                    tile->flipOff();
                }
            }
        }
    }

    victory = false;
    gameFinished = false;
    defeat = false;

    tileGrid = levelList[currentLevel].tileGrid;
    infoTileGrid = levelList[currentLevel].infoTileGrid;
    countTiles();
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
                if (checkVictory()) {
                    levelBeat_sfx.play();
                    victory = true;
                }
            canPlay = true;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(41,165,107,255);

    if (showRules) {
        ofSetColor(ofColor::white);
        int widthRules = ofGetWidth() * 4/16;
        int heightRules = ofGetHeight() * 4/10;
        
        int widthPoints = ofGetWidth() * 5.5/16;
        int heightPoints = ofGetHeight() * 4/10;

        rules.draw(ofGetWidth() * 11/16, ofGetHeight() * 1/10, widthRules, heightRules);
        font.drawString(to_string(currentLevel + 1), ofGetWidth() * 13.6/16, ofGetHeight() * 1.6/10);


        points.draw(ofGetWidth() * 10/16, ofGetHeight() * 5.5/10, widthPoints, heightPoints);
        ofSetColor(ofColor::black);
        string pointsStr = to_string(currentPoints);
        string storedPointsStr = to_string(storedPoints);

        // Calculate font size or adjust scaling based on the number of digits
        int maxLength = max(pointsStr.length(), storedPointsStr.length());
        int adjustedFontSize = 85 - (maxLength * 10); // Decrease font size as digits increase

        // Load or scale font size dynamically
        titleFont.load("Silkscreen-Regular.ttf", max(adjustedFontSize, 32)); // Ensure a minimum font size of 40

        // Center or adjust the position of the text
        float xPosition = ofGetWidth() * 13.5/16 - (maxLength * 10); // Adjust X position for centering
        titleFont.drawString(pointsStr, xPosition, ofGetHeight() * 6.7/10);
        titleFont.drawString(storedPointsStr, xPosition,  ofGetHeight() * 8.7/10);
        ofSetColor(ofColor::white);
    } 


    for (unsigned int row = 0; row < tileGrid.size(); row++) {
        for (unsigned int col = 0; col < tileGrid[row].size(); col++) {
            if (infoTileGrid[row][col]) {
                infoTileGrid[row][col]->draw();
            }
        }
    }

    for (unsigned int row = 0; row < tileGrid.size(); row++) {
        for (unsigned int col = 0; col < tileGrid[row].size(); col++) {
            if (tileGrid[row][col]) {
                tileGrid[row][col]->draw();
            }
        }
    }


    if (victory) {
        ofSetBackgroundColor(ofColor::green);
        font.drawString("Victory! You've won!", ofGetWidth()* 3/4 - 50, ofGetHeight() * 0.8/10);
        font.drawString("Press space to continue!", ofGetWidth()* 1/4 - 50, ofGetHeight());
    }
    else if (defeat) {
        ofSetBackgroundColor(ofColor::red);
        font.drawString("Defeat! You lost.", ofGetWidth() * 3/4 - 50, ofGetHeight() * 0.8/10);
         font.drawString("Press space to restart!", ofGetWidth()* 1/4 - 50, ofGetHeight());
        pullPointsFromBank();
        storePointsInBank();
    }
    else if (gameFinished) {
        ofSetBackgroundColor(ofColor::white);
        font.drawString("Game finished. Press space to restart.", ofGetWidth()* 3/4 - 50, ofGetHeight());
        storePointsInBank();
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
        setupLevel();
        storePointsInBank();
        currentPoints = 1;
        pointsTallied_sfx.play();
    }
    if (defeat && key == ' ') {
        defeat = false;
        currentLevel = 0;
        currentPoints = 1; 
        tileGrid.clear();
        infoTileGrid.clear();
        setupLevel();
    }

    if (gameFinished && key == ' ') {
        gameFinished = false;
        tileGrid.clear();
        infoTileGrid.clear();
        currentLevel = 0;
        setupLevel();
    }

    if (key == 'r') {
        showRules = !showRules;
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
                
                if(tileGrid[row][col]->mouseHovering(x, y) && button == OF_MOUSE_BUTTON_1 && canPlay) {
                    if (!tileGrid[row][col]->isFlipped()) {
                        canPlay = false;           
                        tileGrid[row][col]->startFlip();
                        // countedTile = false;
                        if(!countedTile) {
                            updateTileCount(tileGrid[row][col]->getValueType());
                            // countedTile = true;
                            checkTimer = 20;    //Don't lower this any more. It'll break the lose check. 
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
            if(int(type) > 1) {
                pointMult_sfx.play();
            }
            currentPoints *= (int) type;
        }

        // cout << "Updating tile count for: " << type << " to: " << tileValueCounts[type] << endl;
        // cout << "------" << endl;
        // cout << "current Count " << endl;
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

