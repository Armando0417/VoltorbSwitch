#pragma once

#include "ofMain.h"

#include <string>
#include <windows.h>
#include <iostream>
#include <mutex>

/**************************************************************************//**
 * Hey there! Fancy class you got here. Hopefully you are having fun exploring
 * this codebase. 
 
 * This is a Utility namespace that contains some really useful functions. 
 
 * Originally I had created this namespace as a way to log messages to the console
 * since the traditional openframeworks ofLog() and the famous std::cout did not want
 * to work out of the box. So i took it upon myself to make a better, and improved
 * logging system.
 
 * There are other functions here but the main focus is the logging system.
  
 * You can use the print___ functions to log messages to the console. In addition
 * you can use the <ANSI> escape codes to color any part of the messages. Pretty 
 * cool, huh?
 
 * I hope you find this useful, and if you need any more specific formatting 
 * options, feel free to add them here. For how to use this, check out the 
 * individual functions in this file. For how to implement new ones, check out 
 * the cpp file as you may take inspiration from the existing functions.
  
 * Have fun exploring!
  
 * ps. if you are questioning why namespace instead of a class? I don't know either.
 ******************************************************************************/

namespace Utilities {

    #define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
    #define PBWIDTH 60

    void printProgress(float percentage);


    /**
     * @brief This is a mutex that is a lock for the console.
     *      This is used to prevent multiple threads from writing to the console
     * 
     */
    extern std::mutex consoleMutex; 

    // ANSI escape codes for colors:
        extern const std::string RESET;
        extern const std::string BOLD;
        extern const std::string UNDERLINE;
        extern const std::string ITALIC;

        extern const std::string RED;
        extern const std::string GREEN;
        extern const std::string YELLOW;
        extern const std::string BLUE;
        extern const std::string MAGENTA;
        extern const std::string CYAN;




    // Tag Constants (Use these if you feel lazy to type a tag for each message)
        extern const std::string INFO_TAG;
        extern const std::string WARNING_TAG;
        extern const std::string ERROR_TAG;


/**
 * @brief Use this function to a small block message to the console. 
 * I recommend using this function for big updates or important messages.
 * 
 * @param tag The tag of the message (e.g. INFO, WARNING, ERROR)
 * @param message The message you want to log
 */
    void printUpdateLog(const std::string& tag, const std::string& message);


/**
 * @brief Use this function to print the status of a thread.
 * 
 * For a project without multi-threading, this function is not needed.
 * 
 * @param message 
 * @param threadId 
 */
    void printThreadStatus(const std::string& message, int threadId);



/**
 * @brief This function is used to basically print random messages to the console.
 * You can use this to print general information like which children was generated.
 * 
 * @param message The message you want to log
 */
    void printInfo(const std::string& message);

/**
 * @brief I recommend to use this function if the program completes a task (e.g. finished generating a fractal)
 * 
 * @param message A message telling you what the program finished doing
 */
    void printSuccess(const std::string& message);
    
/**
 * @brief Use this function to print warnings to the console. A warning is a message
 * that something may not be right but the program can still work. This was mainly
 * used for memory pool problems with allocating & deallocating memory. 
 * 
 * @param message The message of what may not be right
 */
    void printWarning(const std::string& message);

/**
 * @brief The message we want to both know immediately and also hope we never see. 
 * Use this one to Log any errors that occur in the program. It is important to know what went wrong.
 * 
 * @param message The message of what failed
 */
    void printError(const std::string& message);



/**************************************************************************//**
 * You may be asking yourself, "Wait, why is there a update log function and a
 * success, and error log function? Aren't they the same thing?" Well yes, yes 
 * they are. However, I wanted to make it easier for you to log a message based
 * on the type of message you want to log (the purpose of the specific log functions).
 * 
 * The printUpdateLog function is for general updates that may or may not fall into the 
 * particular categories of the other Log functions. 
 * 
 * For example, let's say I wanted to Log that the program finished generating the children
 * while the program was already running (spoilers: the program generates children in the background
 * while you admire a fractal). I would use the printUpdateLog function. Why? Because I would want 
 * to know that the worker threads went to standby after generating enough children. 
 * 
 * Another example would be if I wanted to know about the memory pool working properly 
 * (allocating or deallocating memory). I would use the printUpdateLog function for this.
 * 
 * Hope this clears things up!
 ******************************************************************************/


}


