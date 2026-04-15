#include "Handle_Mouse_Input.h"
#include "Es13.h"

Handle_Mouse_Input::Handle_Mouse_Input
(   
    Draw_board* ptr,
    std::shared_ptr<Handle_Fen_String> fen,
    Movement_Piece* move,
    Handle_Chessboard* chess,
    std::shared_ptr<Handle_Enpassant> enpassant,
    std::shared_ptr<Update_Moves> update_moves,
    std::shared_ptr<Castling> castling,
    std::shared_ptr<Find_King> find_king,
    std::shared_ptr<Check> check,
    std::shared_ptr<Handle_Pin> pin,
    std::shared_ptr<Promotion_Pawn> promotion_pawn
)
    :mouse_ptr(ptr),    
     fen_smart(fen),
     handle_movement(move),
     handle_chessboard(chess),
     enpassant_shared(enpassant),
     update_moves_shared(update_moves),
     castling_shared(castling),
     find_king_shared(find_king),
     check_shared(check),
     pin_shared(pin),
     promotion_pawn_shared(promotion_pawn)
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
    if
    (
        piece_ptr 
        &&
        piece_ptr->get_color()==handle_chessboard->get_turn() 
    )
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

        if(promotion_pawn_shared.get()->is_promotion_pawn())
        {   
            Draw_Promotion_Dialog promotion(nullptr);
            
            while (promotion.ShowModal() != wxID_OK)
            {
                //Finchè non sceglie il pezzo non andare avanti
            }
            
            char promotion_char = promotion.get_character_choice();

            promotion_pawn_shared.get()->handle_promotion_pawn(promotion_char);
        }
        
        handle_chessboard->change_turn();

        update_moves_shared.get()->update_moves_all_piece();
        
        Piece *king = find_king_shared.get()->find_king_current_turn
        (
            fen_smart.get()->get_piece(),
            handle_chessboard->get_turn()
        );
        int position_king = king->get_square();
        
        //Non funziona il non suicidio del re....
        if
        (
            check_shared.get()->handle_check_on_king_straight
            (
                position_king,
                fen_smart.get()->get_piece(),
                handle_chessboard->get_turn()
            )
        )
        {
            wxLogMessage(wxT("SCACCO!"));
            update_moves_shared.get()->update_move_in_check
            (
                handle_chessboard->get_turn(),
                check_shared.get()->get_v_check_attack()
            );
        }
        if
        (
            check_shared.get()->handle_check_on_king_diagonal
            (
                position_king,
                fen_smart.get()->get_piece(),
                handle_chessboard->get_turn()
            )
        )
        {
            wxLogMessage(wxT("SCACCO!"));
            update_moves_shared.get()->update_move_in_check
            (
                handle_chessboard->get_turn(),
                check_shared.get()->get_v_check_attack()
            );
        }
        if
        (
            check_shared.get()->handle_check_on_king_knight
            (
                position_king,
                fen_smart.get()->get_piece(),
                handle_chessboard->get_turn()
            )
        )
        {
            wxLogMessage(wxT("SCACCO!"));
            update_moves_shared.get()->update_move_in_check
            (
                handle_chessboard->get_turn(),
                check_shared.get()->get_v_check_attack()
            );
        }

        castling_shared.get()->handle_castling_dx();
        castling_shared.get()->handle_castling_sx();
        
        pin_shared.get()->handle_pin_on_king_straight
        (
            fen_smart.get()->get_piece(),
            handle_chessboard->get_turn()
        );
        pin_shared.get()->handle_pin_on_king_diagonal
        (
            fen_smart.get()->get_piece(),
            handle_chessboard->get_turn()
        );

        enpassant_shared.get()->handle_capture_enpassant();

        mouse_ptr->Refresh();

        reset_attributes();
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