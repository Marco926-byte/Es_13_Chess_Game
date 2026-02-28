#ifndef MOVE_H
#define MOVE_H

#include "Piece_factory/Piece.h"

#include <wx/wx.h>

class Move
{
private:
    int from_square, to_square;

    char character_captured;

    Piece* piece_status=nullptr;
    Piece* piece_captured=nullptr;
public:
    Move();

    int get_from_square() const;
    void set_from_square(int from);
    int get_to_square() const;
    void set_to_square(int to);
    
    char get_character_captured() const;
    void set_character_captured(char new_char);

    Piece* get_piece_status() const;
    Piece* get_piece_captured() const;

    void set_piece_status(Piece* p);
    void set_piece_captured(Piece *pc);
};


#endif //MOVE_H