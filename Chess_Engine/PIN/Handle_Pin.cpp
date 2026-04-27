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
    std::cout<<"-------INIZIO PIN STRAIGHT --------\n";
    //Inizializzo il puntatore al re del turno corrente
    Piece *ptr_king =find_king_shared.get()->find_king_current_turn
    (
        board,
        current_player_color
    );

    std::cout<<"Il re si trova nella posizione: "<<ptr_king->get_square()<<std::endl;

    //Inizializzo il vettore dei pezzi amici a zero
    std::vector<Piece*> v_piece_friend={};

    //Singolo spostamento dritto
    int single_straight[4]={-8,8,-1,1};

    if(!ptr_king)
    {
        //Problema: ptr_king è nullptr
        std::cout<<"ptr_king è nullptr\n";
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

    std::cout<<"- Inizio il ciclo for -\n";
    for(int i = 0; i < 4; i++)
    {
        int current_move = ptr_king->get_square();     //Resetto la mossa ipotetica
        
        std::cout<<"i: "<<i<<std::endl;
        std::cout<<"current_move: "<<current_move<<std::endl;

        std::cout<<"pulisco il vettore amico...\n";

        //Pulisco il vettore amico...
        v_piece_friend.clear();
        
        std::cout<<"end_board_straight["<<i<<"]"<<" : "<<end_board_straight[i]<<std::endl;
        
        std::cout<<"- Inizio secondo for -\n";

        for(int j=0; j<end_board_straight[i]; j++)
        {
            std::cout<<"j : "<<j<<std::endl;

            current_move+=single_straight[i];
            std::cout<<"current_move: "<<current_move<<std::endl;

            //Non deve uscire dai numeri della scacchiera
            if(current_move<0 || current_move>64)
            {
                std::cout<<"current_move è uscito dalla scacchiera! continuo il ciclo\n";        
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
                std::cout<<"In : "<<current_move<<" c'è un pezzo amico! Lo inserisco nel vettore amico\n";
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
                std::cout<<"In : "<<current_move<<" c'è la regina o la torre!/n";
                
                if(v_piece_friend.size()==1)
                {
                    std::cout<<"Il vettore amico contiene un solo carattere\n";

                    //Okay ho il pezzo amico, ora devo simulare le mosse e registrare solamente le mosse
                    //che coprono il re, le altre le devo cancellare
                    
                    std::cout<<"Parte la simulazione...\n";
                    for(auto itr : v_piece_friend)
                    {                   
                        std::cout<<"itr nome pezzo: "<<itr->get_name_piece()<<std::endl;
                        std::cout<<"Itero le mosse legali per il pezzo di nome: "<<itr->get_name_piece()<<std::endl;

                        for(int move : itr->get_legal_moves())
                        {
                            std::cout<<"Mossa legale: "<<move<<std::endl;

                            //Devo simulare le mosse....
                            int original_square = itr->get_square();

                            std::cout<<"Casella originale: "<<original_square<<std::endl;

                            Piece *original_piece = board[move];    
                                //original_piece serve perchè se io durante la simulazione trovo un pezzo
                                //il pezzo per la strada non potrà essere nullptr sennò segfault :)

                            //Temporaneamente muovo il pezzo e simulo...
                            board[move]= itr;
                            std::cout<<"Nella casella: "<<move<<" ora c'è il pezzo: "<<board[move]->get_name_piece()<<std::endl;
                            
                            board[original_square] = nullptr;
                            
                            if(!board[original_square])
                            {
                                std::cout<<"Momentaneamente nella casella originaria non c'è niente\n";
                            }

                            itr->set_square(move);

                            if(check_shared.get()->handle_check_on_king_straight(ptr_king->get_square(),board,current_player_color))
                            {
                                std::cout<<"mossa non va bene perchè sennò scacco al re, rimuovo la mossa: "<<move<<" dalle mosse legali\n";
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

                            if(check_shared.get()->handle_check_on_king_diagonal(ptr_king->get_square(),board,current_player_color))
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