#pragma once

#include "ofMain.h"
// #include "gameTiles.h"
// #include "infoTiles.h"
// #include "gameGrids.h"
#include "GameManager.h"


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
		
		
		GameManager* gameManager;
		ofImage globalAnimationFrame; // This is the image that will be the explosion and points animation.
		


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



		ofSoundPlayer ost;

	// Variables to keep track of current score and stored score
		int currentPoints = 1;
		int storedPoints = 0;



};