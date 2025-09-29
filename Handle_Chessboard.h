#ifndef HANDLE_CHESSBOARD_H
#define HANDLE_CHESSBOARD_H

#include <vector>

#include "Movement_Handler.h"

class Handle_Chessboard
{
private:
    Color turn;  
    Piece *board[64];
public:
    //Costruttore
    Handle_Chessboard();

    void change_turn();

    std::vector<Piece*> get_piece_turn();
    std::vector<Piece*> get_no_piece_turn();

    /*----------GETTER----------------*/
    Color get_turn();
    /*----------FINE GETTER----------------*/
    
};

#endif //HANDLE_CHESSBOARD_H