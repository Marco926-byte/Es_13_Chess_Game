#ifndef MOVEMENT_PIECE_H
#define MOVEMENT_PIECE_H

#include <iostream>
#include <wx/wx.h>
#include <memory>
#include <stack>

#include "Piece_factory/Piece.h"
#include "Handle_Fen_String.h"
#include "Handle_Chessboard.h"
#include "Move.h"

class Draw_board;

class Movement_Piece
{
private:
    int draw_counter;

    std::stack<Move*>stack;
    std::vector<int> attacked_square;

    Draw_board* draw=nullptr;
    Handle_Chessboard* handle_chess=nullptr;

    std::shared_ptr<Handle_Fen_String> fen_shared;
public:
    Movement_Piece
    (
        Draw_board* board,
        std::shared_ptr<Handle_Fen_String> fen,
        Handle_Chessboard* chess
    );

    void set_attack_vector(std::vector<int> v_attack);

    bool handle_move(int from, int to);
    void update_moves_all_piece();
    void update_move_in_check(Color team_turn,std::vector<int> v_attack);
};

#endif //MOVEMENT_PIECE_H