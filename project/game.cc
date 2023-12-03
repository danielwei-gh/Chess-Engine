#include "game.h"

Move Game::getPreviousMove() const {
    return moveHistory.top();
}

void Game::clearBoard() {
    for (int i = 0; i < board.getSize(); ++i) {
        for (int j = 0; j < board.getSize(); ++j)
            board.removePiece(i, j);
    }
}

Game::Game(int size): board{size}, whiteScore{0.0}, blackScore{0.0} {

    // adds an default initialized move to moveHistory, used as a dummy object
    //  to represent that there was no previous move
    moveHistory.emplace();
}

void Game::start() {
    std::string outerCommand, aux;
    bool customSetup = false;
    Colour firstPlayerColour = Colour::White;

    while (true) {

        std::cout << "\nEnter command: ";
        std::cin >> outerCommand;

        if (!std::cin)
            break;

        if (outerCommand == "game") {
            std::string strWhitePlayer, strBlackPlayer;
            std::cin >> strWhitePlayer >> strBlackPlayer;

            if (strWhitePlayer == "human")
                player1 = std::make_unique<HumanPlayer>(Colour::White);
            else if (strWhitePlayer == "computer[1]")
                player1 = std::make_unique<ComputerPlayer>(Colour::White, 1);
            else if (strWhitePlayer == "computer[2]")
                player1 = std::make_unique<ComputerPlayer>(Colour::White, 2);
            else if (strWhitePlayer == "computer[3]")
                player1 = std::make_unique<ComputerPlayer>(Colour::White, 3);
            else if (strWhitePlayer == "computer[4]")
                player1 = std::make_unique<ComputerPlayer>(Colour::White, 4);
            else {
                std::cout << "\nInvalid argument: " << strWhitePlayer << std::endl;
                std::getline(std::cin, aux);
                continue;
            }
            
            if (strBlackPlayer == "human")
                player2 = std::make_unique<HumanPlayer>(Colour::Black);
            else if (strBlackPlayer == "computer[1]")
                player2 = std::make_unique<ComputerPlayer>(Colour::Black, 1);
            else if (strBlackPlayer == "computer[2]")
                player2 = std::make_unique<ComputerPlayer>(Colour::Black, 2);
            else if (strBlackPlayer == "computer[3]")
                player2 = std::make_unique<ComputerPlayer>(Colour::Black, 3);
            else if (strBlackPlayer == "computer[4]")
                player2 = std::make_unique<ComputerPlayer>(Colour::Black, 4);
            else {
                std::cout << "\nInvalid argument: " << strBlackPlayer << std::endl;
                std::getline(std::cin, aux);
                continue;
            }
            
            // if setup mode has not been entered, initialized the board with
            //  all the needed pieces for a default chess game
            if (!customSetup)
                board.initBoard();
            
            // output the current board
            std::cout << "\n" << board << std::endl;

            // set up which colour player will play first
            Player *currentPlayer = firstPlayerColour == Colour::White ?
                player1.get() : player2.get();

            std::string innerCommand;

            while (true) {
                
                std::cout << "\n" << (currentPlayer->getColour() == Colour::White ?
                    "White " : "Black ") << "player's turn: ";
                std::cin >> innerCommand;

                if (!std::cin)
                    break;

                if (innerCommand == "move") {

                    // gets the player's move
                    Move playerMove = 
                        currentPlayer->makeMove(board, getPreviousMove());
                    
                    // if the player's move is invalid or illegal, reprompt
                    //  the player for another move (should only apply to
                    //  human players)
                    if (!playerMove.movedPiece)
                        continue;
                    
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

                    // if the attacking piece has moved yet, set to to be moved
                    if (!attackingPiece->isMoved())
                        attackingPiece->firstMove();
                    
                    // gets the colour of the attacking piece
                    Colour attackingColour = attackingPiece->getColour();

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
                        castledRook->firstMove();
                    }

                    // if the attacking pawn can perform pawn promotion
                    else if (attackingPiece->getType() == PieceType::Pawn &&
                            ((attackingColour == Colour::White && endRow == 0) ||
                            (attackingColour == Colour::Black && endRow == 7)))
                    {   
                        // gets the choice of promotion piece type from player
                        PieceType promotionType = currentPlayer->promotionPiece();

                        // if the player's choice of promotion was invalid,
                        //  set the promotion type to Queen
                        if (promotionType == PieceType::King) {
                            std::cout << "\nDefaulting to Queen." << std::endl;
                            promotionType = PieceType::Queen;
                        }

                        // remove the Pawn at (endRow, endCol) and replace with
                        //  a newly allocated chosen Piece
                        board.removePiece(endRow, endCol);
                        board.placePiece(endRow, endCol, 
                            generatePiece(attackingColour, promotionType));
                    }

                    // add the player's move to moveHistory
                    moveHistory.push(playerMove);

                    // output the current board
                    std::cout << "\n" << board << std::endl;

                    // gets the colour of the current player
                    Colour allyColour = currentPlayer->getColour();

                    // gets the colour of the other player
                    Colour enemyColour = allyColour == Colour::White ? 
                        Colour::Black : Colour::White;
                    
                    // if the other player's King is now in check
                    if (Rules::check(enemyColour, board, getPreviousMove())) {

                        // if the other player's King is now in checkmate
                        if (Rules::checkmate(enemyColour, board, getPreviousMove())) {
                            std::cout << "\n" << "Checkmate! " 
                                << (allyColour == Colour::White ? "White " : "Black ")
                                << "wins!" << std::endl;
                            
                            // increment the score for current player's colour
                            allyColour == Colour::White ? ++whiteScore : ++blackScore;

                            // end the current game
                            break;
                        }
                        
                        else
                            std::cout << "\n" << (enemyColour == Colour::White ? 
                                "White " : "Black ") << "is in check."  << std::endl;
                    }

                    // if the other player's King is not in check and stalemated
                    else if (Rules::stalemate(enemyColour, board, getPreviousMove())) {
                        std::cout << "\nStalemate!" << std::endl;
                        
                        // increment both scores by half a point
                        whiteScore += 0.5;
                        blackScore += 0.5;

                        // end the current game
                        break;
                    }
                    
                    // alternate the current player to the other player
                    currentPlayer = currentPlayer == player1.get() ? 
                        player2.get() : player1.get();

                } else if (innerCommand == "resign") {
                    std::cout << "\n" << (currentPlayer->getColour() == Colour::White ? 
                        "Black wins!" : "White wins!") << std::endl;

                    // increment the score for other player's colour
                    currentPlayer->getColour() == Colour::White ? 
                        ++blackScore : ++whiteScore;

                    // end the current game
                    break;

                } else {
                    std::cout << "\nInvalid command: " << innerCommand << std::endl;
                    std::getline(std::cin, aux);
                }
            }
            
            // reset the board to an empty board
            clearBoard();
        }

        else if (outerCommand == "setup") {
            
            // indicate that setup mode has been entered
            customSetup = true;

            std::string fnCommand;

            // maps a string that represents the square position to a pair 
            //  of ints that represent the square position
            std::map<std::string, std::pair<int, int>> squareMap = {

                {"a8", {0, 0}}, {"b8", {0, 1}}, {"c8", {0, 2}}, {"d8", {0, 3}},
                {"e8", {0, 4}}, {"f8", {0, 5}}, {"g8", {0, 6}}, {"h8", {0, 7}},

                {"a7", {1, 0}}, {"b7", {1, 1}}, {"c7", {1, 2}}, {"d7", {1, 3}},
                {"e7", {1, 4}}, {"f7", {1, 5}}, {"g7", {1, 6}}, {"h7", {1, 7}},

                {"a6", {2, 0}}, {"b6", {2, 1}}, {"c6", {2, 2}}, {"d6", {2, 3}},
                {"e6", {2, 4}}, {"f6", {2, 5}}, {"g6", {2, 6}}, {"h6", {2, 7}},

                {"a5", {3, 0}}, {"b5", {3, 1}}, {"c5", {3, 2}}, {"d5", {3, 3}},
                {"e5", {3, 4}}, {"f5", {3, 5}}, {"g5", {3, 6}}, {"h5", {3, 7}},

                {"a4", {4, 0}}, {"b4", {4, 1}}, {"c4", {4, 2}}, {"d4", {4, 3}},
                {"e4", {4, 4}}, {"f4", {4, 5}}, {"g4", {4, 6}}, {"h4", {4, 7}},

                {"a3", {5, 0}}, {"b3", {5, 1}}, {"c3", {5, 2}}, {"d3", {5, 3}},
                {"e3", {5, 4}}, {"f3", {5, 5}}, {"g3", {5, 6}}, {"h3", {5, 7}},

                {"a2", {6, 0}}, {"b2", {6, 1}}, {"c2", {6, 2}}, {"d2", {6, 3}},
                {"e2", {6, 4}}, {"f2", {6, 5}}, {"g2", {6, 6}}, {"h2", {6, 7}},

                {"a1", {7, 0}}, {"b1", {7, 1}}, {"c1", {7, 2}}, {"d1", {7, 3}},
                {"e1", {7, 4}}, {"f1", {7, 5}}, {"g1", {7, 6}}, {"h1", {7, 7}}
            };

            // maps a string that represents a piece to a pair of a Colour
            //  and a PieceType
            std::map<std::string, std::pair<Colour, PieceType>> pieceTypeMap {

                {"K", {Colour::White, PieceType::King}}, 
                {"Q", {Colour::White, PieceType::Queen}}, 
                {"B", {Colour::White, PieceType::Bishop}}, 
                {"R", {Colour::White, PieceType::Rook}}, 
                {"N", {Colour::White, PieceType::Knight}}, 
                {"P", {Colour::White, PieceType::Pawn}},

                {"k", {Colour::Black, PieceType::King}}, 
                {"q", {Colour::Black, PieceType::Queen}}, 
                {"b", {Colour::Black, PieceType::Bishop}}, 
                {"r", {Colour::Black, PieceType::Rook}}, 
                {"n", {Colour::Black, PieceType::Knight}}, 
                {"p", {Colour::Black, PieceType::Pawn}},
            };

            while (true) {

                std::cout << "\nEnter function command: ";
                std::cin >> fnCommand;

                if (!std::cin)
                    break;

                if (fnCommand == "+") {
                    std::string strPiece, strPos;
                    std::cin >> strPiece >> strPos;
                        
                    // if the arguments are invalid
                    if (!pieceTypeMap.contains(strPiece) || 
                        !squareMap.contains(strPos))
                    {
                        std::cout << "\nInvalid arguments: " << strPiece
                            << " or " << strPos << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }

                    // if the piece to be placed is the white King
                    if (strPiece == "K") {
                        
                        // gets the pair representing the position of the 
                        //  white King on the board
                        std::pair<int, int> whiteKingPos = board.getWhiteKingPos();

                        // if there is already a white King on the board
                        if (whiteKingPos.first != -1 && whiteKingPos.second != -1)
                        {
                            std::cout << "\nWhite King already on the board." 
                                << std::endl;
                            std::getline(std::cin, aux);
                            continue;
                        }
                    }

                    // if the piece to be placed is the black King
                    if (strPiece == "k") {

                        // gets the pair representing the position of the 
                        //  black King on the board
                        std::pair<int, int> blackKingPos = board.getBlackKingPos();

                        // if there is already a black King on the board
                        if (blackKingPos.first != -1 && blackKingPos.second != -1)
                        {
                            std::cout << "\nBlack King already on the board. " 
                                << std::endl;
                            std::getline(std::cin, aux);
                            continue;
                        }
                    }

                    Colour colour = pieceTypeMap[strPiece].first;
                    PieceType type = pieceTypeMap[strPiece].second;
                    int row = squareMap[strPos].first;
                    int col = squareMap[strPos].second;
                    
                    // remove the piece on the square with position
                    //  (row, col) if there is one, and place the newly
                    //  allocate piece
                    board.removePiece(row, col);
                    auto newPiece = generatePiece(colour, type);
                    board.placePiece(row, col, newPiece);

                    // explicitly set the placed piece as moved to not
                    //  handle enPassant and castling after board setup
                    newPiece->firstMove();

                    // redisplay the board
                    std::cout << "\n" << board << std::endl;
                }

                else if (fnCommand == "-") {
                    std::string strPos;
                    std::cin >> strPos;
                        
                    // if the argument are invalid
                    if (!squareMap.contains(strPos)) 
                    {
                        std::cout << "\nInvalid argument: " << strPos << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }

                    int row = squareMap[strPos].first;
                    int col = squareMap[strPos].second;

                    // remove the piece on the square with position
                    //  (row, col) if there is one
                    auto removedPiece = board.removePiece(row, col);

                    // if there is no piece on the square with position 
                    //  (row, col)
                    if (!removedPiece)
                    {
                        std::cout << "\nNo piece on " << strPos << "." << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }

                    // redisplay the board
                    std::cout << "\n" << board << std::endl;
                }

                else if (fnCommand == "=") {
                    std::string strColour;
                    std::cin >> strColour;

                    if (strColour != "white" && strColour != "black")
                    {
                        std::cout << "\nInvalid argument: " << strColour 
                            << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }

                    // set the player who will play first to the
                    //  the choice of colour
                    firstPlayerColour = strColour == "white" ? 
                        Colour::White : Colour::Black;
                    
                    std::cout << "\n" << (firstPlayerColour == Colour::White ? 
                        "White" : "Black") << " player will have the first move." 
                        << std::endl;
                }

                else if (fnCommand == "done") {

                    // gets the square positions of the white King and black
                    //  King on the board
                    std::pair<int, int> whiteKingPos = board.getWhiteKingPos();
                    std::pair<int, int> blackKingPos = board.getBlackKingPos();

                    // if there is no white King or black King on the board
                    if ((whiteKingPos.first == -1 && whiteKingPos.second == -1) ||
                        (blackKingPos.first == -1 && blackKingPos.second == -1))
                    {
                        std::cout << "\nInvalid board setup. Continue to setup "
                            "the board." << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }

                    bool firstOrLastRowPawn = false;

                    // check if any Pawns are on the first or last row
                    for (int i = 0; i < board.getSize(); ++i) {

                        // gets the piece on the square with position (0, i)
                        //  if there is one
                        auto piece = board.getSquare(0, i).getPiece();

                        // if the piece on the square with position (0, i)
                        //  is a Pawn
                        if (piece && piece->getType() == PieceType::Pawn) {
                            firstOrLastRowPawn = true;
                            break;
                        }

                        // gets the piece on the square with position
                        //  (board.getSize() - 1, i) if there is one
                        piece = board.getSquare(board.getSize() - 1, i).getPiece();

                        // if the piece on the square with position
                        //  (board.getSize() - 1, i) is a Pawn
                        if (piece && piece->getType() == PieceType::Pawn) {
                            firstOrLastRowPawn = true;
                            break;
                        }
                    }

                    // if there are any Pawns on the first or last row of the 
                    //  board
                    if (firstOrLastRowPawn)
                    {
                        std::cout << "\nInvalid board setup. Continue to setup "
                            "the board." << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }

                    // if the white King is in check
                    if (Rules::check(Colour::White, board, getPreviousMove()))
                    {
                        std::cout << "\nInvalid board setup. Continue to setup "
                            "the board." << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }

                    // if the black King is in check
                    if (Rules::check(Colour::Black, board, getPreviousMove()))
                    {
                        std::cout << "\nInvalid board setup. Continue to setup "
                            "the board." << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }

                    std::cout << "\nBoard setup success." << std::endl;

                    // leave setup mode
                    break;
                }

                else {
                    std::cout << "\nInvalid command: " << fnCommand << std::endl;
                    std::getline(std::cin, aux);
                }
            }
        }
        
        else {
            std::cout << "\nInvalid command: " << outerCommand << std::endl;
            std::getline(std::cin, aux);
        }
    }

    // display the final score 
    std::cout << "\n\nFinal score:" << std::endl;
    std::cout << "White: " << whiteScore << std::endl;
    std::cout << "Black: " << blackScore << std::endl;
}
