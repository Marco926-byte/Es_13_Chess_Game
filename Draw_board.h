#ifndef DRAW_BOARD_H
#define DRAW_BOARD_H

#include "start/MyProjectBase.h"

#include <memory>
#include <wx/wx.h>
#include <map>
#include <wx/bitmap.h>
#include <wx/image.h>

#include "Chess_Engine/MOVEMENT_PIECE/Movement_Piece.h"
#include "Chess_Engine/FEN/Handle_Fen_String.h"
#include "Chess_Engine/CHESSBOARD_TURN/Handle_Chessboard.h"
#include "Chess_Engine/ENPASSANT/Handle_Enpassant.h"
#include "Chess_Engine/UPDATE_MOVES/Update_Moves.h"
#include "Chess_Engine/CASTLING/Castling.h"
#include "Chess_Engine/FIND_KING/Find_King.h"
#include "Chess_Engine/CHECK/Check.h"
#include "Chess_Engine/PROMOTION_PAWN/Promotion_Pawn.h"
#include "Chess_Engine/PIN/Handle_Pin.h"

#include "Handle_Mouse_Input.h"
/*
    NOTE:
    Il mio programma crea le celle e inizia da 0,0.
    Quindi se provo a inserire un immagine a caso e la imposto in 0,0 mi da come
    posizione alto a sinistra quindi siccome il primo blocco del log ha coordinata 
    0,0 allora parto dall'alto e proseguo fino al basso.
    Le diagonali quindi a destra +1 a sinistra -1 in basso +8 e in alto -8, combinando
    e facendo le somme trovo anche le diagonali.
*/

class Handle_Mouse_Input;

class Update_Moves;

class Draw_board: public MyPanel1
{
private:
    wxBitmap bitmap;
    wxCoord square_size;

    //Mappa che serve a disegnare i pezzi
    std::map<char,wxBitmap> chess_piece_bitmaps;

    std::shared_ptr<Handle_Fen_String> fen_shared;
    
    Handle_Chessboard* chess_handler=nullptr;
    Movement_Piece* game_movement=nullptr;

    std::shared_ptr<Find_King> find_king_shared;
    std::shared_ptr<Check> check_shared;
    std::shared_ptr<Handle_Pin> pin_shared;
    std::shared_ptr<Handle_Enpassant> enpassant_shared;
    std::shared_ptr<Castling> castling_shared;
    std::shared_ptr<Update_Moves> update_moves_shared;
    std::shared_ptr<Promotion_Pawn> promotion_pawn_shared;
    
    Handle_Mouse_Input* mouse_handler=nullptr;

    //Gestione ridimensionamento finestra
    void OnSize(wxSizeEvent& event);
    
public:
    //Costruttore principale
    Draw_board(wxFrame* parent);

    //Disegno dei quadratini
    void draw_squares(wxDC& dc, int row, int col, wxCoord square_size); 
    
    //Disegno pezzi
    void draw_piece(wxDC& dc, int row, int col, wxCoord square_size);  
    
    //Rappresentazione dei pezzi
    void render_piece();
    
    //Disegno principale
    void on_paint(wxPaintEvent& evt);
    
    int get_square_size();
    
    ~Draw_board();
};

#endif //DRAW_BOARD_H