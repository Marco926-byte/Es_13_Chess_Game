#include "Handle_Mouse_Input.h"

Handle_Mouse_Input::Handle_Mouse_Input
(   
    Draw_board* ptr,
    std::shared_ptr<Handle_Fen_String> fen,
    Movement_Piece* move,
    Handle_Chessboard* chess
)
    :mouse_ptr(ptr),    
     fen_smart(fen),
     handle_movement(move),
     handle_chessboard(chess)    
    {    
        is_select_piece=false;
        select_piece=-1;
        handle_piece=nullptr;
    }

void Handle_Mouse_Input::onMouseLeftDown(wxMouseEvent& event)
{   
    wxPoint point=event.GetPosition();
    
    mouse_x=point.x;
    mouse_y=point.y;

    int square_size = mouse_ptr->get_square_size();    

    int clicked_row=mouse_y/square_size;
    int clicked_col=mouse_x/square_size;

    piece_ptr=fen_smart.get()->get_piece()[clicked_row*8+clicked_col];

    handle_select_square(clicked_row,clicked_col);
    
    mouse_ptr->Refresh();  
}

void Handle_Mouse_Input::onMouseLeftUp(wxMouseEvent& event)
{
    

}

void Handle_Mouse_Input::handle_select_square(int &clicked_row, int &clicked_col)
{
    if(select_piece==clicked_row*8+clicked_col && is_select_piece)
    {
        is_select_piece=false;
        select_piece=-1;
    }
    else if(piece_ptr!=nullptr)
    {
        is_select_piece=true;
        select_piece=clicked_row*8+clicked_col;
    }
    else
    {
        is_select_piece=false;
        select_piece=-1;
        
    }
    if(select_piece!=-1)
    {
        handle_piece=fen_smart.get()->get_piece()[select_piece];
    }
    else
    {
        handle_piece=nullptr;
    }
}

bool Handle_Mouse_Input::get_is_select_piece() const
{
    return is_select_piece;
}

void Handle_Mouse_Input::set_is_select_piece(bool s)
{
    is_select_piece=s;
}

int Handle_Mouse_Input::get_selected_piece() const
{
    return select_piece;
}

Piece* Handle_Mouse_Input::get_handle_piece() const
{
    return handle_piece;
}

Handle_Mouse_Input::~Handle_Mouse_Input()
{


}