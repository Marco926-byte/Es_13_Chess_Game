#include "Handle_Enpassant.h"

#include "../../Piece_factory/Piece.h"
#include "../MOVE/Move.h"

Handle_Enpassant::Handle_Enpassant
(
    std::shared_ptr<Handle_Fen_String> fen,
    Movement_Piece* movement
)
    :
    fen_shared(fen),
    game_movement(movement)
{

}

bool Handle_Enpassant::is_enpassant()
{
    //TODO: debug mossa 30->21, non killa quando fa enpassant
    Move last_move;

    if(game_movement && game_movement->get_stack().empty())
    {
        is_enpassant_value = false;
        fen_shared.get()->set_is_enpassant(is_enpassant_value);
        set_all_piece_team_is_not_enpassant();

        return false;
    }
    else
    {
        //Ottengo l'ultima mossa fatta...
        last_move = game_movement->get_stack().top();
    }

    //Se il pezzo non è un pedone...
    if
    (
        last_move.get_type_piece()!=PAWN 
    )
    {
        is_enpassant_value = false;
        fen_shared.get()->set_is_enpassant(is_enpassant_value);
        set_all_piece_team_is_not_enpassant();
        
        return false;
    }

    //Se l'ultima mossa non è un doppio salto del pedone...
    if
    (
        std::abs
        (
            last_move.get_to_square()-last_move.get_from_square()
        )!=16
    )
    {
        is_enpassant_value = false;
        fen_shared.get()->set_is_enpassant(is_enpassant_value);
        set_all_piece_team_is_not_enpassant();
        
        return false;
    }

    
    //alzo di due ma devo controllare i lati a sx e dx
    int side[2]={1,-1};
    
    fen_shared.get()->set_color_last_move(last_move.get_color_piece());
    fen_shared.get()->set_to_square_last_move(last_move.get_to_square());
    fen_shared.get()->set_from_square_last_move(last_move.get_from_square());

    for(int i=0; i<2; i++)
    {
        //Casella del pedone enpassant
        int square = side[i]+ last_move.get_to_square();

        //Se la casella non è sulla scacchiera, continua
        if (square < 0 || square > 63) 
        {
            continue;
        }

        //Controllo se sono sulla stessa riga...
        if(square/8 != last_move.get_to_square()/8)
        {
            continue;
        }

        //Se la casella affiaco del pedone è nullptr quindi vuota allora continua il ciclo
        if(!fen_shared.get()->get_piece()[square])
        {
            continue;
        }

        //L'altro pezzo deve essere di un altro colore
        if
        (
            fen_shared.get()->get_piece()[square]->get_color() 
            == last_move.get_color_piece()
        )
        {
            continue;
        }

        // Se il pezzo accanto al pedone doppio salto non è un pedone allora continua il ciclo
        if (!fen_shared.get()->get_piece()[square]->is_pawn()) 
        {
            continue;
        }

        //Converto da Piece* a Pawn* usando un cast statico perchè sono sicuro che avrò 
        //solamente un pedone
        Pawn *pawn = static_cast<Pawn *>(fen_shared.get()->get_piece()[square]);
        
        //Se ho BIANCO dovrò diminuire di 8 perchè 0 è in alto a sx
        int color_offset = pawn->get_color() == WHITE ? -8 : 8;
        
        //Parte la gestione dell'en_passant
        //TODO: MAKE LINK TO HANDLE_ENPASSANT
        pawn->handle_en_passant(last_move.get_to_square() + color_offset);
        
        //provo.....
        pawn->set_is_pawn_enpassant(true);

        is_enpassant_value = true;

        fen_shared.get()->set_is_enpassant(is_enpassant_value);
        fen_shared.get()->set_square_enpassant(last_move.get_to_square());

        return true;
    }

    set_all_piece_team_is_not_enpassant();
    return false;
}

void Handle_Enpassant::set_all_piece_team_is_not_enpassant()
{
    for(int i = 0; i<64; i++)
    {
        if
        (
            fen_shared.get()->get_piece()[i] 
            &&
            fen_shared.get()->get_piece()[i]->get_color() == fen_shared.get()->get_turn_ptr()->get_turn()
        )
        {
            fen_shared.get()->get_piece()[i]->set_is_pawn_enpassant(false);
        }
    }
}

bool Handle_Enpassant::handle_capture_enpassant()
{
    if(game_movement->get_stack().size()==0)
    {
        return false;
    }

    // Ottieni l'ultima mossa:
    Move last_move = game_movement->get_stack().top();

    // Se l'ultima mossa associata al pezzo non è un pedone, esci...
    if (last_move.get_type_piece()!=PAWN) 
    {
        return false;
    }

    // Se l'ultima mossa non è una singola mossa diagonale, esci...
    if 
    (
        abs
        (
            last_move.get_from_square() - last_move.get_to_square()
        ) != 9 
        &&
        abs
        (
            last_move.get_from_square() - last_move.get_to_square()
        ) != 7
    ) 
    {
        return false;
    }
    
    if(!is_enpassant_value)
    {
        return false;
    }

    int color_offset = last_move.get_color_piece() == WHITE ? 8 : -8;

    
    // Se la casella diagonale è nullptr, elimina il pezzo
    if(fen_shared.get()->get_piece()[last_move.get_to_square()+color_offset])
    {
        delete fen_shared.get()->get_piece()[last_move.get_to_square()+color_offset];
        fen_shared.get()->get_piece()[last_move.get_to_square()+color_offset]=nullptr;
        return true;
    }
    return false;
}

int Handle_Enpassant::get_debug_int() const
{
    return debug_int;
}

bool Handle_Enpassant::get_is_enpassant() const
{
    return is_enpassant_value;
}

void Handle_Enpassant::set_debug_int(int debug)
{
    //std::cout<<"---------HANDLE_ENPASSANT: ciao debug_int = 77-----------\n";
    debug_int=debug;
}

void Handle_Enpassant::set_is_enpassant(bool new_is_enpassant)
{
    is_enpassant_value = new_is_enpassant;
}

Handle_Enpassant::~Handle_Enpassant()
{
    
}