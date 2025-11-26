#ifndef MOVEMENT_PIECE_H
#define MOVEMENT_PIECE_H


#include <iostream>
#include <wx/wx.h>
#include <memory>
#include "Piece_factory/Piece.h"

class Movement_Piece
{
private:
    int from_square, to_square;
    char character_piece_captured;

    //std::shared_ptr<Piece> piece_shared;
    std::shared_ptr<Piece> piece_captured;

public:
    Movement_Piece();


    void handle_move(int from, int to);
};


#endif //MOVEMENT_PIECE_H