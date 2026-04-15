#ifndef HANDLE_CHESSBOARD_H
#define HANDLE_CHESSBOARD_H

#include <vector>
#include <memory>

#include "../../Piece_factory/King/King.h"
#include "../FEN/Handle_Fen_String.h"

class Draw_board;

class Handle_Chessboard
{
private:
    Color turn;      

    std::shared_ptr<Handle_Fen_String> handler_fen;
public:
    //Costruttore
    Handle_Chessboard
    (
        std::shared_ptr<Handle_Fen_String>fen
    );
    
    void change_turn();
    void set_turn(Color t);

    //----------GETTER----------------
    Color get_turn();
    //----------FINE GETTER----------------
};

#endif //HANDLE_CHESSBOARD_H