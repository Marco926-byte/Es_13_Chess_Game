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
            //wxLogMessage(wxT("Ho trovato il re, è nella casella: [%d]"),board[i]->get_square());
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
                break;
            }

            //Se durante il percorso trovo un mio stesso pezzo, esci
            if
            (
                   board[current_move]
                && board[current_move]->get_color()==current_player_color
            )
            {
                //wxLogMessage(wxT("Ho trovato un pezzo amico, esco dal ciclo"));               
                break;
            }

            //Se durante il percorso trovo la regina o l'alfiere, devo ottenere questo percorso
            if
            (      board[current_move]
                && board[current_move]->is_rock()
                || board[current_move]
                && board[current_move]->is_queen()
            ) 
            {
                wxLogMessage(wxT("Ho trovato la regina o l'alfiere"));
                
                //Sono indeciso se ripartire da capo = costoso oppure ci deve essere un
                //altro modo
                for(int k =0; k<end_board_straight[i]; k++)
                {
                    straight_attack+=single_straight[k];
                    wxLogMessage(wxT("straight_attack dentro ciclo finale: %d"),straight_attack);
                    v_check_attack.push_back(straight_attack);
                }
                return true;
            }   
        }       
    }
    return false;
}
/*
bool Handle_Chessboard::handle_check_on_king_diagonal(Piece **board, Color current_player_color)
{
    //posizioni delle quattro diagonali della cella avanzato di 1 insomma   
    /*int diagonal[4]{-9,-7,7,9};

    Piece *ptr_king=find_king(board,current_player_color);

    if(!ptr_king)
    {
        //Problema, ptr_king è nullo
        return false;
    }

    //posizione delle quattro diagonali della cella in totale
    int end_board_diagonal[4]
    {
        /*std::min(this->row,this->coloum),
        std::min(this->row,7-this->coloum),
        std::min(7-this->row,this->coloum),
        std::min(7-this->row,7-this->coloum),*/
        
    //};

    //parte la vista del re in diagonale:
    /*for(auto i:diagonal)
    {
        int current_move = ptr_king->get_square();
        int diagonal_attack = ptr_king->get_square();

        for(int j=0; j<end_board_straight[i]; j++)
        {
            current_move+=diagonal[i];
            
            //Non deve uscire dai numeri della scacchiera
            if(current_move<0 || current_move>64)
            {
                //wxLogMessage(wxT("current move è uscito dal range del legale"));
                break;
            }

            //Se durante il percorso trovo un mio stesso pezzo, esci
            if
            (
                   board[current_move]!= nullptr 
                && board[current_move]->get_color()==current_player_color
            )
            {
                break;
            }
            //Per controllare lo scacco del pedone devo accertarmi che sono nella prima 
            //casella diagonale
            if
            (
                i==0 
                && board[current_move]!=nullptr
                && board[current_move]->is_pawn()
            )
            {
                diagonal_attack+=diagonal[i];
                v_check_attack.push_back(diagonal_attack);
                return true;
            }
            //Se durante il percorso trovo la regina o l'alfiere, devo ottenere questo percorso
            if
            (      board[current_move]!=nullptr
                && board[current_move]->is_bishop()
                || board[current_move]
                && board[current_move]->is_queen()
            ) 
            {
                //Sono indeciso se ripartire da capo = costoso oppure ci deve essere un
                //altro modo
                for(int k =0; k<end_board_straight[i]; k++)
                {
                    diagonal_attack+=diagonal[k];
                    v_check_attack.push_back(diagonal_attack);
                }
                return true;
            }   
        }
    }
    return false;

 */
