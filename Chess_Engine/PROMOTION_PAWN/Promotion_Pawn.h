#ifndef PROMOTION_PAWN_H
#define PROMOTION_PAWN_H

#include <memory>

#include "../MOVE/Move.h"
#include "../MOVEMENT_PIECE/Movement_Piece.h"
#include "../CHESSBOARD_TURN/Handle_Chessboard.h"
#include "../FEN/Handle_Fen_String.h"
#include "../CHECK/Check.h"
#include "../PIN/Handle_Pin.h"
#include "../FIND_KING/Find_King.h"

class Promotion_Pawn
{
private:
    std::shared_ptr<Movement_Piece> movement_shared;
    std::shared_ptr<Handle_Chessboard> turn_chessboard_shared;
    std::shared_ptr<Handle_Fen_String> fen_shared;
    std::shared_ptr<Check> check_shared;
    std::shared_ptr<Handle_Pin> pin_shared;
    std::shared_ptr<Find_King> find_king_shared;
public:
    Promotion_Pawn
    (
        Movement_Piece* movement,
        Handle_Chessboard* turn_chessboard,
        std::shared_ptr<Handle_Fen_String> fen,
        std::shared_ptr<Check> check,
        std::shared_ptr<Handle_Pin> pin,
        std::shared_ptr<Find_King> find_king
    );
    
    bool is_promotion_pawn();
    bool handle_promotion_pawn(char character_promotion);
};


#endif //PROMOTION_PAWN_H