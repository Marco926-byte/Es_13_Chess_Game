#ifndef HANDLE_FEN_STRING_H
#define HANDLE_FEN_STRING_H

#include <string>
#include <unordered_map>

#include "Piece_factory/Piece.h"

class Handle_Fen_String
{
private:
    std::string fen_string; 
    std::unordered_map<std::string, int> occurences_position;
    Piece *piece[64];   //Serve per controllare i pezzi
                        //tramite puntatore nella scacchiera
public:
    Handle_Fen_String();
    
    //Funzione che serve all'inizio a far posizionare i pezzi
    void set_board_fenstring(std::string fen_string);

    //Serve per generare la fen per descrivere la posizione dei pezzi
    std::string generate_fen_string();

    //Aggiungi la fen alla mappa
    void add_fen_to_map(std::string fen_string);
};



#endif //HANDLE_FEN_STRING_H