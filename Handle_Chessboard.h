#ifndef HANDLE_CHESSBOARD_H
#define HANDLE_CHESSBOARD_H

#include <vector>
#include <wx/wx.h>
#include <wx/log.h>
//#include "Movement_Handler.h"
#include "Movement_Piece.h"
#include "Piece_factory/King/King.h"

class Handle_Chessboard
{
private:
    Color turn;  
    //Piece *board[64];
public:
    //Costruttore
    Handle_Chessboard();
    
    //void change_turn();

    //std::vector<Piece*> get_piece_turn();
    //std::vector<Piece*> get_no_piece_turn();

    //----------GETTER----------------
    Color get_turn();
    //----------FINE GETTER----------------
    //~Handle_Chessboard();
};

#endif //HANDLE_CHESSBOARD_H