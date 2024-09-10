#include "gameGrids.h"

/*
    Author's Note:
        - Don't be scared. The code is extensive but relatively simple to read.
        - I left you many comments to help you understand the code.
*/

gameGrids::gameGrids(vector<vector<int>>& currentLevel, vector<ofImage>& _voltorb_explosion, vector<ofImage>& _success_animations) {
    int gridSize = 5;
    int rows = gridSize + 1; // offset by 1 to accommodate the info tiles
    int cols = gridSize + 1; // offset by 1 to accommodate the info tiles

    // voltorb_explosion = _voltorb_explosion;
    // success_animations = _success_animations;

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
                    tileGrid[row][col]->setAnimation(_voltorb_explosion);
                }
                else if (currentLevel[row][col] == 1) {
                    tileGrid[row][col]->setValue(tileType::ONE);
                    tileGrid[row][col]->setAnimation(_success_animations);
                } 
                else if (currentLevel[row][col] == 2) {
                    tileGrid[row][col]->setValue(tileType::TWO);
                    tileGrid[row][col]->setAnimation(_success_animations);
                } 
                else if (currentLevel[row][col] == 3) {
                    tileGrid[row][col]->setValue(tileType::THREE);
                    tileGrid[row][col]->setAnimation(_success_animations);
                }
            
            }

        }
    }
}
