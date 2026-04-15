#ifndef UPDATE_MOVES_H
#define UPDATE_MOVES_H

#include "../../Draw_board.h"

#include "../FEN/Handle_Fen_String.h"
#include "../ENPASSANT/Handle_Enpassant.h"
#include "../CASTLING/Castling.h"
#include "../MOVEMENT_PIECE/Movement_Piece.h"

#include <memory> 

class Update_Moves
{
private:
    std::shared_ptr<Handle_Fen_String> fen_shared;
    std::shared_ptr<Handle_Enpassant> enpassant_shared;
    Movement_Piece* movement_ptr;
    std::shared_ptr<Castling> castling_shared;

    std::vector<int> attacked_square;
public:
    Update_Moves
    (
        std::shared_ptr<Handle_Fen_String> fen,
        std::shared_ptr<Handle_Enpassant> enpassant,
        Movement_Piece * movement,
        std::shared_ptr<Castling> castling
    );    
    void update_moves_all_piece();

    void update_move_in_check
    (
        Color team_turn,
        std::vector<int> v_attack
    );   
};


#endif //UPDATE_MOVES_H