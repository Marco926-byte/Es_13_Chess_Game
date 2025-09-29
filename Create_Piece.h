#ifndef CREATE_PIECE_H
#define CREATE_PIECE_H

#include "Piece_factory/Piece.h"
#include "Piece_factory/Pawn/Pawn.h"
#include "Piece_factory/Bishop/Bishop.h"
#include "Piece_factory/Queen/Queen.h"
#include "Piece_factory/King/King.h"
#include "Piece_factory/Knight/Knight.h"
#include "Piece_factory/Rock/Rock.h"

class Create_Piece
{
private:
    King *white_king;   
    King *black_king;   
public:

    //Crea il pezzo con la fen
    Piece* create_piece(char c, int square);

    //Getter
    King* get_white_king();
    King* get_black_king();
};


#endif //CREATE_PIECE_H