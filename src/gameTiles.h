#pragma once
#include "ofMain.h"
#include "Databank.h"



// ============================ Main Game Tile Class ============================
class gameTile {

    #define ANIM_OVERLAY_DURATION 3.0f
    #define ANIM_FLIP_DURATION 2.0f
    #define ANIM_OVERLAY_DELAY 2.0f

    
    private:
    /*
         This are going to be the row and column of the tile in the grid.

            - [0] is the row.
            - [1] is the column. 
    */
        int row_col[2]; 

    // This is going to be the position of the tile on the screen (the X and Y coordinates for openframeworks to draw it in)
        ofPoint position; 
    
    /**
       * This is going to be the value of the Tile.
       * If you are wondering why an "image type" it's because that's the enum
       * that holds the different tile types (voltorb, one, two, or three).
    */
        Databank::Image_Types value; 

    // These are going to be the dimensions of the tile
        double width = ofGetWidth() /16;
        double height = ofGetWidth() /16;

    
    // Boolean conditions to know information about the tile
        bool flipped;
        bool hovering; //? this can be a spec
    
    // These are going to be the images of the tile
        ofImage backOfTile; // The back of it
        ofImage frontOfTile; // The front of it
        ofImage hoverImage; // This is going to be the red square around the tile when you hover over it
        ofImage borderImage; // This is going to be the general border of the tile
        ofImage flipAnimationFrame;
        ofImage animationOverlayFrame;

        bool isPlayingAnimation = false;
        unsigned int currentAnimationFrameIndex = 0;


    //** This is the animation Section */
        vector<ofImage> tileFlipFrames;
        vector<ofImage> animFrames; 
        
    // This is the timer to ensure that the animation is visible
        float animTime = 0.0f;


        float tileAnimTime = 0.0f;


        float delayOverlayTimer = 0.5f;




    // For the animation of the rotation only
    bool isFlipping = false; // To control the flipping state
    unsigned int currFlipFrameIndex = 0;

    public:
    /*
        Main Constructor for the Game Tile
        @param _value: The value of the tile (VOLTORB, ONE, TWO, THREE)
        @param x_pos: The X position of the tile (for the screen)
        @param y_pos: The Y position of the tile (for the screen)
        @param row: The row of the tile in the grid
        @param col: The column of the tile in the grid
    */
        gameTile(Databank::Image_Types _value, int x_pos, int y_pos, int row, int col);

    //* ============ Getters ============
      
      //Returns the row and column of the tile in the grid
        ofPoint getPosition() { 
            return position; 
        }   
      // Returns the width of the tile
        double getWidth() { 
            return width; 
        }     
      // Returns the height of the tile   
        double getHeight() { 
            return height; 
        }
      // Returns the numeric value (int) of the tile
        int getValue() { 
            return (int) value; 
        }   
      // Returns the ENUM value type of the tile (VOLTORB, ONE, TWO, THREE)
        Databank::Image_Types getValueType() { 
            return value; 
        }  


    // * ============ Important Methods ============

    // This method is for Updating the state of the tile
        void update();  

    // This is the method to draw the tile
        void draw();    

        bool animPlayed = false;
        void drawTileAnimation();
        vector<double> getAnimLayoutParams(bool isBomb);



    /*
        This method is to set the value of the tile. 
        It will then set the appropriate images and animation frames for the tile

        @param _value: The value of the tile (VOLTORB, ONE, TWO, THREE)
    */  
        void setValue(Databank::Image_Types _value){}; 
        


        bool mouseHovering(int x, int y);
        
    // Flip methods

        // This is the method to flip the tile. In particular it focuses on setting the boolean variable `isFlipping` to start the flipping animation
            void tileFlipTrigger();

            void flipBackDown();  


            
                    
       
        // This method is only to get the boolean variable "flipped" (so that i know if the tile is flipped or not
            bool isFlipped();      
    
};  