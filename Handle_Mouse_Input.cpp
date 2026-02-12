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
        from_square=0;
        to_square=0;
    }

void Handle_Mouse_Input::onMouseLeftDown(wxMouseEvent& event)
{   
    wxPoint point=event.GetPosition();
    
    mouse_x=point.x;
    mouse_y=point.y;

    int square_size = mouse_ptr->get_square_size();    

    int clicked_row=mouse_y/square_size;
    int clicked_col=mouse_x/square_size;

    position_board=clicked_row*8+clicked_col;

    piece_ptr=fen_smart.get()->get_piece()[position_board];

    handle_select_square(clicked_row,clicked_col);
    
    mouse_ptr->Refresh();  
}

void Handle_Mouse_Input::onMouseLeftUp(wxMouseEvent& event)
{
    

}

void Handle_Mouse_Input::handle_select_square(int &clicked_row, int &clicked_col)
{
    if(!is_select_piece || handle_piece==nullptr)
    {
        //SONO NEL PRIMO CLICK:
        //Se clicco su una casella vuota all'inizio esci:
        if(piece_ptr==nullptr)
        {
            return;
        }
        //Controllo se il click è su un pezzo della mia squadra:
        if(piece_ptr->get_color()==handle_chessboard->get_turn())
        {
            from_square = piece_ptr->get_square();
            is_select_piece=true;
            select_piece=position_board;
            handle_piece=piece_ptr;
        }
        //Se clicco su un pezzo dell'avversario ovviamente devo uscire
        else
        {
            return;
        }
    }
    else
    {
    //SONO NEL SECONDO CLICK:
    //Se clicco sulla stessa casella allora deseleziona tutto 
    if(piece_ptr==handle_piece)
    {
        reset_attributes();
        return;
    }
    //Se clicco la 2° volta su una casella con personaggio diverso ma della stessa 
    //squadra: 
    if(piece_ptr 
        &&piece_ptr->get_color()==handle_chessboard->get_turn() )
    {
        select_piece=position_board;   
        handle_piece=piece_ptr;
        from_square=handle_piece->get_square();
        return;
    }
    //Se clicco la 2° volta su una casella vuota o nemico ma è una mossa legale per il 
    //pezzo di partenza:
    if(handle_piece->is_legal_move(position_board))
    {
        handle_movement->handle_move(from_square,position_board);
        handle_chessboard->change_turn();
        handle_movement->update_moves_all_piece();
        if(handle_chessboard->handle_check_on_king_straight(fen_smart.get()->get_piece(),handle_chessboard->get_turn()))
        {
            wxLogMessage(wxT("Handle_check_on_king_straight funziona!!!"));
            handle_chessboard->print_v_check_attack();
            handle_movement->update_move_in_check(handle_chessboard->get_turn(),handle_chessboard->get_v_check_attack());
        }
        if(handle_chessboard->handle_pin_on_king_straight(fen_smart.get()->get_piece(),handle_chessboard->get_turn()))
        {
            wxLogMessage(wxT("Handle_pin_on_king_straight funziona!!!"));
        }
        
        if(handle_chessboard->handle_pin_on_king_diagonal(fen_smart.get()->get_piece(),handle_chessboard->get_turn()))
        {
            wxLogMessage(wxT("Handle_pin_on_king_diagonal funziona!!!"));
        }
        if(handle_chessboard->handle_check_on_king_diagonal(fen_smart.get()->get_piece(),handle_chessboard->get_turn()))
        {
            wxLogMessage(wxT("Handle_check_on_king_diagonal funziona!!!"));
            handle_chessboard->print_v_check_attack();
            handle_movement->update_move_in_check(handle_chessboard->get_turn(),handle_chessboard->get_v_check_attack());
        }
        if(handle_chessboard->handle_check_on_king_knight(fen_smart.get()->get_piece(),handle_chessboard->get_turn()))
        {
            wxLogMessage(wxT("Handle_check_on_king_knight funziona!!!!"));
            handle_chessboard->print_v_check_attack();
            handle_movement->update_move_in_check(handle_chessboard->get_turn(),handle_chessboard->get_v_check_attack());
        }
        mouse_ptr->Refresh();
        reset_attributes();
        handle_chessboard->clear_v_check_attack();
    }
    else
        return;
    }  
}

void Handle_Mouse_Input::reset_attributes()
{
    is_select_piece=false;
    handle_piece=nullptr;
    select_piece=-1;
    from_square=-1;
    to_square=-1;
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