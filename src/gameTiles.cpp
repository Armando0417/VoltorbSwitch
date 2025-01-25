#include "gameTiles.h"

/*
    Author Note:
        - This file is for the implementation of the 'GameTiles class. 
        - All of the code of how the methods work will be here!
*/

gameTile::gameTile(Databank::Image_Types _value, int x_pos, int y_pos, int row, int col) {
        value = _value;
        position = ofPoint(x_pos, y_pos);
        row_col[0] = row;
        row_col[1] = col;
        flipped = false;
        hovering = false;

        Databank& bank = Databank::getInstance(); // Author's note: This is to extract the relevant images stored in the bank

        backOfTile = bank.getTileImages()[Databank::Image_Types::BACK];
        
        if (_value == Databank::Image_Types::VOLTORB) {
            frontOfTile = bank.getTileImages()[Databank::Image_Types::VOLTORB];
        }
        else if (_value == Databank::Image_Types::ONE) {
            frontOfTile = bank.getTileImages()[Databank::Image_Types::ONE];
        }
        else if (_value == Databank::Image_Types::TWO) {
            frontOfTile = bank.getTileImages()[Databank::Image_Types::TWO];
        }
        else if (_value == Databank::Image_Types::THREE) {
            frontOfTile = bank.getTileImages()[Databank::Image_Types::THREE];
        }

        animFrames = bank.getAnimFrames()[_value > 0 ? Databank::Tile_Types::POINTS : Databank::Tile_Types::BOMB];
        tileFlipFrames = bank.getTileFlipFrames()[value];

}

void gameTile::update() {
    if (isFlipping) {
        if (++animTime > ANIM_FLIP_DURATION) {
            animTime = 0;
            currFlipFrameIndex++;
            if (currFlipFrameIndex == tileFlipFrames.size()) {
                Databank::getInstance().playSound(Databank::Sound_Effects::FLIP_TILE);
                isFlipping = false;
                flipped = true;
                currFlipFrameIndex = tileFlipFrames.size() - 1;
            }
        }
    }
}


void gameTile::draw() {
    ofNoFill();
    ofDrawRectangle(position.x, position.y, width, height);
    ofFill();
    if (flipped) {
        frontOfTile.draw(position.x, position.y, width, height);

        if (delayOverlayTimer <= ANIM_OVERLAY_DELAY) {
            delayOverlayTimer += 0.1;
        }
        else {
            drawTileAnimation();
        }
    }

    else if (isFlipping) {
        flipAnimationFrame = tileFlipFrames[currFlipFrameIndex];
        flipAnimationFrame.draw(position.x, position.y, width, height);
    }

    else {
        backOfTile.draw(position.x, position.y, width, height);
    }
}

void gameTile::drawTileAnimation() {
    if (animPlayed) return;
    
    // Databank& bank = Databank::getInstance(); 

    if (value == Databank::Image_Types::VOLTORB) { 
        animationOverlayFrame = animFrames[currentAnimationFrameIndex];
        vector<double> layoutParams = getAnimLayoutParams(true);
        animationOverlayFrame.draw(layoutParams[0], layoutParams[1], layoutParams[2], layoutParams[3]);
    }

    else {  
        animationOverlayFrame = animFrames[currentAnimationFrameIndex];  
        vector<double> layoutParams = getAnimLayoutParams(false);
        animationOverlayFrame.draw(layoutParams[0], layoutParams[1], layoutParams[2], layoutParams[3]);
    }

    if (++tileAnimTime > ANIM_OVERLAY_DURATION) {
        tileAnimTime = 0;
        currentAnimationFrameIndex++;
        if (currentAnimationFrameIndex == animFrames.size()) {
            animPlayed = true;
        }
    }
}

vector<double> gameTile::getAnimLayoutParams(bool isBomb) {
    if (!isBomb) {
        double offSetX = position.x - (width/2);
        double offSetY = position.y - (height/2);
        return {offSetX, offSetY, width * 2, height * 2};
    }
    else if (currentAnimationFrameIndex >= 3 && isBomb) {
        // Center the bomb image when the index is greater than or equal to 3
        double scaledWidth = width * 3;
        double scaledHeight = height * 3;

        // Adjust position to center the scaled image
       double offSetX = position.x - (width);
        double offSetY = position.y - (height);

        return {offSetX, offSetY, scaledWidth, scaledHeight};
    }
    else {
        return {position.x, position.y, width, height};
    }
 }


/*
    Author's note
        - Why is there two methods doing sorta the same thing?
            - Well, pretty much one is used to draw the image of the red border when you hover over the tile.
            The other one is to just know if the mouse is currently hovering over the tile.

*/


bool gameTile::mouseHovering(int x, int y) {
    if ((x > position.x) && (x < position.x + width) && (y > position.y) && (y < position.y + height)) {
        return true;
    }
    else {
        return false;
    }
}



bool gameTile::isFlipped() { return flipped; }

void gameTile::tileFlipTrigger() {
    isFlipping = true;
}


