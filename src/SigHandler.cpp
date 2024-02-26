#include "../inc/SigHandler.hpp"





// SigHandler::SigHandler(){
//     // sa.sa_handler = handleSignal;
//     // sa.sa_flags = 0;
// };

// SigHandler::~SigHandler(){

// };


  SignalHandler::SignalHandler() {
        // Set up the signal handler for SIGINT
        struct sigaction sa;
        sa.sa_handler = SignalHandler::handleSignal;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;

        if (sigaction(SIGINT, &sa, NULL) == -1) {
            std::cerr << "Error setting up signal handler." << std::endl;
        }
    }

    void SignalHandler::handleSignal(int signal) {
        if (signal == SIGINT) {
            std::cout << "SIGINT received. Handling the signal." << std::endl;
            //Add something to handle the server here
        }
    }

// void SigHandler::handleSignal(int signum){
//     // sa.sa_handler = handleSignal;
//     // sa.sa_flags = 0;

// };

// int SigHandler::initHandler(){
//     // if (sigaction(SIGINT, &sa, nullptr) == -1) {
//     //     std::cerr << "Error setting up signal handler." << std::endl;
//     //     return (-1);
//     //  }
// };






    // struct sigaction sa;
    // sa = handleSignal;
    // sa.sa_flags = 0;

    // // Register the signal handler for SIGINT
    // if (sigaction(SIGINT, &sa, nullptr) == -1) {
    //     std::cerr << "Error setting up signal handler." << std::endl;
    //     return 1;
    // }