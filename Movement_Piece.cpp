#include "Movement_Piece.h"

Movement_Piece::Movement_Piece
(
    Draw_board* board, 
    std::shared_ptr<Handle_Fen_String> fen,
    Handle_Chessboard *chess
) 
    :draw(board),
    fen_shared(fen),
    handle_chess(chess)
{  
    
}

void Movement_Piece::handle_move(int from, int to)
{
    
    //Creo la nuova mossa:
    Move move;
    move.set_from_square(from);
    move.set_to_square(to);

    //Gestisco la legalità dei pezzi:
    move.set_piece_status(fen_shared.get()->get_piece()[move.get_from_square()]);

    if(!move.get_piece_status()->is_legal_move(move.get_to_square()))
    {
        wxLogMessage(wxT("Mossa non legale"));
    }
    //Tutto okay, incremento il contatore del pareggio:
    this->draw_counter++;

    //Gestisco la cattura:
    if(fen_shared.get()->get_piece()[move.get_to_square()]!=nullptr)
    {
        //puntatore al pezzo catturato andrà al to_square:
        move.set_piece_captured(fen_shared.get()->get_piece()[move.get_to_square()]);
        
        //Voglio sapere che tipo di carattere è....
        move.set_character_captured(fen_shared.get()->get_piece()[move.get_to_square()]->get_name_piece());
        
        //elimino il pezzo puntato dal carattere ucciso:
        delete fen_shared.get()->get_piece()[move.get_to_square()];
        
        //riporto a zero il contatore del pareggio pk se mangio reset
        this->draw_counter=0;
    }
    //Se non c'è nessun pezzo ad ostacolare la mossa legale allora:
    else
    {
        //Metto piece_captured=nullptr, per forza non mangia quindi è nullptr
        move.set_piece_captured(nullptr);
        //il personaggio catturato sarà ovviamente vuoto:
        move.set_character_captured(' ');
    }
    fen_shared.get()->get_piece()[move.get_to_square()]=move.get_piece_status();
    fen_shared.get()->get_piece()[move.get_from_square()]=nullptr;

    if(move.get_piece_status()->is_pawn())
    {
        this->draw_counter=0;
    }
    move.get_piece_status()->set_square(move.get_to_square());
    move.get_piece_status()->set_ismoved(true);  
}

void Movement_Piece::update_moves_all_piece()
{
    const auto& piece=fen_shared.get()->get_piece();
    for(int i=0; i<64; ++i)
    {
        if(piece[i])
        {
            piece[i]->update_legal_moves(fen_shared);
        }
    }
}



