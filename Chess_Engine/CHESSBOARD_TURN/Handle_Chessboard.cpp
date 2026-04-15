#include "Handle_Chessboard.h"

//Costruttore:
Handle_Chessboard::Handle_Chessboard
(
    std::shared_ptr<Handle_Fen_String>fen
)
    :handler_fen(fen)
    {
        turn=WHITE;        
    }

Color Handle_Chessboard::get_turn()
{
    return turn;
}

void Handle_Chessboard::change_turn()
{
    if(turn==WHITE)
        set_turn(BLACK);
    else
        set_turn(WHITE);
}

void Handle_Chessboard::set_turn(Color t)
{
    turn=t;
}