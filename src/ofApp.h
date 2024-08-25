#pragma once

#include "ofMain.h"
#include "Tiles.h"

class gameGrids {

	public:
		vector<vector<shared_ptr<gameTile>>> tileGrid;
		vector<vector<shared_ptr<infoTile>>> infoTileGrid;
		
		gameGrids(vector<vector<int>>& currentLevel) {
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
						}
						else if (currentLevel[row][col] == 1) {
							tileGrid[row][col]->setValue(tileType::ONE);
						} 
						else if (currentLevel[row][col] == 2) {
							tileGrid[row][col]->setValue(tileType::TWO);
						} 
						else if (currentLevel[row][col] == 3) {
							tileGrid[row][col]->setValue(tileType::THREE);
						}
					
					}

				}
			}
		}
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
	bool songPlaying = false;

	vector<vector<shared_ptr<gameTile>>> tileGrid;
	vector<vector<shared_ptr<infoTile>>> infoTileGrid;
	ofTrueTypeFont font;

	//	Author's note: I'm so sorry
		vector < vector < vector <int> > > levels; // This is just a vector that contains all of the levels (which are the grids of the game)
		vector<gameGrids> levelList;

	map<tileType, int> tileValueCounts;


	unsigned int currentLevel = 0;


	void countTiles();
	void updateTileCount(tileType type);
	
	bool checkVictory();

	bool victory;
	bool gameFinished;
	bool defeat;

	bool countedTile = false;
	int checkTimer = 0;

	bool checkDefeat();

	void setupLevel();

};




