#ifndef MOVEMENT_PIECE_H
#define MOVEMENT_PIECE_H

#include <iostream>
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

    std::stack<Move>stack;
    std::vector<int> attacked_square;

    Draw_board* draw=nullptr;
    std::shared_ptr<Handle_Fen_String> fen_shared;
    Handle_Chessboard* handle_chess=nullptr;
public:
    Movement_Piece
    (
        Draw_board* board,
        std::shared_ptr<Handle_Fen_String> fen,
        Handle_Chessboard* chess
    );

    void set_attack_vector(std::vector<int> v_attack);

    std::vector<int> get_attacked_square() const;

    bool handle_move(int from, int to);
    
    bool handle_capture_enpassant();
    bool handle_castling_dx();
    bool handle_castling_sx();

    void update_moves_all_piece();
    void update_move_in_check(Color team_turn,std::vector<int> v_attack);

    bool is_enpassant();
    bool is_castling_dx();
    bool is_castling_sx();
    bool is_promotion_pawn();

    int get_king_position();

    bool handle_promotion_pawn(char character_promotion);
    void print_all_move();
};

#endif //MOVEMENT_PIECE_H