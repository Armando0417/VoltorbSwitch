#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ost.load("music_intro.mp3");
    ost.setLoop(true);
    sfx.load("pointIncreaseSfx.mp3");
    background.load("Assets/background.png");
    rules.load("Assets/rules.png");
    points.load("Assets/points.png");

    if (firstBoot == false) {
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
        firstBoot = true;
    }

    setupLevel();


    cout << "==========================================" << endl;
    cout << "Level: " << currentLevel << endl;


    font.load("pokemon-ds-font.ttf", 40);
    titleFont.load("Silkscreen-Bold.ttf", 100);
    ost.play();
    ost.setVolume(0.50);

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
    pointsCounter = 1; 
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
            canPlay = true;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(41,165,107,255);
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), 10, 20);

    ofDrawBitmapString("X coord: " + ofToString(mouseXCoord), 10, 40);
    ofDrawBitmapString("Y coord: " + ofToString(mouseYCoord), 10, 60);

    ofDrawBitmapString("Width: " + ofToString(ofGetWidth()), 10, 80);
    ofDrawBitmapString("Height: " + ofToString(ofGetHeight()), 10, 100);

    if (showRules) {
        ofSetColor(ofColor::white);
        // font.drawString("Click on a Voltorb to flip it", ofGetWidth() * 3/4, 200);
        rules.draw(1200, 110, 650, 450);
        font.drawString(to_string(currentLevel), 1630, 170);

        points.draw(1200, 700, 650, 450);
        ofSetColor(ofColor::black);
        titleFont.drawString(to_string(pointsCounter), 1580, 850);
        titleFont.drawString(to_string(storedPoints), 1580, 1100);
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
        font.drawString("Victory! You've won!", ofGetWidth()/2 - 50, 100);
    }
    else if (defeat) {
        ofSetBackgroundColor(ofColor::red);
        font.drawString("Defeat! You lost.", ofGetWidth() * 3/4 - 50, 100);
        pullPoints();
        writeHighScore();
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
        setupLevel();
    }
    if (defeat && key == ' ') {
        defeat = false;
        currentLevel = 0;
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
    mouseXCoord = x;
    mouseYCoord = y;
    
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
                        // cout << "Tile clicked: " << tileGrid[row][col]->getValueType() << endl;
                        // cout << "at Row: " << row << " Col: " << col << endl;
                        countedTile = false;
                        if(!countedTile) {
                            updateTileCount(tileGrid[row][col]->getValueType());
                            countedTile = true;
                            checkTimer = 20;
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
                sfx.play();
            }
            pointsCounter *= (int) type;
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
