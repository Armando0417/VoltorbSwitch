#pragma once

#include "ofMain.h"
#include "Utilities.h"
#include "GameGrids.h"


/**************************************************************************
 * This is the Game Manager Class  (Original, I know).
 * 
 * The purpose of this class is to help abstract a lot of the game Logic.
 * It's a really important class for the game as it basically IS the game.
 * 
 * Responsibilities include: 
 * 1. Generating a new board.
 * 2. In the case you want debug boards here you make them
 * 3. Setting up the game. 
 * 4. Keeping track of the level & score.
 * 5. Reads the score from the file and stores the new score.
 * 6. Making sure the user does not break the game disabling interactions
 * 
 * If you were looking for where one of those listed things were, you can find them here.
 * 
 * You may notice that the syntax is a bit different for some variables. It is intentional
 * so that you as the student are exposed to a different syntax.
 **************************************************************************/




class GameManager {

    private:
        bool isInteractionAllowed {true};
        bool scoreUpdated {false};

        int level {1};
        int score {0};

        unique_ptr<gameGrids> currentBoard;

        bool disablePlay = false;
        bool displayUI = true;
        ofFbo rulesetChart;

        ofTrueTypeFont  font;
        ofImage rulesImage;

        ofTrueTypeFont scoreFont;
        vector<ofRectangle> scoreRectangles;


    public:
        GameManager();
        ~GameManager();

        void update();

        bool checkVictory();
        bool checkDefeat();

        void incrementLevel();
        void incrementScore(int points);

        void generateNewBoard();
        void mousePressed(int x, int y, int button);
        void keyPressed(int key);

        void drawBoard();
        void showPoints();
        void showRules();
        



};