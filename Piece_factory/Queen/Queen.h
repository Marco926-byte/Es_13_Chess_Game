#ifndef QUEEN_H
#define QUEEN_H

#include "../Piece.h"

class Queen: public Piece
{
private:
    /* data */
public:
    Queen(int position, char character);
    
    bool get_is_pawn_enpassant() const override;
    void set_is_pawn_enpassant(bool enpassant) override;
    void update_legal_moves(std::shared_ptr<Handle_Fen_String> ptr_smart) override;
    void get_attack(Piece **board, std::vector<int> &attacked_squares) override;
};



#endif //QUEEN_H