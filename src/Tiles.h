#include "ofMain.h"

#include "ofxGui.h"
#include "ofxPanel.h"



enum tileType {
    VOLTORB,
    ONE,
    TWO,
    THREE
};


class gameTile {
    protected:
        int row_col[2];
        ofPoint position;

        tileType value;

        int width = 150;
        int height = 150;
        
        bool flipped;
        ofImage backOfTile;
        ofImage frontOfTile;


    // For the animation only
    float rotationAngle = 0; // Initial rotation angle
    bool isFlipping = false; // To control the flipping state

    public:

        gameTile(int x_pos, int y_pos, int row, int col) {
            row_col[0] = row;
            row_col[1] = col;
            position = ofPoint(x_pos, y_pos);
            flipped = false;

            backOfTile.load("images/backOfTile.png");
        }
        
        void setValue(tileType _value) {
            value = _value;
            if (value == VOLTORB) {
                frontOfTile.load("images/Voltorb.png");
            }
            else if (value == ONE) {
                frontOfTile.load("images/One.png");
            }
            else if (value == TWO) {
                frontOfTile.load("images/Two.png");
            }
            else if (value == THREE) {
                frontOfTile.load("images/Three.png");
            }
        }

        int getValue() {
            return (int)value;
        }

        tileType getValueType() {
            return value;
        }

        bool mouseHovering(int x, int y) {
            if ((x > position.x) && (x < position.x + width) && (y > position.y) && (y < position.y + height)) {
                return true;
            }
            else {
                return false;
            }
        }
    
    
    void update() {
        if (isFlipping) {
            rotationAngle += 10; // Adjust speed as needed
            if (rotationAngle >= 180) {
                rotationAngle = 180;
                isFlipping = false;
                flipOn(); // Set the tile as flipped after 180 degrees
            }
        }
    }
        void startFlip() { isFlipping = true; }
        void flipOn() { flipped = true; }
        void flipOff() { flipped = false; }
        bool isFlipped() {  return flipped; }


    virtual void draw() {
        ofPushMatrix();

        // Translate to the center of the tile
        ofTranslate(position.x + width / 2, position.y + height / 2);

        // Rotate around the X-axis to simulate the flipping effect
        ofRotateXDeg(rotationAngle);

        // Check the rotation angle to determine which side to draw
        if (rotationAngle < 90 || rotationAngle >= 270) {
            // Draw the back of the tile normally
            backOfTile.draw(-width / 2, -height / 2, width, height);
        } else {
            // Draw the front of the tile but flip it vertically
            ofScale(1, -1); // Flip the image vertically
            frontOfTile.draw(-width / 2, -height / 2, width, height);
        }

        ofPopMatrix();
    }

};  



class infoTile  {
    
    private:
        int row_col[2];
        ofPoint position;

        int width = 150;
        int height = 150;
        

    public:

        int BombCount = 0;
        int PointCount = 0;
        string topPart; 
        string bottomPart;
        ofTrueTypeFont font;
        ofImage voltorbMini;

        bool markCol;
        bool markRow;

        infoTile(int x_pos, int y_pos, int row, int col) {
            row_col[0] = row;
            row_col[1] = col;
            position = ofPoint(x_pos, y_pos);



            topPart = to_string(PointCount);
            bottomPart = to_string(BombCount);            

            font.load("SilkScreen-Bold.ttf", 45);
            voltorbMini.load("images/VoltorbMini.png");
        }

        void markColOn() { markCol = true; }
        void markRowOn() { markRow = true; }

        void countPoints(vector<vector<unique_ptr<gameTile>>>& tileGrid) {
            
            if (markRow) {
                for (unsigned int colIndex = 0; colIndex < tileGrid[row_col[0]].size(); colIndex++) {
                    if (tileGrid[row_col[0]][colIndex]) {
                        
                        PointCount += tileGrid[row_col[0]][colIndex]->getValue();

                        if (tileGrid[row_col[0]][colIndex]->getValue() == 0) {
                            BombCount++;
                        }
                    }
                    
                }
            }
            else { 
                for (unsigned int rowIndex = 0; rowIndex < tileGrid.size(); rowIndex++) {
                    if (tileGrid[rowIndex][row_col[1]]) {
                        PointCount += tileGrid[rowIndex][row_col[1]]->getValue();

                        if (tileGrid[rowIndex][row_col[1]]->getValue() == 0) {
                            BombCount++;
                        }
                }
                }
            }

            topPart = to_string(PointCount);
            bottomPart = to_string(BombCount);
        }
            
    
        void draw() {
                ofSetColor(ofColor::turquoise);
                ofRectangle rect = ofRectangle(position.x, position.y, width, height);
                ofDrawRectRounded(rect, 8);
                ofSetLineWidth(10);
                ofSetColor(ofColor::black); 
                ofDrawLine(position.x, position.y + height / 2, position.x + width, position.y + height / 2); // Line across the middle
                
                font.drawString(topPart, position.x + 95, position.y + 60);
                font.drawString(bottomPart, position.x + 95, position.y + height - 16);

                ofSetColor(ofColor::white);
                voltorbMini.draw(position.x + 2.5, position.y + 81.5, 66, 66);
            }
};