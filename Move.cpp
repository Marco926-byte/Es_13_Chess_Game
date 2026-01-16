#include "Move.h"
Move::Move()
:   from_square(0),
    to_square(0),
    character_captured(' '),
    piece_status(nullptr),
    piece_captured(nullptr)
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

char Move::get_character_captured() const
{
    return character_captured;
}

void Move::set_character_captured(char new_char)
{
    character_captured=new_char;
    
}

Piece* Move::get_piece_status() const
{
    return piece_status;
}

Piece* Move::get_piece_captured() const
{
    return piece_captured;
}

void Move::set_piece_status(Piece* p)
{
    piece_status=p;
}

void Move::set_piece_captured(Piece *pc)
{
    piece_captured=pc;
}