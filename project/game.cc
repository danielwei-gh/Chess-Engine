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

    Player *currentPlayer = nullptr;

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
            
            currentPlayer = player1.get();

            std::string innerCommand;

            while (std::cin >> innerCommand) {

                if (innerCommand == "move") {

                    // gets the player's move
                    Move playerMove = 
                        currentPlayer->makeMove(board, previousMove());
                    
                    int startRow = playerMove.startPos.first;
                    int startCol = playerMove.startPos.second;

                    int endRow = playerMove.endPos.first;
                    int endCol = playerMove.endPos.second;

                    int enPassantRow = playerMove.enPassantPos.first;
                    int enPassantCol = playerMove.enPassantPos.second;

                    // move the attacking piece and remove the captured piece
                    //  (if there is one)
                    auto attackingPiece = board.removePiece(startRow, startCol);
                    board.removePiece(endRow, endCol);
                    board.placePiece(endRow, endCol, attackingPiece);

                    // if the move was enPassant, remove the enPassanted piece
                    if (enPassantRow != -1 && enPassantRow != -1)
                        board.removePiece(enPassantRow, enPassantCol);
                    
                    // otherwise if the move was castling
                    else if (playerMove.castledRook) {
                        int rookStartRow = playerMove.rookStartPos.first;
                        int rookStartCol = playerMove.rookStartPos.second;

                        int rookEndRow = playerMove.rookEndPos.first;
                        int rookEndCol = playerMove.rookEndPos.second;
                        
                        // move the castled Rook
                        auto castledRook = board.removePiece(rookStartRow, rookStartCol);
                        board.removePiece(rookEndRow, rookEndCol);
                        board.placePiece(rookEndRow, rookEndCol, castledRook);
                    }

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
