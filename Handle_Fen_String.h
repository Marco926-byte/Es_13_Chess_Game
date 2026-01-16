#ifndef HANDLE_FEN_STRING_H
#define HANDLE_FEN_STRING_H

#include <string>
#include <unordered_map>
#include <wx/wx.h>

#include "Create_Piece.h"
class Piece;

class Handle_Fen_String
{
private:
    std::string fen_string; 

    std::unordered_map<std::string, int> occurences_position;

    Create_Piece* create_ptr=nullptr;
    Piece **piece;                   //Serve per controllare i pezzi
                                        //tramite puntatore nella scacchiera
public:
    Handle_Fen_String();
    
    //Funzione che serve all'inizio a far posizionare i pezzi
    void set_board_fenstring(std::string fen_string);

    //Serve per generare la fen per descrivere la posizione dei pezzi
    std::string generate_fen_string();

    //Aggiungi la fen alla mappa
    void add_fen_to_map(std::string fen_string);

    //getter fen_string:
    std::string get_fen_string();

    Piece **get_piece();
    
    ~Handle_Fen_String();
};



#endif //HANDLE_FEN_STRING_H