#include "Utilities.h"

namespace Utilities {
    const std::string RESET = "\033[0m";
    const std::string BOLD = "\033[1m";
    const std::string UNDERLINE = "\033[4m";
    const std::string ITALIC = "\033[3m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    
    std::mutex consoleMutex;  
    const std::string INFO_TAG = "INFO";

    void printProgress(float percentage) {
        int val = (int)(percentage);
        int lpad = (int)(percentage * PBWIDTH);
        int rpad = PBWIDTH - lpad;
        printf ("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
        fflush(stdout);
    }

    void printUpdateLog(const std::string& tag, const std::string& message) {
        std::lock_guard<std::mutex> lock(consoleMutex);

        std::cout << "\n--------------------------------" << std::endl;
        std::cout << BLUE << "[PROGRAM UPDATE] " << RESET;
        std::cout << "[" << tag << "] " << message << std::endl;

        std::cout << "--------------------------------" << std::endl;
    }


    void printThreadStatus(const std::string& message, int threadId) {
        std::lock_guard<std::mutex> lock(consoleMutex);

        auto time = ofGetElapsedTimeMillis(); // Time in ms
        std::cout << "\n--------------------------------" << std::endl;
        std::cout << ITALIC << MAGENTA << "[THREAD STATUS] " << RESET;
        std::cout << "[" << threadId << "] " << message << " at time " << time << " ms" << std::endl;
    }

    void printInfo(const std::string& message) {
        std::lock_guard<std::mutex> lock(consoleMutex);

        std::cout << GREEN << "[INFO] " << RESET;
        std::cout << message << std::endl;
    }

    void printSuccess(const std::string& message) {
        std::lock_guard<std::mutex> lock(consoleMutex);

        std::cout << GREEN << "[SUCCESS] " << RESET;
        
        std::cout << message << std::endl;
    }

    void printWarning(const std::string& message) {
        std::lock_guard<std::mutex> lock(consoleMutex);

        std::cout << YELLOW << "[WARNING] " << RESET;
        
        std::cout << message << std::endl;
    }

    void printError(const std::string& message) {
        std::lock_guard<std::mutex> lock(consoleMutex);

        std::cout << RED << "[ERROR] " << RESET;
        
        std::cout << message << std::endl;
    }




}