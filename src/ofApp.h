#pragma once

#include "ofMain.h"
#include "Tiles.h"

class RuleManager {
	public:
		map<tileType, int> tileCount;
	

		RuleManager() {
			tileCount[tileType::VOLTORB] = 0;
            tileCount[tileType::ONE] = 0;
            tileCount[tileType::TWO] = 0;
            tileCount[tileType::THREE] = 0;
		}

		void countTiles(vector<vector<unique_ptr<gameTile>>>& tileGrid) {
			for (unsigned int row = 0; row < tileGrid.size(); row++) {
				for (unsigned int col = 0; col < tileGrid[row].size(); col++) {
					if (tileGrid[row][col]) {
						tileCount[tileGrid[row][col]->getValueType()]++;
					}
				}
			}
		}

		bool checkVictory() {
			// Win when there are no more Two's or Three's in the grid
			return tileCount[tileType::TWO] == 0 && tileCount[tileType::THREE] == 0;
		}


        bool checkDefeat(vector<vector<unique_ptr<gameTile>>>& tileGrid) {
            for (auto& row : tileGrid) {
                for (auto& tile : row) {
                    if (tile && tile->getValue() == tileType::VOLTORB && tile->isFlipped()) {
                        return true;
                    }
                }
            }
            return false;
        }

		void updateTileCount(tileType type) {
            if (tileCount.find(type) != tileCount.end()) {
                tileCount[type]--;
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
		

	vector<vector<unique_ptr<gameTile>>> tileGrid;
	vector<vector<unique_ptr<infoTile>>> infoTileGrid;
	ofTrueTypeFont font;

	//	Author's note: I'm so sorry
		vector < vector < vector <int> > > levels; // This is just a vector that contains all of the levels (which are the grids of the game)
	
	// unique_ptr<RuleManager> ruleManager;

	

	int currentLevel = 0;

	

};


