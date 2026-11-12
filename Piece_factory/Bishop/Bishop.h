#ifndef BISHOP_H
#define BISHOP_H

#include "../Piece.h"

#include <vector>

class Bishop: public Piece
{
private:
    /* data */   
public:
    Bishop(int position, char character);
    
    bool get_is_pawn_enpassant() const override;
    void set_is_pawn_enpassant(bool enpassant) override;

    void update_legal_moves(std::shared_ptr<Handle_Fen_String> ptr_smart) override;
    void get_attack(Piece **board, std::vector<int> &attacked_squares) override;
};



#endif //BISHOP_H