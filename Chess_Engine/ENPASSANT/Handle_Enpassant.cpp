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

    //std::cout<<"ciao da is_enpassant\n";
    Move last_move;

    if(game_movement && game_movement->get_stack().empty())
    {
        //std::cout<<"Nessuna mossa registrata, ritorno false\n",
        is_enpassant_value = false;
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
        return false;
    }

    
    //alzo di due ma devo controllare i lati a sx e dx
    int side[2]={1,-1};

    for(int i=0; i<2; i++)
    {
        //std::cout<<"i: "<<i<<std::endl;
        //Casella del pedone enpassant
        int square = side[i]+ last_move.get_to_square();

        //Se la casella non è sulla scacchiera, continua
        if (square < 0 || square > 63) 
        {
            //std::cout<<"La casella non è sulla scacchiera, continua\n";
            continue;
        }

        //Controllo se sono sulla stessa riga...
        if(square/8 != last_move.get_to_square()/8)
        {
            //std::cout<<"La casella non è sulla stessa riga, continua\n";
            continue;
        }

        //Se la casella affiaco del pedone è nullptr quindi vuota allora continua il ciclo
        if(!fen_shared.get()->get_piece()[square])
        {
            //std::cout<<"La casella affiaco del pedone è nullptr, continua\n";
            continue;
        }

        //L'altro pezzo deve essere di un altro colore
        if
        (
            fen_shared.get()->get_piece()[square]->get_color() 
            == last_move.get_color_piece()
        )
        {
            //std::cout<<"L'altro pezzo deve è dello stesso colore, continua\n";
            continue;
        }

        // Se il pezzo accanto al pedone doppio salto non è un pedone allora continua il ciclo
        if (!fen_shared.get()->get_piece()[square]->is_pawn()) 
        {
            //std::cout<<"il pezzo accanto al pedone doppio salto non è un pedone, continua\n";
            continue;
        }

        //Converto da Piece* a Pawn* usando un cast statico perchè sono sicuro che avrò 
        //solamente un pedone
        Pawn *pawn = static_cast<Pawn *>(fen_shared.get()->get_piece()[square]);
        
        //Se ho BIANCO dovrò diminuire di 8 perchè 0 è in alto a sx
        int color_offset = pawn->get_color() == WHITE ? -8 : 8;
        
        //Parte la gestione dell'en_passant
        pawn->handle_en_passant(last_move.get_to_square() + color_offset);
        
        fen_shared.get()->set_is_enpassant(true);
        fen_shared.get()->set_square_enpassant(last_move.get_to_square());
        
        is_enpassant_value = true;
        //std::cout<<"In: "<<square<<" i: "<<i<<" is_enpassant è true\n";
        
        return true;
    }
    //std::cout<<"is_enpassant: cado nel return false\n";
    return false;
}

bool Handle_Enpassant::handle_capture_enpassant()
{
    //std::cout<<"ciao da handle_capture_enpassant\n";
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

bool Handle_Enpassant::get_is_enpassant() const
{
    return is_enpassant_value;
}

void Handle_Enpassant::set_is_enpassant(bool new_is_enpassant)
{
    is_enpassant_value = new_is_enpassant;
}

Handle_Enpassant::~Handle_Enpassant()
{
    
}