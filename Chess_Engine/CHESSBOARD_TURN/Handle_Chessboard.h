#ifndef HANDLE_CHESSBOARD_H
#define HANDLE_CHESSBOARD_H

#include "../../Piece_factory/King/King.h"


class Draw_board;

class Handle_Chessboard
{
private:
    Color turn;      
public:
    //Costruttore
    Handle_Chessboard
    (
        
    );
    
    void change_turn();
    void set_turn(Color t);

    //----------GETTER----------------
    Color get_turn();
    //----------FINE GETTER----------------
};

#endif //HANDLE_CHESSBOARD_H