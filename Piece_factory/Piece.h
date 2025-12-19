#ifndef PIECE_H
#define PIECE_H

#include <cctype>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
#include <wx/wx.h>

class Handle_Fen_String;

    //IDENTIFICARE COLORE SQUADRA
    enum Color
    {
        WHITE=1,
        BLACK=2,
        ENDGAME=0
    };

    //IDENTIFICARE IL TIPO DI PEZZO
    enum Character
    {
        PAWN=0,
        BISHOP=1,
        KNIGHT=2,
        QUEEN=3,
        KING=4,
        ROCK=5
    };

    //IDENTIFICARE IL NUMERO DELLA COLONNA
    enum Colomn
    {
        A=0,
        B=1,
        C=2,
        D=3,
        E=4,
        F=5,
        G=6,
        H=7   
    };

class Piece
{
private:

    int row,coloum,square;
    char name_piece;
    bool is_moved;

    Color color;
    Character type_piece;

    std::vector<int> legal_moves;
    std::map<int,std::vector<int>> map_path;          
                                            
    //Funzionamento delle mosse:
    //+8 scendi alla cella inferiore
    //-8 sali alla cella superiore
    //+1 vo a destra
    //-1 vo a sinistra 

public:
    /*------COSTRUTTORE-------------*/
    Piece(int pos, char c);
    /*------FINE COSTRUTTORE--------*/

    /*-----------GETTER-------------*/
        //Ottieni il numero della riga:
        int get_row() const;

        std::string get_debug() const;

        //Ottieni il numero della colonna:
        int get_col() const;
        
        //Ottieni il numero della casella:
        int get_square() const;

        //Ottieni il char associato al pezzo:
        char get_name_piece() const;

        //Ottieni se si è mosso:
        bool get_ismoved() const;
        
        //Controlla se lo spostamento è legale:
        bool is_legal_move(int square) const;

        //Ottieni il tipo di squadra:
        Color get_color() const;
        
        //Ottieni le mosse legali:
        std::vector<int> get_legal_moves() const;
        
        //Ottieni il percorso della mappa gioco
        std::map<int,std::vector<int>> get_map_path() const;

        /*Inizio: controllo se sono pezzi specifici:*/
        bool is_pawn();
        bool is_rock();
        bool is_king();
        bool is_knight();
        bool is_bishop();
        /*Fine: controllo se sono pezzi specifici*/
    /*-----------FINE GETTER-------------*/

    /*-----------SETTER------------------*/

        void set_row(int new_row);
        void set_col(int new_col);
        void set_square(int new_square);

        void set_name_piece(char new_name);

        void set_ismoved(bool new_moved);

        void set_color(Color new_color);

        void set_legal_moves(std::vector<int> new_legal_moves);
        
    /*-----------FINE SETTER------------------*/

    /*-----------FUNZIONI-----------------*/

        /*Inizio: Gestione degli spostamenti:*/
        void diagonal_move
        (
            Piece** ptr, 
            std::vector<int> &legal_moves
        );
        
        void straight_move
        (
            Piece** ptr, 
            std::vector<int> &legal_moves
        );
        /*Fine: Gestione degli spostamenti:*/

        //Controlla il percorso del re
        std::vector<int> check_is_king
        (
            std::shared_ptr<Handle_Fen_String> ptr_smart, 
            Piece *King
        );
    
        /*Inizio: Gestione delle mosse legali che puoi fare*/
        void add_legal_move(int square);
        void remove_legal_move(int square);
        /*Fine: Gestione delle mosse legali che puoi fare*/

    /*-----------FINE FUNZIONI-----------------*/
    
    /*-----------FUNZIONI VIRTUALI----------*/    
        //Aggiornare le mosse legali per i pezzi specifici 
        virtual void update_legal_moves
        (
            std::shared_ptr<Handle_Fen_String> ptr_smart
        )=0;    
    /*-----------FINE FUNZIONI VIRTUALI----------*/

    virtual ~Piece()= default;
};



#endif //PIECE_H