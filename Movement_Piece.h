#ifndef MOVEMENT_PIECE_H
#define MOVEMENT_PIECE_H

#include <stack>
#include <iostream>
#include <algorithm>

#include "Movement_Handler.h"
#include "Handle_Chessboard.h"
#include "Create_Piece.h"
#include "Piece_factory/Pawn/Pawn.h"
#include "Piece_factory/King/King.h"

class Movement_Piece: public Movement_Handler
{
private:

    int count_draw;

    Piece *piece[64];
    
    std::stack<Movement_Handler> move_stack;
    std::vector<Piece*> pieces_attacking;
    
    Create_Piece* create;
    Handle_Chessboard* handle_chess;

public:
    Movement_Piece();

    //Gestione movimenti da casella a casella
    void handle_move(int from_square, int to_square);

    //Aggiungi la mossa alla lista di mosse fatte nella partita
    void add_move_to_stack(Movement_Handler move);

    //Ad ogni mossa le mosse legali dovranno essere aggiornate
    void update_move_pieces();

    //Imposta l'empassant square
    void set_enpassant_square();

    //Gestisci enpassant
    void handle_enpassant_capture();
    
    //Gestisci l'arrocco a destra
    void handle_castling_rights();
    
    //Gestisci l'arrocco per la torre
    void handle_castling_rook();

    //Gestisci lo scacco del re
    void handle_king_check();

    //Aggiorna le mosse possibili sotto scacco
    void update_moves_in_check();
    
};


#endif //MOVEMENT_PIECE_H