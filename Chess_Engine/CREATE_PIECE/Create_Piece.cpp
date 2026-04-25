#include "Create_Piece.h"

Create_Piece::Create_Piece()
{
   
}


Piece* Create_Piece::create_piece(char c, int square)
{
    switch (c)
    {
    //Caso Pedone:
    case 'p':
    case 'P':
        return new Pawn(square,c);
    
    //Caso Torre:
    case 'r':
    case 'R':
        return new Rock(square,c);
    
    //Caso Alfiere:
    case 'b':
    case 'B':
        return new Bishop(square,c);
    
    //Caso Re:
    case 'k':
    case 'K': 
        return new King(square,c);
    
    //Caso Cavallo:
    case 'n':
    case 'N':
        return new Knight(square,c);

    //Caso Donna:
    case 'q':
    case 'Q':
        return new Queen(square,c);
    
    default:
        return nullptr; //Carattere sbagliato allora...
    }
}

Create_Piece::~Create_Piece()
{
    
}