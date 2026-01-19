#ifndef HANDLE_CHESSBOARD_H
#define HANDLE_CHESSBOARD_H

#include <vector>
#include <memory>

#include "Piece_factory/King/King.h"
#include "Handle_Fen_String.h"

class Draw_board;

class Handle_Chessboard
{
private:
    Color turn;  
    
    std::shared_ptr<Handle_Fen_String> handler_fen;
    std::vector<int> v_check_attack;

    Draw_board* draw_class = nullptr;
public:
    //Costruttore
    Handle_Chessboard(Draw_board * board,std::shared_ptr<Handle_Fen_String>fen);
    
    void change_turn();
    void set_turn(Color t);

    std::vector<Piece*> get_piece_turn();
    std::vector<Piece*> get_no_piece_turn();

    Piece* find_king(Piece** board, Color color_to_find);

    bool handle_check_on_king_straight(Piece **board, Color current_player_color);
    bool handle_check_on_king_diagonal(Piece **board, Color current_player_color);
    bool handle_check_on_king_knight(Piece **board, Color current_player_color);
    //----------GETTER----------------
    Color get_turn();
    //----------FINE GETTER----------------
};

#endif //HANDLE_CHESSBOARD_H