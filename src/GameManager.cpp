#include "GameManager.h"

GameManager::GameManager() {
    currentBoard = make_unique<gameGrids>(level);
    rulesImage.load("Assets\\ruleset.png");
}

void GameManager::update() {
    currentBoard->update();
}

bool GameManager::checkVictory() {

}

bool GameManager::checkDefeat() {

}

void GameManager::incrementLevel() {
    level++;
    currentBoard = make_unique<gameGrids>(level);
}

void GameManager::incrementScore(int points) {
    score *= points;
    scoreUpdated = true;
}

void GameManager::generateNewBoard() {
    currentBoard = make_unique<gameGrids>(level);
}

void GameManager::keyPressed(int key) {
    if (disablePlay) return;
    
    if (key == 'r') {
        displayUI = !displayUI;
    }

}

void GameManager::mousePressed(int x, int y, int button) {
    if (disablePlay) return;
    currentBoard->mousePressed(x, y, button);
}

void GameManager::drawBoard() {
    currentBoard->draw();
}

void GameManager::showPoints() {
 if (!displayUI) return;
    ofSetColor(ofColor::gray);
    ofNoFill();
    ofDrawRectangle(ofGetWidth() - 300, ofGetHeight() - 300, 140, 140);
    ofFill();
    ofSetColor(ofColor::white);
    ofDrawRectangle(ofGetWidth() - 280, ofGetHeight() - 280, 100, 100);
}

void GameManager::showRules() {
 if (!displayUI) return;

     rulesImage.draw(ofGetWidth() * 0.60, 200, rulesImage.getWidth(), rulesImage.getHeight());



}

