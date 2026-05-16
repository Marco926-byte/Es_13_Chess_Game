#include "Move.h"
Move::Move()
:   from_square(0),
    to_square(0)
{
       
}

int Move::get_from_square() const
{
    return from_square;
}

void Move::set_from_square(int from)
{
    from_square=from;
}

int Move::get_to_square() const
{
    return to_square;
}

void Move::set_to_square(int to)
{
    to_square=to;
}

Color Move::get_color_piece() const
{
    return color_piece;
}

void Move::set_color_piece(Color piece_color)
{
    color_piece=piece_color;
}

Character Move::get_type_piece() const
{
    return type_piece;
}

void Move::set_type_piece(Character type)
{
    type_piece=type;
}
