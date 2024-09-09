#pragma once

#include "ofMain.h"
#include "Tiles.h"

/*
	Author's Note:
		This class is just here to make the code a lot easier to read.
		This class is for the game grid. Basically, the game grid will contain the 
		tile grids, and info tile grid. In addition, it has the animations to assign them to the tiles upon creating them.
*/
class gameGrids {

	public:
		vector<vector<shared_ptr<gameTile>>> tileGrid;
		vector<vector<shared_ptr<infoTile>>> infoTileGrid;
		vector<ofImage> voltorb_explosion;
		vector<ofImage> success_animations;

		
		// The class only has a constructor in reality. Nothing else is needed
		gameGrids(vector<vector<int>>& currentLevel, vector<ofImage>& _voltorb_explosion, vector<ofImage>& _success_animations) {
			int gridSize = 5;
			int rows = gridSize + 1; // offset by 1 to accommodate the info tiles
			int cols = gridSize + 1; // offset by 1 to accommodate the info tiles

			voltorb_explosion = _voltorb_explosion;
			success_animations = _success_animations;

			// here I'll resize the vector to that size. Since there's no reason to have the vectors occupy additional space
			tileGrid.resize(rows); 
			infoTileGrid.resize(rows);
			for (int i = 0; i < rows; i++) {
				tileGrid[i].resize(cols);
				infoTileGrid[i].resize(cols);
			}

			//here is to start drawing the tile grids.
			int startX = ofGetWidth() / 20;
			int startY = ofGetHeight() / 20;
			int spacing = ofGetWidth() / 10.4;

			for (int row = 0; row < rows; row++) { 
				for (int col = 0; col < cols; col++) {
					// This is for the offset of the tiles.
						int currX = col * spacing + startX;
						int currY = row * spacing + startY;

					// If i reach the last space, then i break since there's no tile going into that last spot
					if (row == gridSize && col == gridSize) {
						break;
					}

					// If i reach the edges, that means a infoTile goes there.
					if (row == gridSize || col == gridSize) {
						infoTileGrid[row][col] = make_shared<infoTile>(currX, currY, row, col);
						
						if (row == gridSize) {
							infoTileGrid[row][col]->markColOn(); // this is to know if it should count the columns
				
						//TODO: PHASE 3
							if (col == 0) {
								infoTileGrid[row][col]->setColor(ofColor(231,115,82));
							}
							else if (col == 1) {
								infoTileGrid[row][col]->setColor(ofColor(66,173,66));
							}
							else if (col == 2) {
								infoTileGrid[row][col]->setColor(ofColor(239,165,57));
							}
							else if (col == 3) {
								infoTileGrid[row][col]->setColor(ofColor(49,148,255));
							}
							else if (col == 4) {
								infoTileGrid[row][col]->setColor(ofColor(198,99,231));
							}
						}
						// else we count the rows
						else {
							cout << "Marking col: " << col << endl;
							infoTileGrid[row][col]->markRowOn();
						//TODO: PHASE 3
							if (row == 0) {
								infoTileGrid[row][col]->setColor(ofColor(231,115,82));
							}
							else if (row == 1) {
								infoTileGrid[row][col]->setColor(ofColor(66,173,66));
							}
							else if (row == 2) {
								infoTileGrid[row][col]->setColor(ofColor(239,165,57));
							}
							else if (row == 3) {
								infoTileGrid[row][col]->setColor(ofColor(49,148,255));
							}
							else if (row == 4) {
								infoTileGrid[row][col]->setColor(ofColor(198,99,231));
							}
						}
						//Make the infoTile count up the points in its respective column/row
						infoTileGrid[row][col]->countPoints(tileGrid);
			

					}
					// if it's not a info tile, then it's a gameTile
					// So we create a gametile and assign values based on the currentLevel to be loaded
					else {
						tileGrid[row][col] = make_shared<gameTile>(currX, currY, row, col);
						if (currentLevel[row][col] == 0) {
							tileGrid[row][col]->setValue(tileType::VOLTORB);
							tileGrid[row][col]->setAnimation(voltorb_explosion);
						}
						else if (currentLevel[row][col] == 1) {
							tileGrid[row][col]->setValue(tileType::ONE);
							tileGrid[row][col]->setAnimation(success_animations);
						} 
						else if (currentLevel[row][col] == 2) {
							tileGrid[row][col]->setValue(tileType::TWO);
							tileGrid[row][col]->setAnimation(success_animations);
						} 
						else if (currentLevel[row][col] == 3) {
							tileGrid[row][col]->setValue(tileType::THREE);
							tileGrid[row][col]->setAnimation(success_animations);
						}
					
					}

				}
			}
		}

};

class ofApp : public ofBaseApp{

	public:
	// Base ofApp stuff
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
		

	// Game Methods
		void setupLevel();
		
	//TODO: Phase 2
		bool checkDefeat();
		bool checkVictory();
		bool gameFinished;
		bool victory;
		bool defeat;


		void pullPointsFromBank(){
			ifstream pointBank("pointBank.txt");
			if (pointBank.is_open()) {
				pointBank >> storedPoints;
				pointBank.close();
			} else {
				storedPoints = 0; // Default to 0 if file doesn't exist
			}
		}

		void storePointsInBank() {
			ofstream pointBank("pointBank.txt");
			if (pointBank.is_open()) {
				pointBank << storedPoints + currentPoints;
				storedPoints += currentPoints;
				pointBank.close();
			}
		}


	// These are going to be for the levels themselves. Each GameGrid contains a 5x5 grid of GameTiles & 1 InfoTile per row AND column.
	// FIXME: CHANGE TO OBJECTS
	//TODO: Phase 3
		vector<gameGrids> levelList;
		vector<vector<shared_ptr<gameTile>>> currentTileGrid; 
		vector<vector<shared_ptr<infoTile>>> currentInfoTileGrid;

	//Index for the current level in the levelList
		unsigned int currentLevel = 0;

	//TODO: These are for the game
		map<tileType, int> tileValueCounts;
	
	//Animations for the tiles 
	// (Reason they are here is so that each tile doesn't have to create a copy of the animation. Instead, you give them this vector for the animations)
		vector<ofImage> success_animations;
		vector<ofImage> voltorb_explosion;


	// These are for the OST
		ofSoundPlayer ost;
		ofSoundPlayer pointMult_sfx;
		ofSoundPlayer levelBeat_sfx;
		ofSoundPlayer pointsTallied_sfx;


	// These are for the UI
	//FIXME: Make only one font
		ofTrueTypeFont titleFont;
		ofTrueTypeFont font;

	//small flag to toggle the rules & points
		bool showRules = true;
		bool showPoints = true;

	// Images for the ui
		ofImage rules;
		ofImage points;


		void countTiles();
		void updateTileCount(tileType type);

	//TODO: Phase 2
		int checkTimer = 0;


	// Variables to keep track of current score and stored score
		int currentPoints = 1;
		int storedPoints = 0;


	//TODO: Phase 2
	//Boolean to make sure enough time passes before the next tile can be flipped
		bool canPlay = true;


};




