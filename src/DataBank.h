#pragma once

#include "ofMain.h"
#include "Utilities.h"


/** ************************************************************************
 * This is the Data Bank Class.
 * 
 * This class is the one used to store all of the data for the game.
 * We need this so that way we have a centralized place to store the data
 * to use it across the entire project. 
 * 
 * It is crucial that this class is made at the start of the project's lifetime.
 * 
 * This class stores:
 * 1. The Tile images
 * 2. The animation frames for the tiles.
 * 3. The flip animations for the tiles.
 * 4. The sound effects for the game. 
 * 5. The various constant delays we need for the animations.
 * 
 * Use and modify this class if you want to add new files to the game.  
 **************************************************************************/

class Databank {

     public:
        Databank(const Databank&) = delete;
        Databank& operator=(const Databank&) = delete;

        static Databank& getInstance() {
            static Databank instance;
            return instance;
        }

        enum Tile_Types {POINTS, BOMB};
        enum Image_Types {VOLTORB, ONE, TWO, THREE, BACK, MINI};
        enum Sound_Effects {EXPLOSION, INCREASE_POINTS, FLIP_TILE, LEVEL_COMPLETE, STORING_POINTS, BUTTON_PRESSED};

        void playSound(Sound_Effects sound) {
            sfxTable[sound].play();
        }

        map<Tile_Types, vector<ofImage>> getAnimFrames() {
            return animFrames;
        }

        map<Image_Types, vector<ofImage>> getTileFlipFrames() {
            return tileFlipFrames;
        }

        map<Image_Types, ofImage> getTileImages() {
            return tileImages;
        }
        
    private:

        const string IMAGE_FOLDER_PATH = "Assets\\";
        const string SOUND_FOLDER_PATH = "Sounds\\";

        map<Tile_Types, vector<ofImage>> animFrames;
        map <Image_Types, vector<ofImage>> tileFlipFrames;
        map<Image_Types, ofImage> tileImages;  
        map<Sound_Effects, ofSoundPlayer> sfxTable;

        
        Databank() {
            animFrames = map<Tile_Types, vector<ofImage>>();
            tileFlipFrames = map<Image_Types, vector<ofImage>>();
            tileImages = map<Image_Types, ofImage>();
            sfxTable = map<Sound_Effects, ofSoundPlayer>();
            loadFiles(); 
        }


        void loadFiles() {
            // Load the tile Images
           tileImages [Image_Types::VOLTORB]    =  ofImage(IMAGE_FOLDER_PATH + "voltorb.png");
            tileImages[Image_Types::ONE]        =  ofImage(IMAGE_FOLDER_PATH + "one.png");
            tileImages[Image_Types::TWO]        =  ofImage(IMAGE_FOLDER_PATH + "two.png");
            tileImages[Image_Types::THREE]      =  ofImage(IMAGE_FOLDER_PATH + "three.png");
            tileImages[Image_Types::BACK]       =  ofImage(IMAGE_FOLDER_PATH + "big_back_of_tile.png");
            tileImages[Image_Types::MINI]       =  ofImage(IMAGE_FOLDER_PATH + "voltorbMini.png");


            // Load the animation frames:
                for (int i = 0; i < 9; i++) {
                    string animExplosion = "animation_explosion_";
                    string animPoints = "animation_points_";

                    if (i < 4) {
                        animFrames[Tile_Types::POINTS]
                            .push_back( ofImage(IMAGE_FOLDER_PATH + animPoints + ofToString(i) + ".png") );
                    }
                    animFrames[Tile_Types::BOMB]
                        .push_back( ofImage(IMAGE_FOLDER_PATH + animExplosion + ofToString(i) + "_final.png") );
                }

            // Load the flip animation frames:
                vector<ofImage> flipFrames;
                flipFrames.push_back( ofImage(IMAGE_FOLDER_PATH + "big_back_of_tile.png"));
                flipFrames.push_back( ofImage(IMAGE_FOLDER_PATH + "flip_back.png"));
                flipFrames.push_back( ofImage(IMAGE_FOLDER_PATH + "flip_middle.png"));

                for (int i = 0; i < 4; i++) {
                    vector<ofImage> remainingFlipFrames = flipFrames;

                    if (i == 0 ) {
                        remainingFlipFrames.push_back( ofImage(IMAGE_FOLDER_PATH + "flip_voltorb_transition.png"));
                        remainingFlipFrames.push_back( ofImage(IMAGE_FOLDER_PATH + "voltorb.png"));
                        tileFlipFrames[Image_Types::VOLTORB] = remainingFlipFrames;
                    }
                    else {
                        remainingFlipFrames.push_back( ofImage(IMAGE_FOLDER_PATH + "flip_" + ofToString(i) + "transition.png"));
                        if (i == 1) {
                            remainingFlipFrames.push_back( ofImage(IMAGE_FOLDER_PATH + "one.png"));
                            tileFlipFrames[Image_Types::ONE] = remainingFlipFrames;
                        }
                        else if (i == 2) {
                            remainingFlipFrames.push_back( ofImage(IMAGE_FOLDER_PATH + "two.png"));
                            tileFlipFrames[Image_Types::TWO] = remainingFlipFrames;
                        }
                        else {
                            remainingFlipFrames.push_back( ofImage(IMAGE_FOLDER_PATH + "three.png"));
                            tileFlipFrames[Image_Types::THREE] = remainingFlipFrames;
                        }
                    }
                    remainingFlipFrames.clear();
                
                }

                //load the sound effects: 
                sfxTable[Sound_Effects::EXPLOSION] = ofSoundPlayer();
                sfxTable[Sound_Effects::EXPLOSION].load (SOUND_FOLDER_PATH + "sfx/flipExplosionSound.mp3");

                sfxTable[Sound_Effects::INCREASE_POINTS] = ofSoundPlayer();
                sfxTable[Sound_Effects::INCREASE_POINTS].load (SOUND_FOLDER_PATH + "sfx\\pointIncreaseSfx.mp3");
                
                sfxTable[Sound_Effects::FLIP_TILE] = ofSoundPlayer();
                sfxTable[Sound_Effects::FLIP_TILE].load (SOUND_FOLDER_PATH + "sfx\\flipSound.mp3");
                
                sfxTable[Sound_Effects::LEVEL_COMPLETE] = ofSoundPlayer();
                sfxTable[Sound_Effects::LEVEL_COMPLETE].load (SOUND_FOLDER_PATH + "sfx\\levelBeat.mp3");

                sfxTable[Sound_Effects::STORING_POINTS] = ofSoundPlayer();
                sfxTable[Sound_Effects::STORING_POINTS].load (SOUND_FOLDER_PATH + "sfx\\pointsTallied.mp3");
    
            return;
        }



};