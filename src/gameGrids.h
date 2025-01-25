#pragma once
#include "ofMain.h"
#include "Databank.h"
#include "gameTiles.h"
#include "infoTiles.h"




/** ************************************************************************
 * This is the Game Grid (or "board") Class.
 * 
 * The purpose of this class is to encapsulate the board of the game. 
 * It makes it a lot simpler to manipulate the board.
 * 
 * Responsibilities include: 
 * 1. Algorithm for random Generation of the board.
 * 2. Making the tiles for the game.
 * 3. Checking if Victory or Defeat.
 * 
 * I hope you find this code entertaining,
 * because debugging it will certainly be a game of its own. :)
 **************************************************************************/
class gameGrids {

	private:
		bool DEBUG_MODE {true};

		int BOARD_SIZE = 6; // 6
        int PLAY_AREA = 5;
    	int MAX_TILE_VALUE = 4;
		int currentLevel = -1;
		bool boardLost = false;
		bool boardCompleted = false;

		vector<vector<shared_ptr<gameTile>>> gameTileGrid;
		vector<vector<shared_ptr<infoTile>>> infoTileGrid;
		vector<shared_ptr<gameTile>> flattenedBoard;

		shared_ptr<gameTile> selectedTile = nullptr;
		bool tileFlipping = false;

		map<Databank::Image_Types, int> tileFrequencies;
		map<int, int> initialWeights;
		vector<pair<int, double>> cumulative_probabilities;
		map <int, double> normalizedWeights;

		void prepareWeights();
		void flattenBoard(); //? COULD BE A SPEC

		vector<pair<int, int>> generateProbabilities(map<int, double> normalizedWeights);
		vector<pair<int, double>> generate_cumulative_probabilities(map<int, double> normalizedWeights);
		map <int, double> normalize_weights(map<int, int> frequencyWeights); 
		void generateWeightedGrid();


		map<int, double> calculateNormalizedWeights(map<int, int> frequencyWeights);

		void createBoard(vector<vector<int>>& newLevel);
		
		vector<int> generateWeightedRow(int rowIndex);
		vector<vector<int>> testBoardGenerator();	
		
		void countBoard();

		int getRandomTileValue(double probability);
		void populateInfoTiles();

	
	public:		
		// The class only has a constructor in reality. Nothing else is needed
		gameGrids(int level);

		void update();

		void draw();

		void mousePressed (int x, int y, int button);

		~gameGrids();




};