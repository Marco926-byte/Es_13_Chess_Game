#include "King.h"

//Costruttore
King::King(int position, char character)
    :Piece(position,character)
    {

    }

//Getter
bool King::get_is_check() const
{
    return is_check;
}

//Funzione virtuale
void King::update_legal_moves(Piece*board[64])
{
    std::vector<int> legal_moves={};

}


//Funzione del movimento del re
void King::handle_movement(Piece*board[64], std::vector<int> legal_moves)
{
    int direction[8]={8,7,9,1,-1,-7,-8,-9};
    

    for(int i=0; i<8; i++)
    {
        int square=this->get_square()+direction[i];

        if(square>=0 && square<64 && abs(this->get_col()-square %8)<=1)
        {
            if(board[square]==nullptr)
            {
                legal_moves.push_back(square);
            }
            else if(board[square]->get_color()!=this->get_color())
            {
                legal_moves.push_back(square);
            }
        }
    }
}

void King::handle_arrok(Piece*board[64], int rook_position, std::vector<Piece*>& piece_attacking)
{
    //Se il re è sotto scacco non puoi arroccare:
    if(this->get_is_check())
    {
        return;
    }

    //Se la torre non è nella posizione rook_position esci:
    if(board[rook_position]==nullptr)
    {
        return;
    }

    //Se un pezzo diverso dalla torre è nella posizione rook_position esci:
    if(!board[rook_position]->is_rock())
    {
        return;
    }

    //Se la torre nella posizione rook_position si è spostata esci:
    if(board[rook_position]->get_ismoved())
    {
        return;
    }

    //Se la torre nella posizione rook_position ha un colore diverso dal re esci:
    if(board[rook_position]->get_color()!=this->get_color())
    {
        return;
    }

    int direction= rook_position>this->get_square() ? 1 : -1;
    int start= this->get_square()+direction;
    int end= rook_position;

    //Controllo se nel percorso esiste qualche pezzo nell'arrocco, se si esci
    for(int square=start; square!=end; square +=direction)
    {
        if(board[square]!=nullptr)
        {
            return;
        }
        //Controllo se il re si è mosso tramite arrocco:

    }

}

bool King::is_attack(Piece *board[64], 
                     std::vector<Piece *> &pieces, 
                     std::vector<Piece *> &pieces_attacking_king)
{
    //Controllo pezzi che attaccano il re:
    for(Piece* piece: pieces)
    {
        for(int square : piece->get_legal_moves())
        {
            if(square==this->get_square())
            {
                pieces_attacking_king.push_back(piece);
                this->is_check=true;
                return true;
            }
        }
    }
    //Se non c'è nessun pezzo allora nulla...
    pieces_attacking_king={};
    this->is_check=false;
    return false;
}

bool King::handle_king_move_check(Piece *board[64],
                                  int to_square,
                                  std::vector<Piece*> pieces_attacking_king)
    {
    
        std::vector<Piece*> piece={}; //Creo questo a zero perchè ci devo inserire
                                  //tutti i pezzi presenti nella scacchiera

        //Devo ottenere tutti i pezzi sulla scacchiera:
        for(int i=0; i<64; i++)
        {
            if(board[i]->get_color()!=this->get_color() && board[i]!=nullptr)
            {
                piece.push_back(board[i]);
            }
        }

        int original_square= this->get_square();

        //Controllo se il re è sotto scacco nella direzione scelta:
        board[to_square]=this;
        board[original_square]=nullptr;
        this->set_square(to_square);        

        //Controllo dello scacco:
        bool is_check= this->is_attack(board,piece,pieces_attacking_king);

        //Resetto tutto:
        board[original_square]=this;
        board[to_square]=nullptr;
        this->set_square(original_square);

        return is_check;

    }
