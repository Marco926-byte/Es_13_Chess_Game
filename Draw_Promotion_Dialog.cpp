#include "Draw_Promotion_Dialog.h"

#include <iostream>
#include <wx/wx.h>

Draw_Promotion_Dialog::Draw_Promotion_Dialog(wxFrame* parent)
    :Promotion_dialog(parent,ID_PROMOTION_DIALOG,"PROMOZIONE DEL PEDONE",wxPoint(200,100))
    {
        Bind(wxEVT_BUTTON,&Draw_Promotion_Dialog::promotion_queen,this, ID_BTN_QUEEN);
        Bind(wxEVT_BUTTON,&Draw_Promotion_Dialog::promotion_bishop,this, ID_BTN_BISHOP);
        Bind(wxEVT_BUTTON,&Draw_Promotion_Dialog::promotion_knight,this, ID_BTN_KNIGHT);
        Bind(wxEVT_BUTTON,&Draw_Promotion_Dialog::promotion_rook,this, ID_BTN_ROOK);
    }

void Draw_Promotion_Dialog::promotion_queen(wxCommandEvent& event)
{
    character_choice = 'q';
    EndModal(wxID_OK);
}

void Draw_Promotion_Dialog::promotion_bishop(wxCommandEvent& event)
{
    character_choice = 'b';
    EndModal(wxID_OK);
}

void Draw_Promotion_Dialog::promotion_knight(wxCommandEvent& event)
{
    character_choice = 'k';
    EndModal(wxID_OK);
}

void Draw_Promotion_Dialog::promotion_rook(wxCommandEvent& event)
{
    character_choice = 'r';
    EndModal(wxID_OK);
}

char Draw_Promotion_Dialog::get_character_choice()
{
    return character_choice;
}