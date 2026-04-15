#ifndef MOVEMENT_PIECE_H
#define MOVEMENT_PIECE_H

#include <iostream>
#include <memory>
#include <stack>

#include "../../Piece_factory/Piece.h"
#include "../FEN/Handle_Fen_String.h"
#include "../CHESSBOARD_TURN/Handle_Chessboard.h"
#include "../MOVE/Move.h"

class Draw_board;

class Movement_Piece
{
private:
    int draw_counter;   //Todo:

    std::stack<Move>stack;

    std::shared_ptr<Handle_Fen_String> fen_shared;        
public:
    Movement_Piece
    (
        std::shared_ptr<Handle_Fen_String> fen
    );

    std::stack<Move> get_stack() const;

    bool handle_move(int from, int to);
    
    void print_all_move();

};

#endif //MOVEMENT_PIECE_H