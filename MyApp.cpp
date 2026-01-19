#include "MyApp.h"

bool MyApp::OnInit()
{
    //wxInitAllImageHandlers();
    MyFrame1*frame=new Es13(nullptr);
    frame->Show();
    return true;
}