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
			int spacing = ofGetWidth() / 11;

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
		

	ofSoundPlayer ost;

	vector<vector<shared_ptr<gameTile>>> tileGrid;
	vector<vector<shared_ptr<infoTile>>> infoTileGrid;
	ofTrueTypeFont font;
	ofTrueTypeFont titleFont;
	ofImage background;

	//	Author's note: I'm so sorry
		vector < vector < vector <int> > > levels; // This is just a vector that contains all of the levels (which are the grids of the game)
		vector<gameGrids> levelList;

	map<tileType, int> tileValueCounts;


	unsigned int currentLevel = 0;

	bool firstBoot = false;


	void countTiles();
	void updateTileCount(tileType type);
	
	bool checkVictory();

	bool victory;
	bool gameFinished;
	bool defeat;

	int mouseXCoord;
	int mouseYCoord;

	bool countedTile = false;
	bool showRules = true;

	int checkTimer = 0;

	vector<ofImage> success_animations;
	vector<ofImage> voltorb_explosion;

	bool checkDefeat();

	ofImage rules;
	ofImage points;
	int pointsCounter = 1;
	int storedPoints = 0;

	ofSoundPlayer sfx;

	bool canPlay = true;
	// void loseAnimation();


	void setupLevel();

	void pullPoints(){
            ifstream highScoreFile("points.txt");
            if (highScoreFile.is_open()) {
                highScoreFile >> storedPoints;
                highScoreFile.close();
            } else {
                storedPoints = 0; // Default to 0 if file doesn't exist
            }
        }

		void writeHighScore() {
            ofstream highScoreFile("points.txt");
            if (highScoreFile.is_open()) {
                highScoreFile << storedPoints + pointsCounter;
                highScoreFile.close();
            }
        }
	

};




