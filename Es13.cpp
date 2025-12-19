#include "Es13.h"

Es13::Es13(wxWindow* parent)
    :MyFrame1(parent,6000,wxT("BEST SCACCHI EVER"))
    {
        /*Creo il frame principale*/
        
        Bind(wxEVT_BUTTON,&Es13::open_board,this, ID_BOARD);

    }

void Es13::open_board(wxCommandEvent& event)
{
    board= new Draw_board(this);
   
    board->Show();   

}

Es13::~Es13()
{
    delete board;
    board=nullptr;
}