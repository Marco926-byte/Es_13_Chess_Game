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
     turn_chess_shared(turn_chess),
     find_king_shared(find_king)
{
    
}

bool Castling::is_castling_dx()
{
    
    //Trovo il re sulla scacchiera con find_king
    Piece *king = find_king_shared.get()->find_king_current_turn(fen_shared.get()->get_piece(),turn_chess_shared.get()->get_turn());
    
    //Se il re si è mosso esci
    if(king->get_ismoved())
    {
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
            return false;
        }
        
        //Controllo se sulla casella successiva c'è qualcosa
        if(fen_shared.get()->get_piece()[position_king+i])
        {        
            //Controllo se trovo la torre durante il ciclo:
            if(fen_shared.get()->get_piece()[position_king+i]->is_rock())
            {
                //Trovo la torre, me la memorizzo in un puntatore creato sul momento
                Piece* rock = fen_shared.get()->get_piece()[position_king+i];
                
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
                                    turn_chess_shared.get()->get_turn()
                                )
                                ||
                                check_shared.get()->handle_check_on_king_knight
                                (
                                    king->get_square()+i,
                                    fen_shared.get()->get_piece(),
                                    turn_chess_shared.get()->get_turn()
                                )
                                ||
                                check_shared.get()->handle_check_on_king_diagonal
                                (
                                    king->get_square()+i,
                                    fen_shared.get()->get_piece(),
                                    turn_chess_shared.get()->get_turn()
                                )
                            )
                            {
                                return true;
                            }

                        }
                        king->add_legal_move(position_king+2);
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
            //Non ho trovato la torre, continuo la ricerca
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
    //Non ho trovato niente, ritorno false
    return false;
    
   return false;
}

bool Castling::is_castling_sx()
{
    
    //Trovo il re sulla scacchiera con find_king
    Piece *king = find_king_shared.get()->find_king_current_turn
    (
        fen_shared.get()->get_piece(),
        turn_chess_shared.get()->get_turn()
    );

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
                                check_shared.get()->handle_check_on_king_straight
                                (
                                    king->get_square()-i,
                                    fen_shared.get()->get_piece(),
                                    turn_chess_shared.get()->get_turn()
                                )
                                ||
                                check_shared.get()->handle_check_on_king_knight
                                (
                                    king->get_square()-i,
                                    fen_shared.get()->get_piece(),
                                    turn_chess_shared.get()->get_turn()
                                )
                                ||
                                check_shared.get()->handle_check_on_king_diagonal
                                (
                                    king->get_square()-i,
                                    fen_shared.get()->get_piece(),
                                    turn_chess_shared.get()->get_turn()
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
    
   return false;
}

bool Castling::handle_castling_dx()
{
    int position_rook=0;
    
    // Ottieni l'ultima mossa:
    Move last_move = movement_ptr->get_stack().top();

    // Se l'ultima mossa associata al pezzo non è il re, esci...
    if (!last_move.get_piece_status()->is_king())
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

    if(last_move.get_piece_status()->get_color()==WHITE)
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
        wxLogMessage(wxT("Ho fatto l'arrocco sx da Castling!"));       
        return true;        
    }
    else
    {
        return false;
    }
}