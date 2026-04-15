#include "Create_Piece.h"

Create_Piece::Create_Piece()
{
   // wxLogMessage("Entro nel costruttore di Create_Piece");
}


Piece* Create_Piece::create_piece(char c, int square)
{
    //wxLogMessage("Entro in create_piece");
    switch (c)
    {
    //Caso Pedone:
    case 'p':
    case 'P':
        //wxLogMessage("ritorno del pedone");
        return new Pawn(square,c);
    
    //Caso Torre:
    case 'r':
    case 'R':
        //wxLogMessage("ritorno della torre");
        return new Rock(square,c);
    
    //Caso Alfiere:
    case 'b':
    case 'B':
        //wxLogMessage("ritorno dell'alfiere");
        return new Bishop(square,c);
    
    //Caso Re:
    case 'k':
        //wxLogMessage("ritorno del re nero");
        black_king=new King(square,c);
        return black_king;

    case 'K':
        //wxLogMessage("ritorno del re bianco");
        white_king= new King(square,c);
        return white_king;
    
    //Caso Cavallo:
    case 'n':
    case 'N':
        //wxLogMessage("ritorno del cavallo");
        return new Knight(square,c);

    //Caso Donna:
    case 'q':
    case 'Q':
        //wxLogMessage("ritorno della donna");
        return new Queen(square,c);
    
    default:
        //wxLogMessage("puntatore ritorna a nullptr");
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

Create_Piece::~Create_Piece()
{
    
}