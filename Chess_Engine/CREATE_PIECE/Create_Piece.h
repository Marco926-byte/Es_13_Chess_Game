#ifndef CREATE_PIECE_H
#define CREATE_PIECE_H

#include <wx/wx.h>

#include "../../Piece_factory/Piece.h"
#include "../../Piece_factory/Pawn/Pawn.h"
#include "../../Piece_factory/Bishop/Bishop.h"
#include "../../Piece_factory/Queen/Queen.h"
#include "../../Piece_factory/King/King.h"
#include "../../Piece_factory/Knight/Knight.h"
#include "../../Piece_factory/Rock/Rock.h"

class Create_Piece
{
private:
      
public:
    Create_Piece();
    
    //Crea il pezzo con la fen
    Piece* create_piece(char c, int square);

    ~Create_Piece();
};


#endif //CREATE_PIECE_H