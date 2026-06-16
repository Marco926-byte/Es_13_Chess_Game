#ifndef HANDLE_FEN_STRING_H
#define HANDLE_FEN_STRING_H

#include <string>
#include <unordered_map>
#include <wx/wx.h>

#include "../CREATE_PIECE/Create_Piece.h"
#include "../CHESSBOARD_TURN/Handle_Chessboard.h"
#include "../FIND_KING/Find_King.h"

class Castling;

class Piece;

class Handle_Fen_String
{
private:
    std::string fen_string; 

    std::unordered_map<std::string, int> occurences_position;

    Create_Piece* create_ptr=nullptr;
    Handle_Chessboard* chess_turn_ptr=nullptr;
    std::shared_ptr<Find_King> find_king_smart;

    Piece **piece;                      //Serve per controllare i pezzi
                                        //tramite puntatore nella scacchiera

    std::map<int,bool> map_is_moved;

    bool is_long_castling= false;
    bool is_short_castling=false;
    bool is_last_move_black = false;
    bool is_enpassant = false;

    int square_enpassant = 0;
    int count_move_black = 0;

public:
    Handle_Fen_String
    (
        Handle_Chessboard*chess_turn,
        std::shared_ptr<Find_King> find_king
    );
    
    //Serve per generare la fen per descrivere la posizione dei pezzi
    std::string generate_fen_string();
    
    void controll_piece(int i);

    //Aggiungi la fen alla mappa
    void add_fen_to_map(std::string fen_string);
    
    Create_Piece* get_create_ptr() const;  
    Piece **get_piece();
    std::map<int,bool> map_get_is_moved() const;
    std::string get_fen_string() const;

    void set_long_castling(bool long_castling);
    void set_short_castling(bool long_castling);
    void set_is_enpassant(bool enpassant);
    void set_is_last_move_black(bool is_black);
    
    void set_board_fenstring(std::string fen_string);
    void set_square_enpassant(int enpassant_square);
    void set_is_moved(bool is_moved, int position_square);

    ~Handle_Fen_String();
};



#endif //HANDLE_FEN_STRING_H