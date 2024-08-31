#pragma once

#include "ofMain.h"
#include "Tiles.h"

class gameGrids {

	public:
		vector<vector<shared_ptr<gameTile>>> tileGrid;
		vector<vector<shared_ptr<infoTile>>> infoTileGrid;
		vector<ofImage> voltorb_explosion;
		vector<ofImage> success_animations;

		
		gameGrids(vector<vector<int>>& currentLevel, vector<ofImage>& _voltorb_explosion, vector<ofImage>& _success_animations) {
			int gridSize = 5;
			int rows = gridSize + 1;
			int cols = gridSize + 1;

			voltorb_explosion = _voltorb_explosion;
			success_animations = _success_animations;

			tileGrid.resize(rows); 
			infoTileGrid.resize(rows);
			for (int i = 0; i < rows; i++) {
				tileGrid[i].resize(cols);
				infoTileGrid[i].resize(cols);
			}

			// int startX = 100;
			// int startY = 100;
			// int spacing = (150 + 30);

			int startX = ofGetWidth() / 20;
			int startY = ofGetHeight() / 20;
			int spacing = ofGetWidth() / 10.4;

			for (int row = 0; row < rows; row++) { 
				for (int col = 0; col < cols; col++) {

					int currX = col * spacing + startX;
					int currY = row * spacing + startY;


					if (row == gridSize && col == gridSize) {
						break;
					}

					if (row == gridSize || col == gridSize) {
						infoTileGrid[row][col] = make_shared<infoTile>(currX, currY, row, col);
						if (row == gridSize) {
							cout << "Marking row: " << row << endl;
							infoTileGrid[row][col]->markColOn();
						}
						else {
							cout << "Marking col: " << col << endl;
							infoTileGrid[row][col]->markRowOn();
						}
							infoTileGrid[row][col]->countPoints(tileGrid);
					}

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

enum infoTileColors {
	RED = 0,
	GREEN = 1,
	ORANGE = 2,
	BLUE = 3, 
	PURPLE = 4
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
		bool checkDefeat();
		
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
		vector<gameGrids> levelList;
		vector<vector<shared_ptr<gameTile>>> tileGrid; 
		vector<vector<shared_ptr<infoTile>>> infoTileGrid;

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
	
	bool checkVictory();

	bool victory;
	bool gameFinished;
	bool defeat;

	bool countedTile = false;

	int checkTimer = 0;



	int currentPoints = 1;
	int storedPoints = 0;


	//Boolean to make sure enough time passes before the next tile can be flipped
	bool canPlay = true;


};




