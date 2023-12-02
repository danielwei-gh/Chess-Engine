#include "human.h"
#include "rules.h"

HumanPlayer::HumanPlayer(Colour c): Player{c}
{
    squareMap = {
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
}

Move HumanPlayer::makeMove(const Board &board, const Move &previousMove)
{   
    std::string strStart, strEnd, aux;
    std::pair<int, int> start, end;

    while (std::cin >> strStart >> strEnd) {

        // if the arguments are invalid, re-prompt the player for another pair
        if (!squareMap.contains(strStart) || !squareMap.contains(strEnd)) {
            std::getline(std::cin, aux);
            std::cout << "Invalid arguments. Enter arguments: [(a1-h8) (a1-h8)]" 
                << std::endl;
            continue;
        }

        // gets the starting and ending positions of the piece to be moved
        start = squareMap[strStart];
        end = squareMap[strEnd];

        // gets the piece to be moved
        auto piece = board.getSquare(start.first, start.second).getPiece();

        // if there is no piece on the square with position start or the piece
        //  has a different colour than the player's assigned colour, re-prompt
        //  the player for another pair
        if (!piece || piece->getColour() != getColour()) {
            std::getline(std::cin, aux);
            std::cout << "No piece to move or invalid piece to move."
                << " Enter arguments: [(a1-h8) (a1-h8)]" << std::endl;
            continue;
        }

        // generate all legal moves for the piece on the square with 
        //  position start
        std::vector<Move> fullyLegalMoves = 
            Rules::generateFullyLegalMoves(start, board, previousMove);
        
        for (auto &move : fullyLegalMoves) {

            // if the ending position of one of the legal moves is the same as
            //  end, return that legal move
            if (move.endPos == end) {
                return move;
            }
        }

        std::getline(std::cin, aux);
        std::cout << "Move is illegal. Enter arguments: [(a1-h8) (a1-h8)]" 
            << std::endl;
    }

    // this statement is just for compiling purposes, will never run due to
    //  the while loop that prompts for a legal move
    return Move();
}

PieceType HumanPlayer::promotionPiece() 
{
    std::map<std::string, PieceType> pieceTypeMap {
        {"Q", PieceType::Queen}, {"B", PieceType::Bishop},
        {"R", PieceType::Rook}, {"N", PieceType::Knight}
    };
    std::string strPieceType, aux;
    
    while (std::cin >> strPieceType) {
        std::getline(std::cin, aux);

        if (pieceTypeMap.contains(strPieceType))
            return pieceTypeMap[strPieceType];
        else
            std::cout << "Invalid promotion piece. Enter argument: [Q, B, R, N]"
                << std::endl;
    }

    // this statement is just for compiling purposes, will never run due to
    //  the while loop that prompts for a valid promotion piece
    return PieceType::King;
}
