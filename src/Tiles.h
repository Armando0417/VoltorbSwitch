#include "ofMain.h"

#include "ofxGui.h"
#include "ofxPanel.h"


enum tileType {
    VOLTORB,
    ONE,
    TWO,
    THREE
};

// ============================ Main Game Tile Class ============================
class gameTile {
    
    /*
        Author's note: 
            This class is basically the game. These are the tiles that you will be flipping around. Trying to avoid the bombs
            and getting the highest score possible. I tried to explain the most of the code in the comments below. So i hope you 
            don't feel overwhelmed with the code. 
    */

    private:
    // This are going to be the row and column of the tile in the grid
        int row_col[2]; // Note that the first index (0) is the row, and the second index (1) is the column
    
    // This is going to be the position of the tile on the screen (the X and Y coordinates for openframeworks to draw it in)
        ofPoint position; 
    
    // This is going to be the value of the tile (See the enum above)
        tileType value; 

    // These are going to be the dimensions of the tile
        int width = 150;
        int height = 150;
        
        
    // Boolean conditions to know information about the tile
        bool flipped;
        bool hovering;
        bool playAnimation = false;
    
    // These are going to be the images of the tile
        ofImage backOfTile; // The back of it
        ofImage frontOfTile; // The front of it
        ofImage hoverImage; // This is going to be the red square around the tile when you hover over it
        ofImage borderImage; // This is going to be the general border of the tile
    
    // For the sound when flipping the tile
        ofSoundPlayer flipSound;

    // For the animation (each image in the vector is a frame of the animation)
        vector<ofImage> animationFrames; 

    // To control the current frame of the animation
    unsigned int currentFrame = 0; 

    // For the animation of the rotation only
    float rotationAngle = 0; // Initial rotation angle
    bool isFlipping = false; // To control the flipping state


    public:
    // This is the constructor for the tile
        gameTile(int x_pos, int y_pos, int row, int col) {
            row_col[0] = row;
            row_col[1] = col;
            position = ofPoint(x_pos, y_pos);
            flipped = false;
            hovering = false;
            // If you see this and ask yourself: "why is the front image not there?" 
            //      - it's because when i make the tile, the tile doesn't have the value to give it a front image appropriate to it.
            backOfTile.load("Assets/TileImages/backOfTile.png");
            hoverImage.load("Assets/TileImages/hover.png");
            borderImage.load("Assets/TileImages/Border2.png");
            flipSound.setVolume(1.0);
        }

        ofPoint getPosition() {
            return position;
        }        

        // This method is to assign the front image of the tile to the value that was assigned to it.
        void setValue(tileType _value) {
            value = _value;
            if (value == VOLTORB) {
                frontOfTile.load("Assets/TileImages/Voltorb.png");
                flipSound.load("flip_explosionSound.mp3");
            }
            else if (value == ONE) {
                frontOfTile.load("Assets/TileImages/One.png");
                flipSound.load("flipSound.mp3");
            }
            else if (value == TWO) {
                frontOfTile.load("Assets/TileImages/Two.png");
                flipSound.load("flipSound.mp3");
            }
            else if (value == THREE) {
                frontOfTile.load("Assets/TileImages/Three.png");
                flipSound.load("flipSound.mp3");
            }
        }
        // This method is to give it the animation frames
        // Why here? because the voltorb tiles and the other value tiles have different animations
        void setAnimation(vector<ofImage> _animationFrames) {
            animationFrames = _animationFrames;
        }

        // This is the method to get the value of the tile. The numeric value. 
        int getValue() {
            return (int)value;
        }

        // This is the method to get the type of the tile. Not the numeric value, but the enum itself
        tileType getValueType() {
            return value;
        }
        
        // This is the method to know if the tile is being hovered. Its only job is to give the appropriate value to the "hovering" boolean variable
        void isHovering(int x, int y) {
            if ((x > position.x) && (x < position.x + width) && (y > position.y) && (y < position.y + height)) {
                hovering = true;
            }
            else {
                hovering = false;
            }
        }

        bool mouseHovering(int x, int y) {
            if ((x > position.x) && (x < position.x + width) && (y > position.y) && (y < position.y + height)) {
                return true;
            }
            else {
                return false;
            }
        }
        
        // This is the method to flip the tile. In particular it focuses on setting the boolean variable "flipped" to start the flipping animation
        void startFlip() { 
            isFlipping = true; 
            flipSound.play(); 
        }
        // This method is only to set the boolean variable "flipped" to true
        void flipOn() { flipped = true; }
        // This method is only to set the boolean variable "flipped" to false
        void flipOff() { flipped = false; }
        // This method is only to get the boolean variable "flipped" (so that i know if the tile is flipped or not)
        bool isFlipped() {  return flipped; }
    
    

    // This is the method to update the animation
        void update() {
            if (isFlipping) {
                rotationAngle += 10; // Adjust speed as needed
                if (rotationAngle >= 180) {
                    rotationAngle = 180;
                    isFlipping = false;
                    flipOn(); // Set the tile as flipped after 180 degrees
                    playAnimation = true;

                }
            }
        }


    // This is the method to draw the tile.
    // If you wondering about the matrix and ofTranslate, basically it's so that the tile can rotate on screen.
    void draw() {
        ofPushMatrix();
        
        // Translate to the center of the tile
        ofTranslate(position.x + width / 2, position.y + height / 2);

        // Rotate around the X-axis to simulate the flipping effect
        ofRotateXDeg(rotationAngle);

        // Check the rotation angle to determine which side to draw
        if (rotationAngle < 90 || rotationAngle >= 270) {

            // Draw the back of the tile normally
            backOfTile.draw(-width / 2, -height / 2, width, height);
        } 
        else {
            // Draw the front of the tile but flip it vertically
            ofScale(1, -1); // Flip the image vertically
            frontOfTile.draw(-width / 2, -height / 2, width, height);
        }

        // Draw the hover image if the tile is being hovered
        if (hovering) {
            hoverImage.draw(-width / 2, -height / 2, width, height);
        }
        else {
            // borderImage.draw(-width / 2, -height / 2, width, height);
        }

        //TODO : FIX THIS
        // Play the animation if the tile is flipped and the animation is active
        if (playAnimation) {
            if (currentFrame < animationFrames.size()) {
                // if(currentFrame % 2 == 0) {
                    ofSleepMillis(100);
                    animationFrames[currentFrame].draw(-width / 2, -height / 2, width, height);
                    currentFrame++;
                
            } else {
                playAnimation = false;
                currentFrame = 0;
            }
        }

        ofPopMatrix();
    }



};  


// ============================= Info Tile Class ============================
class infoTile  {
    
    /*
        Author's note: 
            This class is basically very similar to the gameTile class since ultimately, they are both tiles.
            Difference is that this class has a lot of differing information on it. This class is the edge tiles that display 
            the total number of bombs and total number of points. There are gonna be less comments since they are very similar.
    */

    private:
        // Same as the gameTile class
            int row_col[2];
            ofPoint position;

            int width = 150;
            int height = 150;
        

    // Here the information of the tile starts to change
    public:
        // This is a variable to store the amount of bombs in the row|column
            int BombCount = 0;
        // This is a variable to store the amount of points in the row|column
            int PointCount = 0;

        // This is a string to write to the screen the information i need to display
            string topPart; 
            string bottomPart;
        
        // This is the font that will be used to display the information
            ofTrueTypeFont font;

        // This is the image of the voltorb in the bottom half of the edge tiles.
            ofImage voltorbMini;

        // These booleans are used to know if i gotta count the row or column
            bool markCol;
            bool markRow;

        // This is for the elongated rectangle
            ofRectangle backgroundPipe;
            ofColor backgroundColor = ofColor(255, 255, 255);
            ofImage borderImage;


        // This is the constructor for the tile
        infoTile(int x_pos, int y_pos, int row, int col) {
            row_col[0] = row;
            row_col[1] = col;
            position = ofPoint(x_pos, y_pos);

            markCol = false;
            markRow = false;

            topPart = to_string(PointCount);
            bottomPart = to_string(BombCount);            

            font.load("pokemon-ds-font.ttf", 45);
            voltorbMini.load("Assets/TileImages/VoltorbMini.png");
            borderImage.load("Assets/TileImages/Border2.png");

        }
        
        void setColor(ofColor color) {
            backgroundColor = color;
        }

        // These are used to set the boolean variables  to true
        void markColOn() { markCol = true; }
        void markRowOn() { markRow = true; }


        // This is the method to count the points and bombs It is the most code intensive one since well... it has to be. 
        // But don't worry, it's not that bad.
        void countPoints(vector<vector<shared_ptr<gameTile>>>& tileGrid) {
            if (markRow) {
                int myRowIndex = row_col[0];

                for (unsigned int colIndex = 0; colIndex < tileGrid[myRowIndex].size(); colIndex++) {
                    if (tileGrid[myRowIndex][colIndex]) {
                        PointCount += tileGrid[myRowIndex][colIndex]->getValue();
                        if (tileGrid[myRowIndex][colIndex]->getValue() == 0) {
                            BombCount++;
                        }
                    }
                }
                // Update the pipe length and position for row marking
                backgroundPipe.setWidth(position.x - tileGrid[myRowIndex][0]->getPosition().x);
                backgroundPipe.setHeight(height / 5);
                backgroundPipe.setPosition(position.x - backgroundPipe.getWidth() + 30, position.y + height / 2 - backgroundPipe.getHeight() / 2);
            
            } 
            
            else {
                int myColIndex = row_col[1];

                for (unsigned int rowIndex = 0; rowIndex < tileGrid.size(); rowIndex++) {
                    if (tileGrid[rowIndex][myColIndex]) {
                        PointCount += tileGrid[rowIndex][myColIndex]->getValue();
                        if (tileGrid[rowIndex][myColIndex]->getValue() == 0) {
                            BombCount++;
                        }
                    }
                }
                // Update the pipe length and position for column marking
                backgroundPipe.setWidth(width / 5);
                backgroundPipe.setHeight(position.y - tileGrid[0][myColIndex]->getPosition().y);
                backgroundPipe.setPosition(position.x + width / 2 - backgroundPipe.getWidth() / 2, position.y - backgroundPipe.getHeight() + 30);
            }
            topPart = to_string(PointCount);
            bottomPart = to_string(BombCount);
        }
            
    
    // This is the method to draw the tile. Basically a bunch of colors, and drawing lines, and writing the text and showing the voltorb image.
        void draw() {
            ofSetColor(ofColor::white);
            borderImage.draw(position.x, position.y, width, height);
            // ofRectangle rect1 = ofRectangle(position.x, position.y, width, height);
            // ofDrawRectRounded(rect1, 8);
            // cout << "X: " << position.x << " Y: " << position.y << endl;
            ofRectangle pipeBorder = ofRectangle(backgroundPipe.getX() - 10.5, backgroundPipe.getY() - 8.5, backgroundPipe.getWidth() + 21, backgroundPipe.getHeight() + 17.5);
            ofDrawRectangle(pipeBorder);
            ofSetColor(ofColor::darkMagenta);
            ofRectangle rect2 = ofRectangle(position.x + 10.5, position.y + 10.5, width * 0.86, height * 0.86);
            cout << "X2: " << position.x + 10.5 << " Y2: " << position.y + 10.5 << endl;
            ofDrawRectRounded(rect2, 8);
            
            

            ofDrawRectangle(backgroundPipe);

            ofSetColor(ofColor::white);

            ofSetLineWidth(11.5);
            if(markRow) {
                ofDrawLine(position.x, pipeBorder.getY() + 3.5, position.x + width, pipeBorder.getY() + 3.5);
            }
            else {
                ofDrawLine(position.x, position.y + height/2 - 14.2, position.x + width, position.y + height/2 - 14.2);
            }

            //Time to finally write the text and draw the voltorb
            // Draw the top part (point count)
            ofSetColor(ofColor::black);
            // font.drawString(topPart, position.x + width / 2 - font.stringWidth(topPart) / 2, position.y + height / 4);
            font.drawString(topPart, position.x + 95, position.y + 50);

            // Draw the bottom part (bomb count) and Voltorb mini image
            // font.drawString(bottomPart, position.x + width / 2 - font.stringWidth(bottomPart) / 2, position.y + (3 * height) / 4);
            font.drawString(bottomPart, position.x + 95, position.y + height - 16);

            ofSetColor(ofColor::white);
            voltorbMini.draw(position.x + 5, position.y + 75, 66, 66);


  
            // // Draw the white background
            // ofSetColor(ofColor::white);
            // // Adjust the width and height to cover both the infoTile and the pipe
            // if (markRow) {
            //     // For row marking
            //     ofDrawRectangle(position.x - 5, position.y - 5, backgroundPipe.getWidth() + width + 10, height + 10);
            // } 
            // else {
            //     // For column marking
            //     ofDrawRectangle(position.x - 5, position.y - 5, width * 1/5 + 10, backgroundPipe.getHeight() + height + 10);
            // }



            // // Draw the background pipe
            // ofSetColor(backgroundColor);
            // ofDrawRectRounded(backgroundPipe, 8);

            // // Draw the infoTile itself
            // ofSetColor(backgroundColor);
            // ofRectangle rect = ofRectangle(position.x, position.y, width, height);
            // ofDrawRectRounded(rect, 8);
            // ofSetColor(ofColor::black); 
            // ofSetLineWidth(10);
            // ofDrawLine(position.x, position.y + height / 2, position.x + width, position.y + height / 2); // Line across the middle
            
            // font.drawString(topPart, position.x + 95, position.y + 60);
            // font.drawString(bottomPart, position.x + 95, position.y + height - 16);

            // ofSetColor(ofColor::white);
            // voltorbMini.draw(position.x + 2.5, position.y + 81.5, 66, 66);
            // ofDrawBitmapString("Row: " + to_string(row_col[0]) + " Col: " + to_string(row_col[1]), position.x, position.y );

            }

        // void drawBeam() {
        //     ofSetColor(ofColor::lightGoldenRodYellow);
        //     ofDrawRectangle(backgroundPipe);
        //     ofSetColor(ofColor::white);
        // }
};