#ifndef PAWN_H
#define PAWN_H

#include "../Piece.h"

class Pawn: public Piece
{
private:
    bool is_pawn_enpassant = false;
public:
    Pawn(int pos, char character);
    
    bool get_is_pawn_enpassant() const override;
    void set_is_pawn_enpassant(bool enpassant) override;

    void update_legal_moves(std::shared_ptr<Handle_Fen_String> ptr_smart) override;
    void get_attack(Piece **board, std::vector<int> &attacked_squares) override;


    void handle_movement(Piece** ptr, std::vector<int>& legal_moves);
    void handle_offensive(Piece** ptr, std::vector<int>& legal_moves);
    void handle_en_passant(int square);
};


#endif //PAWN_H