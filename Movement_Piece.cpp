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

void Movement_Piece::set_attack_vector(std::vector<int> v_attack)
{
    attacked_square=v_attack;
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
    this->draw_counter++;

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
    piece[move.get_to_square()]=move.get_piece_status();
    piece[move.get_from_square()]=nullptr;

    if(move.get_piece_status()->is_pawn())
    {
        this->draw_counter=0;
    }
    move.get_piece_status()->set_square(move.get_to_square());
    move.get_piece_status()->set_ismoved(true); 
    
    //RIGENERA LA NUOVA FEN_STRING:
    std::string new_fen= fen_shared.get()->generate_fen_string();
    fen_shared.get()->add_fen_to_map(new_fen);

    return true;
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
void Movement_Piece::update_move_in_check(Color team_color,std::vector<int> v_attack)
{
    const auto& piece=fen_shared.get()->get_piece();
    
    //Itero tutto
    for (int i=0; i<64; i++)
    {
        //pulisco il vettore delle mosse per ogni pezzo
        attacked_square.clear();

        //Controllo se il pezzo è giusto...
        if
        (
            piece[i] 
            && 
            piece[i]->get_color()==team_color 
            && 
            !piece[i]->is_king()
        )
        {
            //Itero tutte le mosse legali del pezzo:
            for(int itr_normal_legal_move : piece[i]->get_legal_moves())
            {
                //Itero tutto il vettore dell'attacco:
                for(int itr_attack : v_attack)
                {
                    //Se un vettore di attacco contiene una mossa legale del pezzo allora inserisci:   
                    if(itr_attack == itr_normal_legal_move)
                    {
                        attacked_square.push_back(itr_attack);
                    }
                }
            }
            //Imposto le nuove mosse legali...
            piece[i]->set_legal_moves(attacked_square);
        }
    }
}