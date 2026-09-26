#include "Castling.h"

Castling::Castling
(
    std::shared_ptr<Handle_Fen_String> fen,
    Movement_Piece* movement,
    std::shared_ptr<Check> check,
    Handle_Chessboard* turn_chess,
    std::shared_ptr<Find_King> find_king
)
    :fen_shared(fen),
     movement_ptr(movement),
     check_shared(check),
     turn_chess_ptr(turn_chess),
     find_king_shared(find_king)
{
    
}

bool Castling::is_castling_dx()
{
    //std::cout<<"ciao da is_castling_dx\n";   
    //Trovo il re sulla scacchiera con find_king
    Piece *king = 
    find_king_shared.get()->find_king_current_turn
    (
        fen_shared.get()->get_piece(),
        turn_chess_ptr->get_turn()
    );

    //std::cout<<"dopo find_king is_castling_dx\n";
    Piece* rock_piece = nullptr;
    
    //Se il re si è mosso esci
    if(king->get_ismoved())
    {
        fen_shared.get()->set_short_castling(false);
        return false;
    }

    //Ottengo la posizione del re
    int position_king = king->get_square();

    //itero di 3, metto 1 perchè voglio vedere la casella successiva al re
    for(int i = 1; i<4; i++)
    {
        //Controllo dei confini della scacchiera
        if(position_king+i>=64 || position_king+i<0)
        {
            //std::cout<<"is_castling_dx: chiudo per controllo confini\n";
            return false;
        }
        
        //Controllo se sulla casella successiva c'è qualcosa
        if(fen_shared.get()->get_piece()[position_king+i])
        {
            if((position_king+i)!=63 && king->get_color()==WHITE)
            {
                fen_shared.get()->set_short_castling(true);
                //std::cout<<"is_castling_dx: chiudo per possibilità di arroccare da destra\n";
                return false;
            }

            if((position_king+i)!=7 && king->get_color()==BLACK)
            {
                fen_shared.get()->set_short_castling(true);
                //std::cout<<"is_castling_dx: 1\n";
                return false;
            }

            //Controllo se trovo la torre durante il ciclo:
            if
            (
                fen_shared.get()->get_piece()[position_king+i]->is_rock()
                &&
                fen_shared.get()->get_piece()[position_king+i]->get_color()==king->get_color()
            )
            {
                //Trovo la torre, me la memorizzo in un puntatore creato sul momento
                Piece* rock = fen_shared.get()->get_piece()[position_king+i];
                
                //Controllo se la torre si è mossa:
                if(rock->get_ismoved())
                {
                    //std::cout<<"is_castling_dx: 2\n";

                    return false;
                }
                else
                {   
                    //Controllo se nelle 2 caselle successive al re c'era qualcosa:
                    if
                    (
                        !fen_shared.get()->get_piece()[position_king+1]
                        &&
                        !fen_shared.get()->get_piece()[position_king+2]
                    )
                    {
                        for(int i = 1; i<3; i++)
                        {
                            if
                            (
                                check_shared.get()->handle_check_on_king_straight
                                (
                                    king->get_square()+i,
                                    fen_shared.get()->get_piece(),
                                    turn_chess_ptr->get_turn()
                                )
                                ||
                                check_shared.get()->handle_check_on_king_knight
                                (
                                    king->get_square()+i,
                                    fen_shared.get()->get_piece(),
                                    turn_chess_ptr->get_turn()
                                )
                                ||
                                check_shared.get()->handle_check_on_king_diagonal
                                (
                                    king->get_square()+i,
                                    fen_shared.get()->get_piece(),
                                    turn_chess_ptr->get_turn()
                                )
                            )
                            {
                                fen_shared.get()->set_short_castling(true);
                                //std::cout<<"is_castling_dx: 3\n";
                                return false;
                            }
                        }
                        king->add_legal_move(position_king+2);
                        fen_shared.get()->set_short_castling(true);
                        //std::cout<<"is_castling_dx: 4\n";
                        return true;
                    }
                    //In una delle due caselle successive alla casella del re c'era qualcosa
                    //non aggiungo la mossa per arroccare, ma comunque arrocco possibile
                    else
                    {
                        fen_shared.get()->set_short_castling(true);
                        //std::cout<<"is_castling_dx: 5\n";
                        return false;
                    }       
                }                    
            }
            //Non ho trovato la torre, continuo la ricerca
            else
            {
                //std::cout<<"is_castling_dx: 6\n";
                continue;
            }                
        }
        //Non c'è niente sulla casella successiva 
        else
        {
            //std::cout<<"is_castling_dx: 7\n";
            continue;
        } 
    }    
    //Non ho trovato niente, ritorno false
    //std::cout<<"ciao da fine is_castling_dx\n";
    return false;
}

bool Castling::is_castling_sx()
{
    
    //Trovo il re sulla scacchiera con find_king
    Piece *king = find_king_shared.get()->find_king_current_turn
    (
        fen_shared.get()->get_piece(),
        turn_chess_ptr->get_turn()
    );

    //std::cout<<"is_castling_sx: dopo ricerca re\n";
    //Se il re si è mosso esci
    if(king->get_ismoved())
    {
        //std::cout<<"is_castling_sx: 1\n";
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
            //std::cout<<"is_castling_sx: 2\n";
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
                    //std::cout<<"is_castling_sx: 3\n";
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
                                check_shared.get()->handle_check_on_king_straight
                                (
                                    king->get_square()-i,
                                    fen_shared.get()->get_piece(),
                                    turn_chess_ptr->get_turn()
                                )
                                ||
                                check_shared.get()->handle_check_on_king_knight
                                (
                                    king->get_square()-i,
                                    fen_shared.get()->get_piece(),
                                    turn_chess_ptr->get_turn()
                                )
                                ||
                                check_shared.get()->handle_check_on_king_diagonal
                                (
                                    king->get_square()-i,
                                    fen_shared.get()->get_piece(),
                                    turn_chess_ptr->get_turn()
                                )
                            )
                            {
                                fen_shared.get()->set_long_castling(true);
                                //std::cout<<"is_castling_sx: 4\n";
                                return true;
                            }

                        }
                        king->add_legal_move(position_king-2);
                        fen_shared.get()->set_long_castling(true);
                        //std::cout<<"is_castling_sx: 5\n";
                        return true;
                    }
                    //In una delle due caselle successive alla casella del re c'era qualcosa
                    //non aggiungo la mossa per arroccare, ma comunque arrocco possibile
                    else
                    {
                        fen_shared.get()->set_long_castling(true);
                        //std::cout<<"is_castling_sx: 6\n";
                        return true;
                    }       
                }                    
            }
            else
            {
                //std::cout<<"is_castling_sx: 7\n";
                continue;
            }                
        }
        //Non c'è niente sulla casella successiva 
        else
        {
            //std::cout<<"is_castling_sx: 8\n";
            continue;
        }   
    }
    //std::cout<<"is_castling_sx: 9\n";
    return false;
}

bool Castling::handle_castling_dx()
{
    if(movement_ptr->get_stack().size()==0)
    {
        return false;
    }
    int position_rook=0;
    
    // Ottieni l'ultima mossa:
    Move last_move = movement_ptr->get_stack().top();


    // Se l'ultima mossa associata al pezzo non è il re, esci...
    if
    (
        last_move.get_type_piece()!=KING
    )
    {
        return false;
    }

    // Se l'ultima mossa non è un doppio salto in avanti, esci...
    if 
    (
        (last_move.get_to_square() - last_move.get_from_square()) != 2 
    ) 
    {
        return false;
    }

    if(last_move.get_color_piece()==WHITE)
    {
        position_rook = 63;
    }
    else
    {
        position_rook = 7;
    }

    //Gestisci il movimento della torre!
    if(fen_shared.get()->get_piece()[position_rook])
    {        
        fen_shared.get()->get_piece()[position_rook-2] = fen_shared.get()->get_piece()[position_rook];
        fen_shared.get()->get_piece()[position_rook]=nullptr;
        wxLogMessage(wxT("Ho fatto l'arrocco dx da Castling!"));
        return true;        
    }
    else
    {
        return false;
    }
}

bool Castling::handle_castling_sx()
{
    // Ottieni l'ultima mossa:
    Move last_move = movement_ptr->get_stack().top();

    if(movement_ptr->get_stack().size()==0)
    {
        return false;
    }

    int position_rook=0;

    // Se l'ultima mossa associata al pezzo non è il re, esci...
    //if (!last_move.get_piece_status()->is_king())
    if(last_move.get_type_piece()!=KING)
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

    if(last_move.get_color_piece()==WHITE)
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
        wxLogMessage(wxT("Ho fatto l'arrocco sx da Castling!"));       
        return true;        
    }
    else
    {
        return false;
    }
}