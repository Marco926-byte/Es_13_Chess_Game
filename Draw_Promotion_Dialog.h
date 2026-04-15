#ifndef DRAW_PROMOTION_DIALOG_H
#define DRAW_PROMOTION_DIALOG_H

#include "start/MyProjectBase.h"
#include "Chess_Engine/MOVEMENT_PIECE/Movement_Piece.h"

#include <memory>

class Draw_Promotion_Dialog: public Promotion_dialog
{
private:
    char character_choice;
public:
    //Costruttore
    Draw_Promotion_Dialog(wxFrame* parent);
    
    /*  EVENTI BOTTONI  */  
    void promotion_queen(wxCommandEvent& event);
    void promotion_bishop(wxCommandEvent& event);
    void promotion_rook(wxCommandEvent& event);
    void promotion_knight(wxCommandEvent& event);


    /*  GETTER  */
    char get_character_choice();

};


#endif //DRAW_PROMOTION_DIALOG_H