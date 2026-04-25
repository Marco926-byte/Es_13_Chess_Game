#include "Check.h"

Check::Check()
{
    
}

std::vector<int> Check::get_v_check_attack() const
{
    return v_check_attack;
}

bool Check::handle_check_on_king_diagonal
(
    int position_king,
    Piece **board, 
    Color current_player_color
)
{
    //posizioni delle quattro diagonali della cella avanzato di 1 insomma   
    int diagonal[4]{-9,-7,7,9};

    int row_for_check = position_king/8;
    int col_for_check = position_king%8;

    //posizione delle quattro diagonali della cella in totale
    int end_board_diagonal[4]
    {
        std::min(row_for_check, col_for_check),
        std::min(row_for_check,7-col_for_check),
        std::min(7-row_for_check, col_for_check),
        std::min(7-row_for_check,7-col_for_check)        
    };

    //parte la vista del re in diagonale:
    for(int i=0; i<4; i++)//da correggere....
    {
        int current_move = position_king;
        int diagonal_attack = position_king;
        
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
                    std::cout<<"Metto in v_check_attack: "<<diagonal_attack<<std::endl;
                    v_check_attack.push_back(diagonal_attack);
                }
                return true;
            }   
        }
    }
    return false;
}

bool Check::handle_check_on_king_straight(int position_king,Piece **board, Color current_player_color)
{
    //Singolo spostamento dritto
    int single_straight[4]={-8,8,-1,1};

    int row_for_check = position_king/8;
    int col_for_check = position_king%8;

    //Spostamento dritto fino alla fine della scacchiera
    int end_board_straight[4] =
    {
        row_for_check,
        7-row_for_check,
        col_for_check,
        7-col_for_check
    };

    for(int i =0; i<4; i++)
    {
        int current_move = position_king;     //Resetto la mossa ipotetica
        int straight_attack = position_king;  //Resetto straight attack
                                                       //da modificare probabilmente
        for(int j=0; j<end_board_straight[i]; j++)
        {
            current_move+=single_straight[i];

            //Non deve uscire dai numeri della scacchiera
            if(current_move<0 || current_move>64)
            {
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

bool Check::handle_check_on_king_knight(int position_king,Piece **board, Color current_player_color)
{
    //Le direzioni che può fare il cavallo:
    int directions[8]={17,15,10,-6,6,-10,-15,-17};
    
    int row_for_check = position_king/8;
    int col_for_check = position_king%8;

    //ciclo per ogni direzione del cavallo, voglio trovare il cavallo:
    for(int i=0; i<8; i++)
    {
        //current_move si dovrà resettare ogni volta a inizio ciclo 
        //per cambiare la direzione
        int current_move = position_king;
        
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
                abs(col_for_check - current_move %8)<3  
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