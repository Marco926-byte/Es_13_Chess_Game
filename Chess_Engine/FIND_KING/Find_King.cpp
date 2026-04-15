#include "Find_King.h"

Find_King::Find_King()
{
    
}

Piece* Find_King::find_king_current_turn
(
    Piece** board, 
    Color color_to_find
)
{
    for (int i = 0; i < 64; i++) 
    {
        if 
        (
            board[i] != nullptr && 
            board[i]->is_king() && 
            board[i]->get_color() == color_to_find
        ) 
        {
            return board[i];
        }
    }
    return nullptr;
}