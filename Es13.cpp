#include "Es13.h"

Es13::Es13(wxWindow* parent)
    :MyFrame1(parent,6000,wxT("BEST SCACCHI EVER"))
    {
        board= new Draw_board(this);
        board->Show(); 
    }


void Es13::open_promotion_dialog()
{
    dialog= new Draw_Promotion_Dialog(this);
    dialog->ShowModal();
}

Es13::~Es13()
{
   
}