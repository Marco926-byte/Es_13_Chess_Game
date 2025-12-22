#ifndef HANDLE_MOUSE_INPUT_H
#define HANDLE_MOUSE_INPUT_H

#include <memory>
#include <vector>

#include "Piece_factory/Piece.h"
#include "Handle_Fen_String.h"
#include "Handle_Chessboard.h"
#include "Movement_Piece.h"
#include "Draw_board.h"

class Draw_board;   //class declaration perchè se faccio classico include mi entra nel
                    //famosissimo loop e scoppia tutto il programma

class Handle_Mouse_Input
{
private:
    int mouse_x, mouse_y, select_piece;
    
    bool is_select_piece;

    std::shared_ptr<Handle_Fen_String> fen_smart;
    
    Piece* handle_piece=nullptr; 
    Piece* piece_ptr=nullptr;

    Draw_board* mouse_ptr=nullptr; 
    Handle_Chessboard* handle_chessboard=nullptr;
    Movement_Piece* handle_movement=nullptr;
    
public:
    Handle_Mouse_Input
    (
        Draw_board* ptr,
        std::shared_ptr<Handle_Fen_String> fen,
        Movement_Piece* move,
        Handle_Chessboard* chess
    );

    /*----- EVENTI DEL MOUSE -------*/
    void onMouseLeftUp(wxMouseEvent& event);
    void onMouseLeftDown(wxMouseEvent& event);
    /*----- FINE EVENTI MOUSE ------*/

    /*----- INIZIO GETTER: ---------*/
    bool get_is_select_piece() const;
    void set_is_select_piece(bool select);
    int get_selected_piece() const;
    Piece* get_handle_piece() const;
    /*----- FINE GETTER:   ---------*/

    void handle_select_square(int &clicked_row, int &clicked_col);

    ~Handle_Mouse_Input();
};


#endif //HANDLE_MOUSE_INPUT_H