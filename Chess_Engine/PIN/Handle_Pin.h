#ifndef HANDLE_PIN_H
#define HANDLE_PIN_H

#include "../../Piece_factory/Piece.h"
#include "../FIND_KING/Find_King.h"
#include "../CHECK/Check.h"

#include <memory>

class Handle_Pin
{
private:
    std::shared_ptr<Find_King> find_king_shared;
    std::shared_ptr<Check> check_shared;
public:
    Handle_Pin
    (
        std::shared_ptr<Find_King> find_king,
        std::shared_ptr<Check> check
    );

    bool handle_pin_on_king_straight(Piece **board, Color current_player_color);
    bool handle_pin_on_king_diagonal(Piece **board, Color current_player_color);
};


#endif //HANDLE_PIN_H