#include "Handle_Chessboard.h"

//Costruttore:
Handle_Chessboard::Handle_Chessboard()
{
    turn=WHITE;
}

Color Handle_Chessboard::get_turn()
{
    return turn;
}
