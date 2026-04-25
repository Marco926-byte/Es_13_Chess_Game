#include "Promotion_Pawn.h"

#include "../MOVE/Move.h"

Promotion_Pawn::Promotion_Pawn
(
    Movement_Piece* movement,
    Handle_Chessboard* turn_chessboard,
    std::shared_ptr<Handle_Fen_String> fen,
    std::shared_ptr<Check> check,
    std::shared_ptr<Handle_Pin> pin,
    std::shared_ptr<Find_King> find_king
)
    :movement_ptr(movement),
    turn_chessboard_ptr(turn_chessboard),
    fen_shared(fen),
    check_shared(check),
    pin_shared(pin),
    find_king_shared(find_king)
{
    
}

bool Promotion_Pawn::is_promotion_pawn()
{
    Move last_move;
    
    if(movement_ptr->get_stack().size()==0)
    {
        return false;
    }
    else
    {
        //Ottengo l'ultima mossa fatta...
        last_move = movement_ptr->get_stack().top();
    }

    if(last_move.get_type_piece()!=PAWN)
    {
        return false;
    }

    if
    (
        last_move.get_to_square()<=63
        &&
        last_move.get_to_square()>=56
        ||
        last_move.get_to_square()>=0
        &&
        last_move.get_to_square()<=7
    )
    {
        
        return true;
    }

    return false;
}

bool Promotion_Pawn::handle_promotion_pawn(char character_promotion)
{
    char promotion;

    if(turn_chessboard_ptr->get_turn()==WHITE)
    {
        promotion= toupper(character_promotion);       
    }
    else
    {
        promotion = character_promotion;
    }

    Move last_move = movement_ptr->get_stack().top();
    
    //Importante per aggiornare il pezzo...
    delete fen_shared.get()->get_piece()[last_move.get_to_square()];
    fen_shared.get()->get_piece()[last_move.get_to_square()]=nullptr;

    fen_shared.get()->get_piece()[last_move.get_to_square()] = 
            fen_shared.get()->get_create_ptr()->create_piece
            (
                promotion,
                last_move.get_to_square()
            );
            
    //TODO: DEVI CHIAMARE LE MOSSE PER AGGIORNARE IL PEZZO CANCELLATO
    /*last_move.set_piece_status
    (
        fen_shared.get()->get_piece()[last_move.get_to_square()]
    );*/

    fen_shared.get()->get_piece()[last_move.get_to_square()]->set_square
    (
        last_move.get_to_square()
    );

    Piece *king = find_king_shared.get()->find_king_current_turn
    (
        fen_shared.get()->get_piece(),
        turn_chessboard_ptr->get_turn()
    );
    if(!king)
    {
        return false;
    }
    int position_king = king->get_square();
    
    check_shared.get()->handle_check_on_king_diagonal
    (
        position_king,
        fen_shared.get()->get_piece(),
        turn_chessboard_ptr->get_turn()
    );

    check_shared.get()->handle_check_on_king_knight
    (
        position_king,
        fen_shared.get()->get_piece(),
        turn_chessboard_ptr->get_turn()
    );

    check_shared.get()->handle_check_on_king_straight
    (
        position_king,
        fen_shared.get()->get_piece(),
        turn_chessboard_ptr->get_turn()
    );

    pin_shared.get()->handle_pin_on_king_straight
    (
        fen_shared.get()->get_piece(),
        turn_chessboard_ptr->get_turn()
    );

    pin_shared.get()->handle_pin_on_king_diagonal
    (
       fen_shared.get()->get_piece(),
       turn_chessboard_ptr->get_turn() 
    );

    king->update_legal_moves(fen_shared);
    
    return true;
}