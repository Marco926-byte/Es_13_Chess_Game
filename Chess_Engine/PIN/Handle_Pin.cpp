#include "Handle_Pin.h"

Handle_Pin::Handle_Pin
(
    std::shared_ptr<Find_King> find_king,
    std::shared_ptr<Check> check
)
    :find_king_shared(find_king),
    check_shared(check)
{
    
}

bool Handle_Pin::handle_pin_on_king_straight
(
    Piece **board, 
    Color current_player_color
)
{
    //Inizializzo il puntatore al re del turno corrente
    Piece *ptr_king =find_king_shared.get()->find_king_current_turn(board,current_player_color);

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

                            if(check_shared.get()->handle_check_on_king_straight(move,board,current_player_color))
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

bool Handle_Pin::handle_pin_on_king_diagonal
(
    Piece **board,
    Color current_player_color
)
{
    //posizioni delle quattro diagonali della cella avanzato di 1 insomma   
    int diagonal[4]{-9,-7,7,9};

    Piece *ptr_king=find_king_shared.get()->find_king_current_turn(board,current_player_color);

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

                            if(check_shared.get()->handle_check_on_king_diagonal(move,board,current_player_color))
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