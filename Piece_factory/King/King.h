#ifndef KING_H
#define KING_H

#include "../Piece.h"
class King: public Piece
{
private:
    bool is_check, is_under_attack;

    std::vector<int> attacked_square_total;
public:
    //Costruttore
    King(int position, char character);
    
    //Getter
    bool get_is_check() const;
    
    //Funzione virtuale
    void update_legal_moves(std::shared_ptr<Handle_Fen_String> ptr_smart) override;

    //Funzioni del re
    void handle_movement(Piece**board, std::vector<int> &legal_moves);

    void handle_arrok(Piece**board, int rook_position, std::vector<Piece*>& piece_attacking);

    bool is_attack(Piece **board, std::vector<Piece *> &pieces, std::vector<Piece *> &pieces_attacking_king);
    void get_attack(Piece **board, std::vector<int> &attacked_squares) override;

    bool handle_king_move_check(Piece **board,int to_square,std::vector<Piece*> pieces_attacking_king);


};



#endif //KING_H