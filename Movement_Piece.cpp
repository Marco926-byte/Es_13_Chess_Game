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

bool Movement_Piece::handle_capture_enpassant()
{
    // Ottieni l'ultima mossa:
    Move last_move = stack.top();

    // Se l'ultima mossa associata al pezzo non è un pedone, esci...
    if (!last_move.get_piece_status()->is_pawn())
    {
        return false;
    }

    // Se l'ultima mossa non è una singola mossa diagonale, esci...
    if 
    (
        abs(last_move.get_from_square() - last_move.get_to_square()) != 9 
        &&
        abs(last_move.get_from_square() - last_move.get_to_square()) != 7
    ) 
    {
        return false;
    }

    // Se la casella diagonale è nullptr, elimina il pezzo
    if (last_move.get_piece_captured() == nullptr) 
    {
        int color_offset = last_move.get_piece_status()->get_color() == WHITE ? 8 : -8;
        last_move.set_piece_status(fen_shared.get()->get_piece()[last_move.get_to_square()+color_offset]);
        
        delete fen_shared.get()->get_piece()[last_move.get_to_square()+color_offset];
        fen_shared.get()->get_piece()[last_move.get_to_square()+color_offset]=nullptr;
        
        return true;
    }
    return false;
}

bool Movement_Piece::handle_castling_dx()
{
    std::cout<<"------------Entro in HANDLE_CASTLING_DX ------------\n";
    int position_rook=0;
    
    // Ottieni l'ultima mossa:
    Move last_move = stack.top();

    // Se l'ultima mossa associata al pezzo non è il re, esci...
    if (!last_move.get_piece_status()->is_king())
    {
        std::cout<<"Ultima mossa non è stata fatta dal re, ritorno false\n";
        return false;
    }

    std::cout<<"last_move.get_from_square() ="<<last_move.get_from_square()<<std::endl;
    std::cout<<"last_move.get_to_square() ="<<last_move.get_to_square()<<std::endl;
    std::cout<<"to - from = "<<last_move.get_to_square()-last_move.get_from_square()<<std::endl;

    // Se l'ultima mossa non è un doppio salto in avanti, esci...
    if 
    (
        (last_move.get_to_square() - last_move.get_from_square()) != 2 
    ) 
    {
        std::cout<<"L'ultima mossa non è un doppio spostamento a destra (2), ritorno false\n";
        return false;
    }

    if(last_move.get_piece_status()->get_color()==WHITE)
    {    
        position_rook = 63;
    }
    else
    {
        position_rook = 7;
    }
    std::cout<<"La posizione della torre: "<<position_rook<<std::endl;

    //Gestisci il movimento della torre!
    if(fen_shared.get()->get_piece()[position_rook])
    {
        std::cout<<"Nella posizione ["<<position_rook<<"] c'è: "<<fen_shared.get()->get_piece()[position_rook]->get_name_piece()<<std::endl;
        std::cout<<"Nella posizione ["<<position_rook-1<<"] c'è "<<fen_shared.get()->get_piece()[position_rook-1]->get_name_piece()<<std::endl;
        
        fen_shared.get()->get_piece()[position_rook-2] = fen_shared.get()->get_piece()[position_rook];
        
        std::cout<<"SCAMBIO EFFETTUATO tra position["<<position_rook<<"] e ["<<position_rook-2<<"]"<<std::endl;
        std::cout<<"Nella posizione ["<<position_rook-1<<"] c'è "<<fen_shared.get()->get_piece()[position_rook-1]->get_name_piece()<<std::endl;

        fen_shared.get()->get_piece()[position_rook]=nullptr;
        std::cout<<"Adesso in position ["<<position_rook<<"] non c'è più niente\n";
        return true;        
    }
    else
    {
        return false;
    }
}

bool Movement_Piece::handle_castling_sx()
{
    // Ottieni l'ultima mossa:
    Move last_move = stack.top();

    int position_rook=0;

    // Se l'ultima mossa associata al pezzo non è il re, esci...
    if (!last_move.get_piece_status()->is_king())
    {
        return false;
    }

    // Se l'ultima mossa non è un doppio salto in qualunque direzione, esci...
    if 
    (
        (last_move.get_to_square() - last_move.get_from_square()) != -2 
    ) 
    {
        return false;
    }

    if(last_move.get_piece_status()->get_color()==WHITE)
    {
        position_rook = 56;
    }
    else
    {
        position_rook = 0;
    }

    //Gestisci il movimento della torre!
    if(fen_shared.get()->get_piece()[position_rook])
    {
        fen_shared.get()->get_piece()[position_rook+3]= fen_shared.get()->get_piece()[position_rook];
        fen_shared.get()->get_piece()[position_rook]=nullptr;
        
        return true;        
    }
    else
    {
        return false;
    }
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
    is_castling_dx();
    is_castling_sx();
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

    if(stack.size()==0)
    {
        return false;
    }
    else
    {
        //Ottengo l'ultima mossa fatta...
        last_move = stack.top();
    }

    if(!last_move.get_piece_status())
    {
        return false;
    }

    //Se il pezzo non è un pedone...
    if
    (
        !last_move.get_piece_status()->is_pawn() 
    )
    {
        return false;
    }

    //Se l'ultima mossa non è un doppio salto del pedone...
    if(std::abs(last_move.get_to_square()-last_move.get_from_square())!=16)
    {
        return false;
    }

    //alzo di due ma devo controllare i lati a sx e dx
    int side[2]={1,-1};

    for(int i=0; i<2; i++)
    {
        //Casella del pedone enpassant
        int square = side[i]+ last_move.get_to_square();

        //Se la casella non è sulla scacchiera, continua
        if (square < 0 || square > 63) 
        {
            continue;
        }

        //Se la casella affiaco del pedone è nullptr quindi vuota allora continua il ciclo
        if(!fen_shared.get()->get_piece()[square])
        {
            continue;
        }

        //L'altro pezzo deve essere di un altro colore
        if(fen_shared.get()->get_piece()[square]->get_color() == last_move.get_piece_status()->get_color())
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
        pawn->handle_en_passant(last_move.get_to_square() + color_offset);
        
        return true;
    }
    return false;
}

int Movement_Piece::get_king_position()
{
    Piece* king = handle_chess->find_king(fen_shared.get()->get_piece(),handle_chess->get_turn());

    return king->get_square();
}

bool Movement_Piece::is_castling_dx()
{
    std::cout<<"------------------IS_CASTLING_DX inizia---------------\n";
    //Trovo il re sulla scacchiera con find_king
    Piece *king = handle_chess->find_king(fen_shared.get()->get_piece(),handle_chess->get_turn());

    //Se il re si è mosso esci
    if(king->get_ismoved())
    {
        std::cout<<"Il re si è mosso, ritorno false\n";
        return false;
    }

    //Ottengo la posizione del re
    int position_king = king->get_square();
    std::cout<<"La posizione del re è: "<<position_king<<std::endl;

    std::cout<<"Entro nel ciclo for: \n";
    
    //itero di 3, metto 1 perchè voglio vedere la casella successiva al re
    for(int i = 1; i<4; i++)
    {
        std::cout<<"i: "<<i<<std::endl;
        
        //Controllo dei confini della scacchiera
        if(position_king+i>=64 || position_king+i<0)
        {
            std::cout<<"Sono uscito dal bordo, ritorno false\n";
            return false;
        }
        
        //Controllo se sulla casella successiva c'è qualcosa
        if(fen_shared.get()->get_piece()[position_king+i])
        {
            std::cout<<"In: "<<position_king+i<<" c'è qualcosa\n";
            std::cout<<"c'è: "<<fen_shared.get()->get_piece()[position_king+i]->get_name_piece()<<std::endl;
        
            //Controllo se trovo la torre durante il ciclo:
            if(fen_shared.get()->get_piece()[position_king+i]->is_rock())
            {
                std::cout<<"Il controllo conferma la presenza di una torre\n";
                //Trovo la torre, me la memorizzo in un puntatore creato sul momento
                Piece* rock = fen_shared.get()->get_piece()[position_king+i];
                
                //Controllo se la torre si è mossa:
                if(rock->get_ismoved())
                {
                    std::cout<<"La torre selezionata, si è mossa, return false\n";
                    return false;
                }
                else
                {
                    std::cout<<"La torre selezionata non si è mossa\n";
                    
                    //Controllo se nelle 2 caselle successive al re c'era qualcosa:
                    if
                    (
                        !fen_shared.get()->get_piece()[position_king+1]
                        &&
                        !fen_shared.get()->get_piece()[position_king+2]
                    )
                    {
                        std::cout<<"in"<<position_king+1<<" non c'era niente\n";
                        std::cout<<"in"<<position_king+2<<" non c'era niente\n";

                        for(int i = 1; i<3; i++)
                        {
                            if
                            (
                                handle_chess->handle_check_on_king_straight
                                (
                                    get_king_position()+i,
                                    fen_shared.get()->get_piece(),
                                    handle_chess->get_turn()
                                )
                                ||
                                handle_chess->handle_check_on_king_knight
                                (
                                    get_king_position()+i,
                                    fen_shared.get()->get_piece(),
                                    handle_chess->get_turn()
                                )
                                ||
                                handle_chess->handle_check_on_king_diagonal
                                (
                                    get_king_position()+i,
                                    fen_shared.get()->get_piece(),
                                    handle_chess->get_turn()
                                )
                            )
                            {
                                std::cout<<"Nelle caselle dell'arrocco sono attaccate, non posso fare la mossa ma comunque potrei\n";
                                return true;
                            }

                        }
                        std::cout<<"Nessun attacco durante le caselle di arrocco, le aggiungo come mossa legale\n";
                        king->add_legal_move(position_king+2);
                        return true;
                    }
                    //In una delle due caselle successive alla casella del re c'era qualcosa
                    //non aggiungo la mossa per arroccare, ma comunque arrocco possibile
                    else
                    {
                        std::cout<<"Nelle caselle successive al re c'era qualcosa, non aggiungo caselle ma possibile arrocco teorico\n";
                        return true;
                    }       
                }                    
            }
            else
            {
                std::cout<<"Non ho trovato la torre, continuo la ricerca\n";
                continue;
            }                
        }
        //Non c'è niente sulla casella successiva 
        else
        {
            std::cout<<"Non c'è niente sulla casella successiva, continuo la ricerca\n";
            continue;
        }   
    }
    std::cout<<"Non ho trovato niente, ritorno false\n";
    return false;
}

bool Movement_Piece::is_castling_sx()
{
    //Trovo il re sulla scacchiera con find_king
    Piece *king = handle_chess->find_king(fen_shared.get()->get_piece(),handle_chess->get_turn());

    //Se il re si è mosso esci
    if(king->get_ismoved())
    {
        return false;
    }

    //Ottengo la posizione del re
    int position_king = king->get_square();

    //itero di 4, metto 1 perchè voglio vedere la casella successiva al re
    for(int i = 1; i<5; i++)
    {
        //Controllo dei confini della scacchiera
        if(position_king-i>=64 || position_king-i<0)
        {
            return false;
        }
        
        //Controllo se sulla casella successiva c'è qualcosa
        if(fen_shared.get()->get_piece()[position_king-i])
        {
            //Controllo se trovo la torre durante il ciclo:
            if(fen_shared.get()->get_piece()[position_king-i]->is_rock())
            {
                //Trovo la torre, me la memorizzo in un puntatore creato sul momento
                Piece* rock = fen_shared.get()->get_piece()[position_king-i];
                
                //Controllo se la torre si è mossa:
                if(rock->get_ismoved())
                {
                    return false;
                }
                else
                {
                    //Controllo se nelle 2 caselle successive al re c'era qualcosa:
                    if
                    (
                        !fen_shared.get()->get_piece()[position_king-1]
                        &&
                        !fen_shared.get()->get_piece()[position_king-2]
                        &&
                        !fen_shared.get()->get_piece()[position_king-3]
                    )
                    {
                        for(int i = 1; i<4; i++)
                        {
                            if
                            (
                                handle_chess->handle_check_on_king_straight
                                (
                                    get_king_position()-i,
                                    fen_shared.get()->get_piece(),
                                    handle_chess->get_turn()
                                )
                                ||
                                handle_chess->handle_check_on_king_knight
                                (
                                    get_king_position()-i,
                                    fen_shared.get()->get_piece(),
                                    handle_chess->get_turn()
                                )
                                ||
                                handle_chess->handle_check_on_king_diagonal
                                (
                                    get_king_position()-i,
                                    fen_shared.get()->get_piece(),
                                    handle_chess->get_turn()
                                )
                            )
                            {
                                return true;
                            }

                        }
                        king->add_legal_move(position_king-2);
                        return true;
                    }
                    //In una delle due caselle successive alla casella del re c'era qualcosa
                    //non aggiungo la mossa per arroccare, ma comunque arrocco possibile
                    else
                    {
                        return true;
                    }       
                }                    
            }
            else
            {
                continue;
            }                
        }
        //Non c'è niente sulla casella successiva 
        else
        {
            continue;
        }   
    }
    return false;
}

bool Movement_Piece::is_promotion_pawn()
{
    Move last_move;

    if(stack.size()==0)
    {
        return false;
    }
    else
    {
        //Ottengo l'ultima mossa fatta...
        last_move = stack.top();
    }

    if(!last_move.get_piece_status())
    {
        return false;
    }

    if(!last_move.get_piece_status()->is_pawn())
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