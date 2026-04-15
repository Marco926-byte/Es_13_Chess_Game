#ifndef CHECK_H
#define CHECK_H

#include "../../Piece_factory/Piece.h"

class Check
{
private:
    std::vector<int> v_check_attack;
public:
    Check();
    
    bool handle_check_on_king_straight(int position_king,Piece **board, Color current_player_color);
    bool handle_check_on_king_diagonal(int position_king,Piece **board, Color current_player_color);
    bool handle_check_on_king_knight(int position_king,Piece **board, Color current_player_color);

    std::vector<int> get_v_check_attack() const;
};

#endif //CHECK_H