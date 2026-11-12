#ifndef ROCK_H
#define ROCK_H

#include "../Piece.h"

class Rock: public Piece
{
private:
    
public:
    /*-----------Costruttore-----------------*/
    Rock(int coordinate,char character);
    /*------------Fine Costruttore-----------*/

    /*----Funzioni virtuale----*/  
    bool get_is_pawn_enpassant() const override;
    void set_is_pawn_enpassant(bool enpassant) override;
    void update_legal_moves(std::shared_ptr<Handle_Fen_String> ptr_smart) override;
    void get_attack(Piece **board, std::vector<int> &attacked_squares) override;
    /*----Fine funzione virtuale----*/
    
};


#endif //ROCK_H