#include "game.h"

Move Game::previousMove() const {
    return moveHistory.top();
}

Game::Game(int size): board{size} {   

    // adds an default initialized move to moveHistory, used as a dummy object
    //  to represent that there was no previous move
    moveHistory.emplace();
}

void Game::start() {
    std::string outerCommand, arg;
    bool customSetup = false;

    while (std::cin >> outerCommand) {

        if (outerCommand == "game") {
            std::string whitePlayer, blackPlayer;
            std::cin >> whitePlayer >> blackPlayer;

            if (whitePlayer == "human")
                player1 = std::make_unique<HumanPlayer>(Colour::White);
            else if (whitePlayer == "computer[1]")
                player1 = std::make_unique<ComputerPlayer>(Colour::White, 1);
            else if (whitePlayer == "computer[2]")
                player1 = std::make_unique<ComputerPlayer>(Colour::White, 2);
            else if (whitePlayer == "computer[3]")
                player1 = std::make_unique<ComputerPlayer>(Colour::White, 3);
            else
                player1 = std::make_unique<ComputerPlayer>(Colour::White, 4);
            
            if (blackPlayer == "human")
                player2 = std::make_unique<HumanPlayer>(Colour::Black);
            else if (blackPlayer == "computer[1]")
                player2 = std::make_unique<ComputerPlayer>(Colour::Black, 1);
            else if (blackPlayer == "computer[2]")
                player2 = std::make_unique<ComputerPlayer>(Colour::Black, 2);
            else if (blackPlayer == "computer[3]")
                player2 = std::make_unique<ComputerPlayer>(Colour::Black, 3);
            else
                player2 = std::make_unique<ComputerPlayer>(Colour::Black, 4);
            
            // if setup mode has not been entered, initialized the board with
            //  all the needed pieces for a default chess game
            if (customSetup)
                board.initBoard();
            
            Player *currentPlayer = player1.get();

            std::string innerCommand;

            while (std::cin >> innerCommand) {

                if (innerCommand == "move") {

                    // gets the player's move
                    Move playerMove = currentPlayer->makeMove(board);

                    



                } else if (innerCommand == "resign") {

                } else {
                    std::cout << "Unrecognized command: " << innerCommand << std::endl;
                    std::cout << "Please try again: ";
                }
            }
            

        } else if (outerCommand == "setup") {



        } else {
            std::cout << "Unrecognized command: " << outerCommand << std::endl;
            std::cout << "Please try again: ";
        }
    }
}
