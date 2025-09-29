#include "Create_Piece.h"

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
        black_king=new King(square,c);
        return black_king;

    case 'K':
        white_king= new King(square,c);
        return white_king;
    
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

King* Create_Piece::get_black_king()
{
    return black_king;
}

King* Create_Piece::get_white_king()
{
    return white_king;
}
