#ifndef MOVEMENT_HANDLER_H
#define MOVEMENT_HANDLER_H

#include "Piece_factory/Piece.h"

class Movement_Handler
{
private:
    int from_square;
    int to_square;
    Piece *piece;
    Piece *captured_piece;
    char captured_piece_type;
public:
    
    Movement_Handler();

    /*----  GETTER   ---*/
    int get_from_square();
    int get_to_square();
    Piece* get_piece();
    Piece* get_captured_piece();
    char get_captured_piece_type();
    /*----  FINE GETTER   ---*/
    
    /*----  SETTER   ---*/
    void set_from_square(int new_from_square);
    void set_to_square(int new_to_square);
    void set_piece(Piece* new_piece);
    void set_captured_piece(Piece* new_captured_piece);
    void set_captured_piece_type(char new_captured_piece_type);
    /*----  FINE SETTER   ---*/
    
    ~Movement_Handler();
};


#endif //HANDLE_MOVEMENT_H