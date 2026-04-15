#ifndef HANDLE_ENPASSANT_H
#define HANDLE_ENPASSANT_H

#include <memory>

#include "../FEN/Handle_Fen_String.h"
#include "../MOVEMENT_PIECE/Movement_Piece.h"

class Handle_Enpassant
{
private:

    std::shared_ptr<Handle_Fen_String> fen_shared;
    
    Movement_Piece* game_movement;

public:
    Handle_Enpassant(std::shared_ptr<Handle_Fen_String> fen, Movement_Piece* movement);
    
    bool is_enpassant();
    bool handle_capture_enpassant();

    ~Handle_Enpassant();
};



#endif //HANDLE_ENPASSANT_H