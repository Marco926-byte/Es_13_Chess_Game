#ifndef HANDLE_MOUSE_INPUT_H
#define HANDLE_MOUSE_INPUT_H

#include <memory>
#include <vector>
#include <wx/app.h>

#include "Piece_factory/Piece.h"

#include "Draw_board.h"
#include "Draw_Promotion_Dialog.h"

#include "Chess_Engine/CHESSBOARD_TURN/Handle_Chessboard.h"
#include "Chess_Engine/MOVEMENT_PIECE/Movement_Piece.h"
#include "Chess_Engine/FEN/Handle_Fen_String.h"
#include "Chess_Engine/ENPASSANT/Handle_Enpassant.h"
#include "Chess_Engine/UPDATE_MOVES/Update_Moves.h"
#include "Chess_Engine/CASTLING/Castling.h"
#include "Chess_Engine/FIND_KING/Find_King.h"
#include "Chess_Engine/CHECK/Check.h"
#include "Chess_Engine/PROMOTION_PAWN/Promotion_Pawn.h"
#include "Chess_Engine/PIN/Handle_Pin.h"

class Draw_board;   //class declaration perchè se faccio classico include mi entra nel
                    //famosissimo loop e scoppia tutto il programma
class Update_Moves;

class Handle_Mouse_Input
{
private:
    int mouse_x, mouse_y, select_piece, from_square, to_square;
    int position_board;

    bool is_select_piece, check_king;

    
    Piece* handle_piece=nullptr; 
    Piece* piece_ptr=nullptr;

    Draw_board* mouse_ptr=nullptr;
    
    std::shared_ptr<Handle_Fen_String> fen_smart;
    Movement_Piece* handle_movement=nullptr;
    Handle_Chessboard* handle_chessboard=nullptr;
    std::shared_ptr<Handle_Enpassant> enpassant_shared;
    std::shared_ptr<Update_Moves> update_moves_shared;
    std::shared_ptr<Castling> castling_shared;
    std::shared_ptr<Find_King> find_king_shared;
    std::shared_ptr<Check> check_shared;
    std::shared_ptr<Handle_Pin> pin_shared;
    std::shared_ptr<Promotion_Pawn> promotion_pawn_shared;
public:
    Handle_Mouse_Input
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
    void reset_attributes();
    
    ~Handle_Mouse_Input();
};


#endif //HANDLE_MOUSE_INPUT_H