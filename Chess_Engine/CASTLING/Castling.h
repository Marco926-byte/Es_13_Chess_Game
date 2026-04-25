#ifndef CASTLING_H
#define CASTLING_H

#include <memory>

#include "../MOVEMENT_PIECE/Movement_Piece.h"
#include "../FEN/Handle_Fen_String.h"
#include "../CHECK/Check.h"
#include "../CHESSBOARD_TURN/Handle_Chessboard.h"
#include "../FIND_KING/Find_King.h"

class Castling
{
private:
    std::shared_ptr<Handle_Fen_String> fen_shared;    
    Movement_Piece* movement_ptr =nullptr;
    std::shared_ptr<Check> check_shared;
    Handle_Chessboard* turn_chess_ptr = nullptr;
    std::shared_ptr<Find_King> find_king_shared;  
public:
    Castling
    (
        std::shared_ptr<Handle_Fen_String> fen,
        Movement_Piece* movement,
        std::shared_ptr<Check> check,
        Handle_Chessboard* turn_chess,
        std::shared_ptr<Find_King> find_king
    );
    
    bool is_castling_dx();
    bool is_castling_sx();

    bool handle_castling_dx();
    bool handle_castling_sx();
};


#endif //CASTLING_H