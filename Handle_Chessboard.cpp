#include "Handle_Chessboard.h"

//Costruttore:
Handle_Chessboard::Handle_Chessboard
(
    Draw_board * board,
    std::shared_ptr<Handle_Fen_String>fen
)
    :draw_class(board),
    handler_fen(fen)
    {
        turn=WHITE;
        
    }

Color Handle_Chessboard::get_turn()
{
    return turn;
}

void Handle_Chessboard::change_turn()
{
    if(turn==WHITE)
        set_turn(BLACK);
    else
        set_turn(WHITE);
}

void Handle_Chessboard::set_turn(Color t)
{
    turn=t;
}

std::vector<Piece*> Handle_Chessboard::get_piece_turn()
{
    std::vector<Piece*> piece_turn={};
    for
    (
        auto itr= handler_fen.get()->get_piece()[0];
        itr!= handler_fen.get()->get_piece()[64]; 
        ++itr
    )
    {
        if(itr->get_color()==get_turn())
        {
            piece_turn.push_back(itr);
        }
    }
    return piece_turn;
}

std::vector<Piece*> Handle_Chessboard::get_no_piece_turn()
{
    std::vector<Piece*> piece_no_turn={};
    for
    (
        auto itr= handler_fen.get()->get_piece()[0];
        itr!= handler_fen.get()->get_piece()[64]; 
        ++itr
    )
    if(itr->get_color()!=get_turn())
    {
        piece_no_turn.push_back(itr);
    }
    return piece_no_turn;
}

std::vector<int> Handle_Chessboard::get_v_check_attack()
{
    return v_check_attack;
}

void Handle_Chessboard::clear_v_check_attack()
{
    v_check_attack.clear();
}

Piece* Handle_Chessboard::find_king(Piece** board, Color color_to_find)
{
    for (int i = 0; i < 64; i++) 
    {
        if 
        (
            board[i] != nullptr && 
            board[i]->is_king() && 
            board[i]->get_color() == color_to_find
        ) 
        {
            return board[i];
        }
    }
    return nullptr;
}

bool Handle_Chessboard::handle_check_on_king_straight(Piece **board, Color current_player_color)
{
    Piece *ptr_king=find_king(board,current_player_color);
    
    //Singolo spostamento dritto
    int single_straight[4]={-8,8,-1,1};

    if(!ptr_king)
    {
        //Problema: ptr_king è nullptr
        return false;
    }

    //Spostamento dritto fino alla fine della scacchiera
    int end_board_straight[4] =
    {
        ptr_king->get_row(),
        7-ptr_king->get_row(),
        ptr_king->get_col(),
        7-ptr_king->get_col()
    };

    for(int i =0; i<4; i++)
    {
        int current_move = ptr_king->get_square();     //Resetto la mossa ipotetica
        int straight_attack = ptr_king->get_square();  //Resetto straight attack
                                                       //da modificare probabilmente
        for(int j=0; j<end_board_straight[i]; j++)
        {
            current_move+=single_straight[i];

            //Non deve uscire dai numeri della scacchiera
            if(current_move<0 || current_move>64)
            {
                //wxLogMessage(wxT("Oioia, sono uscito dalla scacchiera"));
                continue;
            }

            //Se durante il percorso trovo un mio stesso pezzo, esci
            if
            (
                   board[current_move]
                && board[current_move]->get_color()==current_player_color
            )
            {
                break;
            }

            
            //Se durante il percorso trovo la regina o l'alfiere, devo ottenere questo percorso
            if
            (   
                board[current_move]
                && 
                board[current_move]->get_name_piece()=='r'
                ||
                board[current_move]
                &&
                board[current_move]->get_name_piece()=='R'
                || 
                board[current_move]
                && 
                board[current_move]->get_name_piece()=='q'
                ||
                board[current_move]
                &&
                board[current_move]->get_name_piece()=='Q'
            ) 
            {
                for(int k =0; k<=j; k++)
                {
                    straight_attack+=single_straight[i];
                    v_check_attack.push_back(straight_attack);
                }
                return true;
            }   
        }       
    }
    return false;
}

bool Handle_Chessboard::handle_check_on_king_diagonal(Piece **board, Color current_player_color)
{
    //posizioni delle quattro diagonali della cella avanzato di 1 insomma   
    int diagonal[4]{-9,-7,7,9};

    Piece *ptr_king=find_king(board,current_player_color);

    if(!ptr_king)
    {
        //Problema, ptr_king è nullo
        return false;
    }

    //posizione delle quattro diagonali della cella in totale
    int end_board_diagonal[4]
    {
        std::min(ptr_king->get_row(),ptr_king->get_col()),
        std::min(ptr_king->get_row(),7-ptr_king->get_col()),
        std::min(7-ptr_king->get_row(),ptr_king->get_col()),
        std::min(7-ptr_king->get_row(),7-ptr_king->get_col())        
    };

    //parte la vista del re in diagonale:
    for(int i=0; i<4; i++)//da correggere....
    {
        int current_move = ptr_king->get_square();
        int diagonal_attack = ptr_king->get_square();
        
        for(int j=0; j<end_board_diagonal[i]; j++)
        {   
            current_move+=diagonal[i];
            
            //Non deve uscire dai numeri della scacchiera
            if(current_move<0 || current_move>64)
            {
                continue;
            }

            if(!board[current_move])
            {
                continue;
            }

            //Se durante il percorso trovo un mio stesso pezzo, esci
            if
            (
                   board[current_move]
                   && 
                   board[current_move]->get_color()==current_player_color
            )
            {
                break;
            }
            if
            (   
                j==0
                &&
                board[current_move]->is_pawn()
            )
            {
                std::cout<<"Il pedone mi sta attaccando il re...\n";
                std::cout<<"Pedone che attacca: "<<board[current_move]->get_square()<<std::endl;

                v_check_attack.push_back(board[current_move]->get_square());
                return true;
            }
            
            //Se durante il percorso trovo la regina o l'alfiere, devo ottenere questo percorso
            if
            (   
                board[current_move]->get_name_piece()=='B'
                ||
                board[current_move]->get_name_piece()=='b'
                ||
                board[current_move]->get_name_piece()=='Q'
                ||
                board[current_move]->get_name_piece()=='q'
            ) 
            {
                for(int k =0; k<=j; k++)
                {
                    diagonal_attack+=diagonal[i];
                    v_check_attack.push_back(diagonal_attack);
                }
                return true;
            }   
        }
    }
    return false;
}

bool Handle_Chessboard::handle_check_on_king_knight(Piece **board, Color current_player_color)
{
    //Le direzioni che può fare il cavallo:
    int directions[8]={17,15,10,-6,6,-10,-15,-17};
    
    //Trovo il re del turno corrente....
    Piece *ptr_king=find_king(board,current_player_color);
    
    if(!ptr_king)
    {
        //Problema, ptr_king è nullo
        return false;
    } 
    
    //ciclo per ogni direzione del cavallo, voglio trovare il cavallo:
    for(int i=0; i<8; i++)
    {
        //current_move si dovrà resettare ogni volta a inizio ciclo 
        //per cambiare la direzione
        int current_move = ptr_king->get_square();
        
        //incremento la mossa con la direzione del ciclo
        current_move +=directions[i];
        
        //Controlli:
        if(current_move<0 || current_move>=64)
        {
           continue;
        }
            
        //Controlli:
        if(!board[current_move])
        {
            continue;
        }
        //IF IMPORTANTE: quello che decide se trovo o no il cavallo:
        if
        (  
            (
                board[current_move]->get_name_piece()=='N'
                ||
                board[current_move]->get_name_piece()=='n'
            )
            && 
            (
                abs(ptr_king->get_col() - current_move %8)<3  
                &&
                board[current_move]->get_color()!=current_player_color
            )
        )
        {
            //voglio che la casella che attacca il re venga aggiunta al vettore attack
            v_check_attack.push_back(board[current_move]->get_square());
            return true;
        }
    }
    return false;
}

bool Handle_Chessboard::handle_pin_on_king_straight(Piece **board, Color current_player_color)
{
    //Inizializzo il puntatore al re del turno corrente
    Piece *ptr_king =find_king(board,current_player_color);

    //Inizializzo il vettore dei pezzi amici a zero
    std::vector<Piece*> v_piece_friend={};

    //Singolo spostamento dritto
    int single_straight[4]={-8,8,-1,1};

    if(!ptr_king)
    {
        //Problema: ptr_king è nullptr
        return false;
    }

    //Spostamento dritto fino alla fine della scacchiera
    int end_board_straight[4] =
    {
        ptr_king->get_row(),
        7-ptr_king->get_row(),
        ptr_king->get_col(),
        7-ptr_king->get_col()
    };

    for(int i = 0; i < 4; i++)
    {
        int current_move = ptr_king->get_square();     //Resetto la mossa ipotetica
         
        //Pulisco il vettore amico...
        v_piece_friend.clear();
        
        for(int j=0; j<end_board_straight[i]; j++)
        {
            current_move+=single_straight[i];

            //Non deve uscire dai numeri della scacchiera
            if(current_move<0 || current_move>64)
            {        
                continue;
            }

            //Se durante il percorso trovo un mio stesso pezzo, inseriscilo nel vettore amico
            if
            (
                board[current_move]
                && 
                board[current_move]->get_color()==current_player_color
            )
            {
                v_piece_friend.push_back(board[current_move]);
            }

            //Se durante il percorso trovo la regina o la torre, devo aggiornare le mosse
            //per il pezzo amico 
            if
            (   
                board[current_move]
                && 
                board[current_move]->is_queen()
                &&
                board[current_move]->get_color()!=current_player_color
                ||
                board[current_move]
                &&
                board[current_move]->is_rock()
                &&
                board[current_move]->get_color()!=current_player_color
            ) 
            {
                if(v_piece_friend.size()==1)
                {
                    //Okay ho il pezzo amico, ora devo simulare le mosse e registrare solamente le mosse
                    //che coprono il re, le altre le devo cancellare
                    for(auto itr : v_piece_friend)
                    {                   
                        for(int move : itr->get_legal_moves())
                        {
                            //Devo simulare le mosse....
                            int original_square = itr->get_square();

                            Piece *original_piece = board[move];    
                                //original_piece serve perchè se io durante la simulazione trovo un pezzo
                                //il pezzo per la strada non potrà essere nullptr sennò segfault :)

                            //Temporaneamente muovo il pezzo e simulo...
                            board[move]= itr;
                            board[original_square] = nullptr;
                            itr->set_square(move);

                            if(handle_check_on_king_straight(board,current_player_color))
                            {
                                itr->remove_legal_move(move);                                
                            }

                            //Reimposta la posizione originale....
                            board[original_square] = itr;
                            board[move]= original_piece;

                            itr->set_square(original_square);
                        }
                    }
                    return true;
                }      
            }   
        }       
    }
    return false;
}

bool Handle_Chessboard::handle_pin_on_king_diagonal(Piece **board, Color current_player_color)
{
    //posizioni delle quattro diagonali della cella avanzato di 1 insomma   
    int diagonal[4]{-9,-7,7,9};

    Piece *ptr_king=find_king(board,current_player_color);
    
    std::vector<Piece*> v_piece_friend={};
    

    if(!ptr_king)
    {
        //Problema, ptr_king è nullo
        return false;
    }

    //posizione delle quattro diagonali della cella in totale
    int end_board_diagonal[4]
    {
        std::min(ptr_king->get_row(),ptr_king->get_col()),
        std::min(ptr_king->get_row(),7-ptr_king->get_col()),
        std::min(7-ptr_king->get_row(),ptr_king->get_col()),
        std::min(7-ptr_king->get_row(),7-ptr_king->get_col())        
    };

    v_piece_friend.clear();

    //parte la vista del re in diagonale:
    for(int i=0; i<4; i++)
    {

        int current_move = ptr_king->get_square();     //Resetto la mossa ipotetica

        for(int j=0; j<end_board_diagonal[i]; j++)
        {   
            current_move+=diagonal[i];
            
            //Non deve uscire dai numeri della scacchiera
            if(current_move<0 || current_move>64)
            {
                continue;
            }

            if(!board[current_move])
            {
                continue;
            }

            //Se durante il percorso trovo un mio stesso pezzo, inseriscilo nel vettore amico
            if
            (
                board[current_move]
                && 
                board[current_move]->get_color()==current_player_color
            )
            {
                v_piece_friend.push_back(board[current_move]);
            }
            
            if
            (
                board[current_move]
                &&
                board[current_move]->is_bishop()
                &&
                board[current_move]->get_color()!=current_player_color
                ||
                board[current_move]
                &&
                board[current_move]->is_queen()
                &&
                board[current_move]->get_color()!=current_player_color
            )           
            {
                if(v_piece_friend.size()==1)
                {
                    //Okay ho il pezzo amico, ora devo simulare le mosse e registrare solamente le mosse
                    //che coprono il re, le altre le devo cancellare

                    for(auto itr : v_piece_friend)
                    {
                        for(int move : itr->get_legal_moves())
                        {
                            //Devo simulare le mosse....
                            int original_square = itr->get_square();
                            Piece *original_piece = board[move];

                            //Temporaneamente muovo il pezzo e simulo...
                            board[move]= itr;
                            board[original_square] = nullptr;
                            itr->set_square(move);

                            if(handle_check_on_king_diagonal(board,current_player_color))
                            {
                                itr->remove_legal_move(move);                                
                            }

                            //Reimposta la posizione originale....
                            board[original_square] = itr;
                            board[move]= original_piece;
                            itr->set_square(original_square);
                        }
                    }
                    return true;
                }
                else
                {
                    return false;
                }
                
            }
        }
    }
    return false;

}

void Handle_Chessboard::print_v_check_attack()
{
    std::cout<<"---------------\n";
    std::cout<<"Dentro v_check_attack: \n";

    for(auto itr : v_check_attack)
    {
        std::cout<<itr<<std::endl;
    }
}