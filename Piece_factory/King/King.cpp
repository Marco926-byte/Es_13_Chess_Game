#include "King.h"
#include "../../Chess_Engine/FEN/Handle_Fen_String.h"

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
void King::update_legal_moves(std::shared_ptr<Handle_Fen_String> ptr_smart)
{
    std::vector<int> legal_moves_candidate={};
    std::vector<int> final_safe_moves={};
    
    const auto &piece=ptr_smart.get()->get_piece();

    //Prendo le mosse:
    handle_movement(piece,legal_moves_candidate);

    //Utilizzo la funzione handle_check_king per filtrare le vere mosse che può fare:
    for(int move : legal_moves_candidate)
    {
        std::vector<Piece*> attacking;
     
        //Se handle_king_move_check non restituisce true allora in quella casella è 
        //tranquilla
        if(!handle_king_move_check(piece,move,attacking))
        {
            final_safe_moves.push_back(move);
        }
    }
    
    this->set_legal_moves(final_safe_moves);
}


//Funzione del movimento del re
void King::handle_movement(Piece**board, std::vector<int> &legal_moves)
{
    int direction[8]={-8,8,-1,1,-9,-7,7,9};
    
    attacked_square_total={};
    
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
            //attacked_square_total.push_back(square);
        }
    }
}

void King::handle_arrok(Piece**board, int rook_position, std::vector<Piece*>& piece_attacking)
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

bool King::is_attack
(
    Piece **board, 
    std::vector<Piece *> &pieces, 
    std::vector<Piece *> &pieces_attacking_king
)
{
    //Questa funzione viene chiamata per non far suicidare il Re
    this->is_under_attack=false;
    pieces_attacking_king.clear();

    //Controllo pezzi che attaccano il re:
    for(Piece* enemy: pieces)
    {
        std::vector<int> attacks;
        enemy->get_attack(board,attacks);   //Funziona perchè ho messo la funzione virtuale
        //handle_movement(board,attacks);       //in Piece
        
        for(int square : attacks )
        {
            if(square==this->get_square())
            {
                pieces_attacking_king.push_back(enemy);
                this->is_under_attack=true;
                
                break;
            }
        }
    }
    
    return is_under_attack;
}

void King::get_attack
(
    Piece **board, 
    std::vector<int> &attacked_squares
)
    {
        int direction[8]={-8,8,-1,1,-9,-7,7,9};
        for(int i=0; i<8; i++)
        {
            int target= this->get_square() + direction[i];
            if(target>=0 && target<64 && abs(this->get_col()-target % 8)<=1)
            {
                attacked_squares.push_back(target);
            }
        }
    }

bool King::handle_king_move_check
(
    Piece **board,
    int to_square,
    std::vector<Piece*> pieces_attacking_king
)
{
    // 1. SALVATAGGIO STATO
    int from_square = this->get_square();
    Piece* captured_piece = board[to_square]; // Salva chi c'era lì (o nullptr)

    // 2. APPLICA LA MOSSA TEMPORANEA
    board[to_square] = this;
    board[from_square] = nullptr;
    this->set_square(to_square); // Aggiorna le coordinate interne del Re!

    // 3. RECUPERA NEMICI (Attenzione: se ho mangiato un nemico, lui non attacca più!)
    std::vector<Piece*> active_enemies;
    for(int i=0; i<64; i++) {
        if(board[i] != nullptr && board[i]->get_color() != this->get_color()) 
        {
            active_enemies.push_back(board[i]);
        }
    }

    // 4. VERIFICA SICUREZZA
    // Qui chiamo la nuova is_attack che usa get_attacks
    bool is_suicide = this->is_attack(board, active_enemies, pieces_attacking_king);

    // 5. RIPRISTINO TOTALE (Undo move)
    board[from_square] = this;
    board[to_square] = captured_piece; // Rimetto il pezzo mangiato (se c'era)
    this->set_square(from_square);     // Il Re torna a casa

    return is_suicide;
}