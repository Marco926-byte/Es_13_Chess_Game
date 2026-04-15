#include "Movement_Piece.h"

Movement_Piece::Movement_Piece
(
    std::shared_ptr<Handle_Fen_String> fen  
) 
    :fen_shared(fen)
       
{  


}

std::stack<Move> Movement_Piece::get_stack() const
{
    return stack;
}

bool Movement_Piece::handle_move(int from, int to)
{
    //Creo la nuova mossa:
    Move move;
    
    move.set_from_square(from);
    move.set_to_square(to);

    const auto &piece = fen_shared.get()->get_piece();

    //Gestisco la legalità dei pezzi:
    move.set_piece_status(piece[move.get_from_square()]);

    if(!move.get_piece_status()->is_legal_move(move.get_to_square()))
    {
        return false;
    }

    //Tutto okay, incremento il contatore del pareggio:
    //this->draw_counter++;

    //Gestisco la cattura:
    if(piece[move.get_to_square()]!=nullptr)
    {
        //puntatore al pezzo catturato andrà al to_square:
        move.set_piece_captured(piece[move.get_to_square()]);
        
        //Voglio sapere che tipo di carattere è....
        move.set_character_captured(piece[move.get_to_square()]->get_name_piece());
        
        //elimino il pezzo puntato dal carattere ucciso:
        delete piece[move.get_to_square()];
        
        //riporto a zero il contatore del pareggio pk se mangio reset
        //this->draw_counter=0;
    }
    //Se non c'è nessun pezzo ad ostacolare la mossa legale allora:
    else
    {
        //Metto piece_captured=nullptr, per forza non mangia quindi è nullptr
        move.set_piece_captured(nullptr);
        
        //il personaggio catturato sarà ovviamente vuoto:
        move.set_character_captured(' ');
    }
    piece[move.get_to_square()]=move.get_piece_status();
    piece[move.get_from_square()]=nullptr;

    move.get_piece_status()->set_square(move.get_to_square());
    move.get_piece_status()->set_ismoved(true); 
    
    //RIGENERA LA NUOVA FEN_STRING:
    std::string new_fen= fen_shared.get()->generate_fen_string();
    fen_shared.get()->add_fen_to_map(new_fen);

    stack.push(move);

    return true;
}

void Movement_Piece::print_all_move()
{
    for(int i=0; i<stack.size(); i++)
    {
        std::cout<<"__________________________________\n";
        std::cout<<"|Stampo tutte le mosse: .....     |\n";
        std::cout<<"|Il nome del pezzo:....           |\n"<<stack.top().get_piece_status()->get_name_piece()<<std::endl;
        std::cout<<"|La posizione dove era: ......    |\n"<<stack.top().get_from_square()<<std::endl;
        std::cout<<"|La posizione dove sarà: ......    |\n"<<stack.top().get_to_square()<<std::endl;
        std::cout<<"__________________________________\n";
    }
}

