#ifndef HANDLE_ENPASSANT_H
#define HANDLE_ENPASSANT_H

#include <memory>

#include "../FEN/Handle_Fen_String.h"
#include "../MOVEMENT_PIECE/Movement_Piece.h"

class Handle_Enpassant
{
private:
    std::shared_ptr<Handle_Fen_String> fen_shared;
    Movement_Piece* game_movement =nullptr;

    bool is_enpassant_value = false;
    bool debug_is_enpassant = false;

    int debug_int = 0;
public:
    Handle_Enpassant
    (
        std::shared_ptr<Handle_Fen_String> fen, 
        Movement_Piece* movement
    );
    
    bool is_enpassant();

    void set_all_piece_team_is_not_enpassant(); 

    bool get_is_enpassant() const;
    int get_debug_int() const;

    void set_is_enpassant(bool new_is_enpassant);
    void set_debug_int(int debug);
    
    bool handle_capture_enpassant();

    ~Handle_Enpassant();
};



#endif //HANDLE_ENPASSANT_H