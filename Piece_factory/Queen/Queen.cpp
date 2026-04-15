#include "Queen.h"
#include "../../Chess_Engine/FEN/Handle_Fen_String.h"

Queen::Queen(int position, char character)
    :Piece(position,character)
    {

    }

void Queen::update_legal_moves(std::shared_ptr<Handle_Fen_String> ptr_smart) 
{
    std::vector<int> legal_moves={};

    const auto& board= ptr_smart.get()->get_piece();

    straight_move(board,legal_moves);
    diagonal_move(board,legal_moves);
    
    set_legal_moves(legal_moves);
}

void Queen::get_attack(Piece **board, std::vector<int> &attacked_squares)
{
    int directions[] = {-8, 8, -1, 1}; // Su, Giù, Sx, Dx

    for(int dir : directions)
    {
        int current = this->get_square();
        
        while(true)
        {
             // Controllo bordi laterali per Sx e Dx
             if(dir == -1 && current % 8 == 0) break; // Bordo sinistro
             if(dir == 1 && current % 8 == 7) break;  // Bordo destro

             current += dir;

             if(current < 0 || current >= 64) break; // Bordo su/giù

             // Aggiungo la casella
             attacked_squares.push_back(current);

             // Se incontro un pezzo (amico o nemico), mi fermo
             if(board[current] != nullptr) break;
        }
    }
    // Direzioni: NO, NE, SO, SE
    int directions1[] = {-9, -7, 7, 9};
    
    // Limiti di distanza dal bordo per ogni direzione
    // (Usa la stessa logica dei tuoi array end_board_diagonal precedenti)
    // Ma per semplicità qui faccio il calcolo passo-passo
    
    for(int dir : directions1)
    {
        int current = this->get_square();
        
        while(true)
        {
            // Controllo "Bordo Colonna" prima di sommare
            // Se sto andando a destra (+1, -7, +9) e sono sulla colonna 7 -> STOP
            if((dir == -7 || dir == 9 || dir == 1) && (current % 8 == 7)) break;
            // Se sto andando a sinistra (-1, -9, +7) e sono sulla colonna 0 -> STOP
            if((dir == -9 || dir == 7 || dir == -1) && (current % 8 == 0)) break;

            current += dir;

            // Controllo Bordo Scacchiera
            if(current < 0 || current >= 64) break;

            // 1. Questa casella è sotto tiro. Aggiungila.
            attacked_squares.push_back(current);

            // 2. Se ho trovato un pezzo (qualsiasi), il raggio si ferma QUI.
            if(board[current] != nullptr) break;
        }
    }
}