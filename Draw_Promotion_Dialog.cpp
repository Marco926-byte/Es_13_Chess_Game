#include "Draw_Promotion_Dialog.h"

Draw_Promotion_Dialog::Draw_Promotion_Dialog(wxFrame* parent)
:Promotion_dialog(parent,ID_PROMOTION_DIALOG,"PROMOZIONE DEL PEDONE",wxPoint(200,100))
{
    std::cout<<"Ciao da Draw_Promotion_Dialog!\n";
}