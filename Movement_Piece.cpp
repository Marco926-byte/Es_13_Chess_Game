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

    stack.push(move);

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
    is_enpassant();
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

bool Movement_Piece::is_enpassant()
{
    Move last_move;
    std::cout<<"INIZIO\n";
    if(stack.size()==0)
    {
        std::cout<<"lo stack delle mosse è vuoto, returno false\n";
        return false;
    }
    else
    {
        //Ottengo l'ultima mossa fatta...
        std::cout<<"lo stack delle mosse contiene qualcosa\n";
        last_move = stack.top();
    }

    if(!last_move.get_piece_status())
    {
        std::cout<<"il pezzo associato all'ultima mossa è nullptr\n";
        return false;
    }
    else
        std::cout<<"il pezzo associato all'ultima mossa non è nullptr\n";

    //Se il pezzo non è un pedone...
    if
    (
        !last_move.get_piece_status()->is_pawn() 
    )
    {
        std::cout<<"L'ultima mossa non è stata fatta da un pedone, returno false\n";
        return false;
    }
    else
        std::cout<<"L'ultima mossa è stata fatta da un pedone\n";

    //Se l'ultima mossa non è un doppio salto del pedone...
    if(std::abs(last_move.get_to_square()-last_move.get_from_square())!=16)
    {
        std::cout<<"L'ultima mossa non è un doppio salto del pedone, returno false\n";
        return false;
    }

    //alzo di due ma devo controllare i lati a sx e dx
    int side[2]={1,-1};

    for(int i=0; i<2; i++)
    {
        std::cout<<"i : "<<i<<std::endl;
        std::cout<<"lato: side["<<i<<"] = "<<side[i]<<std::endl;
        std::cout<<"Casella dell'ultima mossa: "<<last_move.get_to_square()<<std::endl;

        //Casella del pedone enpassant
        int square = side[i]+ last_move.get_to_square();
        std::cout<<"square di controllo enpassant è: "<<square<<std::endl;

        //Se la casella non è sulla scacchiera, continua
        if (square < 0 || square > 63) 
        {
            std::cout<<"square esce dalla scacchiera, riinizia il ciclo..."<<std::endl;
            continue;
        }

        //Se la casella affiaco del pedone è nullptr quindi vuota allora continua il ciclo
        if(!fen_shared.get()->get_piece()[square])
        {
            std::cout<<"La casella accanto al pedone doppio salto è vuota!, riinizio il ciclo...\n";
            continue;
        }

        //L'altro pezzo deve essere di un altro colore
        if(fen_shared.get()->get_piece()[square]->get_color() == last_move.get_piece_status()->get_color())
        {
            std::cout<<"L'altro pezzo è dello stesso team, riinizio il ciclo\n";
            continue;
        }

        // Se il pezzo accanto al pedone doppio salto non è un pedone allora continua il ciclo
        if (!fen_shared.get()->get_piece()[square]->is_pawn()) 
        {
            std::cout<<"Il pezzo accanto al pedone doppio salto non è un pedone allora continua il ciclo\n";
            std::cout<<"Chi è il pezzo che è accanto al pedone doppio salto? "<<fen_shared.get()->get_piece()[square]->get_name_piece()<<std::endl;
            continue;
        }

        //Converto da Piece* a Pawn* usando un cast statico perchè sono sicuro che avrò 
        //solamente un pedone
        Pawn *pawn = static_cast<Pawn *>(fen_shared.get()->get_piece()[square]);
        
        //Se ho BIANCO dovrò diminuire di 8 perchè 0 è in alto a sx
        int color_offset = pawn->get_color() == WHITE ? -8 : 8;
        
        //Parte la gestione dell'en_passant
        pawn->handle_en_passant(last_move.get_to_square() + color_offset);
        
        std::cout<<"Ho aggiunto la casella enpassant al pawn: \n";
        std::cout<<pawn->get_name_piece()<<std::endl;
        std::cout<<pawn->get_square()<<std::endl;
        std::cout<<last_move.get_to_square() + color_offset<<std::endl;
        
        return true;
    }
    return false;
}