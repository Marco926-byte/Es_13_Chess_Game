#include "Rock.h"
#include "../../Chess_Engine/FEN/Handle_Fen_String.h"

/*----Costruttore------*/
Rock::Rock(int coordinate, char character)
    :Piece(coordinate,character)
{

}
/*----Fine Costruttore----*/

void Rock::update_legal_moves(std::shared_ptr<Handle_Fen_String> ptr_smart)
{
    //imposto il vettore delle mosse legali a 0
    std::vector<int> legal_moves={};
    
    const auto& board = ptr_smart.get()->get_piece();
    
    //Creo le mosse in avanti e le registro in legal moves  
    straight_move(board,legal_moves);
    
    //registro le nuove mosse legali nella variabile della classe base Piece
    set_legal_moves(legal_moves);
}

void Rock::get_attack(Piece **board, std::vector<int> &attacked_squares)
{
    int directions[] = {-8, 8, -1, 1}; // Su, Giù, Sx, Dx

    for(int dir : directions)
    {
        int current = this->get_square();
        
        while(true)
        {
             // Controllo bordi laterali per Sx e Dx
             if(dir == -1 && current % 8 == 0) 
                break; // Bordo sinistro
             if(dir == 1 && current % 8 == 7) 
                break;  // Bordo destro

             current += dir;

             if(current < 0 || current >= 64) 
                break; // Bordo su/giù

             // Aggiungo la casella
             attacked_squares.push_back(current);

             // Se incontro un pezzo (amico o nemico), mi fermo
             if(board[current] != nullptr) break;
        }
    }
}