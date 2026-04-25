#ifndef ES13_H
#define ES13_H

#include "wx/wx.h"
#include "start/MyProjectBase.h"
#include "Draw_board.h"
#include "Handle_Mouse_Input.h"
#include "Draw_Promotion_Dialog.h"

class Es13: public MyFrame1
{
private:
    Draw_board* board=nullptr;
    Draw_Promotion_Dialog* dialog=nullptr;

    void open_board(wxCommandEvent& event);
public:
    /*Costruttore del form:*/
    Es13(wxWindow* parent);   
    /*---------------------*/
    
    void open_promotion_dialog();
    
    ~Es13();
};

//wxDECLARE_APP(Es13);

#endif //ES13_H