#ifndef FIND_KING_H
#define FIND_KING_H

#include "../../Piece_factory/Piece.h"

class Find_King
{
private:
    
public:
    Find_King();
    
    Piece* find_king_current_turn(Piece** board, Color color_to_find);
};


#endif //FIND_KING_H