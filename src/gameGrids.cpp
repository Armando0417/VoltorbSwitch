#include "gameGrids.h"


gameGrids::gameGrids(int level) {

    currentLevel = level;
    tileFrequencies[Databank::VOLTORB] = 0;
    tileFrequencies[Databank::ONE] = 0;
    tileFrequencies[Databank::TWO] = 0;
    tileFrequencies[Databank::THREE] = 0;

if (!DEBUG_MODE) {
    prepareWeights();
}
    generateWeightedGrid();
    countBoard();
    flattenBoard();

}


void gameGrids::update() {
    if (selectedTile != nullptr) {
        if (selectedTile->isFlipped()) {
            selectedTile = nullptr;
            tileFlipping = false;
        }
    }
    for (auto& row : gameTileGrid) 
        for (auto& tile : row) {
            if (tile != nullptr){
                tile->update();
            }
    }
}

void gameGrids::draw() {

    for (auto& row : gameTileGrid) 
        for (auto& tile : row) {
            if (tile != nullptr){
                tile->draw();
            }
        }
    for ( auto& row : infoTileGrid)
        for (auto& tile : row) {
            if (tile != nullptr){
                tile->draw();
            }
        }
}

void gameGrids::mousePressed (int x, int y, int button) {
    for (auto& row : gameTileGrid) {
        for (auto& tile : row) {
            if (tile != nullptr){
                if (tile->mouseHovering(x, y) && button == OF_MOUSE_BUTTON_LEFT 
                    && !tileFlipping && selectedTile == nullptr && !tile->isFlipped()) 
                    {
                        tile->tileFlipTrigger();
                        selectedTile = tile;    
                    }
                }
            }
        }
}

int gameGrids::getRandomTileValue(double randNum) {
    for (auto & pair : cumulative_probabilities) {
        if (randNum < pair.second) {
            return pair.first;
        }
    }
    return -1;
}

void gameGrids::flattenBoard() {
    for (auto &row : gameTileGrid) {
        for (auto &tile : row) {
            if (tile != nullptr)
                flattenedBoard.push_back(tile);
        }
    }
}

void gameGrids::prepareWeights() {
    if (currentLevel < 0) {
        Utilities::printError("Error: Invalid level. Please choose a level between 0 and 9.");
        throw exception();
    }
    
    initialWeights.insert ( pair<int, int>( 0,    5 + currentLevel * 2 ) ) ;
    initialWeights.insert ( pair<int, int>( 1,    max(16 - currentLevel * 2, 8) ) ) ;
    initialWeights.insert ( pair<int, int>( 2,    max(6 - currentLevel, 2)      ) );
    initialWeights.insert ( pair<int, int>( 3,    max(3 - currentLevel, 2)      ) );

    normalizedWeights = map<int, double>( normalize_weights(initialWeights) );
    cumulative_probabilities = generate_cumulative_probabilities(normalizedWeights);
    return;
}

map<int, double> gameGrids::normalize_weights(map<int, int> weights) {
    map<int, double> normalized_weights;
    double total = 0;
    for (auto &entry : weights) {
        total += entry.second;
    }
    for (auto &entry : weights) {
        normalized_weights[entry.first] = (double)entry.second / total;
    }
    return normalized_weights;
}



vector<pair<int, double>> gameGrids::generate_cumulative_probabilities(map<int, double> normalizedWeights) {
    vector<pair <int, double>> cumulative_probabilities;
    double cumulative_prob = 0;

    for (auto &entry : normalizedWeights) {
        cumulative_prob += entry.second;
        cumulative_probabilities.push_back({ entry.first, cumulative_prob });
    }
    return cumulative_probabilities;
}


void gameGrids::generateWeightedGrid() {
    if (DEBUG_MODE) {
        vector<vector<int>> testBoard = testBoardGenerator();
        createBoard(testBoard);
        return;
    }

    vector<vector<int>> initialGridVals;

    for (int rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++) {
        vector<int> newRow = generateWeightedRow(rowIndex);
        initialGridVals.push_back(newRow);
    }
    return createBoard(initialGridVals);
}

vector<int> gameGrids::generateWeightedRow(int rowIndex) {
     vector<int> newRow;

            for (int columnIndex = 0; columnIndex < BOARD_SIZE; columnIndex++) {
                if (rowIndex == BOARD_SIZE - 1 && columnIndex == BOARD_SIZE - 1)
                    continue;

                double randNum = (double)rand() / RAND_MAX;
                int randomTileValue = getRandomTileValue(randNum);

                if (randomTileValue == -1 ){
                    newRow.push_back(0);
                }
                newRow.push_back(randomTileValue);



                if (rowIndex == BOARD_SIZE - 1 || columnIndex == BOARD_SIZE - 1)
                    newRow[columnIndex] = 0;
            }
            return newRow;
        

}

void gameGrids::countBoard() {
    for (auto &row : gameTileGrid) {
        for (auto &tile : row) {
            if (tile != nullptr) {
                tileFrequencies[tile->getValueType()] += 1;
            }
        }
    }
}

void gameGrids::populateInfoTiles() {
    for (auto &row : infoTileGrid) {
        for (auto &tile : row) {
            if (tile != nullptr) {
                tile->countPoints(gameTileGrid);
            }
        }
    }   
}

vector<vector<int>> gameGrids::testBoardGenerator() {
    /*
    Test Board Layout:
        0 3 1 3 2 0
        0 0 0 0 2 0
        0 2 1 3 0 0
        0 0 1 3 0 0
        1 2 3 2 1 0
        0 0 0 0 0 _
    */

    vector<vector<int>> testBoard;
    testBoard.push_back({ 0, 3, 1, 3, 2, 0 });
    testBoard.push_back({ 0, 0, 0, 0, 2, 0 });
    testBoard.push_back({ 0, 2, 1, 3, 0, 0 });
    testBoard.push_back({ 0, 0, 1, 3, 0, 0 });
    testBoard.push_back({ 1, 2, 3, 2, 1, 0 });
    testBoard.push_back({ 0, 0, 0, 0, 0, 0 });
    return testBoard;
}





void gameGrids::createBoard(vector<vector<int>>& level) {
    gameTileGrid.clear();
    infoTileGrid.clear();

    gameTileGrid.resize(BOARD_SIZE, vector<shared_ptr<gameTile>>(BOARD_SIZE));
    infoTileGrid.resize(BOARD_SIZE, vector<shared_ptr<infoTile>>(BOARD_SIZE));

    int tileWidth = 150;   // Width of each tile
    int tileHeight = 150;  // Height of each tile
    int margin = 10;      // Spacing between tiles

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {

            int posX = margin + col * (tileWidth + margin);
            int posY = margin + row * (tileHeight + margin);
            
            if (row == PLAY_AREA && col == PLAY_AREA) {
                continue;
            } 

            if (row == PLAY_AREA) {
                infoTileGrid[row][col] = make_shared<infoTile>(posX, posY, row, col);
            }
            else if (col == PLAY_AREA) {
                infoTileGrid[row][col] = make_shared<infoTile>(posX, posY, row, col);
            }
            else {
                Databank::Image_Types tileVal = static_cast<Databank::Image_Types>(level[row][col]);
                gameTileGrid[row][col] = make_shared<gameTile>(tileVal, posX, posY, row, col);
            }
        }
    }

    populateInfoTiles();


}

gameGrids::~gameGrids() {}
